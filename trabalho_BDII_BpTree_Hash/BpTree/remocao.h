#ifndef REMOCAO_H_INCLUDED
#define REMOCAO_H_INCLUDED

#include <iostream>
using namespace std;

int PEGA_INDICE_DO_VIZINHO(noh* n);
noh* Ajustar_Raiz(noh* RAIZ);
noh* Juntar_Nos(noh* RAIZ, noh* n, noh* VIZINHO, int INDICE_DO_VIZINHO, int PRIMEIRA_CHAVE);
noh* Redistribuir_Nos(noh* RAIZ, noh* n, noh* VIZINHO,int INDICE_DO_VIZINHO,int k_prime_index, int PRIMEIRA_CHAVE);
noh* Excluir_Entrada(noh* RAIZ, noh* n, int CHAVE, void* PONTEIRO);
noh* Deletar(noh* RAIZ, int CHAVE);

/* 
 * FUNÇÕES PARA DELETAR REGISTROS.
 */

/* 
 * RECUPERA O ÍNCIDE DE UM VIZINHO À ESQUERDA, CASO EXISTA.
 * SE NÃO EXISTIR RETORNA -1 PARA INDICAR O CASO ESPECIAL.
 */
int PEGA_INDICE_DO_VIZINHO(noh * n){
	int i;
	/* 
 	 * RETORNA O ÍNDICE DA CHAVE À ESQUERDA DO PONTEIRO NO PAI APONTANDO PARA N.
 	 * SE N É O FILHO MAIS A ESQUERDA, RETORNA -1.
 	 */
	for(i=0; i<=n->pai->numero_chaves; i++)
		if(n->pai->ponteiros[i] == n)
			return i-1;
	/*
	 * ERROR STATE.
	 */
	cout<<"Procura pelo ponteiro não-existente para o nó no pai."<<endl;
	printf("Node:  %#lx\n", (unsigned long)n);
	exit(EXIT_FAILURE);
}

noh * Excluir_Entrada_Do_No(noh * n, int CHAVE, noh * PONTEIRO){
	int i, NUMERO_DE_PONTEIROS;
	/* 
 	 * REMOVE A CHAVE E MUDA AS OUTRAS CHAVES ADEQUADAMENTE.
 	 * GARANTE QUE SE MANTENHA AS PROPRIEDADES DA B+TREE.
 	 */
	i = 0;
	while(n->chave[i] != CHAVE)
		i++;
	for(++i; i < n->numero_chaves; i++)
		n->chave[i - 1] = n->chave[i];
	/* 
 	 * REMOVE O PONTEIRO E MUDA AS DEMAIS CHAVES ADEQUADAMENTE. 
 	 * DETERMINA O VALOR NÚMERO DE PONTEIROS. 
 	 */
	NUMERO_DE_PONTEIROS = n->e_folha ? n->numero_chaves : n->numero_chaves+1;
	i = 0;
	while(n->ponteiros[i] != PONTEIRO)
		i++;
	for (++i; i<NUMERO_DE_PONTEIROS; i++)
		n->ponteiros[i-1] = n->ponteiros[i];
	/* 
 	 * DEFINE UMA CHAVE A MENOS. 
 	 */
	n->numero_chaves--;
	/* 
 	 * ESTABELECE OS DEMAIS PONTEIROS PARA NULL.
 	 * UMA FOLHA USA O ÚLTIMO PONTEIRO PARA APONTAR PARA A PRÓXIMA FOLHA. 
 	 */
	if(n->e_folha)
		for(i=n->numero_chaves; i<order-1; i++)
			n->ponteiros[i] = NULL;
	else
		for(i=n->numero_chaves+1; i<order; i++)
			n->ponteiros[i] = NULL;
	return n;
}

noh * Ajustar_Raiz(noh * RAIZ){
	noh * NOVA_RAIZ;
	/* 
 	 * CASO: UMA RAIZ NÃO VAZIA.
 	 * SOLUÇÃO: CHAVE E PONTEIRO JÁ FORAM DELETADOS, NADA A SER FEITO.
 	 */
	if(RAIZ->numero_chaves>0)
		return RAIZ;
	/* 
 	 * CASO: RAIZ VAZIA. 
 	 * SOLUÇÃO: SE POSSUI UM FILHO, PROMOVE O PRIMEIRO E ÚNICO FILHO COMO NOVA RAIZ. 
 	 */
	if(!RAIZ->e_folha){
		NOVA_RAIZ = RAIZ->ponteiros[0];
		NOVA_RAIZ->pai = NULL;
	}
	/* 
 	 * CASO: É UMA FOLHA E NÃO TEM FILHOS.
 	 * SOLUÇÃO: A B+TREE ESTÁ VAZIA. 
 	 */
	else
		NOVA_RAIZ = NULL;
	free(RAIZ->chave);
	free(RAIZ->ponteiros);
	free(RAIZ);
	return NOVA_RAIZ;
}

