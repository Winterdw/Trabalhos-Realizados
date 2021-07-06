package codigo;
import static codigo.Tokens.*; // SERÁ CRIADA A CLASSE Tokens DO TIPO Enum PARA SER IMPORTADA.

%%
%class Lexer
%type Tokens

L=[a-zA-Z_]+ // LETRAS.
D=[0-9]+ // DÍGITOS.
S=[@,#,$,¨]+ // CARACTERES ESPECIAIS.
Espaco=[" ", ,\t,\r] // ESPAÇO e TABULAÇÃO.
Enter=[\n]+ // QUEBRA DE LINHA.
ID={L}({L}|{D}|_)* // IDENTIFICADORES.
ConstInteira={D} // CONSTANTE INTEIRA.
ConstReal={D}(.)({D})* // CONTANTE REAL.
ConstString=(")({L}|{D}|{S})*(") // CONSTANTE STRING.

Progama={Classe}{ID}
Classe=(public class){ID}("{"){ListaMetodo}{Main}("}")
DeclaracaoVar={Tipo}{ID}(;)
ListaMetodo=({Metodo})*
Metodo={Tipo}{ID}("("){ListaParam}(")")("{")(DeclaracaoVar)*{ListaCmd}{Retorno}("}")
ListaParam={Param}|
           {Param}(","{Param})*
Param={Tipo}{ID}
Retorno=(return){Expressao}(;)
Main=(public static void main)("(")(")")("{")({DeclaracaoVar})*{ListaCmd}("}")
Tipo={TipoPrimitivo}("[")("]")
TipoPrimitivo=(boolean)|
              (int)|
              (String)|
              (float)|
              (void)
ListaCmd=(Cmd)*
Cmd=("{"){ListaCmd}("}")|
    CmdIF|
    CmdWhile|
    CmdAtrib|
    CmdFunc|
    CmdPrint|
    CmdPrintln
CmdIF=(if)("("){Expressao}(")"){Cmd}|
      (if)("("){Expressao}(")"){Cmd}(else){Cmd}
CmdWhile=(while)("("){Expressao}(")")
CmdPrint=(print)("("){Expressao}(")")(;)
CmdPrintln=(println)("("){Expressao}(")")(;)
CmdAtrib={ID}(=){Expressao}(;)|
         {ID}("["){Expressao}("]")(=){Expressao}(;)
CmdFunc={ID}({Expressao}(","{Expressao})*)
Expressao={D}{Op}{D}|
          {ID}([)(])| // CONSERTAR.
          {ID}|
          {ID}("(")  (")")
          {ConstInteira}|
          {ConstReal}|
          {ConstString}|
          (true)|
          (false)|
          (new){TipoPrimitivo}([)  (])|
          {OpUnario}{D}
Op=[||,&&,<,<=,>,>=,==,!=,/,*,-,+]
OpUnario=[_,!]      

%{
    public String lexeme;
%}
%%

// DEFINIÇÃO DE QUE ESPAÇO É IGNORADO E DE COMO SERÃO OS COMENTÁRIOS.
//{Espaco} {/*Ignore*/} // DEFINE QUE O ESPAÇO É IGNORADO.
"//".* {/*Ignore*/} // DEFINE O QUE É COMENTÁRIO.

// DEFINIÇÃO DAS SEQUENCIA DE CARACTERES QUE SERÃO LIDAS.
if|else|while|print|println|main|class|public {lexeme=yytext(); return Reservadas;}
("(-"{D}+")")|{D}+ {lexeme=yytext(); return Numero;}
"("|")"|"["|"]"|"{"|"}"|(')|;|. {lexeme=yytext(); return Simbolo;}
{Op} {lexeme=yytext(); return Op;}
{OpUnario} {lexeme=yytext(); return OpUnario;}
{TipoPrimitivo} {lexeme=yytext(); return TipoPrimitivo;}
{Tipo} {lexeme=yytext(); return Tipo;}
{Tipo}{ID} {lexeme=yytext(); return Param;}
{ListaParam} {lexeme=yytext(); return ListaParam;}
{Tipo}{ID}(;) {lexeme=yytext(); return DeclaracaoVar;}
{Retorno} {lexeme=yytext(); return Retorno;}
{L}({L}|{D}|_)* {lexeme=yytext(); return ID;}
{Enter} {lexeme=yytext(); return Enter;}
{Espaco} {lexeme=yytext(); return Espaco;}
 . {return ERROR;} // ESPAÇO PONTO ESPAÇO É UM ERRO EM PONTO FLUTUANTE.
