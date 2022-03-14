//A classe "Fraction" é responsável por abstrair uma fração, contendo um numerador, um denominador e as operações básicas
//sobre um número fracionário.
#ifndef FRACTION_H
#define FRACTION_H
#include "libraries.h"

class Fraction: public Serializable{
    private:
        int         numerator;
        int         denominator;
    public:
                    Fraction        ();
                    Fraction        (int _numerator, int _denominator);
                    Fraction        (const Fraction &_fraction);
        virtual    ~Fraction        (){}
        void        operator =      (const Fraction &_fraction);
        void        SetNumerator    (int _numerator);
        void        SetDenominator  (int _denominator);
        void        FromString      (char* _string);
        int         GetNumerator    () const;
        int         GetDenominator  () const;
        bool        operator ==     (const Fraction &_fraction);
        char*       ToString        ();
        friend      ostream& operator << (ostream& stream, const Fraction &_fraction);
};

#endif