/*
 * JUNTA UM noh QUE SE TORNOU MUITO PEQUENO APÓS A DELEÇÃO A UM noh VIZINHO.
 * ESTE VIZINHO DEVE TER ESPAÇO SUFICIENTE PARA OS VALORES SEM EXCEDER O MÁXIMO PERMITIDO PELA B+TREE.
 */
noh * Juntar_Nos(noh * RAIZ, noh * n, noh * VIZINHO, int INDICE_DO_VIZINHO, int PRIMEIRA_CHAVE){
	int i, j, INDICE_DE_ISNERCAO_DO_VIZINHO, n_final;
	noh * tmp;
	/* 
 	 * TROCA O VIZINHO COM UM noh SE O noh ESTÁ NA EXTREMA ESQUERDA E O VIZINHO A DIREITA DO noh. 
 	 */
	if(INDICE_DO_VIZINHO==-1){
		tmp = n;
		n = VIZINHO;
		VIZINHO = tmp;
	}
	/* 
 	 * PONTEIRO DE START NO VIZINHO PARA CÓPIA DE CHAVES E PONTEIRO DE N.
 	 * RECHAMA O N E O VIZINHO PARA TROCAREM DE LUGAR NO CASO ESPECIAL DE N SER O FILHO MAIS A ESQUERDA. 
 	 */
	INDICE_DE_ISNERCAO_DO_VIZINHO = VIZINHO->numero_chaves;
	/*
 	 * CASO: SEM noh FOLHA.
 	 * SOLUÇÃO: ACRESCENTAR A PRIMEIRA_CHAVE E SEU PONTEIRO CORRESPONDENTE.
 	 * SOLUÇÃO: ACRESCENTAR TODOS OS PONTEIROS E CHAVES DO VIZINHO.
 	 */
	if(!n->e_folha){
		/* 
 	 	 * ACRESCENTA PRIMEIRA_CHAVE.
 	 	 */
		VIZINHO->chave[INDICE_DE_ISNERCAO_DO_VIZINHO] = PRIMEIRA_CHAVE;
		VIZINHO->numero_chaves++;
		n_final = n->numero_chaves;
		for(i=INDICE_DE_ISNERCAO_DO_VIZINHO+1, j=0; j<n_final; i++, j++){
			VIZINHO->chave[i] = n->chave[j];
			VIZINHO->ponteiros[i] = n->ponteiros[j];
			VIZINHO->numero_chaves++;
			n->numero_chaves--;
		}
		/* 
 	 	 * O NÚMERO DE PONTEIROS É SEMPRE UM A MAIS QUE O NÚMERO DE CHAVES. 
 	 	 */
		VIZINHO->ponteiros[i] = n->ponteiros[j];
		/* 
 	 	 * TODOS OS FILHOS PRECISAM AGORA APONTAR PARA O MESMO PAI. 
 	 	 */
		for(i=0; i<VIZINHO->numero_chaves+1; i++){
			tmp = (noh *)VIZINHO->ponteiros[i];
			tmp->pai = VIZINHO;
		}
	}
	/*
	 * EM UMA FOLHA, ACRESCENTAR AS CHAVES E PONTEIROS DE N PARA O VIZINHO.
	 * ESTABELECER O ÚLTIMO PONTEIRO DO VIZINHO PARA APONTAR PARA O QUE HAVIA SIDO O VIZINHO DA DIREITA DE N.
     */
	else{
		for(i=INDICE_DE_ISNERCAO_DO_VIZINHO, j=0; j<n->numero_chaves; i++, j++){
			VIZINHO->chave[i] = n->chave[j];
			VIZINHO->ponteiros[i] = n->ponteiros[j];
			VIZINHO->numero_chaves++;
		}
		VIZINHO->ponteiros[order-1] = n->ponteiros[order-1];
	}
	RAIZ = Excluir_Entrada(RAIZ, n->pai, PRIMEIRA_CHAVE, (void*)n);
	free(n->chave);
	free(n->ponteiros);
	free(n);
	return RAIZ;
}

