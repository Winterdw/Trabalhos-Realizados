#include<stdio.h>
#include<stdlib.h>

// Compilação por linha de comando em GNU LINUX
// $ gcc max.c -o max

// Execução do programa em GNU LINUX
// $ ./max

/**
 * Algoritmo para retornar o índice do maior elemento de um vetor
 * @param *v Ponteiro para o vetor
 * @param n Tamanho do vetor
 * @return O índice do vetor com o maior elemento
 **/
int max(int *v, int n) {
	int indice = 0;
	
	for(int i=1; i<n;i++) {
		if(v[i] > v[indice]) {
			indice = i;
		}
	}
	
	return indice;
}

int main() {
	int v1[5] = {1,5,3,4,2};
	int n = 5;
	int p = 0;
	
	p = max((int*)v1,n);
	
	printf("O maior elemento de v1 é %d\n",v1[p]);
}
