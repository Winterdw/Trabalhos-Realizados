#include "libraries.h"

Node::Node(){
    this->SetAmount(0);
    this->SetFraction(new Fraction[5]);
    this->SetChild(new ulint[6]);
    this->SetIndex(0);
}

Node::Node(int _amount, Fraction *_fraction, ulint *_child, ulint _index){
    this->SetAmount(_amount);
    this->SetFraction(_fraction);
    this->SetChild(_child);
    this->SetIndex(_index);
}

Node::Node(const Node &_node){
    this->SetAmount(_node.GetAmount());
    this->SetFraction(_node.GetFraction());
    this->SetChild(_node.GetChild());
    this->SetIndex(_node.GetIndex());
}

void Node:: operator = (const Node &_node){
    this->SetAmount(_node.GetAmount());
    this->SetFraction(new Fraction[5]);
    this->SetChild(new ulint[5]);
    this->SetIndex(_node.GetIndex());
    this->SetFraction(_node.GetFraction());
    this->SetChild(_node.GetChild());
    this->fractionAdress = &this->fraction;
    this->childAdress = &this->child;
}

void Node::SetAmount(int _amount){
    this->amount = _amount;
}

void Node::SetFraction(Fraction *_fraction){
    this->fraction = _fraction;
}

void Node::SetFractionByIndex(Fraction _fraction, int _index){
    this->fraction[_index] = _fraction;
}

void Node::SetChild(ulint *_child){
    this->child = _child;
}

void Node::SetChildByIndex(ulint _child, int _index){
    this->child[_index] = _child;
}

void Node::SetIndex(ulint _index){
    this->index = _index;
}

int Node::GetAmount() const{
    return this->amount;
}

Fraction* Node::GetFraction() const{
    return &this->fraction[0];
}

Fraction Node::GetFractionByIndex(int _index) const{
    return this->fraction[_index];
}

ulint* Node::GetChild() const{
    return &this->child[0];
}

ulint Node::GetChildByIndex(int _index) const{
    return this->child[_index];
}

ulint Node::GetIndex() const{
    return this->index;
}

//Função responsável por inserir elementos no nó, recebe como parâmetros a fração a ser inserida e o grau máximo de
//sua árvore.
bool Node::Insert(Fraction _fraction, int _length){
    //Se a quantidade máxima ainda não foi atingida.
    if(this->GetAmount() < _length - 1){
        //Atribui a nova fração a uma posição do nó.
        this->SetFractionByIndex(_fraction, this->GetAmount());
        //Aumenta em 1 a quantidade de elementos.
        this->SetAmount(this->GetAmount() + 1);
        return true;
    }else{
        return false;
    }
}

bool Node::Remove(int _index){
    Fraction aux;
    if(this->GetAmount() != 2){
        if(_index == 4){
            this->SetAmount(this->GetAmount() - 1);
        }else{
            for(int i = _index; i < this->GetAmount(); i++){
                this->SetFractionByIndex(this->GetFractionByIndex(i + 1), i);
            }

            this->SetAmount(this->GetAmount() - 1);
        }
        return true;
    }else{
        return false;
    }
}

