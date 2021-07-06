/*Aluno:Daniel Winter Santos Rocha
N�mero de matr�cula:0021760  */

#include <iostream>
#include<cstdlib>
#include<time.h>

using namespace std;

//Vari�veis usadas para armazenar valores necess�rios das fun��es que irei precisar.

int PessoasV,PessoasB,PessoasA,PessoasZ,Gold=0;

//Primeiro,devo criar matrizes vazias representando as arquibancadas do est�dio.

void CriarMatrizVazia(int m[10][100]){
    for(int l=0;l<10;l++){
            for(int c=0;c<100;c++ ){
                m[l][c]=0;
        }
    }
}
//Ap�s a cria��o das matrizes,usei a fun��o rand para representar com 0=a cadeira estando vazia e com 1=a cadeira cheia para servir de dados de entrada.

void PreencherMatrizes(int m[10][100]){
        for(int l=0;l<10;l++){
            for(int c=0;c<100;c++){
                m[l][c]=rand()%2 ;
        }
    }
}
//A matriz criada ser� mostrada com as cadeiras vazias e as cheias.
void MostrarMatrizes(int m[10][100]){
    srand(time(NULL));
    for(int l=0;l<10;l++){
            for(int c=0;c<100;c++){
               cout<<m[l][c]<<" ";
        }
            cout<<endl;
    }
    cout<<"\n"<<endl;
}
/*A partir daqui,esta criei uma fun��o para cada arquibancada que,contasse a quantidades de pessoas em cada arquibancada
guardando ela dentro de uma vari�vel declarada no in�cio do c�digo. */

 void QuantiaPessoasmVerde (int m[10][100]){
    int auxV=0;
    for(int l=0;l<10;l++){
        for(int c=0;c<100;c++){
            if(m[l][c]==1){
                auxV+=+1;
            }
        }
    }
    cout<<"Existem "<<auxV<<"  pessoas na arquibancada verde. "<<endl;
    PessoasV=auxV;
}
 void QuantiaPessoasmBranca (int m[10][100]){
    int auxB=0;
    for(int l=0;l<10;l++){
        for(int c=0;c<100;c++){
            if(m[l][c]==1){
                auxB+=+1;
            }
        }
    }
    cout<<"Existem "<<auxB<<"  pessoas na arquibancada branca. "<<endl;
    PessoasB=auxB;
}
 void QuantiaPessoasmAmarela (int m[10][100]){
    int auxA=0;
    for(int l=0;l<10;l++){
        for(int c=0;c<100;c++){
            if(m[l][c]==1){
                auxA+=+1;
            }
        }
    }
    cout<<"Existem "<<auxA<<"  pessoas na arquibancada amarela. "<<endl;
    PessoasA=auxA;

}

 void QuantiaPessoasmaZul (int m[10][100]){
    int auxZ=0;
    for(int l=0;l<10;l++){
        for(int c=0;c<100;c++){
            if(m[l][c]==1){
                auxZ+=+1;
            }
        }
    }
    cout<<"Existem "<<auxZ<<"  pessoas na arquibancada azul. "<<endl;
    PessoasZ=auxZ;
}
/*A fun��o abaixo tem a finalidade de comaprar o setor mais lotado atrav�s das compara��es das vari�veis declaradas e armazenadas
nas fun��es acima. */

void SetorMaisLotado(int PessoasV,int PessoasB,int PessoasA,int PessoasZ){
        if(PessoasV>PessoasB&&PessoasV>PessoasA&&PessoasV>PessoasZ){
        cout<<"O setor mais cheio � o setor verde com:"<<PessoasV<<" pessoas."<<endl;
        }else{
            if(PessoasV>PessoasB&&PessoasV>PessoasA&&PessoasV<PessoasZ){
                cout<<"O setor mais cheio � o setor azul com:"<<PessoasZ<<" pessoas."<<endl;
            }else{
                if((PessoasV>PessoasB&&PessoasV<PessoasA)&&PessoasA>PessoasZ ){
                    cout<<"O setor mais cheio � o setor amarelo com:"<<PessoasA<<" pessoas."<<endl;
                }else{
                    if((PessoasV<PessoasB)&&PessoasB>PessoasA&&PessoasB>PessoasZ){
                    cout<<"O setor mais cheio � o setor branco com:"<<PessoasB<<" pessoas."<<endl;
                }
            }
        }
    }
}

