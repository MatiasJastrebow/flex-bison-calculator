#include <stdio.h>
#include "scanner.h"
#include "parser.h"

int main() {
	return yyparse();
}
/* Informa la ocurrencia de un error. */
void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}