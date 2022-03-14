#include "libraries.h"

template <class Generic>
Archive<Generic>::Archive(){
}

//Esse construtor recebe como parâmetros um nome para o arquivo. um tipo e sua versão.
template <class Generic>
Archive<Generic>::Archive(cstring _name, cstring _type, int _version){
    cout << "->\tVerificando necessidade de criação de arquivo." << endl;
    //A variável "aux1" constrói um cabeçalho com os parâmetros escolhidos.
    Header aux1(_name, _type, _version);
    //Atribui o cabeçalho para o arquivo em memória primária.
    this->header = aux1;
    //Carregando o arquivo em memória secundária.
    aux1.FromString(this->ReadHeader());
    //Se o cabeçalho criado em memória primária for igual ao da memória secundária, não é neceśsaria a criação de um arquivo.
    if((aux1.GetName() == _name) && (aux1.GetType() == _type) && (aux1.GetVersion() == _version)){
        cout << "->\tArquivo encontrado. Carregando arquivo." << endl;
        //Atribui ao cabeçalho do arquivo em memória primária o cabeçalho construído anteriormente.
        this->header = aux1;
        cout << "->\tO arquivo foi carregado com sucesso." << endl;
        return;
    }
    //Se a versão ou o tipo do arquivo em memória principal for diferente do que está em memória secundária, aborta o programa.
    if((aux1.GetName() == _name) && ((aux1.GetType() != _type) || (aux1.GetVersion() != _version))){
        cout << "->\tA versão ou o tipo do arquivo estão desatualizados. O arquivo não foi carregado." << endl;
        return;
    }
    //Se o arquivo não existe.
    if((aux1.GetName() != _name) && (aux1.GetType() != _type) && (aux1.GetVersion() != _version)){
        cout << "->\tO arquivo não foi encontrado. Criando arquivo novo." << endl;
        //As linhas 59, 60 e 61 criam o arquivo em memória secundária.
        fstream arquivo(_name, ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc);
        arquivo.open(_name, ios_base::in | ios_base::out | ios_base::binary);
        arquivo.close();
        //Constrói um cabeçalho com os parâmetros escolhidos.
        Header aux2(_name, _type, _version);
        //Atribui ao cabeçalho do arquivo em memória primária o cabeçalho com os parâmetros escolhidos.
        this->header = aux2;
        //Escrever o cabeçalho no arquivo em memória secundária.
        WriteHeader();
        cout << "->\tO arquivo foi criado com sucesso." << endl;
        return;
    }
    //O programa não foi feito para chegar aqui.
    cout << "->\tNenhuma condição foi satisfeita." << endl;
}

template <class Generic>
void Archive<Generic>::operator = (const Archive<Generic> &_archive){
    this->header = _archive.header;
}

//Essa função é responsável pela abertura do arquivo.
template <class Generic>
bool Archive<Generic>::Open(){
    //Se o arquivo não estiver aberto, abra-o e retorne verdadeiro.
    if(!this->is_open()){
        this->open(this->header.GetName(), ios_base::in | ios_base::out | ios_base::binary);
        return true;
    }
    //Caso estiver aberto, retorne falso.
    return false;
}

//Essa função é responsável pelo fechamento do arquivo.
template <class Generic>
bool Archive<Generic>::Close(){
    //Se o arquivo estiver aberto, feche-o e retorne verdadeiro.
    if(this->is_open()){
        this->close();
        return true;
    }
    //Caso estiver fechado, retorne falso.
    return false;
}

//Essa função é responsável pela leitura de uma página no arquivo e recebe como parâmetro um índice.
template <class Generic>
char* Archive<Generic>::ReadRegistry(ulint _index){
    cout << "->\tLendo registro." << endl;
    //A variável "buffer" é responsável por capturar os bytes da página no arquivo.
    char* buffer = new char[110];
    //Limpa o lixo de memória.
    for(int i = 0; i < 110; i++){
        buffer[i] = '\0';
    }
    //Se o arquivo não abrir, manda uma mensagem de erro, fecha o arquivo e retorna "zz" como sinal de erro.
    if(!this->Open()){
        cout << "->\tO arquivo não pôde ser aberto" << endl;
        this->Close();
        return "zz";
    }
    //Posiciona a cabeça de leitura no primeiro byte da página de índice "_index" do arquivo.
    this->seekg((_index * 109) + 40);
    //Lê 109 bytes e o atribui a "buffer".
    this->read(buffer, 109);
    //Se a leitura foi realizada com sucesso manda uma mensagem, caso contrário manda uma mensagem de erro, fecha o arquivo
    //e retorna "zz" como sinal de erro.
    if(this->good()){
        cout << "->\tA leitura do registro foi bem sucedida." << endl;
    }else{
        cout << "->\tRegistro não localizado." << endl;
        this->Close();
        return "zz";
    }
    //Fecha o arquivo.
    this->Close();
    //Retorna a página.
    return buffer;
}

