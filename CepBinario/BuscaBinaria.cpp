#include <stdio.h>
#include <string.h>

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

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int busca = 0,registro = sizeof(Endereco);
	long aux, inicio = 0, fim, meio;

	if(argc != 2){
		fprintf(stderr,"forma correta : %s [CEP]",argv[0]);
		return 1;
	}

	f = fopen("cep_ordenado.dat","r");
	fseek(f,0,SEEK_END);
	aux = ftell(f);
	fim = (aux/registro) - 1;

	while(inicio <= fim){

		busca ++;
		meio = (inicio + fim)/2;
		fseek(f,meio*registro,SEEK_SET);
		fread(&e,registro,1,f);

		if(strncmp(e.cep,argv[1],8) == 0){
			printf("%.72s \n%.72s \n%.72s \n%.72s \n%.2s \n %8.s",e.logradouro, e.bairro, e.cidade, e.uf, e.sigla, e.cep);
			printf("numero de comparaçoes : %d",busca);
			return 0;
		}else if(strncmp(e.cep,argv[1],8) < 0){
			inicio = meio + 1;
		}else{
			fim = meio - 1;
		}
	}

	fprintf(stderr,"numero de comparacoes : %d",busca);
	fprintf(stderr,"\nCEP nao encontrado");

	fclose(f);
	return 0;
}

