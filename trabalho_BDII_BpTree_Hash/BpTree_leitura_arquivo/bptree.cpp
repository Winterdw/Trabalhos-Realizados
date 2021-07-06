/*
 *
 * +----------------------------------------+
 * |                                        |
 * | Engenharia de Computação.              |
 * | Banco de Dados II.                     |
 * | Implementação da B+Tree em C++.        |
 * |                                        |
 * +----------------------------------------+
 * |                                        |
 * | Daniel Winter Santos Rocha.            |
 * | RA: 0021760.                           |
 * |                                        |
 * +----------------------------------------+
 * |                                        |
 * | Rodrigo Matheus Rodrigues de Oliveira. |
 * | RA: 0011647.                           |
 * |                                        |
 * +----------------------------------------+
 *
 */

#include <iostream>
#include <list>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define DEFAULT_ORDER 4
#define MIN_ORDER 2
#define MAX_ORDER 20
#include "exibicao.h"
#include "insercao.h"
#include "remocao.h"

int main(){
    setlocale(LC_ALL, "Portuguese");

    noh * root;
	int input, range2;
	root = NULL;
	list<int> lista;

	/*
	 * INÍCIO LEITURA DO ARQUIVO.
	 */

    string arquivo_ler;
    cout<<"arquivo.txt a ser lido: ";
    cin>>arquivo_ler;

    ifstream data_in;
    string i;
    data_in.open(arquivo_ler);
    cout<<"LENDO ARQUIVO."<<endl;
    do{
        data_in>>i;
        if(i=="+"){
            data_in>>i;
            input=atoi(i.c_str());
            for(int a=0; a<9; a++){
                data_in>>i;
                lista.push_back(atoi(i.c_str()));
            }
            //cout<<"INSERINDO "<<input<<"."<<endl;
            root=Inserir(root, input, input);
            //cout<<"i: "<<i<<endl<<"input: "<<input<<endl;
            //Mostrar_Arvore(root);
        }

        if(i=="-"){
            data_in>>i;
            input=atoi(i.c_str());
            for(int a=0; a<9; a++){
                data_in>>i;
            }
            //cout<<"DELETANDO "<<input<<"."<<endl;
            root=Deletar(root, input);
			//Mostrar_Arvore(root);
        }

       // cout<<endl<<"-------------------------------------------------------"<<endl;
    }while(!data_in.eof() && data_in.good());
    data_in.close();

	/*
	 * INÍCIO DO SISTEMA DE MENU.
	 */

	char instruction;
	cout<<endl<<" > ";
	while (scanf("%c", &instruction)!=EOF){
		switch (instruction) {
		case 'd':
			cin>>input;
			root = Deletar(root, input);
			Mostrar_Arvore(root);
			break;
		case 'i':
			cin>>input;
			root = Inserir(root, input, input);
			Mostrar_Arvore(root);
			break;
		case 'f':
			cin>>input;
			Encontrar_e_Mostrar(root, input, instruction == 'p');
			break;
		case 'r':
			cin>>input>>range2;
			if (input > range2) {
				int tmp = range2;
				range2 = input;
				input = tmp;
			}
			Encontrar_e_mostrar_alcance(root, input, range2, instruction == 'p');
			break;
		case 'q':
			while (getchar()!=(int)'\n');
			return EXIT_SUCCESS;
			break;
		case 't':
			Mostrar_Arvore(root);
			break;
		default:
			uso();
			break;
		}
		while (getchar()!=(int)'\n');
		cout<<endl<<" > ";
	}
	cout<<endl;
    return EXIT_SUCCESS;

}