//Essa função é responsável por construir um nó a partir de uma cadeia de caracteres.
void Node::FromString(char* _string){
    //A string "buffer1" será responsável por receber temporariamente as frações serializadas, os índices dos filhos
    //e o seu próprio índice. "buffer2" será responsável por receber a quantidade atual de elementos e "aux1" por
    //receber temporariamente as frações construídas a partir de cadeia de caracteres.
    char* buffer1 = new char[9];
    char* buffer2 = new char[5];
    this->SetFraction(new Fraction[5]);
    this->SetChild(new ulint[6]);
    Fraction aux1;

    //Garantimos que os "buffers" não tenham lixo de memória.
    for(int i = 0; i < 9; i++){
        buffer1[i] = '\0';

        if(i < 5){
            buffer2[i] = '\0';
        }
    }

    //Atribuimos os quatro primeiros bytes correspondentes de "amount" da cadeia ao "buffer2".
    for(int i = 0; i < 4; i++){
        buffer2[i] = _string[i];
    }

    //Reinterpreta os bytes lidos de "amount" e atribui no objeto seu valor.
    this->SetAmount(*reinterpret_cast<int*>(buffer2));

    //Limpa "buffer2".
    for(int i  = 0; i < 5; i++){
        buffer2[i] = '\0';
    }

    //Esse "for" é responsável por realizar os procedimentos de leitura das frações.
    for(int i = 0; i < 5; i++){
        //Se for a primeira fração a ser lida, lê os próximos oito bytes e o atribui à sua respectiva posição no nó.
        if(i == 0){
            for(int j = 4; j < 12; j++){
                buffer1[j - 4] = _string[j];
            }
            aux1.FromString(buffer1);
            this->SetFractionByIndex(aux1, i);
        }

        //Se for a segunda fração a ser lida, lê os próximos oito bytes e o atribui à sua respectiva posição no nó.
        if(i == 1){
            for(int j = 12; j < 20; j++){
                buffer1[j - 12] = _string[j];
            }
            aux1.FromString(buffer1);
            this->SetFractionByIndex(aux1, i);
        }

        //Se for a terceira fração a ser lida, lê os próximos oito bytes e o atribui à sua respectiva posição no nó.
        if(i == 2){
            for(int j = 20; j < 28; j++){
                buffer1[j - 20] = _string[j];
            }
            aux1.FromString(buffer1);
            this->SetFractionByIndex(aux1, i);
        }

        //Se for a quarta fração a ser lida, lê os próximos oito bytes e o atribui à sua respectiva posição no nó.
        if(i == 3){
            for(int j = 28; j < 36; j++){
                buffer1[j - 28] = _string[j];
            }
            aux1.FromString(buffer1);
            this->SetFractionByIndex(aux1, i);
        }

        //Se for a quinta fração a ser lida, lê os próximos oito bytes e o atribui à sua respectiva posição no nó.
        if(i == 4){
            for(int j = 36; j < 44; j++){
                buffer1[j - 36] = _string[j];
            }
            aux1.FromString(buffer1);
            this->SetFractionByIndex(aux1, i);
        }
    }

    //Limpa "buffer1".
    for(int i = 0; i < 9; i++){
        buffer1[i] = '\0';
    }

    //Esse "for" é responsável pelos procedimentos de leitura dos índices do filhos da cadeia.
    for(int i = 0; i < 6; i++){

        //Se for o primeiro índice a ser lido, lê os próximos oito bytes, os reinterpreta e atribui a uma posição de "child".
        if(i == 0){
            for(int j = 44; j < 52; j++){
                buffer1[j - 44] = _string[j];
            }
            this->SetChildByIndex(*reinterpret_cast<ulint*>(buffer1), i);
        }

        //Se for o segundo índice a ser lido, lê os próximos oito bytes, os reinterpreta e atribui a uma posição de "child".
        if(i == 1){
            for(int j = 52; j < 60; j++){
                buffer1[j - 52] = _string[j];
            }
            this->SetChildByIndex(*reinterpret_cast<ulint*>(buffer1), i);
        }

        //Se for o terceiro índice a ser lido, lê os próximos oito bytes, os reinterpreta e atribui a uma posição de "child".
        if(i == 2){
            for(int j = 60; j < 68; j++){
                buffer1[j - 60] = _string[j];
            }
            this->SetChildByIndex(*reinterpret_cast<ulint*>(buffer1), i);
        }

        //Se for o quarto índice a ser lido, lê os próximos oito bytes, os reinterpreta e atribui a uma posição de "child".
        if(i == 3){
            for(int j = 68; j < 76; j++){
                buffer1[j - 68] = _string[j];
            }
            this->SetChildByIndex(*reinterpret_cast<ulint*>(buffer1), i);
        }

        //Se for o quinto índice a ser lido, lê os próximos oito bytes, os reinterpreta e atribui a uma posição de "child".
        if(i == 4){
            for(int j = 76; j < 84; j++){
                buffer1[j - 76] = _string[j];
            }
            this->SetChildByIndex(*reinterpret_cast<ulint*>(buffer1), i);
        }

        //Se for o sexto índice a ser lido, lê os próximos oito bytes, os reinterpreta e atribui a uma posição de "child".
        if(i == 5){
            for(int j = 84; j < 92; j++){
                buffer1[j - 84] = _string[j];
            }
            this->SetChildByIndex(*reinterpret_cast<ulint*>(buffer1), i);
        }
    }

    //Limpa "buffer1".
    for(int i = 0; i < 9; i++){
        buffer1[i] = '\0';
    }

    //Lê os últimos oito bytes da cadeia de caracteres.
    for(int i = 92; i < 100; i++){
        buffer1[i - 92] = _string[i];
    }

    //Reinterpreta o valor lido e o atribui à "index".
    this->SetIndex(*reinterpret_cast<ulint*>(buffer1));
}

