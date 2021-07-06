#include <iostream>
using namespace std;


struct TPessoa{
    string nome;
    int idade;
    int nota;
    int numInsc;
};

struct TCelula{
    TPessoa pessoa;
    TCelula *proximo;
};

struct TPilha{
    TCelula *fundo;
    TCelula *topo;
    int contador;
};

struct TNoh{
    TPessoa pessoa;
    TNoh *esq,*dir;
};

struct TArvore{
    TNoh *raiz;
    int contador;
};

struct TLista{
    TCelula *primeiro;
    TCelula *ultimo;
    int cont;
};

bool estaVazia(TArvore a){
    return a.raiz == NULL;
}

bool estaVazia(TPilha &p){
    return (p.topo == p.fundo);
}

bool estaVaziaL(TLista l){
    return l.primeiro == l.ultimo;

}

void criaPilhaVazia(TPilha &p){
   p.topo = new TCelula;
   p.fundo = p.topo;
   p.topo->proximo = NULL;
   p.contador = 0;
   cout<<"Pilha criada com sucesso!"<<endl;
}
void criarLVazia(TLista &l){
    l.primeiro = new TCelula;
    l.ultimo = l.primeiro;
    l.primeiro ->proximo = NULL;
    l.cont = 0;
    cout << "Lista criada com sucesso" << endl;

}
void criarArvEmpty(TArvore &a){
    a.raiz = NULL;
    a.contador=0;
}

void empilhar(TPessoa pessoa, TPilha &p){
    TCelula *celAux = new TCelula;
    p.topo->pessoa = pessoa;
    celAux->proximo = p.topo;
    p.topo = celAux;
    p.contador++;
}

void mostrarPilha(TPilha p){
    TCelula *pCelAux;
    pCelAux = p.topo->proximo;
    if (estaVazia(p)){
        cout<<"Pilha está vazia!"<<endl;
    }
    else{
        while (pCelAux != NULL){
            cout<<"Nome: "<<pCelAux->pessoa.nome<<endl;
            cout<<"Idade: " <<pCelAux->pessoa.idade<<endl;
            cout<<"Nota: " <<pCelAux->pessoa.nota<<endl;
            cout<<"Número de inscrição: "<<pCelAux->pessoa.numInsc<<endl;
            pCelAux = pCelAux->proximo;
        }
    }
}

void mostrarItensLista(TLista l){
    TCelula *celAux;
    celAux = l.primeiro->proximo;
    cout<< "Mostrando lista de candidatos cadastrados no conrcuso: " <<endl;
    while(celAux!=NULL){
        int i=0;
        cout<< "Nome: "<<celAux->pessoa.nome <<endl;
        cout<<"Idade: " <<celAux->pessoa.idade<<endl;
        cout<<"Nota: " <<celAux->pessoa.nota<<endl;
        cout<<"Número de inscrição: "<<celAux->pessoa.numInsc<<endl;
        celAux = celAux->proximo;
    }
}

void inserir(TPessoa p,TNoh *&n,TArvore &a){
    if (n == NULL){
        n = new TNoh;

        n->pessoa = p;
        n->esq = NULL;
        n->dir = NULL;
        if (a.raiz == NULL){
            a.raiz = n;
        };
        a.contador++;
    }
    else{

        if ( p.numInsc < n->pessoa.numInsc){
            inserir(p,n->esq,a);
        }
            else{
            if (p.numInsc > n->pessoa.numInsc){

                inserir(p,n->dir,a);
                }
                else{
                cout<<"Candidato já cadastrado na árvore!"<<endl;
                }
            }
        }
}

void inserir(TPessoa x,TLista &l){
    l.ultimo->proximo= new TCelula;
    l.ultimo = l.ultimo ->proximo;
    l.ultimo->pessoa = x;
    l.ultimo->proximo = NULL;
    l.cont++;

}

void cadastrarCandidatos(TArvore &a){
TPessoa x;
string resp;

    cout << endl << "---   CADASTRANDO CANDIDATOS   ----" << endl;
    do{
        cout<< " " <<endl;
        cout<<"Nome do candidato: ";
        cin>>x.nome;
        cout<<"Idade do candidato: ";
        cin>>x.idade;
        cout<<"Nota do candidato: ";
        cin>>x.nota;
        if(x.nota>100){
            cout<< "Nota inválida,por favor digite a nota real do candidato (De 0 até 100)!!!: ";
            cin>>x.nota;
            while(x.nota>100){
                cout<< "Nota inválida,por favor digite a nota real do candidato (De 0 até 100)!!!: ";
                cin>>x.nota;
            }
        }
        cout<<"Digite número de inscrição: ";
        cin>>x.numInsc;
        inserir(x,a.raiz,a);
        cout<< " " <<endl;
        cout << "Deseja cadastrar mais algum candidato? (s/n): ";
        cin >> resp;
    }while(resp!="n");
    cout << endl << "-----------------------------" << endl;
}

