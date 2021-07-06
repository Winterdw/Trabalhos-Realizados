//A classe "Node" é responsável por abstrair uma página. Contendo quantidade de elementos, um vetor de fração, um vetor de
//índice de filhos e o seu próprio índice do arquivo, além das operações básicas sobre ele.
#ifndef NODE_H
#define NODE_H
#include "libraries.h"

class Node: public Serializable{
    private:
        ulint*      child;
        ulint**     childAdress;
        ulint       index;
        Fraction*   fraction;
        Fraction**  fractionAdress;
        int         amount;
    public:
                    Node                ();
                    Node                (int _amount, Fraction *_fraction, ulint *_child, ulint _index);
                    Node                (const Node &_node);
        virtual    ~Node                (){}
        void        operator =          (const Node &_node);
        void        SetAmount           (int _amount);
        void        SetFraction         (Fraction *_fraction);
        void        SetFractionByIndex  (Fraction _fraction, int _index);
        void        SetChild            (ulint *_child);
        void        SetChildByIndex     (ulint _child, int _index);
        void        SetIndex            (ulint _index);
        void        FromString          (char* _string);
        ulint*      GetChild            () const;
        ulint**     GetChildAdress      ();
        ulint       GetChildByIndex     (int _index) const;
        ulint       GetIndex            () const;
        Fraction*   GetFraction         () const;
        Fraction**  GetFractionAdress   ();
        Fraction    GetFractionByIndex  (int _index) const;
        bool        Insert              (Fraction _fraction, int _length);
        bool        Remove              (int _index);
        char*       ToString            ();
        int         GetAmount           () const;
};


#endif
