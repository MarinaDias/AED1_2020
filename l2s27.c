#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


void *ExerRealloc(void *pont, size_t newSize){

	void *destination;
	destination = malloc(newSize);

	if (pont==NULL){
		return destination;
	}

	else {
		destination = memcpy(destination, pont, _msize (pont));
	}

	free (pont);
	return destination;
}


int main(){

	int *pont;

	pont = (int *) malloc(sizeof(int));

	printf("Tamanho: %u\n", _msize(pont));

	pont = ExerRealloc(pont, 10);

	printf("Tamanho: %u\n", _msize(pont));



	free (pont);

	return 0;
}