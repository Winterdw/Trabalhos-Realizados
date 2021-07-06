#ifndef B_TREE_H_INCLUDED
#define B_TREE_H_INCLUDED

typedef struct Registro{
	int valor;
}Registro;

typedef struct noh{
	noh ** ponteiros;
	int * chave;
	struct noh * pai;
	bool e_folha;
	int numero_chaves;
	struct noh * proximo;
}noh;

int order = DEFAULT_ORDER;

noh * queue = NULL;

bool Saida_detalhada = false;

// Assinaturas.
void uso(void);
void Enfileirar(noh * novo_no);
noh * Desenfileirar(void);
int Caminho_para_Raiz(noh * raiz, noh * FILHO);
void Mostrar_Arvore(noh * raiz);
noh * Encontrar_Folha(noh * raiz, int Chave, bool Saida_detalhada);
Registro * Encontrar(noh * raiz, int Chave, bool Saida_detalhada);
int Cortar(int comprimento);

// Inserções.
noh * Inserir_no_pai(noh * RAIZ, noh * ESQUERDA, int CHAVE, noh * DIREITA);
noh * inserir_em_nova_raiz(noh * ESQUERDA, int CHAVE, noh * DIREITA);
noh * comecar_nova_arvore(int CHAVE, Registro * PONTEIRO);
noh * Inserir(noh * RAIZ, int CHAVE, int valor);
int PEGA_INDICE_DO_VIZINHO(noh * n);
noh * Ajustar_Raiz(noh * RAIZ);
noh * Juntar_Nos(noh * RAIZ, noh * n, noh * VIZINHO,int INDICE_DO_VIZINHO, int PRIMEIRA_CHAVE);
noh * Redistribuir_Nos(noh * RAIZ, noh * n, noh * VIZINHO,int INDICE_DO_VIZINHO,int k_prime_index, int PRIMEIRA_CHAVE);
noh * Excluir_Entrada(noh * RAIZ, noh * n, int CHAVE, void * PONTEIRO);
noh * Deletar(noh * RAIZ, int CHAVE);

void uso(void){
	cout<<"-------- ÁRVORE B --------\n\n\n"
	"i         ** Inserir uma chave k. **\n"
	"d         ** Deletar a chave k.   **\n"
	"f         ** Pesquisar registro.  **\n"
	"t         ** Mostrar a árvore B.  **\n"
	"q         ** Sair do programa.    **\n"
	"t?        ** Mostrar essa mensagem de ajuda. **\n"
	<<endl;
}

/*
 * Função para a Mostrar a arvore.
 */
void Enfileirar(noh * NOVO_NO){
	noh * c;
	if(queue == NULL){
		queue = NOVO_NO;
		queue->proximo = NULL;
	}
	else {
		c = queue;
		while(c->proximo != NULL){

			c = c->proximo;
		}
		c->proximo = NOVO_NO;
		NOVO_NO->proximo = NULL;
	}
}

/*
 * Outra função para a mostrar a árvore.
 */
noh * Desenfileirar(void){
	noh * n = queue;
	queue = queue->proximo;
	n->proximo = NULL;
	return n;
}

/*
 * Função de utilidade para mostrar a árvore.
 */

int Caminho_para_Raiz(noh * RAIZ, noh * FILHO){
	int comprimento = 0;
	noh * c = FILHO;
	while (c != RAIZ) {
		c = c->pai;
		comprimento++;
	}
	return comprimento;
}

