#include <string>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <locale.h>
using namespace std;


///Calcula o hash da chave usando expanção polinomial com x = 37

int Cod_Hash(string const & key)
{
  const long x = 41L;
  int n = key.length();
  long value = 0L;
  while( n-- > 0 ) {
    value *= x;   value += key[n];
  }
  return static_cast<int>(value);
}

struct Registro
{
  string valor;

};
/// para a função de procurar e deletar
ostream& operator << (ostream& out, Registro& s) {
      out << s.valor << " Existe " ;
  return out;
}

struct Node{
  Node *proximo;
};

struct Dupla {
  int primeiro;
  Registro *segundo;

  ~Dupla() {
    if(segundo != NULL)
      delete segundo;
  }
};

struct NoInterno : public Node{
  Dupla *elemento;

  ~NoInterno() {
    delete elemento;
  }
};

class ListaEncadeada

 ///BUCKETS na tabela HASH

{
public:
  ListaEncadeada(){
    cabeca = new Node();
    cabeca->proximo = NULL;
  }
  ~ListaEncadeada(){
    del(cabeca);
  }
  void insert(Registro & elem, int ChaveHash){

    Dupla *dados = new Dupla();
    dados->primeiro = ChaveHash;
    dados->segundo = &elem;

    NoInterno *temp = new NoInterno();
    temp->proximo = cabeca->proximo;
    temp->elemento = dados;
    cabeca->proximo = temp;
  }
  Registro* search(int ChaveHash){
    Node *atual = cabeca->proximo;
    while(atual != NULL) {
      if(static_cast<NoInterno*>(atual)->elemento->primeiro == ChaveHash)
        return static_cast<NoInterno*>(atual)->elemento->segundo;
      atual = atual->proximo;
    }
    return NULL;
  }
  void remove(int ChaveHash){
    Node *atual = cabeca->proximo;
    Node *pai = cabeca;
    while(atual != NULL) {
      if(static_cast<NoInterno*>(atual)->elemento->primeiro == ChaveHash) {

        pai->proximo = atual->proximo;
        atual->proximo = NULL;
        del(atual);
        return;
      }
      pai = atual;
      atual = atual->proximo;
    }
  }
  void removeAll(){
    del(cabeca->proximo);
    cabeca->proximo = NULL;
  }
  void print(){
    NoInterno *atual = static_cast<NoInterno*>(cabeca->proximo);
    int i = 1;
    while(atual != NULL) {

      cout << i<<"°valor: "<< atual->elemento->segundo->valor <<endl;
      atual = static_cast<NoInterno*>(atual->proximo);
      ++i;
    }
  }
  Node *PegaLista(){
    return cabeca->proximo;
  }
private:
  void del(Node *node){
    if(node == NULL)
      return;

    del(node->proximo);
    delete node;
  }
  Node *cabeca;
};

class Bucket{
public:
  Bucket(int c, int s = 0) : sig_bits(s), cap(c), sz(0), code(0), raiz(false) {
    dados = new ListaEncadeada();
  }
  ~Bucket(){
    delete dados;
  }
  int capacity(){
    return cap;
  }
  int size(){
    return sz;
  }
  void insert(Registro& elem, int ChaveHash){
    dados->insert(elem, ChaveHash);
    ++sz;
    if(raiz)
      return;
    assert(( size() <= capacity()));
  }
  Registro* search(int ChaveHash){
    return dados->search(ChaveHash);
  }
  void remove(int ChaveHash){
    if(search(ChaveHash) != NULL)
      --sz;
    dados->remove(ChaveHash);
    assert( (size() >= 0) );
  }
  void emptyBucket(){
    dados->removeAll();
    sig_bits = 0;
    sz = 0;
  }
  bool isEmpty(){
    return size() == 0;
  }
  void print() {
    std::cout << "----- <BUCKET (";
    printcode();
    std::cout << ") > -----" << std::endl;
    dados->print();
    std::cout << std::endl;
  }
  Node* PegaLista(){
    return dados->PegaLista();
  }
  int getSIG_BITS(){
    return sig_bits;
  }
  void setSIG_BITS(int s){
    sig_bits = s;
    assert((sig_bits >= 0));
  }
  void setCODE(int c){
    code = c;
  }
  void setRAIZ(bool state) {
    raiz = state;
  }
private:
  void printcode(){
    int length = sig_bits;
    int temp = code;
    while(length-- > 0) {
      std::cout << temp%2;
      temp >>= 1;
    }
  }
  ListaEncadeada *dados;
  int sig_bits;
  int cap;
  int sz;
  int code;
  bool raiz;
};

