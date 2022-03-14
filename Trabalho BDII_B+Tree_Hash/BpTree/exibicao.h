#ifndef EXIBICAO_H_INCLUDED
#define EXIBICAO_H_INCLUDED

#include <iostream>
using namespace std;

/* 
 * DECLARAÇÃO DE VARIÁVEIS. 
 */

typedef struct Registro{
	int valor;
}Registro;

typedef struct noh{
	noh** ponteiros;
	int* chave;
	struct noh* pai;
	bool e_folha;
	int numero_chaves;
	struct noh* proximo;
}noh;

int order=DEFAULT_ORDER;
noh* queue=NULL;
bool Saida_detalhada=false;

/*
 * ASSINATURAS. 
 */

void uso(void);
void Enfileirar(noh* novo_no);
noh* Desenfileirar(void);
int Caminho_para_Raiz(noh* raiz, noh * FILHO);
void Mostrar_Arvore(noh* raiz);
void Encontrar_e_Mostrar(noh* raiz, int Chave, bool Saida_detalhada);
void Encontrar_e_mostrar_alcance(noh* raiz, int DISTANCIA1, int DISTANCIA2, bool Saida_detalhada);
int Encontrar_Alcance(noh* raiz, int CHAVE_INICIAL, int CHAVE_FINAL, bool Saida_detalhada, int CHAVES_RETORNADAS[], void* PONTEIROS_RETORNADOS[]);
noh* Encontrar_Folha(noh* raiz, int Chave, bool Saida_detalhada);
Registro* Encontrar(noh* raiz, int Chave, bool Saida_detalhada);
int Cortar(int comprimento);

/* 
 * IMPLEMENTAÇÕES.
 */	

void uso(void){
	cout<<endl<<
	"  +---------------- B+TREE ----------------+"<<endl<<
	"  |                                        |"<<endl<<
	"  |  i k         INSERIR UMA CHAVE K.      |"<<endl<<
	"  |  d k         DELETAR UMA CHAVE K.      |"<<endl<<
	"  |  f k         PESQUISAR REGISTRO.       |"<<endl<<
	"  |  r k1 k2     PESQUISAR POR INTERVALO.  |"<<endl<<
	"  |  t           EXIBIR A B+TREE.          |"<<endl<<
	"  |  q           SAIR DO PROGRAMA.         |"<<endl<<
	"  |                                        |"<<endl<<
	"  +----------------------------------------+"<<endl<<endl<<
	" > ";
}

/*
 * FUNÇÕES PARA EXIBIR A B+TREE.
 */

void Enfileirar(noh* NOVO_NO){
	noh* c;
	if(queue==NULL){
		queue=NOVO_NO;
		queue->proximo=NULL;
	}
	else{
		c=queue;
		while(c->proximo!=NULL){
			c=c->proximo;
		}
		c->proximo=NOVO_NO;
		NOVO_NO->proximo=NULL;
	}
}

noh* Desenfileirar(void){
	noh* n=queue;
	queue=queue->proximo;
	n->proximo=NULL;
	return n;
}

int Caminho_para_Raiz(noh* RAIZ, noh* FILHO){
	int comprimento=0;
	noh* c=FILHO;
	while(c!=RAIZ){
		c=c->pai;
		comprimento++;
	}
	return comprimento;
}

void Mostrar_Arvore(noh* RAIZ){
	noh* n=NULL;
	int i=0;
	int rank=0;
	int new_rank=0;
	if (RAIZ==NULL){
		cout<<"B+TREE vazia."<<endl;
		return;
	}
	queue=NULL;
	Enfileirar(RAIZ);
	while(queue!=NULL){
		n=Desenfileirar();
		if(n->pai!=NULL&&n==n->pai->ponteiros[0]){
			new_rank=Caminho_para_Raiz(RAIZ, n);
			if(new_rank!=rank){
				rank=new_rank;
				cout<<endl;
			}
		}
		if(Saida_detalhada)
			cout<<(unsigned long)n;
		for(i=0; i<n->numero_chaves; i++) {
			if(Saida_detalhada)
				cout<<" "<<(unsigned long)n->ponteiros[i];
				cout<<" "<<n->chave[i];
		}
		if(!n->e_folha)
			for(i = 0; i <= n->numero_chaves; i++)
				Enfileirar(n->ponteiros[i]);
		if(Saida_detalhada) {
			if(n->e_folha)
				cout<<" "<<(unsigned long)n->ponteiros[order-1];
			else
				cout<<" "<<(unsigned long)n->ponteiros[n->numero_chaves];
		}
		cout<<" |";
	}
	cout<<endl;
}

