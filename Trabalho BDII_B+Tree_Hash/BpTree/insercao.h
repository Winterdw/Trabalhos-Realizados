#ifndef INSERCAO_H_INCLUDED
#define INSERCAO_H_INCLUDED

#include <iostream>
using namespace std;

int Cortar(int comprimento);
noh* Inserir_no_pai(noh* RAIZ, noh* ESQUERDA, int CHAVE, noh* DIREITA);
noh* inserir_em_nova_raiz(noh* ESQUERDA, int CHAVE, noh* DIREITA);
noh* comecar_nova_arvore(int CHAVE, Registro* PONTEIRO);
noh* Inserir(noh* RAIZ, int CHAVE, int valor);

int Cortar(int comprimento){
	if(comprimento%2==0)
		return comprimento/2;
	else
		return comprimento/2+1;
}

/*
 * CRIA UM NOVO REGISTRO PARA GUARDAR O VALOR NO QUAL A CHAVE SE REFERE.
 */
Registro * Fazer_Registro(int valor) {
	Registro * new_record = (Registro *)malloc(sizeof(Registro));
	if (new_record == NULL) {
		perror("Criação Registro.");
		exit(EXIT_FAILURE);
	}
	else {
		new_record->valor = valor;
	}
	return new_record;
}

/*
 * CRIA UM NOVO noh GENÉRICO.
 * PODE SER ADAPTADO PARA SERVIR TANTO PARA FOLHA QUANTO PARA noh INTERNO.
 */
noh * Fazer_Noh(){
	noh * NOVO_NO;
	NOVO_NO = (noh*)malloc(sizeof(noh));
	if(NOVO_NO == NULL){
		perror("CRIAÇÃO DO NO.");
		exit(EXIT_FAILURE);
	}
	NOVO_NO->chave = (int*)malloc((order - 1)*sizeof(int));
	if(NOVO_NO->chave == NULL){
		perror("NOVO NO, VETOR DE CHAVES.");
		exit(EXIT_FAILURE);
	}
	NOVO_NO->ponteiros = (noh**)malloc(order*sizeof(void *));
	if(NOVO_NO->ponteiros == NULL){
		perror("NOVO NO, VETOR DE PONTEIROS.");
		exit(EXIT_FAILURE);
	}
	NOVO_NO->e_folha = false;
	NOVO_NO->numero_chaves = 0;
	NOVO_NO->pai = NULL;
	NOVO_NO->proximo = NULL;
	return NOVO_NO;
}

/*
 * CRIA UMA NOVA FOLHA E UM noh.
 * ADAPTA O noh APROPRIADAMENTE.
 */
noh* Fazer_Folha(void){
	noh* folha = Fazer_Noh();
	folha->e_folha = true;
	return folha;
}

int pegar_indice_esquerdo(noh * pai, noh * esquerdo){
	int indice_esquerdo = 0;
	while (indice_esquerdo <= pai->numero_chaves &&
			pai->ponteiros[indice_esquerdo] != esquerdo)
		indice_esquerdo++;
	return indice_esquerdo;
}

/*
 * INSERE UM NOVO PONTEIRO A UM NOVO REGISTRO E SUA CHAVE CORRESPONDENTE EM UMA FOLHA. 
 * RETORNA A FOLHA ALTERADA.
 */
noh* inserir_em_uma_folha(noh* FOLHA, int CHAVE, Registro* PONTEIRO){
	int i, ponto_de_insercao;
	ponto_de_insercao = 0;
	while(ponto_de_insercao < FOLHA->numero_chaves && FOLHA->chave[ponto_de_insercao] < CHAVE)
		ponto_de_insercao++;
	for (i = FOLHA->numero_chaves; i > ponto_de_insercao; i--){
		FOLHA->chave[i] = FOLHA->chave[i-1];
		FOLHA->ponteiros[i] = FOLHA->ponteiros[i-1];
	}
	FOLHA->chave[ponto_de_insercao] = CHAVE;
	FOLHA->ponteiros[ponto_de_insercao] = (noh*)PONTEIRO;
	FOLHA->numero_chaves++;
	return FOLHA;
}

