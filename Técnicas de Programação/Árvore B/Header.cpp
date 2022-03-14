#include "libraries.h"

Header::Header(){
    this->SetFirstValid(NULL_CONST);
    this->SetFirstNValid(NULL_CONST);
    this->SetType("Padrao");
    this->SetName("harley.sav");
    this->SetVersion(1);
}

Header::Header(cstring _name, cstring _type, cint _version){
    this->SetFirstValid(NULL_CONST);
    this->SetFirstNValid(NULL_CONST);
    this->SetType(_type);
    this->SetName(_name);
    this->SetVersion(_version);
}

Header::Header(const Header &_header){
    this->SetType(_header.GetType());
    this->SetName(_header.GetName());
    this->SetVersion(_header.GetVersion());
    this->SetFirstValid(_header.GetFirstValid());
    this->SetFirstNValid(_header.GetFirstNValid());
}

void Header::operator = (const Header &_header){
    this->SetType(_header.GetType());
    this->SetName(_header.GetName());
    this->SetVersion(_header.GetVersion());
    this->SetFirstValid(_header.GetFirstValid());
    this->SetFirstNValid(_header.GetFirstNValid());
}

//  Essa função é responsável por construir o objeto a partir de dados serializados.
void Header::FromString(char* _string){
    //  A string "buffer1" será responsável por receber os dados serializados correspondentes de "type", "buffer2" responsável por receber os dados de
    //      "version" e "buffer3" por receber os dados de "firstValid" e "firstNValid".
    char* buffer1 = new char[11];
    char* buffer2 = new char[5];
    char* buffer3 = new char[9];

    //  Antes nos certificamos de que não haja lixo de memória em nenhuma das strings.
    for(int i = 0; i < 11; i++){
        buffer1[i] = '\0';

        if(i < 5){
            buffer2[i] = '\0';
        }

        if(i < 9){
            buffer3[i] = '\0';
        }
    }

    //  Copiamos os 10 primeiros bytes dos dados serializados para "buffer1".
    for(int i = 0; i < 10; i++){
        buffer1[i] = _string[i];
    }

    //  Name é igual aos 10 primeiros bytes dos dados serializados.
    this->SetName(buffer1);

    //  Copiamos os próximos 10 bytes dos dados serializados para "buffer1".
    for(int i = 10; i < 20; i++){
        buffer1[i - 10] = _string[i];
    }

    //  O tipo é igual aos 10 primeiros bytes dos dados serializados.
    this->SetType(buffer1);

    //  Copiamos os próximos 4 bytes dos dados serializados para "buffer2".
    for(int i = 20; i < 24; i++){
        buffer2[i - 20] = _string[i];
    }

    //  Reinterpretamos os bytes de "buffer2" para "version".
    this->SetVersion(*reinterpret_cast<int*>(buffer2));

    //  Copiamos os pŕoximos 8 bytes dos dados serializados para "buffer3".
    for(int i = 24; i < 32; i++){
        buffer3[i - 24] = _string[i];
    }

    //  Reinterpretamos os bytes de "buffer3" para "firstValid".
    this->SetFirstValid(*reinterpret_cast<ulint*>(buffer3));

    //  Copiamos os últimos 8 bytes dos dados serializados para "buffer3".
    for(int i = 32; i < 40; i++){
        buffer3[i - 32] = _string[i];
    }

    //  Reinterpretamos os bytes de "buffer3" para "firstNValid".
    this->SetFirstNValid(*reinterpret_cast<ulint*>(buffer3));
}

//  Essa função é responsável por serializar os dados do objeto.
char* Header::ToString(){
    //  A string "buffer1" será responsável por receber o objeto serializado, enquanto que "buffer2" será responsável por receber outros tipos de dados
    //      reinterpretados. Além disso "buffer3" será responsável por receber "type" e "name", "aux1" responsável por receber "version" e "aux2" por
    //      receber "firstValid" e "firstNValid".
    char* buffer1 = new char[41];
    char* buffer2 = new char[11];
    string buffer3 = "";
    int aux1 = 0;
    ulint aux2 = 0;

    //  Antes nos certificamos de retirar qualquer lixo de memória existente em todas as strings.
    for(int i = 0; i < 41; i++){
        buffer1[i] = '\0';

        if(i < 11){
            buffer2[i] = '\0';
            buffer3[i] = '\0';
        }
    }

    //  Copie o valor de "name" para "buffer3".
    buffer3 = this->GetName();

    //  Copie o valor de "name" para os 10 primeiros bytes de "buffer1".
    for(int i = 0; i < 10; i++){
        buffer1[i] = buffer3[i];
    }

    //  Limpamos os valores de "buffer3".
    for(int i = 0; i < 11; i++){
        buffer3[i] = '\0';
    }

    //  Copie o valor de "type" para "buffer3".
    buffer3 = this->GetType();

    //  Copie o valor de "type" para os próximos 10 bytes de "buffer1".
    for(int i = 10; i < 20; i++){
        buffer1[i] = buffer3[i - 10];
    }

    //  Copie o valor de "version" para "aux1".
    aux1 = this->GetVersion();

    //  Reinterprete o valor de "version".
    buffer2 = reinterpret_cast<char*>(&aux1);

    //  Copie o valor reinterpretado de "version" para os próximos 4 bytes de "buffer1".
    for(int i = 20; i < 24; i++){
        buffer1[i] = buffer2[i - 20];
    }

    //  Copie o valor de "firstValid" para "aux2".
    aux2 = this->GetFirstValid();

    //  Reinterprete o valor de "firstValid".
    buffer2 = reinterpret_cast<char*>(&aux2);

    //  Copie o valor reinterpretado de "firstValid" para os próximos 8 bytes de "buffer1".
    for(int i = 24; i < 32; i++){
        buffer1[i] = buffer2[i - 24];
    }

    //  Copie o valor de "firstNValid" para aux2.
    aux2 = this->GetFirstNValid();

    //  Reinterprete o valor de "firstNValid".
    buffer2 = reinterpret_cast<char*>(&aux2);

    //  Copie o valor reinterpretado de "firstNValid" para os últimos 8 bytes de "buffer1".
    for(int i = 32; i < 40; i++){
        buffer1[i] = buffer2[i - 32];
    }

    return buffer1;
}

void Header::SetFirstValid(ulint _index){
    this->firstValid = _index;
}

void Header::SetFirstNValid(ulint _index){
    this->firstNValid = _index;
}

void Header::SetType(string _type){
    this->type = _type;
}

void Header::SetVersion(int _version){
    this->version = _version;
}

void Header::SetName(string _name){
    this->name = _name;
}

string Header::GetType() const{
    return this->type;
}

ulint Header::GetFirstValid() const{
    return this->firstValid;
}

ulint Header::GetFirstNValid() const{
    return this->firstNValid;
}

int Header::GetVersion() const{
    return this->version;
}

string Header::GetName() const{
    return this->name;
}