//Essa função é responsável por excluir uma página do arquivo e recebe um índice como parâmetro. E sim, tivemos que tratar
//casos específicos de exclusão, por isso o tamanho da função.
template <class Generic>
bool Archive<Generic>::DeleteRegistry(ulint _index){
    cout << "->\tRemovendo registro." << endl;
    //As variáveis "aux1", "aux2", "aux3" e "aux4" são necessárias para a manipulação dos valores dos registros do arquivo
    Registry<Generic> aux1;
    Registry<Generic> aux2;
    Registry<Generic> aux3;
    Registry<Generic> aux4;
    //Lê o registro do índice desejado para exclusão.
    aux1.FromString(this->ReadRegistry(_index));
    //Se o registro já for um não válido, envia uma mensagem e retorna falso.
    if(!aux1.IsValid()){
        cout << "->\tO registro a ser removido já não é válido." << endl;
        return false;
    }

    //Se o registro para exclusão for o primeiro válido do arquivo.
    if(this->header.GetFirstValid() == _index){
        cout << "->\tO registro a ser removido é o primeiro válido." << endl;
        //Se não tiver registros não válidos, realiza o procedimento de exclusão.
        if(this->header.GetFirstNValid() == NULL_CONST){
            cout << "->\tO arquivo não possui registros não válidos." << endl;
            //Lê o registro "primeiro válido" do arquivo.
            aux1.FromString(this->ReadRegistry(this->header.GetFirstValid()));
            //Copia o "primeiro válido" para "aux2".
            aux2 = aux1;
            //O registro lido é um não válido.
            aux1.SetValid(false);
            //O próximo registro do registro para exclusão é uma constante que sinaliza registro nulo.
            aux1.SetNext(NULL_CONST);
            //O "primeiro não válido" do arquivo é o "primeiro válido".
            this->header.SetFirstNValid(this->header.GetFirstValid());
            //O "primeiro válido" é o próximo registro do registro para exclusão.
            this->header.SetFirstValid(aux2.GetNext());
            //Escreve o cabeçalho no arquivo em memória secundária.
            this->WriteHeader();
            //Escreve o registro excluído no arquivo em memória secundária e retorna verdadeiro.
            this->WriteRegistry(_index, aux1);
            cout << "->\tO registro foi removido com sucesso." << endl;
            return true;
        }else{
            //Se tiver registros não válidos, realiza o procedimento de exclusão.
            cout << "->\tO arquivo possui registros não válidos." << endl;
            //Lê o "primeiro válido" do arquivo.
            aux1.FromString(this->ReadRegistry(this->header.GetFirstValid()));
            //Copia o "primeiro válido" para "aux2".
            aux2 = aux1;
            //O registro para exclusão é um não válido.
            aux1.SetValid(false);
            //O próximo registro do registro para exclusão é o "primeiro não válido" do arquivo.
            aux1.SetNext(this->header.GetFirstNValid());
            //O "primeiro não válido" do arquivo é o "primeiro válido".
            this->header.SetFirstNValid(this->header.GetFirstValid());
            //O "primeiro válido" do arquivo é o próximo registro do registro para exclusão.
            this->header.SetFirstValid(aux2.GetNext());
            //Escreve o cabeçalho no arquivo em memória secundária.
            this->WriteHeader();
            //Escreve o registro excluído no arquivo em memória secundária e retorna true.
            this->WriteRegistry(_index, aux1);
            cout << "->\tO registro foi removido com sucesso." << endl;
            return true;
        }
    //O registro para exclusão é qualquer registro exceto o "primeiro válido" do arquivo.
    }else{
        //Se não houver registros não válidos no arquivo, realiza o procedimento de exclusão.
        if(this->header.GetFirstNValid() == NULL_CONST){
            cout << "->\tO arquivo não possui registros não válidos." << endl;
            //Lê o "primeiro válido" do arquivo.
            aux1.FromString(this->ReadRegistry(this->header.GetFirstValid()));
            //Lê o próximo registro do "primeiro válido" do arquivo.
            aux2.FromString(this->ReadRegistry(aux1.GetNext()));
            //Se só tiver dois registros válidos no arquivo, realiza o procedimento de exclusão.
            if(aux2.GetNext() == NULL_CONST){
                cout << "->\tO arquivo Só possui dois registros." << endl;
                //Copia o "primeiro válido" para "aux3".
                aux3 = aux1;
                //O "primeiro não válido" do arquivo é o próximo registro do "primeiro válido".
                this->header.SetFirstNValid(aux1.GetNext());
                //O próximo registro do "primeiro válido" é a constante nula.
                aux1.SetNext(NULL_CONST);
                //O próximo registro do "primeiro válido" é um não válido.
                aux2.SetValid(false);
                //Escreve o cabeçalho do arquivo em memória secundária.
                this->WriteHeader();
                //Escreve o próximo registro do "primeiro válido" no arquivo em memória secundária.
                this->WriteRegistry(aux3.GetNext(), aux2);
                //Escreve o "primeiro válido" no arquivo em memória secundária e retorna true.
                this->WriteRegistry(this->header.GetFirstValid(), aux1);
                cout << "->\tO registro foi removido com sucesso." << endl;
                return true;
            }
            //Se o registro para exclusão for o próximo registro do "primeiro válido", realiza o procedimento de exclusão.
            if(aux1.GetNext() == _index){
                cout << "->\tO registro a ser removido é o próximo do primeiro válido." << endl;
                //Copia o "primeiro válido" para "aux3".
                aux3 = aux1;
                //O "primeiro não válido" é o próximo registro do "primeiro válido".
                this->header.SetFirstNValid(aux1.GetNext());
                //O pŕoximo registro do "primeiro válido" é o próximo registro do registro para exclusão.
                aux1.SetNext(aux2.GetNext());
                //O registro para exclusão é um não válido.
                aux2.SetValid(false);
                //O pŕoximo registro do registro para exclusão é a constante nula.
                aux2.SetNext(NULL_CONST);
                //Escreve o cabeçalho do arquivo em memória secundária.
                this->WriteHeader();
                //Escreve o registro excluído no arquivo em memória secundária.
                this->WriteRegistry(_index, aux2);
                //Escreve o "primeiro válido" no arquivo em memória secundária e retorna true.
                this->WriteRegistry(this->header.GetFirstValid(), aux1);
                cout << "->\tO registro foi removido com sucesso." << endl;
                return true;
            }
            //Caso nenhum dos casos especiais forem acionados, lê o "primeiro válido" do arquivo.
            aux1.FromString(this->ReadRegistry(this->header.GetFirstValid()));
            //Encontra o registro a ser excluído, e os dois registros anteriores a ele.
            while(aux2.GetNext() != _index){
                aux1.FromString(this->ReadRegistry(aux1.GetNext()));
                aux2.FromString(this->ReadRegistry(aux1.GetNext()));
                aux3.FromString(this->ReadRegistry(aux2.GetNext()));
            }
            //O "primeiro não válido" é o registro a ser excluído.
            this->header.SetFirstNValid(aux2.GetNext());
            //O registro a ser excuído é um não válido.
            aux3.SetValid(false);
            //O pŕoximo registro do registro anterior ao que será excluído é o próximo registro do registro que será excluído.
            aux2.SetNext(aux3.GetNext());
            //O próximo registro do registro que será excluído é a constante nula.
            aux3.SetNext(NULL_CONST);
            //Escreve o cabeçalho no arquivo em memória secundária.
            this->WriteHeader();
            //Escreve o registro anterior ao registro excluído no arquivo em memória secundária.
            this->WriteRegistry(aux1.GetNext(), aux2);
            //Escreve o registro excluído no arquivo em memória secundária e retorna true.
            this->WriteRegistry(_index, aux3);
            cout << "->\tO registro foi removido com sucesso." << endl;
            return true;
        //Se houver registros não válidos no arquivo, realiza o procedimento de exclusão.
        }else{
            cout << "->\tO arquivo possui registros não válidos." << endl;
            //Lê o "primeiro válido" do arquivo.
            aux1.FromString(this->ReadRegistry(this->header.GetFirstValid()));
            //Lê o próximo registro do "primeiro válido" do arquivo.
            aux2.FromString(this->ReadRegistry(aux1.GetNext()));
            //Se só houver dois registros válidos no arquivo, realiza o procedimento de exclusão.
            if(aux2.GetNext() == NULL_CONST){
                cout << "->\tO arquivo Só possui dois registros." << endl;
                //Copia o "primeiro válido" para "aux3".
                aux3 = aux1;
                //O próximo registro do registro a ser excluído é o "primeiro não válido".
                aux2.SetNext(this->header.GetFirstNValid());
                //O "primeiro não válido" é o próximo registro do "primeiro válido".
                this->header.SetFirstNValid(aux1.GetNext());
                //O próximo registro do "primeiro válido" é a constante nula.
                aux1.SetNext(NULL_CONST);
                //O registro a ser excluído é um não válido.
                aux2.SetValid(false);
                //Escreve o cabeçalho no arquivo em memória secundária.
                this->WriteHeader();
                //Escreve o registro excluído no arquivo em memória secundária.
                this->WriteRegistry(aux3.GetNext(), aux2);
                //Escreve o "primeiro válido" no arquivo em memória secundária e retorna true.
                this->WriteRegistry(this->header.GetFirstValid(), aux1);
                cout << "->\tO registro foi removido com sucesso." << endl;
                return true;
            }
            //Se o registro a ser excluído é o próximo do "primeiro válido", realiza o procedimento de exclusão.
            if(aux1.GetNext() == _index){
                cout << "->\tO registro a ser removido é o próximo do primeiro válido." << endl;
                //Copia o "primeiro válido" para "aux3".
                aux3 = aux1;
                //O "primeiro não válido" é o registro a ser excluído.
                this->header.SetFirstNValid(aux1.GetNext());
                //O próximo registro do "primeiro válido" é o próximo registro do registro a ser excluído.
                aux1.SetNext(aux2.GetNext());
                //O registro a ser excluído é um não válido.
                aux2.SetValid(false);
                //O próximo registro do registro a ser excluído é a constante nula.
                aux2.SetNext(NULL_CONST);
                //Escreve o cabeçalho no arquivo em memória secundária.
                this->WriteHeader();
                //Escreve o registro excluído no arquivo em memória secundária.
                this->WriteRegistry(_index, aux2);
                //Escreve o "primeiro válido" no arquivo em memória secundária e retorna true.
                this->WriteRegistry(this->header.GetFirstValid(), aux1);
                cout << "->\tO registro foi removido com sucesso." << endl;
                return true;
            }
            //Caso nenhum dos casos especiais forem acionados, lê o "primeiro válido" do arquivo.
            aux1.FromString(this->ReadRegistry(this->header.GetFirstValid()));
            //Encontra o registro a ser excluído, e os dois registros anteriores a ele.
            while(aux2.GetNext() != _index){
                aux1.FromString(this->ReadRegistry(aux1.GetNext()));
                aux2.FromString(this->ReadRegistry(aux1.GetNext()));
                aux3.FromString(this->ReadRegistry(aux2.GetNext()));
            }
            //Copia o registro a ser excluído para "aux4".
            aux4 = aux3;
            //O próximo registro do registro a ser excluído é o "primeiro não válido".
            aux3.SetNext(this->header.GetFirstNValid());
            //O "primeiro não válido" é o registro a ser excluído.
            this->header.SetFirstNValid(aux2.GetNext());
            //O registro a ser excluído é um não válido.
            aux3.SetValid(false);
            //O próximo registro do registro anterior ao registro que será excluído é o próximo registro do registro que será
            //excluído.
            aux2.SetNext(aux4.GetNext());
            //Escreve o cabeçalho no arquivo em memória secundária.
            this->WriteHeader();
            //Escreve o registro anterior ao registro que foi excluído no arquivo em memória secundária.
            this->WriteRegistry(aux1.GetNext(), aux2);
            //Escreve o registro excluído no arquivo em memória secundária e retorna true.
            this->WriteRegistry(_index, aux3);
            cout << "->\tO registro foi removido com sucesso." << endl;
            return true;
        }
    }
    //O programa não foi feito para chegar aqui.
    return false;
}