struct TrieNode{
  Bucket *page;
  TrieNode *proximo[2];
  TrieNode *pai;

  ~TrieNode() {
    if(page != NULL)
      delete page;
  }
};

///Implementação da tabela Hash extensível

 class TabelaHash{
public:
  TabelaHash(int buk = DFL_BUCKET_SIZE) : bucket_size(buk){
    sig_bits = 0;
    indice = new TrieNode();
    indice->page = new Bucket(bucket_size, sig_bits);
    indice->proximo[0] = NULL;
    indice->proximo[1] = NULL;
    indice->pai = NULL;
    no_of_buckets = 1;
  }
  ~TabelaHash(){
    del(indice);
  }
  Registro* search(std::string number){
    int code;
    int ChaveHash = Cod_Hash(number);
    TrieNode *node = EncontrarNo(ChaveHash, &code);
    return node->page->search(ChaveHash);
  }
  void insert(Registro A){
    Registro & st = *new Registro();
    st.valor = A.valor;
    int ChaveHash = Cod_Hash(st.valor);
    int code;
    TrieNode *node = EncontrarNo(ChaveHash, &code);
    Bucket *page = node->page;
    if(page->size()+1 <= page->capacity())
    {
      /// Insere no bucket
      page->insert(st, ChaveHash);

      return;
    } else {  ///bucket está cheio, faça um novo bucket

      Bucket *newPage = new Bucket(bucket_size);
      no_of_buckets++;

      ListaEncadeada *Q = new ListaEncadeada();
      NoInterno *atual = static_cast<NoInterno*>( page->PegaLista() );
      while(atual != NULL) {
        Q->insert(*(atual->elemento->segundo), atual->elemento->primeiro);
        atual = static_cast<NoInterno*>(atual->proximo);
      }
      Q->insert(st, ChaveHash);

      int antigo = page->getSIG_BITS();
      int MASK = 1 << antigo;
      newPage->setSIG_BITS(antigo + 1);

      page->emptyBucket();
      page->setSIG_BITS(antigo + 1);
      if(antigo+1 > sig_bits){
        ++sig_bits;
      }
        node->page = NULL;
        TrieNode *esquerda = new TrieNode();
        TrieNode *direita = new TrieNode();
        node->proximo[0] = esquerda;
        node->proximo[1] = direita;
        esquerda->page = page;
        direita->page = newPage;
        esquerda->proximo[0] = esquerda->proximo[1] = NULL; esquerda->pai = node;
        direita->proximo[0] = direita->proximo[1] = NULL; direita->pai = node;
        esquerda->page->setCODE(code);
        direita->page->setCODE(code | MASK);

      atual = static_cast<NoInterno*>( Q->PegaLista() );

      while(atual != NULL){
        insert( *(atual->elemento->segundo) );
        atual = static_cast<NoInterno*>( atual->proximo );
      }

    }
  }
  void remove(std::string number){
    int ChaveHash = Cod_Hash(number);
    int code;
    TrieNode *node = EncontrarNo(ChaveHash, &code);
    Bucket *page = node->page;
    if(page->search(ChaveHash) == NULL)
      return;
    page->remove(ChaveHash);
    if(page->size() == 0 && node->pai != NULL){
      TrieNode *pai = node->pai;
      TrieNode *irmao = (pai->proximo[0] == node)?
            (pai->proximo[1]) : (pai->proximo[0]);
      if(irmao->proximo[0] != NULL || irmao->proximo[1] != NULL)
        return;

      no_of_buckets--;
      pai->page = irmao->page;
      irmao->page = NULL;
      pai->proximo[0] = NULL;
      pai->proximo[1] = NULL;
      del(node);
      del(irmao);
      pai->page->setSIG_BITS(pai->page->getSIG_BITS() - 1);
      int MASK = 1 << pai->page->getSIG_BITS();
      MASK -= 1;
      code &= MASK;
      pai->page->setCODE(code);
      sig_bits = max_bits(indice);
    }
  }
  void print(){
    cout << "************************************" << endl;
    cout << "Capacidade do Bucket : " << bucket_size <<endl;
    cout << "Número de buckets : " << no_of_buckets << endl;
    int total = printNode(indice);
    cout << "Elementos na tabela Hash : " << total << endl;
    cout << "************************************" << endl;
  }
private:
  TrieNode* EncontrarNo(int ChaveHash, int *const code) {
    int d = 1;
    d <<= sig_bits;
    d -= 1;
    int key = ChaveHash & d;
    *code = 0;
    int length = 0;
    TrieNode *atual = indice;
    while(atual != NULL) {
      if(atual->page != NULL)
        return atual;
      if(atual->proximo[key & 1] != NULL){
        atual = atual->proximo[key & 1];
        int MASK = key&1; // decisão atual
        if(length != 0)
          MASK <<= length;
        *code |= MASK;
        key >>= 1;
        ++length;
      }
    }
    assert( 0 );
    return NULL;
  }
  void del(TrieNode *node){
    if(node == NULL)
      return;
    TrieNode *esquerda, *direita;
    esquerda = node->proximo[0];
    direita = node->proximo[1];
    del(esquerda);
    del(direita);
    delete node;
  }
  int printNode(TrieNode *atual){
    if(atual == NULL)
      return 0;
    if(atual->page != NULL) {
      atual->page->print();
      return atual->page->size();
    }
    int number = printNode(atual->proximo[0]);
    number += printNode(atual->proximo[1]);
    return number;
  }
  int max_bits(TrieNode *node) {
    if(node->page != NULL)
      return node->page->getSIG_BITS();
    int esquerda = max_bits(node->proximo[0]);
    int direita = max_bits(node->proximo[1]);
    int max = (esquerda > direita) ? esquerda : direita;
    return max;
  }
  const static int DFL_BUCKET_SIZE = 4;   /// Tamanho padrão do bucket
  TrieNode *indice;
  int sig_bits;
  int bucket_size;
  int no_of_buckets;

};

