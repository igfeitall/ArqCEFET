#include<stdio.h>
#include<string.h>
#include "exmerge.h"

#define N 8

typedef struct _Endereco Endereco;
 
struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int Merge (String in,int (*compara)(const void*,const void*)){

    FILE * inicio, fim;
    long div= N,totalbyte,totalreg,tamreg = sizeof(Endereco),divreg;

    inicio = fopen(in,"r");

    fseek(inicio,0,SEEK_END);
    totalbyte = ftell(inicio);      //calcula o tamanho em bytes do arquivo
    totalreg = totalbyte/tamreg;    //calcula a quantidade de registros
    divreg = totalreg/div;          //calcula a quantidade de registros por parte
    rewind(inicio);
    
    Endereco *e = new Endereco[divreg];

    for(i=0;i<N-1;i++){

        fread(e,tamreg,divreg,inicio);
        qsort(e,divreg,tamreg,compara);
        fim = fopen("teste" + i +".dat","w");
        fwrite(e,tamreg,divreg,fim);
        fclose(fim);

    }   

    delete[e];

    long sobra = totalreg - (divreg*N-1)
    Endereco *e = new Endereco[sobra];
    
    fread(e,tamreg,sobra,inicio);
    qsort(e,sobra,tamreg,compara);
    fim = fopen("teste" + N-1 +".dat","w");
    fwrite(e,tamreg,sobra,fim);
    fclose(fim);


    fclose(inicio);
    return 0;
} 