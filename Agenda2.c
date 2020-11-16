#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char nome[40];
	char telefone[13];
}dados;

typedef struct nodo{
	dados *info;
	struct nodo *proximo;
	struct nodo *anterior;
}nodo;

typedef struct{
	int nElementos;
	nodo *first;
	nodo *last;
}lista;

typedef struct{
	int opcao, i, j, k;
	lista *minhaLista;
	char auxNome[40];
}variaveis;


//-------------------------------------


void testeNulo(void *pbuffer){

	if(pbuffer==NULL){
		printf("Erro!");
		exit(1);
	}
}

nodo *criaElemento(void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;

	nodo *meuNodo;											//"instanciando" um nodo
	meuNodo = malloc (sizeof(nodo));
	testeNulo(meuNodo);
	meuNodo->info = (dados*) malloc (sizeof (dados));
	testeNulo(meuNodo->info);

	meuNodo->proximo = NULL;
	meuNodo->anterior = NULL;

	printf("\nInsira o nome do contato: ");
	scanf ("%s", meuNodo->info->nome);
	printf("\nInsira o telefone do contato: ");
	scanf ("%s", meuNodo->info->telefone);

	printf ("\nNodo criado!\n");

	return meuNodo;
}

void destroiNodo(nodo *meuNodo){
	free(meuNodo->info);
	free(meuNodo);
}

nodo *duplica(nodo *origem){
	nodo *copia;
	copia = malloc (sizeof(nodo));
	testeNulo(copia);
	copia->info = malloc (sizeof(dados));
	testeNulo(copia->info);

	copia->proximo = NULL;
	copia->anterior = NULL;

	strcpy(copia->info->nome, origem->info->nome);
	strcpy(copia->info->telefone, origem->info->telefone);

	return copia;
}

lista *inicializaLista(){
	lista *minhaLista;
	minhaLista = malloc (sizeof(lista));
	testeNulo(minhaLista);

	minhaLista->first = NULL;
	minhaLista->last = NULL;
	minhaLista->nElementos = 0;

	return minhaLista;
}

void destroiLista(lista *minhaLista, void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;

	nodo *executado;
	nodo *atual = minhaLista->first;
	printf ("\nDestruindo a lista...\n");
	for(controle->i = 0; atual != NULL; (controle->i)++){
		executado = atual;
		atual = atual->proximo;
		destroiNodo(executado);
	}

	free(minhaLista);
}

//------------------------------------------------------

int insereElemento(nodo *pNodo, lista *minhaLista, int *posicao, void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;

	//if (minhaLista->first == NULL && *posicao !=0){					//Erro, não há elementos.
	//	return 0;
	//}
	if (minhaLista->first == NULL){									//Inserindo no primeiro elemento.
		minhaLista->first = pNodo;
		minhaLista->last = pNodo;
		minhaLista->first->proximo = NULL;							//Já estão settados no criaElemento.
		minhaLista->first->anterior = NULL;
		(minhaLista->nElementos)++;
		return 1;
	}
	else if (*posicao == 0){										//Inserir na primeira posição. Necessariamente não sendo o primeiro elemento.
		//first->[0]
		//[0]->[1]->[5]
		//[3]->[0]
		//first->[3]
		minhaLista->first->anterior = pNodo;
		pNodo->proximo = minhaLista->first;
		minhaLista->first = pNodo;
		(minhaLista->nElementos)++;
		return 1;
	}
	nodo *atual = minhaLista->first;
	nodo *pAnterior;
	for(controle->i = 0; controle->i <= *posicao && atual != NULL; (controle->i)++){
		pAnterior = atual;
		atual = atual->proximo;
	}
	if (atual == NULL){									//Chega no final da lista. Se o índice for maior que a quantidade de elementos, insere no final da lista.
		minhaLista->last = pNodo;
		pAnterior->proximo = pNodo;
		pNodo->anterior = pAnterior;
		(minhaLista->nElementos)++;
		return 1;
	}

	pNodo->anterior = pAnterior;
	pNodo->proximo = atual;
	atual->anterior = pNodo;
	pAnterior->proximo = pNodo;
	(minhaLista->nElementos)++;

	return 1;
}