/*
 * REDISTRIBUI ENTRADAS ENTRE DOIS NÓS QUADO UM SE TORNOU MUITO PEQUENO DEPOIS DA DELEÇÃO.
 * SEU VIZINHO É GRANDE PARA ACRESCENTAR AS ENTRADAS SEM EXCEDER O MÁXIMO.
 */
noh * Redistribuir_Nos(noh * RAIZ, noh * n, noh * VIZINHO, int INDICE_DO_VIZINHO, int INDICE_DA_PRIMEIRA_CHAVE, int PRIMEIRA_CHAVE){
	int i;
	noh * tmp;
	/*
	 * CASO: N TEM UM VIZINHO A ESQUERDA.
	 * SOLUÇÃO: PUXE O PAR MAIS À DIREITA DE CHAVE-PONTEIRO DO VIZINHO ESQUERDO DE N.
	 */
	if(INDICE_DO_VIZINHO!=-1){
		if(!n->e_folha)
			n->ponteiros[n->numero_chaves+1] = n->ponteiros[n->numero_chaves];
		for (i=n->numero_chaves; i>0; i--){
			n->chave[i] = n->chave[i-1];
			n->ponteiros[i] = n->ponteiros[i-1];
		}
		if(!n->e_folha){
			n->ponteiros[0] = VIZINHO->ponteiros[VIZINHO->numero_chaves];
			tmp = (noh *)n->ponteiros[0];
			tmp->pai = n;
			VIZINHO->ponteiros[VIZINHO->numero_chaves] = NULL;
			n->chave[0] = PRIMEIRA_CHAVE;
			n->pai->chave[INDICE_DA_PRIMEIRA_CHAVE] = VIZINHO->chave[VIZINHO->numero_chaves - 1];
		}else{
			n->ponteiros[0] = VIZINHO->ponteiros[VIZINHO->numero_chaves-1];
			VIZINHO->ponteiros[VIZINHO->numero_chaves-1] = NULL;
			n->chave[0] = VIZINHO->chave[VIZINHO->numero_chaves-1];
			n->pai->chave[INDICE_DA_PRIMEIRA_CHAVE] = n->chave[0];
		}
	}
	/*
     * CASO: N É O FILHO MAIS A ESQUERDA. 
     * SOLUÇÃO: USE UM PARTE DE CHAVE-PONTEIRO DO VIZINHO A DIREITA.
     * SOLUÇÃO: MOVA O PAR DE CHAVE-PONTEIRO DO VIZINHO A ESQUERDA PARA A POSIÇÃO MAIS A DIREITA DE N.
	 */
	else{
		if(n->e_folha){
			n->chave[n->numero_chaves] = VIZINHO->chave[0];
			n->ponteiros[n->numero_chaves] = VIZINHO->ponteiros[0];
			n->pai->chave[INDICE_DA_PRIMEIRA_CHAVE] = VIZINHO->chave[1];
		}
		else{
			n->chave[n->numero_chaves] = PRIMEIRA_CHAVE;
			n->ponteiros[n->numero_chaves+1] = VIZINHO->ponteiros[0];
			tmp = (noh *)n->ponteiros[n->numero_chaves+1];
			tmp->pai = n;
			n->pai->chave[INDICE_DA_PRIMEIRA_CHAVE] = VIZINHO->chave[0];
		}
		for(i=0; i < VIZINHO->numero_chaves-1; i++){
			VIZINHO->chave[i] = VIZINHO->chave[i+1];
			VIZINHO->ponteiros[i] = VIZINHO->ponteiros[i+1];
		}
		if(!n->e_folha)
			VIZINHO->ponteiros[i] = VIZINHO->ponteiros[i+1];
	}
	/*
	 * N AGORA TEM UM CHAVE E UM PONTEIRO A MAIS.  
	 * O VIZINHO TEM UMA CHAVE E UM PONTEIRO A MENOS. 
	 * OS VALORES DEVEM SER ATUALIZADOS.
	 */
	n->numero_chaves++;
	VIZINHO->numero_chaves--;
	return RAIZ;
}

