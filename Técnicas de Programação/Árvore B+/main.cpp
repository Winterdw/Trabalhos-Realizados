//Bacharelado em Engenharia de Computação
//Técnicas de Programação - 2018/2
//
//Daniel Winter Santos Rocha
//RA: 0021760
//
//Harley Vitor Santana de Brito
//RA: 0022919
#include "libraries.h"
#include "b_tree.h"

int main(){
    setlocale(LC_ALL, "Portuguese");
    noh * root;
	int input;
	char instruction;
    int program = 10;
    int option  = 10;
    int numerator = 10;
    int denominator = 10;
    int fractionOption = 10;
    int index = 10;
    int index2 = 10;
    bool arc = 1;
    string buffer1;
    string buffer2;
    char* buf = new char[10];
    Archive<Node> archive;
    Node node;
    Registry<Node> registry;
    Registry<Node> registry2;
    Fraction* fraction = new Fraction[5];
    Fraction* fraction2 = new Fraction[5];
    Fraction  fraction3;
    ulint* child = new ulint[6];
    Fraction** hihi;


    while(program != 0){
        arc = 1;
        program = 10;
        option  = 10;
        numerator = 10;
        denominator = 10;
        fractionOption = 10;
        index = 10;
        cout << endl << endl << endl;
        cout << "\tEscolha um programa" << endl << endl;
        cout << "\t1 - Árvore B" << endl;
        cout << "\t2 - Arquivo em disco" << endl;
        cout << "\t-> ";
        cin >> program;
        system("clear");

        if(program == 1){
            root = NULL;
            while(option != 0){
                cout << endl << endl << endl;
                cout << "\tPrograma: Árvore B" << endl << endl;
                cout << "\t1 - Inserir chave" << endl;
                cout << "\t2 - Deletar chave" << endl;
                cout << "\t3 - Pesquisar registro" << endl;
                cout << "\t4 - Imprimir Árvore" << endl;
                cout << "\t0 - Menu Principal" << endl;
                cout << "\t-> ";
                cin >> option;
                system("clear");

                switch(option){
                    case 1:
                        cout << "\tChave -> ";
                        cin >> input;
                        root = Inserir(root, input, input);
                        cout << endl << endl << endl;
                        break;
                    case 2:
                        cout << "\tChave -> ";
                        cin >> input;
                        root = Deletar(root, input);
                        break;
                    case 3:
                        cout << "\tChave -> ";
                        cin >> input;
                        Encontrar_e_Mostrar(root, input, instruction == 'p');
                        break;
                    case 4:
                        Mostrar_Arvore(root);
                        break;
                }
            }
        }

        if(program == 2){
            while(option != 0){
                if(arc){
                    cout << endl << endl << endl;
                    cout << "\tNome do arquivo: ";
                    cin >> buffer1;
                    cout << "\tTipo: ";
                    cin >> buffer2;
                    cout << "\tVersão: ";
                    cin >> input;
                    system("clear");
                    cout << endl << endl << endl;
                    archive = Archive<Node>(buffer1.c_str(), buffer2.c_str(), input);
                    arc = 0;
                }


                cout << endl << endl << endl;
                cout << "\tPrograma: Arquivo em disco" << endl << endl;
                cout << "\t1 - Criar/Abrir arquivo" << endl;
                cout << "\t2 - Criar página" << endl;
                cout << "\t3 - Pesquisar página" << endl;
                cout << "\t4 - Deletar página" << endl;
                cout << "\t0 - Menu Principal" << endl;
                cout << "\t-> ";
                cin >> option;
                system("clear");

                switch(option){
                    case 1:
                        cout << endl << endl << endl;
                        cout << "\tNome do arquivo: ";
                        cin >> buffer1;
                        cout << "\tTipo: ";
                        cin >> buffer2;
                        cout << "\tVersão: ";
                        cin >> input;
                        system("clear");
                        cout << endl << endl << endl;
                        archive = Archive<Node>(buffer1.c_str(), buffer2.c_str(), input);
                        break;
                    case 2:
                        fractionOption = 10;
                        cout << endl << endl << endl;
                        input = 10;
                        fractionOption = 10;

                        while(input < 2 || input > 5){
                            cout << "\tQuantas frações deseja inserir na nova página: ";
                            cin >> input;

                            if(input < 2 || input > 5){
                                cout << endl << endl << endl;
                                cout << "\tEscolha entre duas ou cinco frações." << endl;
                            }
                        }

                        for(int i = 0; i < input; i++){
                            cout << endl << endl << endl;
                            cout << "\tFração " << i + 1 << ": Numerador\t-> ";
                            cin >> numerator;
                            cout << "\tFração " << i + 1 << ": Denominador\t-> ";
                            cin >> denominator;
                            fraction[i] = Fraction(numerator, denominator);
                        }

                        for(int i = 0; i < 6; i++){
                            child[i] = NULL_CONST;
                        }

                        node = Node(input, fraction, child, NULL_CONST);
                        system("clear");

                        while(fractionOption != 0){
                            cout << endl << endl << endl;
                            cout << "\tEdição de página" << endl << endl;
                            cout << "\t1 - Inserir fração" << endl;
                            cout << "\t2 - Mudar fração" << endl;
                            cout << "\t3 - Apagar fração" << endl;
                            cout << "\t4 - Imprimir página" << endl;
                            cout << "\t5 - Inserir página em disco" << endl;
                            cout << "\t0 - Apagar página" << endl;
                            cout << "\t-> ";
                            cin >> fractionOption;
                            system("clear");

                            switch(fractionOption){
                                case 1:
                                    cout << endl << endl << endl;
                                    cout << "\tNumerador\t-> ";
                                    cin >> numerator;
                                    cout << "\tDenominador\t-> ";
                                    cin >> denominator;
                                    fraction3 = Fraction(numerator, denominator);

                                    if(!node.Insert(fraction3, 6)){
                                        cout << endl << endl << endl;
                                        cout << "\tPágina está cheia" << endl;
                                    }else{
                                        cout << endl << endl << endl;
                                        cout << "\tFração inserida" << endl;
                                    }
                                    fraction2 = node.GetFraction();
                                    cout << endl << endl << endl;
                                    cout << "\tPágina" << endl << endl;
                                    for(int i = 0; i < node.GetAmount(); i++){
                                        cout << "\t" << fraction2[i].GetNumerator() << "\\" << fraction2[i].GetDenominator() << "\t";
                                    }
                                    break;
                                case 2:
                                    cout << endl << endl << endl;
                                    cout << "\tNumerador\t-> ";
                                    cin >> numerator;
                                    cout << "\tDenominador\t-> ";
                                    cin >> denominator;
                                    cout << "\tÍndice\t\t-> ";
                                    cin >> index;
                                    fraction3 = Fraction(numerator, denominator);
                                    node.SetFractionByIndex(fraction3, index);
                                    cout << endl << endl << endl;
                                    cout << "\tFração de índice " << index << " modificada" << endl;
                                    fraction2 = node.GetFraction();
                                    cout << endl << endl << endl;
                                    cout << "\tPágina" << endl << endl;
                                    for(int i = 0; i < node.GetAmount(); i++){
                                        cout << "\t" << fraction2[i].GetNumerator() << "\\" << fraction2[i].GetDenominator() << "\t";
                                    }
                                    break;
                                case 3:
                                    cout << endl << endl << endl;
                                    cout << "\tÍndice -> ";
                                    cin >> index;
                                    if(!node.Remove(index)){
                                        cout << endl << endl << endl;
                                        cout << "\tPágina está com quantidade mínima de elementos." << endl;
                                    }else{
                                        cout << endl << endl << endl;
                                        cout << "\tFração deletada." << endl;
                                    }
                                    fraction2 = node.GetFraction();
                                    cout << endl << endl << endl;
                                    cout << "\tPágina" << endl << endl;
                                    for(int i = 0; i < node.GetAmount(); i++){
                                        cout << "\t" << fraction2[i].GetNumerator() << "\\" << fraction2[i].GetDenominator() << "\t";
                                    }
                                    break;
                                case 4:
                                    fraction2 = node.GetFraction();
                                    cout << endl << endl << endl;
                                    cout << "\tPágina" << endl << endl;
                                    for(int i = 0; i < node.GetAmount(); i++){
                                        cout << "\t" << fraction2[i].GetNumerator() << "\\" << fraction2[i].GetDenominator() << "\t";
                                    }
                                    break;
                                case 5:
                                    cout << endl << endl << endl;
                                    registry.SetData(node);
                                    archive.InsertRegistry(registry);
                                    break;
                            }
                        }
                        break;
                    case 3:
                        fractionOption = 10;
                        cout << endl << endl << endl;
                        cout << "\tÍndice do arquivo -> ";
                        cin >> index2;
                        cout << endl << endl << endl;
                        registry2.FromString(archive.ReadRegistry(index2));
                        buf = archive.ReadRegistry(index2);

                        if(registry2.IsValid() && (buf != "zz")){
                            while(fractionOption != 0){
                                cout << endl << endl << endl;
                                cout << "\tEdição de página" << endl << endl;
                                cout << "\t1 - Inserir fração" << endl;
                                cout << "\t2 - Mudar fração" << endl;
                                cout << "\t3 - Apagar fração" << endl;
                                cout << "\t4 - Imprimir página" << endl;
                                cout << "\t5 - Inserir página em disco" << endl;
                                cout << "\t0 - Apagar página" << endl;
                                cout << "\t-> ";
                                cin >> fractionOption;
                                system("clear");

                                switch(fractionOption){
                                    case 1:
                                        cout << endl << endl << endl;
                                        cout << "\tNumerador\t-> ";
                                        cin >> numerator;
                                        cout << "\tDenominador\t-> ";
                                        cin >> denominator;
                                        fraction3 = Fraction(numerator, denominator);

                                        if(!node.Insert(fraction3, 6)){
                                            cout << endl << endl << endl;
                                            cout << "\tPágina está cheia" << endl;
                                        }else{
                                            cout << endl << endl << endl;
                                            cout << "\tFração inserida" << endl;
                                        }
                                        fraction2 = node.GetFraction();
                                        cout << endl << endl << endl;
                                        cout << "\tPágina" << endl << endl;
                                        for(int i = 0; i < node.GetAmount(); i++){
                                            cout << "\t" << fraction2[i].GetNumerator() << "\\" << fraction2[i].GetDenominator() << "\t";
                                        }
                                        break;
                                    case 2:
                                        cout << endl << endl << endl;
                                        cout << "\tNumerador\t-> ";
                                        cin >> numerator;
                                        cout << "\tDenominador\t-> ";
                                        cin >> denominator;
                                        cout << "\tÍndice\t\t-> ";
                                        cin >> index;
                                        fraction3 = Fraction(numerator, denominator);
                                        node.SetFractionByIndex(fraction3, index);
                                        cout << endl << endl << endl;
                                        cout << "\tFração de índice " << index << " modificada" << endl;
                                        fraction2 = node.GetFraction();
                                        cout << endl << endl << endl;
                                        cout << "\tPágina" << endl << endl;
                                        for(int i = 0; i < node.GetAmount(); i++){
                                            cout << "\t" << fraction2[i].GetNumerator() << "\\" << fraction2[i].GetDenominator() << "\t";
                                        }
                                        break;
                                    case 3:
                                        cout << endl << endl << endl;
                                        cout << "\tÍndice -> ";
                                        cin >> index;
                                        if(!node.Remove(index)){
                                            cout << endl << endl << endl;
                                            cout << "\tPágina está com quantidade mínima de elementos." << endl;
                                        }else{
                                            cout << endl << endl << endl;
                                            cout << "\tFração deletada." << endl;
                                        }
                                        fraction2 = node.GetFraction();
                                        cout << endl << endl << endl;
                                        cout << "\tPágina" << endl << endl;
                                        for(int i = 0; i < node.GetAmount(); i++){
                                            cout << "\t" << fraction2[i].GetNumerator() << "\\" << fraction2[i].GetDenominator() << "\t";
                                        }
                                        break;
                                    case 4:
                                        fraction2 = node.GetFraction();
                                        cout << endl << endl << endl;
                                        cout << "\tPágina" << endl << endl;
                                        for(int i = 0; i < node.GetAmount(); i++){
                                            cout << "\t" << fraction2[i].GetNumerator() << "\\" << fraction2[i].GetDenominator() << "\t";
                                        }
                                        break;
                                    case 5:
                                        cout << endl << endl << endl;
                                        registry.SetData(node);
                                        archive.WriteRegistry(index2, registry);
                                        break;
                                }
                            }
                        }else{
                            cout << endl << endl << endl;
                            cout << "\tO registro não é válido" << endl;
                        }
                        break;

                        case 4:
                            cout << endl << endl << endl;
                            cout << "\tÍndice do arquivo -> ";
                            cin >> index2;
                            cout << endl << endl << endl;
                            archive.DeleteRegistry(index2);
                            break;
                    }
                }
            }
        }



    return 0 ;
}