void insereFilaOrdenada(nodo *pNodo, lista *filaOrdenada, void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;

	printf("\nInserindo na fila ordenada...\n");

	nodo *atual = filaOrdenada->first;
	for(controle->k = 0; atual != NULL; (controle->k)++){
		//if posicao certa
		if (strcmp(pNodo->info->nome, atual->info->nome) < 0){
			//insereElemento();
			if(controle->k == 0) {
				controle->j = 0;
			}
			else {
				controle->j = (controle->k) - 1;
			}
			//printf("Inserindo elemento na posicao correta...\n");
			insereElemento(pNodo, filaOrdenada, &(controle->j), pbuffer);
			return;
		}

		atual = atual->proximo;
	}
	//printf("Inserindo elemento no final...\n");
	insereElemento(pNodo, filaOrdenada, &(filaOrdenada->nElementos), pbuffer);
}

void insereFilaOrdenadaInv(nodo *pNodo, lista *filaOrdenada, void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;

	printf("\nInserindo na fila ordenada...\n");

	nodo *atual = filaOrdenada->first;
	for(controle->k = 0; atual != NULL; (controle->k)++){
		//if posicao certa
		if (strcmp(pNodo->info->nome, atual->info->nome) > 0){
			//insereElemento();
			if(controle->k == 0) {
				controle->j = 0;
			}
			else {
				controle->j = (controle->k) - 1;
			}
			//printf("Inserindo elemento na posicao correta...\n");
			insereElemento(pNodo, filaOrdenada, &(controle->j), pbuffer);
			return;
		}

		atual = atual->proximo;
	}
	//printf("Inserindo elemento no final...\n");
	insereElemento(pNodo, filaOrdenada, &(filaOrdenada->nElementos), pbuffer);
}

nodo *apagarElemento(lista *minhaLista, int *posicao, void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;
	nodo *pNodo;

	if (minhaLista->first == NULL){										//Erro, lista vazia.
		return NULL;
	}
	if (*posicao == 0){
		pNodo = minhaLista->first;
		minhaLista->first = minhaLista->first->proximo;
		minhaLista->first->anterior = NULL;
		(minhaLista->nElementos)--;
		if (pNodo->proximo = NULL){
			minhaLista->last = NULL;
		}
		return pNodo;
	}
	nodo *atual = minhaLista->first;
	nodo *pAnterior;
	for (controle->i = 0; controle->i < *posicao && atual != NULL; (controle->i)++){
		pAnterior = atual;
		atual = atual->proximo;
	}
	if (atual == NULL){							//Removendo elemento do fim. Chegou em um índice que não existe.
		minhaLista->last = pAnterior->anterior;
		pNodo = pAnterior;
		pAnterior->anterior->proximo = NULL;
		(minhaLista->nElementos)--;
		return pNodo;
	}

	//Removendo elementos do meio
	pNodo = atual;
	pAnterior->proximo = atual->proximo;
	if (atual->proximo != NULL) {
		atual->proximo->anterior = pAnterior;
	}
	(minhaLista->nElementos)--;
	return pNodo;
}

void listarElementos(lista *minhaLista, void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;

	nodo *atual = minhaLista->first;
	printf ("\nListando contatos:\n");
	for(controle->i = 0; atual != NULL; (controle->i)++){
		printf ("----------------------\n");
		printf ("Indice: %d\n", controle->i);
		printf ("Nome: %s\n", atual->info->nome);
		printf ("Telefone: %s\n", atual->info->telefone);
		atual = atual->proximo;
	}
	printf ("----------------------\n");
}

void listarElementosInvertido(lista *minhaLista, void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;

	nodo *atual = minhaLista->last;
	printf ("\nListando contatos (invertido): \n");
	for(controle->i = (minhaLista->nElementos)-1; atual != NULL; (controle->i)--){
		printf ("----------------------\n");
		printf ("Indice: %d\n", controle->i);
		printf ("Nome: %s\n", atual->info->nome);
		printf ("Telefone: %s\n", atual->info->telefone);
		atual = atual->anterior;
	}
	printf ("----------------------\n");
}

void listarElementosFilaOrdenada(lista *minhaLista, void *pbuffer, int *escolha){
	variaveis *controle;
	controle = (variaveis*) pbuffer;
	nodo *copia;
	lista *filaOrdenada;
	filaOrdenada = inicializaLista();

	nodo *atual = minhaLista->first;
	for(controle->i = 0; atual != NULL; (controle->i)++){
		copia = duplica(atual);
		if (*escolha == 1){
			insereFilaOrdenada(copia, filaOrdenada, pbuffer);
		}
		else {
			insereFilaOrdenadaInv(copia, filaOrdenada, pbuffer);
		}
		atual = atual->proximo;
	}

	atual = filaOrdenada->first;
	printf ("\nListando contatos em ordem especificada:\n");
	for(controle->i = 0; atual != NULL; (controle->i)++){
		printf ("----------------------\n");
		printf ("Nome: %s\n", atual->info->nome);
		printf ("Telefone: %s\n", atual->info->telefone);
		atual = atual->proximo;
	}
	printf ("----------------------\n");

	destroiLista(filaOrdenada, pbuffer);
}

