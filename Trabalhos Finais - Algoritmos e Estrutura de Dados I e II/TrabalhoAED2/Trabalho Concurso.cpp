#include <clocale>
#include "biblioteca.h"


int main(){
    setlocale(LC_ALL, "Portuguese");
    TPessoa pessoa;
    TPilha pilhaAprov,pilhaReprov;
    TLista lista;
    TArvore a;
    int opcao;
    Menu(opcao,pessoa,pilhaAprov,pilhaReprov,a,lista);
    return 0 ;
}