int printMenu() {
  cout << "******************************" << endl;
  cout << "\t\t 1. Inserir um registro" << endl;
  cout << "\t\t 2. Procurar um registro" << endl;
  cout << "\t\t 3. Deletar um registro" << endl;
  cout << "\t\t 4. Mostrar todos registros"<< endl;
  cout << "\t\t 5. Deletar todos os registros" << endl;
  cout << "\t\t 6. Exit" << endl;
  int escolha;
  cout << "\nEscolha : ";
  cin >> escolha;
  cout.flush();
  return escolha;
}

int main(){
  setlocale(LC_ALL, "Portuguese");
  cout << "Tamanho do bucket: ";
  int n;
  char ch;
  cin >> n;
  TabelaHash *table = new TabelaHash(n);
  while(true) {
    int escolha = printMenu();
    ch = getchar();
    switch(escolha){
      case 1:{
        Registro st;
        cout << "\nNúmero a ser inserido : ";
        getline(cin, st.valor);
        table->insert(st);
        break;
      }
      case 2:{
        string H;
        cout << "\nNúmero a ser pesquisado: ";
        getline(cin, H);
        Registro *st = table->search(H);
        cout << *st;
        cout << endl << "Enter para continuar...";
        ch = getchar();
        break;
      }
      case 3:{
        string entNum;
        cout << "\nNúmero a ser deletado: ";
        getline(cin, entNum);
        table->remove(entNum);
        break;
      }
      case 4:
        table->print();
        cout <<endl << "Enter para continuar ...";
        ch = getchar();
        break;
      case 5:
        delete table;
        table = new TabelaHash(n);
        break;
      case 6:
        goto DONE;
    }
  }
  DONE:
  delete table;
  return 0;
}
