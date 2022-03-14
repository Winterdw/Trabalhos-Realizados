//A classe abstrata "Serializable" é importante para tornar obrigatória a implementação dos métodos "FromString" e "ToString"
//em qualquer classe que precise ter seus dados serializados.
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include "libraries.h"

class Serializable{
    public:
        Serializable                (){}
		virtual	char*   ToString    () = 0;
		virtual void    FromString  (char* _string) = 0;
};

#endif