void Mostrar_Arvore(noh * RAIZ){
	noh * n = NULL;
	int i = 0;
	int rank = 0;
	int new_rank = 0;
	if (RAIZ == NULL){
		printf("Arvore vazia.\n");
		return;
	}
	queue = NULL;
	Enfileirar(RAIZ);
	while(queue != NULL){
		n = Desenfileirar();
		if (n->pai != NULL && n == n->pai->ponteiros[0]){
			new_rank = Caminho_para_Raiz(RAIZ, n);
			if (new_rank != rank){
				rank = new_rank;
				printf("\n");
			}
		}
		if (Saida_detalhada)
			printf("(%lx)", (unsigned long)n);
		for (i = 0; i < n->numero_chaves; i++) {
			if (Saida_detalhada)
				printf("%lx ", (unsigned long)n->ponteiros[i]);
			printf("%d ", n->chave[i]);
		}
		if (!n->e_folha)
			for (i = 0; i <= n->numero_chaves; i++)
				Enfileirar(n->ponteiros[i]);
		if (Saida_detalhada) {
			if (n->e_folha)
				printf("%lx ", (unsigned long)n->ponteiros[order - 1]);
			else
				printf("%lx ", (unsigned long)n->ponteiros[n->numero_chaves]);
		}
		printf("| ");
	}
	printf("\n");
}

void Encontrar_e_Mostrar(noh * RAIZ, int CHAVE, bool Saida_detalhada) {
	Registro * r = Encontrar(RAIZ, CHAVE, Saida_detalhada);
	if (r == NULL)
		cout<<"Registro não encontrado sob a Chave "<<CHAVE<<"."<<endl;
	else
		printf("Registro em %lx -- Chave %d, Valor %d.\n", (unsigned long)r, CHAVE, r->valor);
}

/*
 * Traça o caminho da raiz até a folha procurando pela chave.
 * Retorna a folha contendo a chave dada.
 */
noh * Encontrar_Folha(noh * raiz, int CHAVE, bool Saida_detalhada){
	int i = 0;
	noh * c = raiz;
	if(c == NULL){
		if(Saida_detalhada)
			cout<<"Arvore vazia."<<endl;
		return c;
	}
	while(!c->e_folha){
		if(Saida_detalhada){
			cout<<"[";
			for (i=0; i<c->numero_chaves-1; i++)
				printf("%d ", c->chave[i]);
			printf("%d] ", c->chave[i]);
		}
		i = 0;
		while(i < c->numero_chaves){
			if (CHAVE >= c->chave[i]) i++;
			else break;
		}
		if (Saida_detalhada)
			printf("%d ->\n", i);
		c = (noh *)c->ponteiros[i];
	}
	if(Saida_detalhada){
		cout<<"Folha [";
		for (i = 0; i < c->numero_chaves - 1; i++)
			printf("%d ", c->chave[i]);
		printf("%d] ->\n", c->chave[i]);
	}
	return c;
}

/*
 * Encontra e retorna o registro a qual a chave se refere.
 */

Registro * Encontrar(noh * raiz, int CHAVE, bool Saida_detalhada){
	int i = 0;
	noh * c = Encontrar_Folha(raiz, CHAVE, Saida_detalhada);
	if(c == NULL) return NULL;
	for(i = 0; i < c->numero_chaves; i++)
		if (c->chave[i] == CHAVE) break;
	if(i == c->numero_chaves)
		return NULL;
	else
		return (Registro *)c->ponteiros[i];
}

int Cortar(int comprimento){
	if(comprimento%2==0)
		return comprimento/2;
	else
		return comprimento/2+1;
}

/*
 * Cria um novo registro para guardar o valor no qual a chave se refere.
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
 * Cria um novo NO genérico, o qual pode ser adaptado para servir tanto quanto folha quanto para nó interno.
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
 * Cria uma nova folha CRIANDO um noh e então adapta o noh apropriadamente.
 */
