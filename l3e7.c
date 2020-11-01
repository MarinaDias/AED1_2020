#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Faça um programa que lê n números decimais (n fornecido pelo usuário),
//armazenando-os em um vetor.
//Logo após, uma função deve retirar os números duplicados que eventualmente possam existir neste vetor,
//deixando apenas uma ocorrência de cada número.
//Ao final, o vetor resultante deve ser impresso na tela.

float *duplicados(float *vetorPrincipal, int tamOriginal){

	int indice, j, k;

	for (indice=0; indice<tamOriginal; indice++){
		for (j=0; j<tamOriginal; j++){
			if (indice != j){
				if (vetorPrincipal[indice] == vetorPrincipal[j]){
					for (k=j; k<tamOriginal; k++){
						vetorPrincipal[k] = vetorPrincipal[k+1];
					}
					tamOriginal--;
				}
			}
			
		}
	}

	vetorPrincipal = realloc(vetorPrincipal, (tamOriginal) * sizeof(float));
	if (vetorPrincipal == NULL){
		printf("erro");
		exit(1);
	}

	printf ("\nNumeros sem existirem duplicados: ");
	for (indice=0; indice<tamOriginal; indice++){
		printf("%.1f ", vetorPrincipal[indice]);
	}
	printf ("\n");
	return vetorPrincipal;
}


float *leitura(float *vetorPrincipal){
	int tamOriginal = 0, indice = 1;
	printf ("Quantos numeros voce ira digitar? ");
	scanf ("%d", &tamOriginal);
	//printf("DEBUG %d\n", tamOriginal);

	vetorPrincipal = realloc(vetorPrincipal, (tamOriginal) * sizeof(float));

	if (vetorPrincipal == NULL){
		printf("erro");
		exit(1);
	}

	//printf ("DEBUG %f\n", vetorPrincipal);
	
	for (indice=0; indice<tamOriginal; indice++){
		printf ("Digite um numero para a posicao %d: ", indice);
		scanf ("%f", &vetorPrincipal[indice]);
	//	printf("DEBUG %f\n", vetorPrincipal[indice]);
	}
	//DEBUG
	//for (indice=0; indice<tamOriginal; indice++){
	//	printf("%f ", vetorPrincipal[indice]);
	//}

	//printf("\nDEBUG %.1f ", vetorPrincipal);
	vetorPrincipal = duplicados (vetorPrincipal, tamOriginal);

	return vetorPrincipal;
}




int main(){

	float *vetorPrincipal;
	vetorPrincipal = (float *) malloc(sizeof(float));

	if (vetorPrincipal == NULL){
		printf("erro");
		exit(1);
	}
	vetorPrincipal = leitura(vetorPrincipal);

	free (vetorPrincipal);

	return 0;
}