#include <stdio.h>
#include "tokens.h"
#include "scanner.h"

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