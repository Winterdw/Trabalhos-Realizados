//A classe "Registry" é responsável por manter informações importantes sobre um registro no arquivo. Contendo os dados,
//o índice do próximo registro em arquivo e se é válido ou um não válido, além das operações básicas sobre ele.
#ifndef REGISTRY_H
#define REGISTRY_H
#include "libraries.h"

template <class Generic>
    class Registry: public Serializable{
        private:
            Generic     data;
            ulint       next;
            bool        valid;
        public:
                        Registry    ();
                        Registry    (Generic _data);
                        Registry    (const Registry<Generic> &_registry);
            virtual    ~Registry    (){}
            void        operator =  (const Registry<Generic> &_registry);
            void        SetData     (Generic _data);
            void        SetNext     (ulint _index);
            void        SetValid    (bool _valid);
            void        FromString  (char* _string);
            Generic     GetData     () const;
            ulint       GetNext     () const;
            char*       ToString    ();
            bool        IsValid     () const;
};

#endif
