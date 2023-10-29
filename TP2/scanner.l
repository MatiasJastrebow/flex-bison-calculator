%{
#include <stdio.h>
#include "tokens.h"
%}
%option outfile="scanner.c"

id {letra}({letra}|{dig})*
nro {entero}|{real}
entero {dig}+
real {entero}{exp}|{frac}{exp}?
exp [eE][+-]?{entero}
frac {entero}\.{entero}?|{entero}?\.{entero}
letra [a-zA-Z]
dig [0-9]
funct sin|cos|tan|asin|acos|atan|log|sqrt
inval [[:punct:]]{-}[+\-*/=^)(]
invalID {letra}|{dig}|{inval}
invalNRO {letra}|{inval}|{nro}

%%
{funct}                        		return FUNCT;
var|salir                      		return KEYWORD;
{id}         				return ID;
{id}+{inval}+{invalID}*		 	return ID_INVAL;
{nro}		               		return NUM;
{nro}({letra}|{inval})+{invalNRO}*	return NUM_INVAL;
[+\-*/]=?|^|=                 		return OPER;
[)(]	                       		return PUNCT;
{inval}+				return CADENA_INVAL;
\n					printf("'NL'\n");						
.|\s	                           	;


%%
char *token_names[] = {"", "ID", "NUM", "KEYWORD", "OPER", "PUNCT", "FUNCT", "CADENA INVALIDA", "NUMERO INVALIDO", "IDENTIFICADOR INVALIDO"};
int main(){
    
    enum token t;

    while((t = yylex()) != FDT){
        printf("Token: %s\tVALOR: %s\n", token_names[t], yytext);
    }
    
    return 0;
}
