#include <stdio.h>
#include <stdlib.h>


int F1 (unsigned int n){
	if(n==0){
		return n;
	}

	int i , j, k;

	for (i=j=1;i<n;i++,j++){
		for (k=0;k<n;k++,j++);
	}

	printf("%d", j);
	return j;
}


int main (){
	
	unsigned int n=10;

	F1(n);
	
	return 0;
}