void percorrerINOrdem(TNoh *&a){
    if(a!=NULL){
        percorrerINOrdem(a->esq);
        cout<<"Nome: "<< a->pessoa.nome<<endl;
        cout<<"Nota: "<< a->pessoa.nota<<endl;
        percorrerINOrdem(a->dir);
    }
}

void percorrerPREOrdem(TNoh *&a){
    if(a!=NULL){
        cout<<"Nome: "<< a->pessoa.nome<<endl;
        cout<<"Nota: "<< a->pessoa.nota<<endl;
        percorrerPREOrdem(a->esq);
        percorrerPREOrdem(a->dir);
    }
}

void percorrerPOSOrdem(TNoh *&a){
    if(a!=NULL){
        percorrerPOSOrdem(a->esq);
        percorrerPOSOrdem(a->dir);
        cout<<"Nome: "<< a->pessoa.nome<<endl;
        cout<<"Nota: "<< a->pessoa.nota<<endl;
    }
}
void mostrarArvore(TArvore a){
    cout<< "Percorrer In Ordem: " <<endl;
    percorrerINOrdem(a.raiz);
    cout<< " "<<endl;
    cout<<"Percorrer Pré-ordem: " <<endl;
    percorrerPREOrdem(a.raiz);
    cout<< " "<<endl;
    cout <<"Percorrer Pós-ordem: "<<endl;
    percorrerPOSOrdem(a.raiz);
    cout<< " "<<endl;
}

void percorrerEmpilhar(TPilha &p,TNoh *&n){
    TPessoa aux;
    if (n!=NULL){
        percorrerEmpilhar(p,n->esq);
        if(n->pessoa.nota>=60){
            aux.nome = n->pessoa.nome;
            aux.idade = n->pessoa.idade;
            aux.nota = n->pessoa.nota;
            aux.numInsc = n->pessoa.numInsc;
            empilhar(aux,p);
        }
        percorrerEmpilhar(p,n->dir);
    }
}
void percorrerEmpilharReprov(TPilha &p,TNoh *&n){
    TPessoa aux;
    if (n!=NULL){
        percorrerEmpilharReprov(p,n->esq);
        if(n->pessoa.nota<60){
            aux.nome = n->pessoa.nome;
            aux.idade = n->pessoa.idade;
            aux.nota = n->pessoa.nota;
            aux.numInsc = n->pessoa.numInsc;
            empilhar(aux,p);
        }
        percorrerEmpilharReprov(p,n->dir);
    }
}

void percorrerInserir(TLista &l,TNoh *&n){
    TPessoa aux;
    if (n!=NULL){
        percorrerInserir(l,n->esq);
        if(n->pessoa.nota>=0){
            aux.nome = n->pessoa.nome;
            aux.idade = n->pessoa.idade;
            aux.nota = n->pessoa.nota;
            aux.numInsc = n->pessoa.numInsc;
            inserir(aux,l);
        }
        percorrerInserir(l,n->dir);
    }
}

void Menu (int opcao,TPessoa p,TPilha pilhaAprov,TPilha pilhaReprov,TArvore a,TLista lista){
       do{
            cout<<" " <<endl;
            cout<<"Menu de operações: "<<endl;
            cout<<"1- Criar Árvore vazia"<<endl;
            cout<<"2- Cadastrar pessoas na Árvore"<<endl;
            cout<<"3- Mostrar Árvore"<<endl;
            cout<<"4- Criar pilha vazia e transferir pessoas aprovadas da Árvore para Pilha"<<endl;
            cout<<"5- Mostrar Pilha de Candidatos Aprovados"<<endl;
            cout<<"6- Mostrar Pilha de Candidatos Reprovados"<<endl;
            cout<<"7- Mostrar Lista de todos os candidatos do concurso"<<endl;
            cout<< " "<<endl;
            cout<<"Digite a operação a ser realizada: ";
            cin>>opcao;
            switch(opcao){
            case 1:
                criarArvEmpty(a);
                cout<<"Árvore criada com sucesso!!!"<<endl;
            break;
            case 2:
                cadastrarCandidatos(a);
            break;
            case 3:
                mostrarArvore(a);
            break;
            case 4:
                criaPilhaVazia(pilhaAprov);
                percorrerEmpilhar(pilhaAprov,a.raiz);
                cout<<"Pessoas Aprovadas transferidas com sucesso!!"<<endl;
            break;
            case 5:
                cout<<"Candidatos aprovados no concurso: "<<endl;
                mostrarPilha(pilhaAprov);
            break;
            case 6:
                criaPilhaVazia(pilhaReprov);
                percorrerEmpilharReprov(pilhaReprov,a.raiz);
                cout<<"Pessoas Aprovadas transferidas com sucesso!!"<<endl;
                cout<<"Candidatos reprovados no concurso: "<<endl;
                mostrarPilha(pilhaReprov);
            break;
            case 7:
                criarLVazia(lista);
                percorrerInserir(lista,a.raiz);
                mostrarItensLista(lista);
            break;
            default:
                cout<<"Operação inválida,Digite um número de 1 à 7!"<<endl;
            break;
            }
        }while((opcao>0) &&(opcao!=7));
}


