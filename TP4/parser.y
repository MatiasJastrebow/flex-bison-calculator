%code top{
#include <stdio.h>
#include "scanner.h"
#include "calc.h"
}

%union{
    double val;
    char caracter;
    struct symrec *symrec;
}

%code provides{
void yyerror(const char *);
}

%defines "parser.h"
%output "parser.c"
%token <val> NUM
%token <symrec*> ID
%token <caracter*> PR_VAR PR_SALIR
%token <caracter> MAS MAS_IGUAL MENOS MENOS_IGUAL POR POR_IGUAL DIV DIV_IGUAL POT IGUAL PAR_IZQ PAR_DER NL
%type <val> primaria termino expresion linea

%start sesion

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
    | expresion NL                      {printf ("%.10g\n", $1);}
    | PR_VAR ID NL                      {$$ = declarar_var($2);}
    | PR_VAR ID IGUAL expresion NL      {printf("Define ID como variable con valor inicial\n");}
    | PR_SALIR                          {;}
    ;

expresion:
    termino
    | ID IGUAL expresion                {$$ = $3; asignacion($1, $3);}
    | ID MAS_IGUAL expresion            {$$ = $3; asignacion($1, $1->value.var + $3);}
    | ID MENOS_IGUAL expresion          {$$ = $3; asignacion($1, $1->value.var - $3);}
    | ID POR_IGUAL expresion            {$$ = $3; asignacion($1, $1->value.var * $3);}
    | ID DIV_IGUAL expresion            {$$ = $3; asignacion($1, $1->value.var / $3);}
    ;

termino:
    primaria
    | termino MAS termino             {$$ = $1 + $3;}
    | termino MENOS termino           {$$ = $1 - $3;}
    | termino POR termino             {$$ = $1 * $3;}
    | termino DIV termino             {$$ = $1 / $3;}
    | termino POT termino             {$$ = (int)$1 ^ (int)$3;}
    ;

primaria:
    ID                                  {$$ = var_declarada($1);}
    | NUM                               {$$ = $1;}
    | MENOS primaria %prec NEG          {$$ = -$2;}
    | PAR_IZQ expresion PAR_DER         {$$ = $2;}
    | ID PAR_IZQ expresion PAR_DER      {$$ = funcion_existente($1, $3);}
    ;
%%