#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exmerge.h"

void intercala(const char* nomefinal,int N,int (*compara)(const void*,const void*)){

    FILE *a,*b,*saida;
    Endereco ea, eb;
    int inicio = 1,fim = 9,tamreg = sizeof(Endereco);
    char nomea[20],nomeb[20],nomefim[20];
    

    while(!(inicio + 1 == fim)){

        //mudando o nome das partes a serem lidas
        sprintf(nomea,"teste%d.dat",inicio);
        sprintf(nomeb,"teste%d.dat",inicio+1);
        sprintf(nomefim,"teste%d.dat",fim);

        //se for a ultima interação usa o nome do arquivo final do paramentro
        if(inicio + 2 == fim){
            sprintf(nomefim,"%s",nomefinal);
        }

        //abrindo as partes a serem lidas nesse loop
        a = fopen(nomea,"r");
        b = fopen(nomeb,"r");
        saida = fopen(nomefim,"w");

        //lendo os o primeiro registro
        fread(&ea,tamreg,1,a);
        fread(&eb,tamreg,1,b);

        //intercalando ate algum dos arquivos terminar
        while(!feof(a) && !feof(b)){
            
            //se o primeiro elemento for menor escreve
            if(compara(&ea,&eb) < 0){
                fwrite(&ea,tamreg,1,saida);
                fread(&ea,tamreg,1,a);
            }else{
                fwrite(&eb,tamreg,1,saida);
                fread(&ea,tamreg,1,b);
            }   
        }

        //escreve o que sobrou de a
        while(!feof(a)){
            fwrite(&ea,tamreg,1,saida);
            fread(&ea,tamreg,1,a);
        }

        //escreve o que sobrou de b
        while(!feof(b)){
            fwrite(&eb,tamreg,1,saida);
            fread(&eb,tamreg,1,b);
        }

        //fecha o que foi lido nessa interação
        fclose(a);
        fclose(b);
        fclose(saida);

        remove(nomea);
        remove(nomeb);

        inicio += 2;
        fim++;
    }
}

int merge (const char* in,int N,int (*compara)(const void*,const void*)){

    FILE * inicio, *fim;
    long totalbyte ,totalreg ,tamreg = sizeof(Endereco) ,divreg;
    char nomecod[20];

    inicio = fopen(in,"r");

    fseek(inicio,0,SEEK_END);
    totalbyte = ftell(inicio);      //calcula o tamanho em bytes do arquivo
    totalreg = totalbyte/tamreg;    //calcula a quantidade de registros
    divreg = totalreg/N;          //calcula a quantidade de registros por parte
    rewind(inicio);
    
    Endereco *e = new Endereco[divreg];

    //ordena os primeiros N-1 grupos de registros

    for(int i=0;i<N-1;i++){

        fread(e,tamreg,divreg,inicio);
        qsort(e,divreg,tamreg,compara);
        sprintf(nomecod,"teste%d.dat",i+1);
        fim = fopen(nomecod,"w");
        fwrite(e,tamreg,divreg,fim);
        fclose(fim);

    }   

    delete[] e;

    //ordena o ultimo registro
    long sobra = divreg + totalreg%N;
    e = new Endereco[sobra];
    
    fread(e,tamreg,sobra,inicio);
    qsort(e,sobra,tamreg,compara);
    sprintf(nomecod,"teste%d.dat",N);
    fim = fopen(nomecod,"w");
    fwrite(e,tamreg,sobra,fim);
    fclose(fim);
    delete[] e;
    
    //fim da divisão das N partes

    //intercalando as N partes
    intercala("cep_ordenado.dat",N,compara);
    
    fclose(inicio);
    return 0; 
} 