//A classe "Archive" é responsável por manter o cabeçalho do arquivo em memória, além de realizar as operações básicas
//sobre o arquivo em disco.
//
//ReadRegistry 		para ler um registro. Retorna uma cadeia de caractere.
//DeleteRegistry 	para deletar um registro passando o índice.
//InsertRegistry 	para inserir um registro passando o índice e o registro.
#ifndef ARCHIVE_H
#define ARCHIVE_H
#include "libraries.h"

template <class Generic>
class Archive: protected fstream{
	static_assert(is_base_of <Serializable, Generic>::value, "Generic must be Serializable child.");

	private:
		Header  	header;
		bool    	WriteHeader         ();
		bool    	VerifyType          (char* _type);
		bool    	VerifyVersion       (int _version);

		bool    	Open                ();
		bool    	Close               ();
		ulint   	CalculatePosition   (ulint _index);
		ulint   	FirstValid          () const;
		ulint   	FirstNValid         () const;
		char*   	ReadHeader          ();
	public:
        			Archive             ();
        			Archive             (cstring _name, cstring _type, int _version);
		virtual    ~Archive            	(){}
		void		operator =			(const Archive<Generic> &_archive);
		bool    	DeleteRegistry      (ulint _index);
		bool    	InsertRegistry      (Registry<Generic> _registry);
		bool    	IsOpen              ();
		char*   	ReadRegistry        (ulint _index);
		bool    	WriteRegistry       (ulint _index, Registry<Generic> _registry);

};

#endif