//Fun��o usada para definir qual a fileira mais lotada de cada arquibancada.
void fileiraLotada(int m[10][100]){
    int fila=0;
    int aux=0;
    int fileira=0;
    for(int l=0;l<1;l++){
    for(int c=0;c<100;c++){
    fileira+=m[l][c];
    fila=fileira;
        }
    }
        if(aux>fila){
        cout<<aux<<endl;

        }else{
        cout<<fila<<endl;
        aux=fila;
        }
}

int main(){
setlocale(LC_ALL, "Portuguese");
  srand(time(NULL));
  int maZul[10][100];
  int mBranca[10][100];
  int mAmarela[10][100];
  int mVerde[10][100] ;
  int opcao;

/*Criei um "menu",para ordena��o dos passos para tudo ocorrer corretamente,sendo de total importancia seguir a sequ�ncia num�rica
para tudo ocorrer corretamente.A maioria dos "cout<<" "<<endl",utilizados abaixo,foram usados para dar uma melhor clareza na caixa preta.*/

   do{
            cout<<" "<<endl;
            cout<< "---------------------------------------" << endl;
            cout<<"Por favor,seguir a ordem num�rica para compreens�o do c�digo:"<<endl;
            cout<<" "<<endl;
            cout<<"1-Criar Matrizes Vazias" <<endl;
            cout<<"2-Preencher matrizes" <<endl;
            cout<<"3-Mostrar matrizes" <<endl;
            cout<<"4-Quantidade de pessoas no setor e setor mais lotado" <<endl;
            cout<<"5-Arrecada��o do jogo " <<endl;
            cout<<"6-Fila mais cheia " <<endl;
            cin>>opcao;
            switch(opcao){
            case 1:
                cout<<" "<<endl;
                CriarMatrizVazia(maZul);
                CriarMatrizVazia(mBranca);
                CriarMatrizVazia(mAmarela);
                CriarMatrizVazia(mVerde);
                cout<< "  "<<endl;
                cout<<" Matrizes vazias criadas com sucesso"<<endl;

            break;
            case 2:
                cout<<" "<<endl;
                PreencherMatrizes(maZul);
                PreencherMatrizes(mBranca);
                PreencherMatrizes(mAmarela);
                PreencherMatrizes(mVerde);
                cout<<"  "<<endl;
                cout<<"Matrizes preenchidas com sucesso"<<endl;

            break;
            case 3:
                cout<<" "<<endl;
                cout<<"Matriz azul"<<endl;
                cout<<"  " <<endl;
                MostrarMatrizes(maZul);
                cout<<"Matriz branca"<<endl;
                cout<<"  " <<endl;
                MostrarMatrizes(mBranca);
                cout<<"  " <<endl;
                cout<<"Matriz amarela"<<endl;
                cout<<"  " <<endl;
                MostrarMatrizes(mAmarela);
                cout<<"Matriz verde"<<endl;
                cout<<"  " <<endl;
                MostrarMatrizes(mVerde);
            break;
            case 4:
                cout<<" "<<endl;
                QuantiaPessoasmVerde(mVerde);
                QuantiaPessoasmBranca(mBranca);
                QuantiaPessoasmAmarela(mAmarela);
                QuantiaPessoasmaZul(maZul);
                cout<<" "<<endl;
                SetorMaisLotado(PessoasV,PessoasB,PessoasA,PessoasZ);
            break;
            case 5:
                cout<<" "<<endl;
                Gold=(PessoasV+PessoasB)*35;
                Gold+=(PessoasA+PessoasZ)*20;

                cout<<"A arrecada��o do jogo foi de:R$"<<Gold<<",00 reais."<< endl;

            break;
            case 6:
                cout<<" "<<endl;
                cout<<"Fileira do setor verde"<<endl;
                fileiraLotada(mVerde);
                cout<<"Fileira do setor branca"<<endl;
                fileiraLotada(mBranca);
                cout<<"Fileira do setor amarela"<<endl;
                fileiraLotada(mAmarela);
                cout<<"Fileira do setor azul"<<endl;
                fileiraLotada(maZul);


            break;
            default:
                cout<<"Op��o Inv�lida!"<< endl;
            break;
            }
        }while((opcao>0)&&(opcao!=6));

        return 0;


}
