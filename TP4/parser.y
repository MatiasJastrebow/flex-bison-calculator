%code top{
#include <stdio.h>
#include <math.h>
#include "scanner.h"
#include "calc.h"
}

%code provides{
void yyerror(const char *);
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
sesion:
    %empty
    | sesion linea                      {printf("\n");}
    ;

linea:
    NL                                  {$$ = $1;}
    | expresion NL                      {printf("%.10g\n", $1);}
    | PR_VAR ID NL                      {if(declarar_var($2)){$2 = putsym($2->name, ID); printf("%.10g\n", $2->value.var);}}
    | PR_VAR ID IGUAL expresion NL      {if(declarar_var($2)){$2 = putsym($2->name, ID); $2->value.var = $4; printf("%.10g\n", $4);}}
    | PR_SALIR                          {return 0;}
    | error NL                          {yyerrok;}
    ;

expresion:
    termino
    | ID IGUAL expresion                { $$ = $3; $1->value.var = $3; }
    | ID MAS_IGUAL expresion            { $$ = $3; $1->value.var += $3; }
    | ID MENOS_IGUAL expresion          { $$ = $3; $1->value.var -= $3; }
    | ID POR_IGUAL expresion            { $$ = $3; $1->value.var *= $3; }
    | ID DIV_IGUAL expresion            { $$ = $3; $1->value.var /= $3; }
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
    ID                                  {$$ = $1->value.var;}
    | NUM                               {$$ = $1;}
    | MENOS primaria %prec NEG          {$$ = -$2;}
    | PAR_IZQ expresion PAR_DER         {$$ = $2;}
    | FUN PAR_IZQ expresion PAR_DER     {$$ = $1->value.fun($3);}
    ;
%%