#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

vector<vector<int>>CriaMatrizAdj(const int n){

    vector<vector<int>>matrizAdj;
    // inicializa a matriz toda em 0.
    for(int i=0;i<n;i++){
        vector<int>linha;
        matrizAdj.push_back(linha);
        for(int j=0;j<n;j++){
            matrizAdj[i].push_back(0);
        }
    }

    matrizAdj[0][1]= 1;
    matrizAdj[0][2]= 2;
    matrizAdj[1][2]= 4;
    matrizAdj[1][3]= 5;
    matrizAdj[2][1]= 6;
    matrizAdj[2][4]= 7;
    matrizAdj[3][2]= 8;
    matrizAdj[3][5]= 9;
    matrizAdj[4][3]= 10;
    matrizAdj[4][5]= 11;
    return matrizAdj;
}
//Aqui,foi implementado a busca em largura para verificar se o caminho é valido
//Verifica se o sorvedouro foi visitado.
bool BFS(vector<vector<int>>&resmatrizAdj,int &origem,int &sorvedouro,vector<int>&pai){
    int n=resmatrizAdj.size();
    bool visitado[n]={false};
    //Cria uma lista para verificar cada nó
    queue<int>q;
    //Pega a origem e coloca ela na fila marcando ela como visitada com o pai = -1.
    q.push(origem);
    visitado[origem]=true;
    pai[origem]=-1;
    //Faz a busca através dos vértices.
    while(q.empty()==false){
        int u=q.front();
        q.pop();
        //Percorrendo todos os vizinhos.
        for(int i=0;i<n;i++){
            int v=i;
            int capacidade=resmatrizAdj[u][v];
            if(visitado[v]==false &&capacidade>0){
                q.push(v);
                pai[v]=u;
                visitado[v]=true;
            }
        }
    }
    // If the sorvedouro got visitado, then we found a path to it.
    if(visitado[sorvedouro] == true){
            return true;
    }else{
        return false;
    }
}
// Finalmente o Ford Fulkerson para retornar o fluxo máximo.
int FordFulkerson(vector<vector<int>>&matrizAdj,int &origem,int &sorvedouro){
    int fluxomax=0;
    vector<vector<int>>vetmatrizAdj;
    int n=matrizAdj.size();
    for(int i=0;i< n;i++){
        vector<int> linha;
        vetmatrizAdj.push_back(linha);
        for(int j=0;j<matrizAdj[i].size();j++){
            vetmatrizAdj[i].push_back(matrizAdj[i][j]);
        }
    }
    vector<int>pai;
    for(int i=0;i<n;i++){
        pai.push_back(-1);
    }
    while(BFS(vetmatrizAdj,origem,sorvedouro,pai)==true){
        //checa o fluxo máximo através do caminho que foi retornado.
        int caminho = 99999999;
        int v=sorvedouro;
        while(v!=origem){
            int u=pai[v];
            // Atualiza o caminho para a capacidade se ela for menor que a inicial.
            int capacidade=vetmatrizAdj[u][v];
            caminho=min(caminho, capacidade);
            v=u;
        }
        v=sorvedouro;
        while(v!=origem){
            int u=pai[v];
            vetmatrizAdj[u][v]-=caminho;
            vetmatrizAdj[v][u]+=caminho;
            v=u;
        }
        fluxomax += caminho;
    }
    return fluxomax;
}

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "Portuguese");
    fstream arquivo;
    string arquivo_nome=argv[1];
    int origem=(int)argv[2];
    int sorvedouro=(int)argv[3];
    cout<<"Insira o nome do arquivo: ";
    cin>>arquivo_nome;
    float v1,v2;
    double peso;
    int numero_arestas=0;
    int numero_vertices=0;
    //Cria a lista de adjacência
    vector<vector<int>>matrizAdj=CriaMatrizAdj(numero_vertices);
    arquivo.open(arquivo_nome.c_str());
    if(arquivo.good()){

        //Declaração de todas as variáveis para armazenar vértices,o numero de arestas,e os pesos
        arquivo>>numero_vertices; //O primeiro valor do txt será armazenado aqui,para saber o número de vértices
        do{
            arquivo>>v1;
            arquivo>>peso;
            arquivo>>v2;
            numero_arestas++;
            matrizAdj[v1][v2]=peso;
        }while(!arquivo.eof()&&arquivo.good());
        arquivo.close();
        cout<<"Vértices: "<<numero_vertices<<" e Arestas: "<<numero_arestas<<endl;
    }

//Faz a chamada do Ford Fulkerson
        for(int i=0;i<numero_vertices;i++){
        for(int j=0;j<numero_vertices;j++){
            int origem=i;
            int sorvedouro=j;
            if(i==j){
                //apenas uma verificação para saber se chegou ao destino.
                continue;
            }
            cout<<"O fluxo máximo da origem: " <<origem << " até o sorvedouro " << sorvedouro << " é de: "<<FordFulkerson(matrizAdj,origem,sorvedouro)<< endl;

        }
    }

    cout << "Fim da execução."<<endl;
    return 0;
}
