%code top{
#include <stdio.h>
#include "scanner.h"
}

%code provides{
void yyerror(const char *);
}

%defines "parser.h"
%output "parser.c"
%token FDT ID NUM PR_VAR PR_SALIR MAS MAS_IGUAL MENOS MENOS_IGUAL POR POR_IGUAL DIV DIV_IGUAL POT IGUAL PAR_IZQ PAR_DER NL
%define api.value.type {char *}
%define parse.error verbose
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
    NL                                  {printf("\n");}
    | expresion NL                      {printf("Expresion\n");}
    | PR_VAR ID NL                      {printf("Define ID como variable\n");}
    | PR_VAR ID IGUAL expresion NL      {printf("Define ID como variable con valor inicial\n");}
    | PR_SALIR                       
    | error NL                          {yyerrok;}
    ;

expresion:
    termino
    | ID IGUAL expresion                {printf("Asignacion\n");}
    | ID MAS_IGUAL expresion            {printf("Asignacion con suma\n");}
    | ID MENOS_IGUAL expresion          {printf("Asignacion con resta\n");}
    | ID POR_IGUAL expresion            {printf("Asignacion con multiplicacion\n");}
    | ID DIV_IGUAL expresion            {printf("Asignacion con division\n");}
    ;

termino:
    primaria
    | expresion MAS termino             {printf("Suma\n");}
    | expresion MENOS termino           {printf("Resta\n");}
    | expresion POR termino             {printf("Multiplicacion\n");}
    | expresion DIV termino             {printf("Division\n");}
    | expresion POT termino             {printf("Potenciacion\n");}
    ;

primaria:
    ID                                  {printf("ID\n");}
    | NUM                               {printf("Numero\n");}
    | MENOS NUM %prec NEG               {printf("Cambio signo\n");}
    | MENOS ID %prec NEG                {printf("ID\n");}
    | PAR_IZQ expresion PAR_DER         {printf("Cierra parentesis\n");}
    | ID PAR_IZQ expresion PAR_DER      {printf("Funcion\n");}
    ;
%%