%{
#include <stdio.h>
#include "tokens.h"
%}
%option outfile="scanner.c"

entero {dig}+
real {entero}{exp}|{frac}{exp}?
exp [eE][+-]?{entero}
frac {entero}\.{entero}?|{entero}?\.{entero}
letra [a-zA-Z]
dig [0-9]
keyword var|salir
oper [+\-*/]=?|^|=
punct [)(]
funct sin|cos|tan|asin|acos|atan|log|sqrt

%%
{letra}({letra}|{dig})*         return ID;
{letra}({letra}|{dig})*.+       return ID_INVAL;
{entero}|{real}                 return NUM;
({entero}|{real}).+             return NUM_INVAL;
{keyword}                       return KEYWORD;
{oper}                          return OPER;
{punct}                         return PUNCT;
{funct}                         return FUNCT;
\n                           	;
.*                              return CADENA_INVAL;

%%
char *token_names[] = {"", "ID", "NUM", "KEYWORD", "OPER", "PUNCT", "FUNCT", "CADENA INVALIDA", "NUMERO INVALIDO", "IDENTIFICADOR INVALIDO"};
int main(){
    
    enum token t;

    while((t = yylex()) != FDT){
        printf("Token: %s\tVALOR: %s\n", token_names[t], yytext);
    }
    
    return 0;
}