/*
 * INSERE UMA NOVA CHAVE E UM PONTEIRO PARA UM NOVO REGISTRO EM UM NÓ.
 * EXCEDE A ORDEM DA B+TREE, CAUSANDO A DIVISÃO DO noh.
 */
noh * inserir_em_uma_folha_depois_de_dividir(noh * RAIZ, noh * FOLHA, int CHAVE, Registro * PONTEIRO){
	noh * FOLHA_NOVA;
	int * CHAVE_TEMPORARIA;
	void ** PONTEIRO_TEMPORARIO;
	int indice_de_insercao, DIVISAO, NOVA_CHAVE, i, j;

	FOLHA_NOVA = Fazer_Folha();

	CHAVE_TEMPORARIA = (int*)malloc( order * sizeof(int) );
	if(CHAVE_TEMPORARIA == NULL){
		perror("VETOR DE CHAVES TEMPORARIO.");
		exit(EXIT_FAILURE);
	}

	PONTEIRO_TEMPORARIO = (void**)malloc( order * sizeof(void *) );
	if (PONTEIRO_TEMPORARIO == NULL) {
		perror("VETOR DE PONTEIROS TEMPORARIO.");
		exit(EXIT_FAILURE);
	}

	indice_de_insercao = 0;
	while(indice_de_insercao < order - 1 && FOLHA->chave[indice_de_insercao] < CHAVE)
		indice_de_insercao++;

	for(i = 0, j = 0; i < FOLHA->numero_chaves; i++, j++){
		if(j == indice_de_insercao) j++;
		CHAVE_TEMPORARIA[j] = FOLHA->chave[i];
		PONTEIRO_TEMPORARIO[j] = FOLHA->ponteiros[i];
	}

	CHAVE_TEMPORARIA[indice_de_insercao] = CHAVE;
	PONTEIRO_TEMPORARIO[indice_de_insercao] = PONTEIRO;

	FOLHA->numero_chaves = 0;

	DIVISAO = Cortar(order - 1);

	for(i=0; i<DIVISAO; i++){
		FOLHA->ponteiros[i] = (noh*)PONTEIRO_TEMPORARIO[i];
		FOLHA->chave[i] = CHAVE_TEMPORARIA[i];
		FOLHA->numero_chaves++;
	}

	for(i=DIVISAO, j=0; i<order; i++, j++){
		FOLHA_NOVA->ponteiros[j] = (noh*)PONTEIRO_TEMPORARIO[i];
		FOLHA_NOVA->chave[j] = CHAVE_TEMPORARIA[i];
		FOLHA_NOVA->numero_chaves++;
	}

	free(PONTEIRO_TEMPORARIO);
	free(CHAVE_TEMPORARIA);

	FOLHA_NOVA->ponteiros[order - 1] = FOLHA->ponteiros[order - 1];
	FOLHA->ponteiros[order - 1] = FOLHA_NOVA;

	for(i=FOLHA->numero_chaves; i<order-1; i++)
		FOLHA->ponteiros[i] = NULL;
	for(i=FOLHA_NOVA->numero_chaves; i<order-1; i++)
		FOLHA_NOVA->ponteiros[i] = NULL;

	FOLHA_NOVA->pai = FOLHA->pai;
	NOVA_CHAVE = FOLHA_NOVA->chave[0];

	return Inserir_no_pai(RAIZ, FOLHA, NOVA_CHAVE, FOLHA_NOVA);
}

/*
 * INSERE UMA NOVA CHAVE UM UM PONTEIRO PARA UM noh ADEQUADO.
 * SE PREOCUPA COM NÃO VIOLAR AS PROPRIEDADES DE B+TREE.
 */
