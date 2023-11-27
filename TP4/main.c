#include <stdio.h>
#include "scanner.h"
#include "parser.h"
#include "calc.h"

int main() {
	init_table();
	return yyparse();
}
/* Informa la ocurrencia de un error. */
void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}