//Essa função é responsável por inserir registros no arquivo e recebe como parâmetro o registro a ser inserido.
template <class Generic>
bool Archive<Generic>::InsertRegistry(Registry<Generic> _registry){
    cout << "->\tInserindo registro." << endl;
    //A variável "index" é necessária para capturar o índice de "primeiro válido" ou do "primeiro não válido".
    ulint index = 0;
    //Se não houver registros não válidos.
    if(this->header.GetFirstNValid() == NULL_CONST){
        cout << "->\tO arquivo não possui registros não válidos." << endl;
        //Se o arquivo estiver vazio, realiza o procedimento de inserção.
        if(this->header.GetFirstValid() == NULL_CONST){
            cout << "->\tO arquivo está vazio." << endl;
            //O índice é zero.
            index = 0;
            //O "primeiro válido" do arquivo é o primeiro registro.
            this->header.SetFirstValid(index);
            //Escreve o registro no arquivo em memória secundária.
            this->WriteRegistry(index, _registry);
            //Escreve o cabeçalho no arquivo em memória secundária e retorna true.
            this->WriteHeader();
            cout << "->\tO registro foi inserido com sucesso." << endl;
            return true;
        //Se o arquivo não estiver vazio, realiza o procedimento de inserção.
        }else{
            cout << "->\tO arquivo não está vazio." << endl;
            //O índice é igual ao índice do "primeiro válido".
            index = this->header.GetFirstValid();
            //O próximo registro do registro a ser inserido é o "primeiro válido".
            _registry.SetNext(index);
            //O "primeiro válido" é o próximo registro.
            this->header.SetFirstValid(index + 1);
            //Escreve o cabeçalho no arquivo em memória secundária.
            this->WriteHeader();
            //Escreve o registro inserido no arquivo em memória secundária e retorna true.
            this->WriteRegistry(index + 1, _registry);
            cout << "->\tO registro foi inserido com sucesso." << endl;
            return true;
        }
    //Se houver registros não válidos no arquivo, realiza o procedimento de inserção.
    }else{
        cout << "->\tO arquivo possui registros não válidos." << endl;
        //O índice é o índice do "primeiro não válido".
        index = this->header.GetFirstNValid();
        //A variável "aux" é necessária para manipular os valores dos registros em memória primária.
        Registry<Generic> aux;
        //Lê o "primeiro não válido" do arquivo.
        aux.FromString(this->ReadRegistry(index));
        //Se não houver próximo registro ao do "primeiro não válido", realiza o procedimento de inserção.
        if(aux.GetNext() == NULL_CONST){
            cout << "->\tO arquivo só possui um registro não válido." << endl;
            //O próximo registro do registro a ser inserido é o "primeiro válido".
            _registry.SetNext(this->header.GetFirstValid());
            //O "primeiro válido" é o "primeiro não válido".
            this->header.SetFirstValid(this->header.GetFirstNValid());
            //O "primeiro não válido" é a constante nula.
            this->header.SetFirstNValid(NULL_CONST);
            //Escreve o cabeçalho no arquivo em memória secundária.
            this->WriteHeader();
            //Escreve o registro inserido no arquivo em memória secundária e retorna true.
            this->WriteRegistry(index, _registry);
            cout << "->\tO registro foi inserido com sucesso." << endl;
            return true;
        //Se houver mais de um registro não válido no arquivo, realiza o procedimento de inserção.
        }else{
            //As variáveis "aux1" e "aux2" são necessárias para manipulação dos valores dos registros em memória primária.
            Registry<Generic> aux1;
            Registry<Generic> aux2;
            cout << "->\tO arquivo possui múltiplos registros não válidos." << endl;
            //O índice é igual ao índice do "primeiro não válido".
            index = this->header.GetFirstNValid();
            //Lê o "primeiro não válido" do arquivo.
            aux1.FromString(this->ReadRegistry(index));
            //Lê o próximo registro do "primeiro não válido" do arquivo.
            aux2.FromString(this->ReadRegistry(aux1.GetNext()));
            //O próximo registro do registro a ser inserido é o "primeiro válido".
            _registry.SetNext(this->header.GetFirstValid());
            //O "primeiro válido" é o "primeiro não válido".
            this->header.SetFirstValid(index);
            //O "primeiro não válido" é o próximo registro do "primeiro não válido".
            this->header.SetFirstNValid(aux1.GetNext());
            //Escreve o cabeçalho no arquivo em memória secundária.
            this->WriteHeader();
            //Escreve o registro inserido no arquivo em memória secundária e retorna true.
            this->WriteRegistry(this->header.GetFirstValid(), _registry);
            cout << "->\tO registro foi inserido com sucesso." << endl;
            return true;
        }
    }
    //O programa não foi feito para chegar aqui.
    cout << "->\tNenhuma das condições foram satisfeitas. O registro não foi inserido." << endl;
    return false;
}