noh *inserir_no_noh(noh * RAIZ, noh * n, int indice_esquerdo, int CHAVE, noh * DIREITO){
	int i;
	for(i=n->numero_chaves; i>indice_esquerdo; i--){
		n->ponteiros[i+1] = n->ponteiros[i];
		n->chave[i] = n->chave[i-1];
	}
	n->ponteiros[indice_esquerdo+1] = DIREITO;
	n->chave[indice_esquerdo] = CHAVE;
	n->numero_chaves++;
	return RAIZ;
}

/*
 * INSERE UM NOVA CHAVE A UM PONTIERO PARA UM noh.
 * O noh EXECE E ORDEM E SE DIVIDE.
 */
noh * inserir_em_no_depois_de_dividir(noh * RAIZ, noh * ANTIGO_NO, int INDICE_ESQUERDO, int CHAVE, noh * DIREITA){
	int i, j, DIVIDE, k_prime;
	noh * NOVO_NO, * FILHO;
	int * CHAVES_TEMPORARIAS;
	noh ** PONTEIROS_TEMPORARIOS;

	/*
	 * PRIMEIRAMENTE CRIA UMA QUANTIDADE DE CHAVES E PONTEIROS TEMPORÁRIOS PARA GUARDAR OS DADOS.
	 * ISSO INCLUI A NOVA CHAVE E O NOVO PONTEIRO.
	 * ALÉM DE SUAS POSIÇÕES CORRESPONDENTES. 
	 * ENTÃO CRIA-SE UM NOVO noh E METADE DOS DADOS SÃO TRANSFERIDOS A ELE.
	 */
	PONTEIROS_TEMPORARIOS = (noh**)malloc((order + 1) * sizeof(noh *));
	if(PONTEIROS_TEMPORARIOS == NULL){
		perror("Temporary pointers array for splitting nodes.");
		exit(EXIT_FAILURE);
	}
	CHAVES_TEMPORARIAS = (int*)malloc(order * sizeof(int));
	if (CHAVES_TEMPORARIAS == NULL){
		perror("Temporary keys array for splitting nodes.");
		exit(EXIT_FAILURE);
	}

	for(i=0, j=0; i<ANTIGO_NO->numero_chaves+1; i++, j++){
		if(j == INDICE_ESQUERDO+1) j++;
		PONTEIROS_TEMPORARIOS[j] = ANTIGO_NO->ponteiros[i];
	}
	for(i=0, j=0; i<ANTIGO_NO->numero_chaves; i++, j++){
		if(j == INDICE_ESQUERDO) j++;
		CHAVES_TEMPORARIAS[j] = ANTIGO_NO->chave[i];
	}

	PONTEIROS_TEMPORARIOS[INDICE_ESQUERDO+1] = DIREITA;
	CHAVES_TEMPORARIAS[INDICE_ESQUERDO] = CHAVE;

	DIVIDE = Cortar(order);
	NOVO_NO = Fazer_Noh();
	ANTIGO_NO->numero_chaves = 0;
	for(i=0; i<DIVIDE-1; i++){
		ANTIGO_NO->ponteiros[i] = PONTEIROS_TEMPORARIOS[i];
		ANTIGO_NO->chave[i] = CHAVES_TEMPORARIAS[i];
		ANTIGO_NO->numero_chaves++;
	}
	ANTIGO_NO->ponteiros[i] = PONTEIROS_TEMPORARIOS[i];
	k_prime = CHAVES_TEMPORARIAS[DIVIDE-1];
	for(++i, j=0; i<order; i++, j++){
		NOVO_NO->ponteiros[j] = PONTEIROS_TEMPORARIOS[i];
		NOVO_NO->chave[j] = CHAVES_TEMPORARIAS[i];
		NOVO_NO->numero_chaves++;
	}
	NOVO_NO->ponteiros[j] = PONTEIROS_TEMPORARIOS[i];
	free(PONTEIROS_TEMPORARIOS);
	free(CHAVES_TEMPORARIAS);
	NOVO_NO->pai = ANTIGO_NO->pai;
	for(i = 0; i <= NOVO_NO->numero_chaves; i++){
		FILHO = NOVO_NO->ponteiros[i];
		FILHO->pai = NOVO_NO;
	}
	return Inserir_no_pai(RAIZ, ANTIGO_NO, k_prime, NOVO_NO);
}

