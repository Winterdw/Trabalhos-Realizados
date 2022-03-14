#include "libraries.h"

Fraction::Fraction(){
    this->SetNumerator(0);
    this->SetDenominator(1);
}

Fraction::Fraction(int _numerator, int _denominator){
    this->SetNumerator(_numerator);
    this->SetDenominator(_denominator);
}

Fraction::Fraction(const Fraction &_fraction){
    this->SetNumerator(_fraction.GetNumerator());
    this->SetDenominator(_fraction.GetDenominator());
}

bool Fraction::operator == (const Fraction &_fraction){
    return (this->GetNumerator() == _fraction.GetNumerator() && this->GetDenominator() == _fraction.GetDenominator());
}

void Fraction::operator = (const Fraction &_fraction){
    this->SetNumerator(_fraction.GetNumerator());
    this->SetDenominator(_fraction.GetDenominator());
}

void Fraction::SetNumerator(int _numerator){
    this->numerator = _numerator;
}

void Fraction::SetDenominator(int _denominator){
    this->denominator = _denominator;
}

int Fraction::GetNumerator() const{
    return this->numerator;
}

int Fraction::GetDenominator() const{
    return this->denominator;
}

//Função responsável por construir a fração a partir de dados serializados
void Fraction::FromString(char* _string){
    //A string "buffer" será responsável por receber os 4 bytes dos inteiros que serão reinterpretados.
    char* buffer = new char[5];

    //Antes, nos certificamos de que não haja lixo de memória no "buffer".
    for(int i = 0; i < 5; i++){
        buffer[i] = '\0';
    }

    //Copiamos os 4 primeiros bytes dos dados serializados para o "buffer".
    for(int i = 0; i < 4; i++){
        buffer[i] = _string[i];
    }

    //Reinterpretamos os bytes copiados do "buffer" para x.
    this->SetNumerator(*reinterpret_cast<int*>(buffer));

    //Copiamos os 4 últimos bytes dos dados serializados para o "buffer".
    for(int i = 4; i < 9; i++){
        buffer[i - 4] = _string[i];
    }

    //Reinterpretamos os bytes copiados do "buffer" para y.
    this->SetDenominator(*reinterpret_cast<int*>(buffer));
}

//Função responsável por serializar os dados de uma fração
char* Fraction::ToString(){
    //A string "buffer1" será responsável por receber o objeto serializado enquanto que "buffer2" será responsável por receber
    //a representação em caracter dos inteiros. A variável aux será responsável por receber os parâmetros do objeto.*/
    char*   buffer1 = new char[9];
    char*   buffer2 = new char[9];
    int     aux = 0;

    //Limpe qualquer lixo de memória que possa existir nas strings.
    for(int i = 0; i < 9; i++){
        buffer1[i] = '\0';
        buffer2[i] = '\0';
    }

    //Receba o valor do numerador do objeto e o reinterprete.
    aux = this->GetNumerator();
    buffer2 = reinterpret_cast<char*>(&aux);

    //Copie o valor do numerador reinterpretado para os primeiros 4 bytes da string "buffer1".
    for(int i = 0; i < 4; i++){
        buffer1[i] = buffer2[i];
    }

    //Receba o valor do denominador do objeto e o reinterprete.
    aux = this->GetDenominator();
    buffer2 = reinterpret_cast<char*>(&aux);

    //Copie o valor do denominador reinterpretado para os próximos 4 bytes da string "buffer1".
    for(int i = 4; i < 9; i++){
        buffer1[i] = buffer2[i - 4];
    }

    return buffer1;
}
