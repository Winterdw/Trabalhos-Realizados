#include<stdio.h>
#include<stdlib.h>

// Compilação por linha de comando em GNU LINUX
// $ gcc minmax.c -o minmax

// Execução do programa em GNU LINUX
// $ ./minmax

int buscamax(int *v, int n) {
	int chave = v[0];
	
	for(int i=1; i<n;i++) {
		if(v[i] > chave) {
			chave = v[i];
		}
	}
	
	return chave;
}

int buscamin(int *v, int n) {
	int chave = v[0];
	
	for(int i=1; i<n;i++) {
		if(v[i] < chave) {
			chave = v[i];
		}
	}
	
	return chave;
}

/**
 * Algoritmo para identificar os índices do maior e menor elemento de um vetor
 * @param *v Ponteiro para o vetor
 * @param n Tamanho do vetor
 * @param *min Ponteiro para o inteiro que referencia ao menor elemento
 * @param *max Ponteiro para o inteiro que referencia ao maior elemento
 **/
void minmax(int *v, int n,int *min,int *max) {	
	*min = v[0];
	*max = v[0];
	
	for(int i=1; i<n; i++) {
		if(v[i] > *max) *max = v[i];
		if(v[i] < *min) *min = v[i];
	}
}

/**
 * Algoritmo para identificar os índices do maior e menor elemento de um vetor
 * @param *v Ponteiro para o vetor
 * @param n Tamanho do vetor
 * @param *min Ponteiro para o inteiro que referencia ao menor elemento
 * @param *max Ponteiro para o inteiro que referencia ao maior elemento
 **/
void minmax2(int *v, int n,int *min,int *max) {	
	*min = v[0];
	*max = v[0];
	
	for(int i=1; i<n; i++) {
		if(v[i] > *max) *max = v[i];
		else if(v[i] < *min) *min = v[i];
	}
}

/**
 * Algoritmo para identificar os índices do maior e menor elemento de um vetor
 * @param *v Ponteiro para o vetor
 * @param n Tamanho do vetor
 * @param *min Ponteiro para o inteiro que referencia ao menor elemento
 * @param *max Ponteiro para o inteiro que referencia ao maior elemento
 **/
void minmax3(int *v, int n,int *min,int *max) {	
	int *aux = 0;
	
	// Aloca um novo vetor, copia os elementos e replica o último
	if(n%2 != 0) {		
		aux = malloc((n+1)*sizeof(int));
		
		for(int i=0; i<n; i++) {
			aux[i] = v[i];
		}
		
		aux[n] = v[n-1];
		v = aux;
		n++;
	}
	
	// Cria os vetores de min e max
	int *vmin = malloc((n/2)*sizeof(int));
	int *vmax = malloc((n/2)*sizeof(int));
	
	// Verifica para qual vetor os elementos vão
	for(int i=0; i<n; i+=2) {
		if(v[i] > v[i+1]) {
			vmax[i/2] = v[i];
			vmin[i/2] = v[i+1];
		}else{
			vmin[i/2] = v[i];
			vmax[i/2] = v[i+1];
		}
	}
	
	*min = buscamin(vmin,n/2);
	*max = buscamax(vmax,n/2);
	free(vmax);
	free(vmin);
	free(aux);
}

int main() {
	int v1[5] = {1,5,3,4,2};
	int n = 5;
	int min,max;
	
	minmax((int*)v1,n,&min,&max);
	
	printf("O maior elemento de v1 é %d e o menor é %d\n",min,max);
	
	minmax2((int*)v1,n,&min,&max);
	
	printf("O maior elemento de v1 é %d e o menor é %d\n",min,max);
	
	minmax3((int*)v1,n,&min,&max);
	
	printf("O maior elemento de v1 é %d e o menor é %d\n",min,max);
}