//Essa função é responsável por serializar um nó
char* Node::ToString(){
    //A string "buffer1" será responsável por receber o nó serializado, enquanto que "buffer2" é responsável por receber
    //"amount" reinterpretado e buffer3 por receber as frações e os índices dos filhos reinterpretados. "aux1" é respon
    //sável por receber "amount", "aux2" por receber os índices dos filhos e o seu próprio índice e "aux3" por receber
    //uma fração.
    char*       buffer1 = new char[101];
    char*       buffer2 = new char[5];
    char*       buffer3 = new char[9];
    int         aux1 = 0;
    ulint       aux2 = 0;
    Fraction    aux3;

    //Antes garantimos que não haja lixo de memória nos "buffers".
    for(int i = 0; i < 100; i++){
        buffer1[i] = '\0';

        if(i < 5){
            buffer2[i] = '\0';
        }

        if(i < 9){
            buffer3[i] = '\0';
        }
    }

    //Copia o valor de "amount" para "aux1".
    aux1 = this->GetAmount();

    //Copia o valor de "amount" reinterpretado para "buffer2".
    buffer2 = reinterpret_cast<char*>(&aux1);

    //Copia o valor de "amount" reinterpretado para os primeiros quatro bytes do nó serializado.
    for(int i = 0; i < 4; i++){
        buffer1[i] = buffer2[i];
    }

    //Esse "for" reúne os procedimentos para a serialiação das frações.
    for(int i = 0; i < 5; i++){
        //Copia a fração de índice "i" para "aux3".
        aux3 = this->GetFractionByIndex(i);

        //Copia a fração serializada para "buffer3".
        buffer3 = aux3.ToString();

        //Se for a primeira fração a ser serializada, copie-a para os próximos oito bytes do nó serializado.
        if(i == 0){
            for(int j = 4; j < 12; j++){
                buffer1[j] = buffer3[j - 4];
            }
        }

        //Se for a segunda fração a ser serializada, copie-a para os próximos oito bytes do nó serializado.
        if(i == 1){
            for(int j = 12; j < 20; j++){
                buffer1[j] = buffer3[j - 12];
            }
        }

        //Se for a terceira fração a ser serializada, copie-a para os próximos oito bytes do nó serializado.
        if(i == 2){
            for(int j = 20; j < 28; j++){
                buffer1[j] = buffer3[j - 20];
            }
        }

        //Se for a quarta fração a ser serializada, copie-a para os próximos oito bytes do nó serializado.
        if(i == 3){
            for(int j = 28; j < 36; j++){
                buffer1[j] = buffer3[j - 28];
            }
        }


        //Se for a quinta fração a ser serializada, copie-a para os próximos oito bytes do nó serializado.
        if(i == 4){
            for(int j = 36; j < 44; j++){
                buffer1[j] = buffer3[j - 36];
            }
        }
    }

    //Esse "for" reúne os procedimentos para a serialização dos índices dos filhos.
    for(int i = 0; i < 6; i++){
        //Limpa a string "buffer3".
        for(int j = 0; j < 9; j++){
            buffer3[j] = '\0';
        }

        //Copia o índice do filho de índice "i" para "aux2".
        aux2 = this->GetChildByIndex(i);

        //Copia o índice do filho reinterpretado para "buffer3".
        buffer3 = reinterpret_cast<char*>(&aux2);

        //Se for o primeiro índice a ser serializado, copie-o para os próximos oito bytes do nó serializado.
        if(i == 0){
            for(int k = 44; k < 52; k++){
                buffer1[k] = buffer3[k - 44];
            }
        }

        //Se for o segundo índice a ser serializado, copie-o para os próximos oito bytes do nó serializado.
        if(i == 1){
            for(int k = 52; k < 60; k++){
                buffer1[k] = buffer3[k - 52];
            }
        }

        //Se for o terceiro índice a ser serializado, copie-o para os próximos oito bytes do nó serializado.
        if(i == 2){
            for(int k = 60; k < 68; k++){
                buffer1[k] = buffer3[k - 60];
            }
        }

        //Se for o quarto índice a ser serializado, copie-o para os próximos oito bytes do nó serializado.
        if(i == 3){
            for(int k = 68; k < 76; k++){
                buffer1[k] = buffer3[k - 68];
            }
        }

        //Se for o quinto índice a ser serializado, copie-o para os próximos oito bytes do nó serializado.
        if(i == 4){
            for(int k = 76; k < 84; k++){
                buffer1[k] = buffer3[k - 76];
            }
        }

        //Se for o sexto índice a ser serializado, copie-o para os próximos oito bytes do nó serializado.
        if(i == 5){
            for(int k = 84; k < 92; k++){
                buffer1[k] = buffer3[k - 84];
            }
        }
    }

    //Limpa a string "buffer3".
    for(int j = 0; j < 9; j++){
        buffer3[j] = '\0';
    }

    //Copia o valor do índice do nó para "aux2".
    aux2 = this->GetIndex();

    //Copia o valor do índice do nó reinterpretado para "buffer3".
    buffer3 = reinterpret_cast<char*>(&aux2);

    //Copia o valor do índice do nó reinterpretado para os últimos oito bytes do nó serializado.
    for(int i = 92; i < 100; i++){
        buffer1[i] = buffer3[i - 92];
    }

    return buffer1;
}
