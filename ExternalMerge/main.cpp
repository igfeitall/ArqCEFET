#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exmerge.h"


int compara(const void *e1, const void *e2)
{
    return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main (){
	
    int estado;
    estado = merge("cep.dat",8,compara);

    if(estado == 0){
        printf("Ordenacao concluida\n");
    }else{
        fprintf(stderr,"Erro na Ordenacao");
    }

    return 0;
}