int buscarContatoInd(lista *minhaLista, void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;

	nodo *atual = minhaLista->first;
	printf ("Digite o indice do contato desejado: ");
	scanf ("%d", &controle->opcao);
	for(controle->i = 0; atual != NULL; (controle->i)++){
		if (controle->opcao == controle->i){
			printf ("\n----------------------\n");
			printf ("Indice: %d\n", controle->i);
			printf ("Nome: %s\n", atual->info->nome);
			printf ("Telefone: %s\n", atual->info->telefone);
			printf ("----------------------\n");
			return 1;
		}
		atual = atual->proximo;
	}
	return 0;
}

int buscarContatoNome(lista *minhaLista, void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;

	nodo *atual = minhaLista->first;
	printf ("Digite o nome do contato desejado: ");
	scanf ("%s", controle->auxNome);
	for(controle->i = 0; atual != NULL; (controle->i)++){
		if (strcmp(controle->auxNome, atual->info->nome) == 0){
			printf ("\n----------------------\n");
			printf ("Indice: %d\n", controle->i);
			printf ("Nome: %s\n", atual->info->nome);
			printf ("Telefone: %s\n", atual->info->telefone);
			printf ("----------------------\n");
			return 1;
		}
		atual = atual->proximo;
	}
	return 0;
}


void menu(void *pbuffer){
	variaveis *controle;
	controle = (variaveis*) pbuffer;
	controle->minhaLista = inicializaLista();
	nodo *pNodo;

	while(1){
		printf ("\nMenu da Agenda: \n");
		printf ("0. Sair da agenda. \n");
		printf ("1. Adicionar contato. \n");
		printf ("2. Excluir contato. \n");
		printf ("3. Listar contatos. \n");
		printf ("4. Buscar contato. \n");
		printf ("Selecione a opcao desejada: ");
		scanf ("%d", &(controle->opcao));
		switch (controle->opcao){
			case 0:
				destroiLista(controle->minhaLista, pbuffer);
				return;
				break;
			case 1:
				pNodo = criaElemento(pbuffer);
				insereElemento(pNodo, controle->minhaLista, &(controle->minhaLista->nElementos), pbuffer);
				break;
			case 2:
				printf("\nDigite o indice do contato que deseja excluir: ");
				scanf("%d", &controle->opcao);
				pNodo = apagarElemento(controle->minhaLista, &(controle->opcao), pbuffer);
				destroiNodo(pNodo);
				break;
			case 3:
				printf("\nListar em:\n");
				printf("1. Ordem normal.\n");
				printf("2. Ordem invertida.\n");
				printf("3. Usando fila ordenada.\n");
				scanf("%d", &controle->opcao);
				if (controle->opcao == 1){
					listarElementos(controle->minhaLista, pbuffer);
				}
				else if (controle->opcao == 2){
					listarElementosInvertido(controle->minhaLista, pbuffer);
				}
				else if (controle->opcao == 3){
					printf("\nCriterio de ordem:\n");
					printf("1. Ordem alfabetica.\n");
					printf("2. Ordem alfabetica invertida.\n");
					scanf("%d", &controle->opcao);
					listarElementosFilaOrdenada(controle->minhaLista, pbuffer, &(controle->opcao));
				}
				break;
			case 4:
				printf("\nBuscar por:\n");
				printf("1. Por indice\n");
				printf("2. Por nome\n");
				scanf("%d", &controle->opcao);
				if (controle->opcao == 1){
					buscarContatoInd(controle->minhaLista, pbuffer);
				}
				if (controle->opcao == 2){
					buscarContatoNome(controle->minhaLista, pbuffer);
				}
				break;
		}
	}
}



int main (){
//meu pbuffer é void, não posso usar um ponteiro void para acessar as coisas. Preciso fazer ele interpretar com tipo variaveis.
	void *pbuffer;

	pbuffer = (void *) malloc (sizeof(variaveis));
	//checagem de memória sempre que houver malloc/realloc
	testeNulo(pbuffer);

	menu(pbuffer);

	free(pbuffer);

	return 0;
}
