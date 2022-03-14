#include "libraries.h"

template <class Generic>
Registry<Generic>::Registry(){
    Generic data;
    this->SetData(data);
    this->SetNext(NULL_CONST);
    this->SetValid(true);
}

template <class Generic>
Registry<Generic>::Registry(Generic _data){
    this->SetData(_data);
    this->SetNext(NULL_CONST);
    this->SetValid(true);
}

template <class Generic>
Registry<Generic>::Registry(const Registry<Generic> &_registry){
    this->SetData(_registry.GetData());
    this->SetNext(_registry.GetNext());
    this->SetValid(_registry.IsValid());
}

template <class Generic>
void Registry<Generic>::operator = (const Registry<Generic> &_registry){
    this->SetData(_registry.GetData());
    this->SetNext(_registry.GetNext());
    this->SetValid(_registry.IsValid());
}

template <class Generic>
void Registry<Generic>::SetData(Generic _data){
    this->data = _data;
}

template <class Generic>
void Registry<Generic>::SetNext(ulint _next){
    this->next = _next;
}

template <class Generic>
void Registry<Generic>::SetValid(bool _valid){
    this->valid = _valid;
}

//Essa função é responsável por construir o registro a partir de dados serializados.
template <class Generic>
void Registry<Generic>::FromString(char* _string){
    //A string "buffer1" será responsável por receber os bytes correspondentes ao valor de "next" e "buffer2" por
    //receber os bytes do nó.
    char* buffer1 = new char[9];
    char* buffer2 = new char[101];

    //Antes, nos certificamos de que não haja lixo de memória nos "buffers".
    for(int i = 0; i < 101; i++){
        buffer2[i] = '\0';

        if(i < 9){
            buffer1[i] = '\0';
        }
    }

    //Copiamos os primeiros 100 bytes dos dados serializados para "buffer2".
    for(int i = 0; i < 100; i++){
        buffer2[i] = _string[i];
    }

    //Construimos o nó do registro a partir dos primeiros 100 bytes serializados.
    data.FromString(buffer2);

    //Copiamos os próximos 8 bytes dos dados serializados para "buffer1".
    for(int i = 100; i < 108; i++){
        buffer1[i - 100] = _string[i];
    }

    //Reinterpretamos os bytes de "buffer1" para "next".
    this->SetNext(*reinterpret_cast<ulint*>(buffer1));

    //Reinterpretamos o último byte dos dados serializados para "valid".
    this->SetValid(*reinterpret_cast<bool*>(&_string[108]));
}

//Essa função é responsável por serializar os dados do registro.
template <class Generic>
char* Registry<Generic>::ToString(){
    //A string "buffer1" será responsável por receber o registro serializado, enquanto que "buffer2" será responsável
    //por receber os dados do nó e "buffer3" por receber o valor de "next" reinterpretado, "aux1" por receber
    //"next" e "aux2" por receber "valid".
    char* buffer1 = new char[110];
    char* buffer2 = new char[101];
    char* buffer3 = new char[9];
    ulint aux1 = 0;
    bool aux2 = 0;

    //Antes nos certificamos de que não haja lixo de memória nas strings.
    for(int i = 0; i < 110; i++){
        buffer1[i] = '\0';

        if(i < 101){
            buffer2[i] = '\0';
        }
    }

    //Copiamos os dados serializados do registro para "buffer2".
    buffer2 = this->GetData().ToString();

    //Copiamos os dados serializados do nó para os primeiros 100 bytes de "buffer1".
    for(int i = 0; i < 100; i++){
        buffer1[i] = buffer2[i];
    }

    //Copiamos o valor de "next" para "aux1".
    aux1 = this->GetNext();

    //Reinterpretamos o valor de "next".
    buffer3 = reinterpret_cast<char*>(&aux1);

    //Copiamos o valor de "next" reinterpretado para os próximos 8 bytes de "buffer1".
    for(int i = 100; i < 108; i++){
        buffer1[i] = buffer3[i - 100];
    }

    //Copiamos os valor de "valid" para "aux2".
    aux2 = this->IsValid();

    //Copiamos o valor de "valid" para o último byte de "buffer1".
    buffer1[108] = *reinterpret_cast<char*>(&aux2);

    return buffer1;
}

template <class Generic>
bool Registry<Generic>::IsValid() const{
    return this->valid;
}

template <class Generic>
Generic Registry<Generic>::GetData() const{
    return this->data;
}

template <class Generic>
ulint Registry<Generic>::GetNext() const{
    return this->next;
}

template class Registry<Node>;
