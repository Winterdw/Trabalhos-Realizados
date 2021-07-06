#include<stdio.h>
#include<stdlib.h>

// Compilação por linha de comando em GNU LINUX
// $ gcc ordenacao.c -o ordenacao

// Execução do programa em GNU LINUX
// $ ./ordenacao

/**
 * Algoritmo de ordenação por inserção
 * @param *v Ponteiro para o vetor a ser ordenado
 * @param n Tamanho do vetor de entrada
 **/
void insertionsort(int *v, int n) {
	int chave,j;
	
	for(int i=1; i<n; i++) {
		chave = v[i];
		j = i-1;
		
		while(j>0 && v[j] > chave) {
			v[j+1] = v[j];
			j = j-1;
		}
		v[j+1]=chave;
	}
}

int main() {
	int v1[5] = {1,5,3,4,2};
	int n = 5;
	
	insertionsort((int*)v1,n);
	
	// Imprime v1
	for(int i=0; i<n; i++) {
		printf("%d ",v1[i]);
	}
	printf("\n");
}