/*
 * INSERE UM NOVO noh EM UMA B+TREE.
 * RETORNA A RAIZ DA B+TREE DEPOIS DA INSERÇÃO.
 */
noh * Inserir_no_pai(noh * RAIZ, noh * ESQUERDA, int CHAVE, noh * DIREITA) {
	int indice_esquerdo;
	noh * pai;
	pai = ESQUERDA->pai;
	if (pai == NULL)
		return inserir_em_nova_raiz(ESQUERDA, CHAVE, DIREITA);
	indice_esquerdo = pegar_indice_esquerdo(pai, ESQUERDA);
	if (pai->numero_chaves < order - 1)
		return inserir_no_noh(RAIZ, pai, indice_esquerdo, CHAVE, DIREITA);
	return inserir_em_no_depois_de_dividir(RAIZ, pai, indice_esquerdo, CHAVE, DIREITA);
}

/*
 * CRIA UMA NOVA RAIZ PARA DUAS SUBÁRVORES E INSERE AS CHAVEZ NA NOVA RAIZ. 
 */
noh * inserir_em_nova_raiz(noh * ESQUERDA, int CHAVE, noh * DIREITA){
	noh * raiz = Fazer_Noh();
	raiz->chave[0] = CHAVE;
	raiz->ponteiros[0] = ESQUERDA;
	raiz->ponteiros[1] = DIREITA;
	raiz->numero_chaves++;
	raiz->pai = NULL;
	ESQUERDA->pai = raiz;
	DIREITA->pai = raiz;
	return raiz;
}

/*
 * PARA COMEÇAR UM NOVA B+TREE, USA-SE O REGISTRO DA CHAVE E A PRÓPRIA CHAVE.
 */
noh * comecar_nova_arvore(int CHAVE, Registro * pointer){
	noh * raiz = Fazer_Folha();
	raiz->chave[0] = CHAVE;
	raiz->ponteiros[0] = (noh*)pointer;
	raiz->ponteiros[order-1] = NULL;
	raiz->pai = NULL;
	raiz->numero_chaves++;
	return raiz;
}

/*
 * 
 * FUNÇÃO DE INSERÇÃO PRINCIPAL. 
 *
 * INSERE UMA CHAVE E UM VALOR ASSOCIADO A ELA.
 * FAZ COM QUE A B+TREE SEJA AJUSTADA QUANDO FOR NECESSÁRIO PARA MANTER SUAS PROPRIEDADES. 
 */
noh * Inserir(noh * raiz, int Chave, int valor){
	Registro * ponteiro;
	noh * folha;
    /*
     * VERIFICA SE O REGISTRO DO VALOR EXISTE.
     */
	if(Encontrar(raiz, Chave, false) != NULL)
		return raiz;
	ponteiro = Fazer_Registro(valor);
	/*
 	 * CASO: A B+TREE AINDA NÃO EXISTE.
 	 * SOLUÇÃO: COMEÇAR UMA NOVA B+TREE.
 	 */
	if(raiz == NULL)
		return comecar_nova_arvore(Chave, ponteiro);
	/*
 	 * CASO: A B+TREE JÁ EXISTE.
 	 * SOLUÇÃO: PROCURA PELA FOLHA ADEQUADA PARA INSERIR A CHAVE.
 	 */
	folha = Encontrar_Folha(raiz, Chave, false);
	/*
	 * CASO: A FOLHA TEM ESPAÇO PARA A CHAVE.
	 */
	if(folha->numero_chaves<order-1){
		folha = inserir_em_uma_folha(folha, Chave, ponteiro);
		return raiz;
	}
	/*
	 * CASO: A FOLHA PRECISA SE DIVIDIR.
	 */
	return inserir_em_uma_folha_depois_de_dividir(raiz, folha, Chave, ponteiro);
}

#endif
