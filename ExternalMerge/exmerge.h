#ifndef __EXMERGE_H__
#define __EXMERGE_H__

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

int Merge (String in,int (*compara)(const void*,const void*));

#endif 