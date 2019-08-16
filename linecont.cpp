#include<iostream>
#include<stdio.h>
using namespace std;

int main(int argc,char** argv){
	
	FILE *arquivo;
	char c;
	int linhas = 1,bytes = 0;
	
	if(argc != 2){
		cerr<<"uso errado do programa, usar no modo : \nlinecout [arquivo]\n";
		return 1;
	}
	
	arquivo = fopen(argv[1],"r");
	
	if(!arquivo){
		cerr<<"nao foi possivel ler o arquivo"<<argv[1]<<endl;
		fclose(arquivo);
		return 1;
	}
	
	c = fgetc(arquivo);
	while(c > 0){
		bytes++;
		if(c == '\n') linhas++;
		c=fgetc(arquivo);
	}
	
	cout<<"o numero de bytes do arquivo foi de : "<<bytes<<endl;
	cout<<" e o numero de linhas foi de : "<<linhas<<endl;
	
	fclose(arquivo);
	return 0;
}