void Encontrar_e_Mostrar(noh* RAIZ, int CHAVE, bool Saida_detalhada){
	Registro* r=Encontrar(RAIZ, CHAVE, Saida_detalhada);
	if (r==NULL)
		cout<<"REGISTRO NÃO ENCONTRADO SOB A CHAVE "<<CHAVE<<"."<<endl;
	else
		cout<<"REGISTRO EM "<<(unsigned long)r<<" -- CHAVE "<<CHAVE<<" VALOR "<< r->valor<<"."<<endl;
}

void Encontrar_e_mostrar_alcance(noh* RAIZ, int CHAVE_INICIAL, int CHAVE_FINAL, bool Saida_detalhada ){
	int i;
	int TAMANHO_VETOR=CHAVE_FINAL-CHAVE_INICIAL+1;
	int CHAVES_RETORNADAS[TAMANHO_VETOR];
	void* PONTEIROS_RETORNADOS[TAMANHO_VETOR];
	int NUMERO_ENCONTRADO=Encontrar_Alcance(RAIZ, CHAVE_INICIAL, CHAVE_FINAL, Saida_detalhada, CHAVES_RETORNADAS, PONTEIROS_RETORNADOS);
	if(!NUMERO_ENCONTRADO)
		cout<<"NENHUM ENCONTRADO."<<endl;
	else{
		for(i=0; i<NUMERO_ENCONTRADO; i++)
			cout<<"KEY: "<<CHAVES_RETORNADAS[i]<<"  LOCAL: "<<(unsigned long)PONTEIROS_RETORNADOS[i]<<"  VALOR: "<<((Registro *) PONTEIROS_RETORNADOS[i])->valor<<endl;
	}
}

int Encontrar_Alcance(noh* RAIZ, int CHAVE_INICIAL, int CHAVE_FINAL, bool Saida_detalhada, int CHAVES_RETORNADAS[], void* PONTEIROS_RETORNADOS[]){
	int i, NUMERO_ENCONTRADO;
	NUMERO_ENCONTRADO=0;
	noh* n=Encontrar_Folha(RAIZ, CHAVE_INICIAL, Saida_detalhada);
	if(n==NULL) return 0;
	for(i=0; i<n->numero_chaves&&n->chave[i]<CHAVE_INICIAL; i++);
	if (i==n->numero_chaves) return 0;
	while (n!=NULL) {
		for ( ; i<n->numero_chaves&&n->chave[i]<=CHAVE_FINAL; i++){
			CHAVES_RETORNADAS[NUMERO_ENCONTRADO]=n->chave[i];
			PONTEIROS_RETORNADOS[NUMERO_ENCONTRADO]=n->ponteiros[i];
			NUMERO_ENCONTRADO++;
		}
		n=n->ponteiros[order-1];
		i=0;
	}
	return NUMERO_ENCONTRADO;
}

/*
 * ESTA FUNÇÃO TRAÇA O CAMINHO DA RAÍZ ATÉ A FOLHA PROCURANDO PELA CHAVE.
 * RETORNA A FOLAH CONTENDO A CHAVE PESQUISADA. 
 */

noh* Encontrar_Folha(noh* raiz, int CHAVE, bool Saida_detalhada){
	int i = 0;
	noh* c=raiz;
	if(c==NULL){
		if(Saida_detalhada)
			cout<<"Arvore vazia."<<endl;
		return c;
	}
	while(!c->e_folha){
		if(Saida_detalhada){
			cout<<"[";
			for (i=0; i<c->numero_chaves-1; i++)
				cout<<c->chave[i]<<" ";
			cout<<c->chave[i]<<"] ";
		}
		i=0;
		while(i<c->numero_chaves){
			if(CHAVE>=c->chave[i]) i++;
			else break;
		}
		if (Saida_detalhada)
			cout<<i<<"->"<<endl;
		c = (noh *)c->ponteiros[i];
	}
	if(Saida_detalhada){
		cout<<"Folha [";
		for (i = 0; i < c->numero_chaves - 1; i++)
			cout<<c->chave[i]<<" ";
		cout<<c->chave[i]<<"] ->";
	}
	return c;
}

/*
 * ESTA FUNÇÃO ENCONTRA E RETORNA O REGISTRO DA CHAVE PESQUISADA.
 */

Registro* Encontrar(noh* raiz, int CHAVE, bool Saida_detalhada){
	int i=0;
	noh* c=Encontrar_Folha(raiz, CHAVE, Saida_detalhada);
	if(c==NULL) return NULL;
	for(i=0; i<c->numero_chaves; i++)
		if(c->chave[i]==CHAVE) break;
	if(i==c->numero_chaves)
		return NULL;
	else
		return (Registro*)c->ponteiros[i];
}

#endif
