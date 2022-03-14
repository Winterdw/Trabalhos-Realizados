//A classe "Header" é responsável por manter informações importantes sobre o arquivo. Com nome, tipo, versão, primeiro válido
//e primeiro não válido, além das operações básicas sobre seus atributos.
#ifndef HEADER_H
#define HEADER_H
#include "libraries.h"

class Header: public Serializable{
    private:
        string  	name;
		string  	type;
		ulint   	firstValid;
		ulint   	firstNValid;
		int     	version;
	public:
					Header          ();
					Header          (cstring _name, cstring _type, cint _version);
					Header          (const Header &_header);
		virtual    ~Header			(){}
		void    	operator =      (const Header &_header);
		void    	SetFirstValid   (ulint _index);
		void    	SetFirstNValid  (ulint _index);
		void    	SetType         (string _type);
		void    	SetVersion      (int _version);
		void    	SetName         (string _name);
		void    	FromString      (char* _string);
		ulint   	GetFirstValid   () const;
		ulint   	GetFirstNValid  () const;
		string 		GetType         () const;
		string  	GetName         () const;
		char*  	 	ToString        ();
		int     	GetVersion      () const;



};

#endif
