//Marina Longo Dias - AED1 2020.2
//Lista 2, slide 28
//Faça um programa que armazene a informação de várias pessoas (nome[30], idade, altura).
//O programa só deve sair quando o usuário disser que não deseja mais entrar com os dados de outra pessoa.
//Antes de sair, o programa deve apresentar, de forma organizada, os dados de todas as pessoas.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char nome[30];
	int idade;
	int altura;
}Pessoa;

typedef struct{
	int cont;
	Pessoa *p;
}Agenda;

void Scanear(Agenda *agenda){
	
	printf("Digite seu nome: ");
	scanf ("%s", agenda->p[agenda->cont].nome);
	printf("\nDigite sua idade: ");
	scanf ("%d", &(agenda->p[agenda->cont].idade));
	printf("\nDigite sua altura (em cm): ");
	scanf("%d", &(agenda->p[agenda->cont].altura));
	(agenda->cont)++;
}

void Armazenar(Agenda *agenda){
	if (agenda->cont == 0){
		Scanear(agenda);
	}
	else {
		agenda->p = realloc(agenda->p, (agenda->cont + 1) * sizeof (Pessoa));
		Scanear(agenda);
	}

}

void Listar(Agenda *agenda){
	int i;
	for (i=0; i < agenda->cont; i++){
		printf("\n-----------------------------\n");
		printf("Pessoa %d\n", i);
		printf("Nome: %s\n", agenda->p[i].nome);
		printf("Idade: %d\n", agenda->p[i].idade);
		printf("Altura: %d cm\n", agenda->p[i].altura);
		printf("-----------------------------\n\n");
	}
}

void menu(Agenda *agenda){
	int opcao;
	while (1){
		printf("\n\n-----------------------------------------\n");
		printf("Armazenamento de dados\n");
		printf("Selecione a opção desejada:\n");
		printf("0. Listar os dados e sair do programa\n");
		printf("1. Armazenar dados\n");
		scanf ("%d", &opcao);

		switch (opcao){
			case 0:
				Listar(agenda);
				return;
				break;
			case 1:
				Armazenar(agenda);
				break;
			default:
				printf("Numero invalido");
				break;
		}
	}
}

int main(){

	Agenda *agenda;

	agenda = (Agenda *) malloc (sizeof(Agenda));
	agenda->p = (Pessoa *) malloc (sizeof(Pessoa));

	agenda->cont = 0;
	
	menu(agenda);

	free (agenda->p);
	free (agenda);

	return 0;
}
