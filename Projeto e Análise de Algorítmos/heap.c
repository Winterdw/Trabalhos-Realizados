#include<stdio.h>
#include<stdlib.h>

// Compilação por linha de comando em GNU LINUX
// $ gcc heap.c -o heap

// Execução do programa em GNU LINUX
// $ ./heap

void heapify(int *v,int n,int i) {	
	int esq = i*2; // Índice à esquerda
	int dir = esq + 1; // Índice à direita
	int min = i; // Posição domenor elemento
	
	printf("%d %d\n",n,i);
	
	// Identifica o menor filho da árvore
	if(esq < n && v[esq] > v[i]) {
		min = esq;
	}
	
	if(dir < n && v[dir] > v[i]) {
		min = dir;
	}
	
	// Caso um filho seja menor que o atual, então faz a troca
	if(min != i) {
		int tmp = v[i];
		v[i] = v[min];
		v[min] = tmp;
		heapify(v,n,min);
	}
}

void heapsort(int *v,int n) {
	int swap;
	
	for(int i=n;n>=2;i--){
		swap = v[0];
		v[0] = v[i-1];
		v[i] = swap;
		heapify(v,i-1,i-1);	
	}	
}

/**
 * Constrói a estrutura Heap
 * @param *v Vetor que será reconstruído
 * @param n Tamanho do vetor
 **/
void heap(int *v,int n) {
	for(int i=n/2;i>=0;i--) {
		heapify(v,n,i);
	}
}

int main() {
	int v1[5] = {1,5,3,4,2};
	int n = 5;
	
	heap((int*)v1,n);
	
	// Imprime v1
	printf("Em Heap: ");
	for(int i=0; i<n; i++) {
		printf("%d ",v1[i]);
	}
	
	heapsort((int*)v1,n);
	
	printf("\nOrdenado: ");
	for(int i=0;i<n;i++) {
		printf("%d ",v1[i]);
	}
	
	printf("\n");
}
