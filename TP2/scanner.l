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
inval [[:punct:]]{-}[+\-*/=^)(]
invalID {letra}|{dig}|{inval}
invalNRO {letra}|{inval}|{nro}

%%
var                      		return PR_VAR;
salir					return PR_SALIR;
{id}         				return ID;
{id}+{inval}+{invalID}*		 	printf("Error Lexico: Identificador invalido: %s\n", yytext);
{nro}		               		return NUM;
{real}({letra}|{inval})+{invalNRO}*	printf("Error Lexico: Real invalido: %s\n", yytext);
{entero}({letra}|{inval})+{invalNRO}*	printf("Error Lexico: Constante invalida: %s\n", yytext);
{inval}+				printf("Error Lexico: Cadena desconocida: %s\n", yytext);
\+					return MAS;
\+=					return MAS_IGUAL;
-					return MENOS;
-=					return MENOS_IGUAL;
\*					return POR;
\*=					return POR_IGUAL;
\/					return DIV;
\/=					return DIV_IGUAL;
\^					return POT;
=					return IGUAL;
\(					return PAR_IZQ;
\)					return PAR_DER;
\n					return NL;						
.|\s	                           	;


%%
char *token_names[] = {"Fin de Archivo", "Identificador", "Numero", "'var'", "'salir'","'+'", "'+='", "'-'", "'-='", "'*'", "'*='", "'/'", "'/='", "'^'", "'='", "'('", "')'", "'NL'"};
int main(){
    
    enum token t;

    while((t = yylex()) != FDT){
        if(t >= 3){
        	printf("Token: %s\n", token_names[t]);
        } else {
        	printf("Token: %s\tLexema: %s\n", token_names[t], yytext);
        }
    }
    
    printf("Token: %s\n", token_names[t]);
    
    return 0;
}