//Essa função é responsável por escrever um registro no arquivo em memória secundária e recebe como parâmetros um índice e
//o registro a ser escrito.
template <class Generic>
bool Archive<Generic>::WriteRegistry(ulint _index, Registry<Generic> _registry){
    cout << "->\tEscrevendo registro." << endl;
    //A variável "buffer" é necessária para serializar o registro que será escrito no arquivo.
    char* buffer = new char[110];
    //Limpa o lixo de memória.
    for(int i = 0; i < 110; i++){
        buffer[i] = '\0';
    }
    //Serializa o registro que será escrito.
    buffer = _registry.ToString();
    //Se o arquivo não abrir, envia uma mensagem de erro e retorna falso.
    if(!this->Open()){
        cout << "->\tO arquivo não pôde ser aberto." << endl;
        return false;
    }
    //Posiciona a cabeça de escrita no primeiro byte da posição do índice.
    this->seekp(40 + (_index * 109));
    //Escreve 109 bytes no arquivo.
    this->write(buffer, 109);
    //Se a escrita foi realizada sem problemas, envia uma mensagem.
    if(this->good()){
        cout << "->\tO registro foi escrito com sucesso." << endl;
    }
    //Fecha o arquivo e retorna true.
    this->clear();
    this->Close();

    return true;
}

