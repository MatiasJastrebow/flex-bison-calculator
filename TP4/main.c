#include <stdio.h>
#include "scanner.h"
#include "parser.h"
#include "calc.h"

int main() {
	init_table();
	return yyparse();
}

void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}