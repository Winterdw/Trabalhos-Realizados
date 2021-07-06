#include<stdio.h>
#include<stdlib.h>

// Compilação por linha de comando em GNU LINUX
// $ gcc mergesort.c -o mergesort

// Execução do programa em GNU LINUX
// $ ./mergesort


/**
 * Faz a intercalação entre os vetores v[p..q-1] e v[q..r-1] de forma crescente
 * @param v vetor V
 * @param p posição inicial do vetor v1
 * @param q posição final do vetor v1 e inicial de v2
 * @param r posição final do vetor v2
 **/
void domerge(int *v, int p, int q, int r) {
	int i, j, k, *w; 
	w = calloc(r-p,sizeof(int));
	i=p;
	j=q;
	k=0;
	
	while(i<q && j<r) {
		if(v[i] <= v[j]) w[k++] = v[i++];
		else w[k++] = v[j++];
	}
	
	while(i<q) 
		w[k++] = v[i++];
	
	while(j<r)
		w[k++] = v[j++];
	
	for(i=p;i<r;i++)
		v[i] = w[i-p];
		
	free(w);
}

/**
 * Execução do algoritmo merge sort
 * @param v vetor V
 * @param p Limite inferior do vetor
 * @param q Limite superior do vetor
 **/
void merge(int *v,int p, int q) {
	if(p < q) {
		int k = (p+q)/2;
		merge(v,p,k);
		merge(v,k+1,q);
		domerge(v,p,k+1,q);
	}
}

int main() {
	int v1[5] = {1,5,3,4,2};
	int n = 5;
	
	merge((int*)v1,0,5);
	
	// Imprime v1
	for(int i=0; i<n; i++) {
		printf("%d ",v1[i]);
	}
	printf("\n");
}
