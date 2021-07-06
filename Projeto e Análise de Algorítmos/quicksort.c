#include<stdio.h>
#include<stdlib.h>

// Compilação por linha de comando em GNU LINUX
// $ gcc quicksort.c -o quicksort

// Execução do programa em GNU LINUX
// $ ./quicksort

int partition(int *v,int p,int q) {
	int k = v[p];
	int i = p+1;
	int j = q;
	
	for(;;) {
		while(v[i] < k && i < q) {
			i++;
		}
		
		while(v[j] > k) {
			j--;
		}
		
		if(i<j) {
			int tmp = v[i];
			v[i] = v[j];
			v[j] = tmp;
			++i;
			--j;
		}else{
			v[p] = v[j];
			v[j] = k; 
			return j;
		}
	}
}

void quicksort(int *v,int p,int q) {
	if(p < q) {
		int k = partition(v,p,q);
		quicksort(v,p,k);
		quicksort(v,k+1,q);
	}
}

int main() {
	int v1[] = {1,5,3,4,2};
	int n = 5;
	
	quicksort((int*)v1,0,n);
	
	// Imprime v1
	for(int i=0; i<n; i++) {
		printf("%d ",v1[i]);
	}
	printf("\n");
}
