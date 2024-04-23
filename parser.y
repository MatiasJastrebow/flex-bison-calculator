%code top{
#include <stdio.h>
#include <math.h>
#include "scanner.h"
#include "calc.h"
}

%code provides{
void yyerror(const char *);
extern int yylexers;
}

%defines "parser.h"
%output "parser.c"
%define api.value.type union
%token <double> NUM
%token <struct symrec *> ID FUN
%token <char*> PR_VAR PR_SALIR
%token <char> MAS MAS_IGUAL MENOS MENOS_IGUAL POR POR_IGUAL DIV DIV_IGUAL POT IGUAL PAR_IZQ PAR_DER NL
%type <double> primaria termino expresion linea
%define parse.error verbose

%precedence IGUAL
%precedence MAS_IGUAL
%precedence MENOS_IGUAL
%precedence POR_IGUAL
%precedence DIV_IGUAL
%left MENOS MAS
%left POR DIV
%precedence NEG
%right POT     

%%
sesion:                                 { if(yynerrs || yylexers || yysemantics) YYABORT; }
    %empty
    | sesion linea                      { printf("\n"); }
    ;

linea:
    NL                                  
    | expresion NL                      { printf("%.10g\n", $1); }
    | PR_VAR ID NL                      { if(declarar_var($2)){$2 = putsym($2->name, ID); printf("%s: %.10g\n", $2->name, $2->value.var);} }
    | PR_VAR ID IGUAL expresion NL      { if(declarar_var($2)){$2 = putsym($2->name, ID); $2->value.var = $4; printf("%s: %.10g\n", $2->name, $4);} }
    | PR_SALIR                          { return 0; }
    | error NL                          
    ;

expresion:
    termino
    | ID IGUAL expresion                { if(var_existente($1)){$1->value.var = $3; $$ = $3;} else {YYERROR;} }
    | ID MAS_IGUAL expresion            { if(var_existente($1)){$1->value.var += $3; $$ = $1->value.var;} else {YYERROR;} }
    | ID MENOS_IGUAL expresion          { if(var_existente($1)){$1->value.var -= $3; $$ = $1->value.var;} else {YYERROR;} }
    | ID POR_IGUAL expresion            { if(var_existente($1)){$1->value.var *= $3; $$ = $1->value.var;} else {YYERROR;} } 
    | ID DIV_IGUAL expresion            { if(var_existente($1)){$1->value.var /= $3; $$ = $1->value.var;} else {YYERROR;} }
    ;

termino:
    primaria                          
    | termino MAS termino             { $$ = $1 + $3; }
    | termino MENOS termino           { $$ = $1 - $3; }
    | termino POR termino             { $$ = $1 * $3; }
    | termino DIV termino             { $$ = $1 / $3; }
    | termino POT termino             { $$ = pow($1, $3); }
    ;

primaria:
    ID                                  { if(var_existente($1)){$$ = $1->value.var;} else {YYERROR;} }
    | NUM                               { $$ = $1; }
    | MENOS primaria %prec NEG          { $$ = -$2; }
    | PAR_IZQ expresion PAR_DER         { $$ = $2; }
    | FUN PAR_IZQ expresion PAR_DER     { $$ = $1->value.fun($3); }
    ;
%%