noh * Fazer_Folha(void){
	noh * folha = Fazer_Noh();
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
 * Insere um novo ponteiro a um novo registro e sua chave correspondente em uma folha.
 * Retorna a folha alterada.
 */
noh * inserir_em_uma_folha(noh * FOLHA, int CHAVE, Registro * PONTEIRO){
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
 * Insere uma nova chave e ponteiro para um novo registro em um nó.
 * Excede a ordem da árvore, fazendo com que o nó se divida ao meio.
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
 * Insere uma nova chave e ponteiro para um no adequado, sem violar as propriedades da arvore B.
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
 * Insere uma nova chave e ponteiro para um noh, fazendo com que o noh exceda a ordem e se divida em dois.
 */
noh * inserir_em_no_depois_de_dividir(noh * RAIZ, noh * ANTIGO_NO, int INDICE_ESQUERDO, int CHAVE, noh * DIREITA){
	int i, j, DIVIDE, k_prime;
	noh * NOVO_NO, * FILHO;
	int * CHAVES_TEMPORARIAS;
	noh ** PONTEIROS_TEMPORARIOS;

	/*
	 * Primeiro cria uma quantidade de chaves e ponteiros temporarios para guardar tudo em ordem, incluindo a nova chave
	e ponteiro, inserindo em seus lugares correspondentes.
	 * Então cria-se um novo noh e copia metade das chaves e ponteiro para o antigo noh e o outro com metade do novo.
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
 * Insere um novo noh em uma arvore B.
 * Retorna a raiz da arvore depois da inserção.
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
 * Cria uma nova raiz para duas subarvores e insere as chaves apropriadas na nova raiz.
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
 * Para começar uma nova árvore, usa-se o registro da dada chave e a própria chave.
 * Começa uma nova árvore.
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
 * FUNÇÃO DE INSERÇÃO PRINCIPAL:
 * Insere uma chave e um valor associado a ela a uma árvore B.
 * Faz com que a arvore seja ajustada quando for necessário para manter suas propriedades
 */
noh * Inserir(noh * raiz, int Chave, int valor){
	Registro * ponteiro;
	noh * folha;
    /*
     * Verifica se o registro do número existe.
     */
	if(Encontrar(raiz, Chave, false) != NULL)
		return raiz;
	ponteiro = Fazer_Registro(valor);
	/*
	 * Caso: A árvore não existe ainda.
	 * Comece uma nova árvore.
	 */
	if(raiz == NULL)
		return comecar_nova_arvore(Chave, ponteiro);
	/*
	 * Caso: A árvore já existe.
	 * Procura a folha adequada para colocar a chave.
	 */
	folha = Encontrar_Folha(raiz, Chave, false);
	/*
	 * Caso: A folha tem espaço para a chave.
	 */
	if(folha->numero_chaves<order-1){
		folha = inserir_em_uma_folha(folha, Chave, ponteiro);
		return raiz;
	}
	/*
	 * Caso: A folha precisa se dividir.
	 */
	return inserir_em_uma_folha_depois_de_dividir(raiz, folha, Chave, ponteiro);
}

// DELEÇÃO.

/*
 * Função de utilidade para deletar um valor.
 * Recupera o índice de um vizinho próximo do nó (irmão) à esquerda se existir algum.
 * Se não existir (o nó é o filho mais à esquerda) retorna -1 para significar o caso em especial.
 */
int PEGA_INDICE_DO_VIZINHO(noh * n){
	int i;
	/*
	 * Retorna o índice da chave  à esquerda do ponteiro no pai apontando para N.
     * Se N é o filho mais à esquerda, isso significa return -1.
	 */
	for(i=0; i<=n->pai->numero_chaves; i++)
		if(n->pai->ponteiros[i] == n)
			return i-1;
	/*
	 * Error state.
	 */
	cout<<"Procura pelo ponteiro não-existente para o nó no pai."<<endl;
	printf("Node:  %#lx\n", (unsigned long)n);
	exit(EXIT_FAILURE);
}

noh * Excluir_Entrada_Do_No(noh * n, int CHAVE, noh * PONTEIRO){
	int i, NUMERO_DE_PONTEIROS;
	/*
	 * Remove a chave e muda as outras chaves adequadamente.
	 */
	i = 0;
	while(n->chave[i] != CHAVE)
		i++;
	for(++i; i < n->numero_chaves; i++)
		n->chave[i - 1] = n->chave[i];
    /*
	 * Remove o ponteiro e muda as outras chaves adequadamente.
	 * Primeiro determina o número de ponteiros.
	 */
	NUMERO_DE_PONTEIROS = n->e_folha ? n->numero_chaves : n->numero_chaves+1;
	i = 0;
	while(n->ponteiros[i] != PONTEIRO)
		i++;
	for (++i; i<NUMERO_DE_PONTEIROS; i++)
		n->ponteiros[i-1] = n->ponteiros[i];
	/*
	 * Uma chave a menos.
	 */
	n->numero_chaves--;
	/*
	 * Estabelece os outros ponteiros para NULL para deixar organizado.
	 * Uma folha usa o último ponteiro para apontar para a próxima folha.
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
	 * Caso: Uma raiz não vazia.
	 * Chave e ponteiro já foram deletados, então nada a ser feito.
	 */
	if(RAIZ->numero_chaves>0)
		return RAIZ;
	/*
	 * Caso: raiz vazia.
	 * Se tem um filho, promove o primeiro (e único) filho como nova raiz.
	 */
	if(!RAIZ->e_folha){
		NOVA_RAIZ = RAIZ->ponteiros[0];
		NOVA_RAIZ->pai = NULL;
	}
	/*
	 * Se for uma folha(e não tem filhos) então a árvore inteira está vazia.
	 */
	else
		NOVA_RAIZ = NULL;
	free(RAIZ->chave);
	free(RAIZ->ponteiros);
	free(RAIZ);
	return NOVA_RAIZ;
}

/*
 * Junta um nó que se tornou muito pequeno depois da deleção com um no vizinho que pode aceitar entradas adicionais sem exceder o máximo.
 */
noh * Juntar_Nos(noh * RAIZ, noh * n, noh * VIZINHO, int INDICE_DO_VIZINHO, int PRIMEIRA_CHAVE){
	int i, j, INDICE_DE_ISNERCAO_DO_VIZINHO, n_final;
	noh * tmp;
	/*
	 * Troca o vizinho com noh se o noh está na extrema esquerda e o vizinho está à direita do noh.
	 */
	if(INDICE_DO_VIZINHO==-1){
		tmp = n;
		n = VIZINHO;
		VIZINHO = tmp;
	}
	/*
	 * Ponto de START no vizinho para cópia de chaves e ponteiros de N.
	 * Rechama o N e vizinho para trocarem de lugar	no caso especial de N ser o filho mais à esquerda.
	 */
	INDICE_DE_ISNERCAO_DO_VIZINHO = VIZINHO->numero_chaves;
	/*
	 * Caso: sem nó folha.
	 * Acrescentar PRIMEIRA_CHAVE e seu ponteiro correspondente.
     * Acrescentar todos os ponteiros e chaves do vizinho.
	 */
	if(!n->e_folha){
		/*
		 * Acrescenta PRIMEIRA_CHAVE.
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
		 * O número de ponteiros é sempre um a mais que o número de chaves
		 */
		VIZINHO->ponteiros[i] = n->ponteiros[j];
		/*
		 * Todos os filhos precisam agora apontar para o mesmo pai.
		 */
		for(i=0; i<VIZINHO->numero_chaves+1; i++){
			tmp = (noh *)VIZINHO->ponteiros[i];
			tmp->pai = VIZINHO;
		}
	}
	/*
	 * Em uma folha, acrescentar as chaves e pointeiros de N para o vizinho.
     * Estabelecer o último ponteiro do vizinho para apontar para o que havia sido o vizinho da direita de N.
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
 * Redistribui entradas entre dois nós quando um se tornou muito pequeno depois da deleção,
 * mas seu vizinho é muito grande para acrescentar as entradas do pequeno nó sem exceder o máximo.
 */
noh * Redistribuir_Nos(noh * RAIZ, noh * n, noh * VIZINHO, int INDICE_DO_VIZINHO, int INDICE_DA_PRIMEIRA_CHAVE, int PRIMEIRA_CHAVE){
	int i;
	noh * tmp;
	/*
	 * Caso: n tem um vizinho à esquerda.Puxe o último par de chave-ponteiro do vizinho do lado direito do vizinho ao final esquerdo de n
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
	 * Case: n é o filho mais à esquerda.
     * Use um par de ponteiro chave do vizinho a direita.
     * Mova o par de ponteiro-chave do vizinho mais à esquerda para a posição mais à direita de N.
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
	 * n agora tem uma chave a mais e um ponteiro a mais.
	 * O vizinho tem um a menos de cada.
	 */
	n->numero_chaves++;
	VIZINHO->numero_chaves--;
	return RAIZ;
}

/*
 * Deleta uma entrada da árvore B.
 * Remove o registro, suas chaves e ponteiros da folha.
 * Faz todas as mudanças apropriadas para preservar as propriedades da árvore B.
 */
noh * Excluir_Entrada(noh * RAIZ, noh * n, int CHAVE, void * PONTEIRO){
	int minimo_de_chaves;
	noh * VIZINHO;
	int INDICE_DO_VIZINHO;
	int INDICE_PRIMEIRA_CHAVE, PRIMEIRA_CHAVE;
	int CAPACIDADE;
	/*
	 * Remove chave e ponteiro do nó.
	 */
	n = Excluir_Entrada_Do_No(n, CHAVE, (noh*)PONTEIRO);
	/*
	 * Caso: deleção da raiz.
	 */
	if (n == RAIZ)
		return Ajustar_Raiz(RAIZ);
	/*
	 * Caso: deleção de um nó abaixo da raiz.
	 * Determine o mínimo permitível do tamanho do nó para ser preservado após a deleção.
	 */
	minimo_de_chaves = n->e_folha ? Cortar(order-1) : Cortar(order)-1;
	/*
	 * Caso: o nó está IGUAL ou ACIMA do mínimo (o caso mais simples).
	 */
	if (n->numero_chaves >= minimo_de_chaves)
		return RAIZ;
	/*
	 * Caso: O nó cai para MENOR que o mínimo.
	 * Juntar_Nos e Redistribuir_Nos são necessarios.
	 * Encontre o noh vizinho apropriado para juntar.
	 * Encontre também a chave (PRIMEIRA_CHAVE) no pai entre o ponteiro para o noh e o ponteiro para o vizinho.
	 */
	INDICE_DO_VIZINHO = PEGA_INDICE_DO_VIZINHO(n);
	INDICE_PRIMEIRA_CHAVE = INDICE_DO_VIZINHO == -1 ? 0 : INDICE_DO_VIZINHO;
	PRIMEIRA_CHAVE = n->pai->chave[INDICE_PRIMEIRA_CHAVE];
	VIZINHO = INDICE_DO_VIZINHO == -1 ? n->pai->ponteiros[1] : n->pai->ponteiros[INDICE_DO_VIZINHO];
	CAPACIDADE = n->e_folha ? order : order - 1;
	/*
	 * Juntar_Nos.
	 */
	if (VIZINHO->numero_chaves + n->numero_chaves < CAPACIDADE)
		return Juntar_Nos(RAIZ, n, VIZINHO, INDICE_DO_VIZINHO, PRIMEIRA_CHAVE);
	/*
	 * Redistribuir_nos.
     */
	else
		return Redistribuir_Nos(RAIZ, n, VIZINHO, INDICE_DO_VIZINHO, INDICE_PRIMEIRA_CHAVE, PRIMEIRA_CHAVE);
}

/*
 * Função MESTRE de DELEÇÃO.
 */
noh * Deletar(noh * RAIZ, int CHAVE){
	noh * CHAVE1;
	Registro * REGISTRO_CHAVE;
    /*
	 * Salva o registro da chave que queremos deletar.
	 */
	REGISTRO_CHAVE = Encontrar(RAIZ, CHAVE, false);
	/*
	 * Salva o noh onde a chave procurada se encontra.
	 */
	CHAVE1 = Encontrar_Folha(RAIZ, CHAVE, false);
	if(REGISTRO_CHAVE != NULL && CHAVE1 != NULL){
		RAIZ = Excluir_Entrada(RAIZ, CHAVE1, CHAVE, REGISTRO_CHAVE);
		free(REGISTRO_CHAVE);
	}
	return RAIZ;
}

#endif // B_TREE_H_INCLUDED
