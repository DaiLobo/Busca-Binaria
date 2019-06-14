#include <stdio.h>
#include <string.h>
#include <locale.h>

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

int main(){

	FILE *f;
	Endereco e;
	int qt;
	long posicao, primeiro, ultimo, meio;

		f = fopen("cep_ordenado.dat","r");

		char buscar_cep[8];
		printf("Digite seu CEP: ");
		scanf("%s", &buscar_cep);

		int cont = 0;
		fseek(f,0,SEEK_END);
		posicao = ftell(f);
		rewind(f);
		primeiro = 0;
		ultimo = (posicao/sizeof(Endereco))-1;

	while(primeiro <= ultimo){

		meio = (primeiro + ultimo) / 2;
		fseek(f, meio * sizeof(Endereco), SEEK_SET);
		cont++;
		fread(&e,sizeof(Endereco),1,f);

		if(strncmp(buscar_cep, e.cep,8) == 0){
			printf("Achei! \n\n", setlocale(LC_ALL, ""));


			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			break;
		}
		else
			if(strncmp(buscar_cep, e.cep,8) < 0){
				ultimo = meio - 1;
			}
			else{
				primeiro = meio + 1;
			}
	}
	printf("\n Numero de enderecos lidos: %d\n", cont);

	fclose(f);
	return 0;

}
