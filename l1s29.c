//Marina Longo Dias - AED1 2020.2
//Lista 1, slide 29
//Faça um programa que armazena nomes.
//O programa deve armazenar todos os nomes na mesma string.
//O tamanho da string deve crescer e diminuir conforme nomes forem colocados ou removidos.
//O menu deve conter Adicionar, Remover, Listar e Sair.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *AdicionarNome(char *vetor){
	char NovoNome[15];
	int tamanhoNovoNome, tamanhoVetor;
	//Passo 1, receber nome e guardar informações
	printf("Digite o nome que quer armazenar: ");					
	scanf ("%s", NovoNome);
	strcat (NovoNome, ",");										
	tamanhoNovoNome = strlen(NovoNome) + 1;
	tamanhoVetor = strlen(vetor) + 1;
	//Passo 2, printar informações
	//printf ("Debug antes\n");
	//printf ("%s\n", NovoNome);
	//printf ("%d\n", tamanhoNovoNome);
	//printf ("%s\n", vetor);
	//printf ("%d\n", tamanhoVetor);
	//Passo 3, realocar vetor
	vetor = realloc(vetor, (tamanhoVetor + tamanhoNovoNome) * sizeof(char));
	if (vetor == NULL){																//Testa se a memória está cheia
		printf ("Memória insuficiente!\n");
		exit(1);
	}
	//Passo 4, copiar dados pro vetor original
	strcat (vetor, NovoNome);
	//printf ("Debug depois\n");
	//printf ("%s\n", vetor);
	//tamanhoVetor = strlen(vetor) + 1;
	//printf ("%d\n", tamanhoVetor);

	return vetor;	
}

char *DeletarNome(char *vetor){
	int i, cont = 1, indDel;
	char *final;
	int tamanhoVetor, tamanhoDeletado=0;
	tamanhoVetor = strlen(vetor) +1;
	if (vetor[0] == '\0'){
		printf ("Nao ha nomes adicionados");
		return vetor;
	}
	//Passo 1, ler índice
	printf ("\nDigite o indice do nome que deseja deletar: ");
	scanf ("%d", &indDel);
	//Passo 2, caminhar até índice no vetor
	//Passo 3, excluir nome nesse índice
	for (i=0; vetor[i]!='\0'; i++){	
		printf ("%c", vetor[i]);
		if (vetor[i] == '\0'){								
			printf ("Seu indice nao foi encontrado");						
		}
		if (vetor[i] == ','){
			if (cont == indDel){
				vetor[i] = '#';
				final = &(vetor[i+1]);
			}
			cont++;
		}
		else if (cont == indDel){
			vetor[i] = '#';
		}				
	}
	for (i=0; vetor[i]!='\0'; i++){
		if (vetor[i] == '#'){
			tamanhoDeletado++;
		}
	}

	printf ("\nprint vetor após delete\n");
	printf ("\n%s\n", vetor);
	//Passo 4, mover resto do vetor
	printf ("Final: %s", final);
	for (i=0; vetor[i]!='\0'; i++){
		if (vetor[i] == '#'){
			strcpy(&vetor[i], final);
		}
	}
	printf("\nVetor final: \n");
	printf("%s", vetor);
	//Passo 5, realocar memória
	vetor = realloc (vetor, (tamanhoVetor - tamanhoDeletado) * sizeof(char));
	return vetor;
}

void ListarNome(char *vetor){
	int i, indice=1;
	//Passo 1, testar se há nomes e adicionar o primeiro índice
	printf("Listando nomes: \n");
	if (vetor[0] == '\0'){
		printf ("Nao ha nomes adicionados");
	}
	else {
		printf ("%d. ", indice);
		indice++;
	}
	//Passo 2, listar e seguir adicionando índices														
	for (i=0; vetor[i]!='\0'; i++){							
		if (vetor[i] != ','){								
			printf ("%c", vetor[i]);						
		}
		else {
			printf ("\n");
			if (vetor[i+1] != '\0'){
				printf ("%d. ", indice);
				indice++;
			}
		}
	}												

}

char *Menu(char *vetor){
	int opcao;
	while (1){
		printf("\n");
		printf("-----------------------------\n");
		printf("Menu da lista de nomes!\n");
		printf("Selecione a opcao desejada:\n");
		printf("0. Sair\n");
		printf("1. Inserir nome\n");
		printf("2. Apagar nome\n");
		printf("3. Listar nomes\n");
		printf("-----------------------------\n");

		scanf("%d", &opcao);

		switch (opcao) {
			case 0:
				return vetor;
				break;
			case 1:
				vetor = AdicionarNome(vetor);
				break;
			case 2:
				vetor = DeletarNome(vetor);
				break;
			case 3:
				ListarNome(vetor);
				break;
			default:
				printf("Numero invalido\n");
				break;
		}
	}
}


int main(){

	char *vetor;

	vetor = (char *) malloc(sizeof(char));

	vetor[0] = '\0';											//Inicializa o vetor sem nada

	vetor = Menu(vetor);

	free(vetor);

	return 0;
}