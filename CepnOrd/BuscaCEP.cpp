#include<stdio.h>
#include<string.h>

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

typedef struct _Endereco Endereco;

int main(int argc,char** argv){
  int line = 0, quantidade;
  Endereco ceptest;
  FILE *entrada;

  if(argc != 2){
    fprintf(stderr,"erro ao chamada do programa\n");
    fprintf(stderr,"forma correta : BuscaCEP [CEP]");
    return 1;
  }

  entrada = fopen("cep.dat","r");
  do{
    line++;
    quantidade = fread(&ceptest,sizeof(Endereco),1,entrada);

    if(strncmp(argv[1],ceptest.cep,8) == 0){
      printf("Rua : %.72s\nBairro : %.72s\nCidade : %.72s\nEstado : %.72s\nUF : %.2s\n",ceptest.logradouro,ceptest.bairro,ceptest.cidade,ceptest.uf,ceptest.sigla);
      fclose(entrada);
      break;
    }

  }while(quantidade>0);

  printf("numero de linhas pesquisadas :%d\n",line);

  return 0;
}