//Essa função é responsável por escrever o cabeçalho no arquivo.
template <class Generic>
bool Archive<Generic>::WriteHeader(){
    cout << "->\tEscrevendo cabeçalho." << endl;
    //A variável "buffer" é necessária para receber o cabeçalho serializado.
    char* buffer = new char[41];
    //Limpa o lixo de memória.
    for(int i = 0; i < 41; i++){
        buffer[i] = '\0';
    }
    //Serializa o cabeçalho.
    buffer = this->header.ToString();
    //Se o arquivo não abrir, envia uma mensagem de erro e retorna falso.
    if(!this->Open()){
        cout << "->\tO arquivo não pôde ser aberto." << endl;
        return false;
    }
    //Posiciona a cabeça de escrita no primeiro byte do arquivo.
    this->seekp(0);
    //Escreve 40 bytes no arquivo.
    this->write(buffer, 40);
    //Se a escrita foi realizada com sucesso, envia uma mensagem.
    if(this->good()){
        cout << "->\tO cabeçalho foi escrito com sucesso." << endl;
    }
    //Fecha o arquivo e retorna true.
    this->clear();
    this->Close();

    return true;
}

//Essa função é responsável por ler o cabeçalho no arquivo.
template <class Generic>
char* Archive<Generic>::ReadHeader(){
    cout << "->\tLendo cabeçalho do arquivo." << endl;
    //A variável "buffer" é necessária para receber os bytes serializados do arquivo.
    char* buffer = new char[41];
    //Limpa o lixo de memória.
    for(int i = 0; i < 41; i++){
        buffer[i] = '\0';
    }
    //Se o arquivo não abrir, envia uma mensagem de erro.
    if(!this->Open()){
        cout << "->\tO arquivo não pôde ser aberto." << endl;
        return buffer;
    }
    //Posiciona a cabeça de leitura no primeiro byte do arquivo.
    this->seekg(0);
    //Lê 40 bytes do arquivo.
    this->read(buffer, 40);
    //Se a leitura foi realizada com sucesso, envia uma mensagem.
    if(this->good()){
        cout << "->\tA leitura do cabeçalho foi bem sucedida." << endl;
    }else{
        //Se não, envia uma mensagem de erro.
        cout << "->\tNão há cabeçalho a ser lido." << endl;
    }
    //Fecha o arquivo.
    this->Close();
    //Retorna o cabeçalho lido do arquivo.
    return buffer;
}

template class Archive<Node>;
