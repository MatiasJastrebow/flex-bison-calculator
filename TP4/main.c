#include <stdio.h>
#include <math.h>
#include "scanner.h"
#include "calc.h"
#include "parser.h"


int main() {
	init_table();
	return yyparse();
}

void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}