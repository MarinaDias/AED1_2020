//Marina Longo Dias - AED1 2020.2
//Lista 1, slide 28
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct agenda{
	char nome[40];
	char telefone[13];
	int free;																		// 0 se ocupado, 1 se livre
} AGENDA;

typedef struct variaveis{
	int count, opcao, index, i, tamanho;											// tamanho = capacidade atual da agenda, count = slots utilizados
	char aux_nome[40];													
	AGENDA *contatos;
} VARIAVEIS;

void incluirContato(void *pbuffer){
	VARIAVEIS *controle;
	controle = pbuffer;

	if (controle->count >= controle->tamanho){
		
		printf ("Agenda cheia, realocando...\n");
		controle->tamanho = controle->tamanho * 2;
		controle->contatos = realloc(controle->contatos, sizeof(AGENDA) * controle->tamanho);
		if(controle->contatos==NULL){
			printf("Erro!");
			exit(1);
		}

		for(controle->i = controle->tamanho/2; controle->i < controle->tamanho; controle->i++) {
			controle->contatos[controle->i].free = 1;
		}
	}

	for(controle->i = 0; controle->i < controle->tamanho; controle->i++) {
		if(controle->contatos[controle->i].free == 1) {
			printf ("Inserir nome do contato: ");
			scanf ("%s", controle->contatos[controle->i].nome);						// já armazena um endereço por ser um ponteiro
			printf ("Inserir telefone do contato: ");
			scanf ("%s", controle->contatos[controle->i].telefone);
			controle->contatos[controle->i].free = 0;
			controle->count++;
			return;
		}
	}
	//printf ("%s", (controle->contatos[0].nome));
	//printf ("%s", (controle->contatos[0].telefone));

}

void apagarContato(void *pbuffer){
	VARIAVEIS *controle;
	controle = pbuffer;

	//controle->index;
	printf ("Inserir indice do contato a ser deletado: ");
	scanf ("%d", &(controle->index));

	for(controle->i = 0; controle->i < controle->tamanho; controle->i++) {
		if(controle->index == controle->i) {
			controle->contatos[controle->i].free = 1;
			strcpy(controle->contatos[controle->i].nome, "");
			strcpy(controle->contatos[controle->i].telefone, "");
			controle->count--;
			return;
		}
	}
	printf ("Contato não encontrado!\n");
}

void listarContato(void *pbuffer){
	VARIAVEIS *controle;
	controle = pbuffer;

	for(controle->i = 0; controle->i < controle->tamanho; controle->i++) {
		if(controle->contatos[controle->i].free == 0) {
			printf ("\nContato %d:\n", controle->i);
			printf ("Nome do contato: %s\n", (controle->contatos[controle->i].nome));
			printf ("Telefone do contato: %s\n\n", (controle->contatos[controle->i].telefone));
		}
	}

}

void buscarContato(void *pbuffer){
	VARIAVEIS *controle;
	controle = pbuffer;

	printf ("Inserir nome do contato a ser buscado: ");
	scanf ("%s", controle->aux_nome);

	for(controle->i = 0; controle->i < controle->tamanho; controle->i++) {
		if(strcmp(controle->aux_nome, controle->contatos[controle->i].nome) == 0) {
			printf ("\nContato %d:\n", controle->i);
			printf ("Nome do contato: %s\n", (controle->contatos[controle->i].nome));
			printf ("Telefone do contato: %s\n\n", (controle->contatos[controle->i].telefone));

			return;
		}
	}
	printf ("Contato não encontrado!");
}

void menu(void *pbuffer){
	VARIAVEIS *controle;
	controle = pbuffer;

	while(1){
		printf ("\nMenu da Agenda: \n");
		printf ("0. Sair da agenda. \n");
		printf ("1. Adicionar contato. \n");
		printf ("2. Excluir contato. \n");
		printf ("3. Listar contatos. \n");
		printf ("4. Buscar contato. \n");
		printf ("Selecione a opção desejada: ");
		scanf ("%d", &(controle->opcao));
		switch (controle->opcao){
			case 0:
				return;
				break;
			case 1:
				incluirContato(pbuffer);
				break;
			case 2:
				apagarContato(pbuffer);
				break;
			case 3:
				listarContato(pbuffer);
				break;
			case 4:
				buscarContato(pbuffer);
				break;
		}

	}
}
void inicializaAgenda(void *pbuffer) {
	VARIAVEIS *controle;
	controle = pbuffer;
	for(controle->i = 0; controle->i < controle->tamanho; controle->i++) {
		//strcpy(controle->contatos[i].nome, "");
		//strcpy(controle->contatos[i].telefone, "");
		controle->contatos[controle->i].free = 1;
	}
}

int main(){
	void *pbuffer;
	VARIAVEIS *controle;

	pbuffer = malloc (sizeof (VARIAVEIS));
	if(pbuffer==NULL){
		printf("Erro!");
		exit(1);
	}

	controle = pbuffer;
	controle->tamanho=4;
	controle->count=0;

	//AGENDA *contatos;
	controle->contatos = malloc (sizeof (AGENDA) * controle->tamanho);

	inicializaAgenda(pbuffer);

	menu(pbuffer);

	free(controle->contatos);
	free(pbuffer);

	return 0;
}