/*
 * DELETA UMA ENTRADA DA B+TREE.
 * REMOVE O REGISTRO, SUAS CHAVES E PONTEIROS DA FOLHA.
 * FAZ TODAS AS MUDANÇAS APROPRIADAS PARA PRESERVAR AS PROPRIEDADES DA B+TREE.
 * IMPORTANTE: OS VALORES NÃO SERÃO EXCLUIDOS DOS noh INTERNOS, APENAS DAS FOLHAS. 
 */
noh * Excluir_Entrada(noh * RAIZ, noh * n, int CHAVE, void * PONTEIRO){
	int minimo_de_chaves;
	noh * VIZINHO;
	int INDICE_DO_VIZINHO;
	int INDICE_PRIMEIRA_CHAVE, PRIMEIRA_CHAVE;
	int CAPACIDADE;
	/*
	 * REMOVE A CHAVE E PONTEIRO DO noh.
	 */
	n = Excluir_Entrada_Do_No(n, CHAVE, (noh*)PONTEIRO);
	/*
	 * CASO: REMOÇÃO DA RAIZ.
	 */
	if (n == RAIZ)
		return Ajustar_Raiz(RAIZ);
	/*
	 * CASO: REMOÇÃO DE UM NÓ ABAIXO DA RAIZ. 
	 * SOLUÇÃO: DETERMINAR O MÍNIMO PERMITÍVEL DO TAMANHO DO NÓ PARA SER PRESERVADO APÓS A REMOÇÃO.
	 */
	minimo_de_chaves = n->e_folha ? Cortar(order-1) : Cortar(order)-1;
	/*
	 * CASO: O noh ESTÁ IGUAL UO ACIMA DO MÍNIMO.
	 * CASO MAIS SIMPLES. 
	 */
	if (n->numero_chaves >= minimo_de_chaves)
		return RAIZ;
	/*
	 * CASO: O noh FICA MENOR QUE O MÍNIMO.
	 * SOLUÇÃO: JUNTAR OS nohS E RESDISTRIBUIR OS VALORES. 
	 * SOLUÇÃO: ENCONTRAR O noh VIZINHO APROPRIADO PARA JUNTAR. 
	 * SOLUÇÃO: ENCONTRAR A CHAVE NO PAI ENTRE O PONTEIRO PARA O noh E O PONTEIRO PARA O VIZINHO.
	 */
	INDICE_DO_VIZINHO = PEGA_INDICE_DO_VIZINHO(n);
	INDICE_PRIMEIRA_CHAVE = INDICE_DO_VIZINHO == -1 ? 0 : INDICE_DO_VIZINHO;
	PRIMEIRA_CHAVE = n->pai->chave[INDICE_PRIMEIRA_CHAVE];
	VIZINHO = INDICE_DO_VIZINHO == -1 ? n->pai->ponteiros[1] : n->pai->ponteiros[INDICE_DO_VIZINHO];
	CAPACIDADE = n->e_folha ? order : order - 1;
	/*
	 * JUNTA OS nohS.
	 */
	if (VIZINHO->numero_chaves + n->numero_chaves < CAPACIDADE)
		return Juntar_Nos(RAIZ, n, VIZINHO, INDICE_DO_VIZINHO, PRIMEIRA_CHAVE);
	/*
	 * REDISTRIBUI OS nohS. 
     */
	else
		return Redistribuir_Nos(RAIZ, n, VIZINHO, INDICE_DO_VIZINHO, INDICE_PRIMEIRA_CHAVE, PRIMEIRA_CHAVE);
}

/*
 * 
 * PRINCIPAL FUNÇÃO DA REMOÇÃO. 
 * 
 */
noh * Deletar(noh * RAIZ, int CHAVE){
	noh * CHAVE1;
	Registro * REGISTRO_CHAVE;
    /*
	 * SALVA O REGISTRO DA CHAVE QUE DEVE SER DELETADA. 
	 */
	REGISTRO_CHAVE = Encontrar(RAIZ, CHAVE, false);
	/*
	 * SALVA O noh ONDE A CHAVE PROCURADA SE ENCONTRA. 
	 */
	CHAVE1 = Encontrar_Folha(RAIZ, CHAVE, false);
	if(REGISTRO_CHAVE != NULL && CHAVE1 != NULL){
		RAIZ = Excluir_Entrada(RAIZ, CHAVE1, CHAVE, REGISTRO_CHAVE);
		free(REGISTRO_CHAVE);
	}
	return RAIZ;
}

#endif
