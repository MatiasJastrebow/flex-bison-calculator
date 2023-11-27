#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

typedef double (func_t) (double);

struct symrec
{
  char *name;  /* name of symbol */
  int type;    /* type of symbol: either VAR or FUN */
  union
  {
    double var;    /* value of a VAR */
    func_t *fun;   /* value of a FUN */
  } value;
  struct symrec *next;  /* link field */
};

typedef struct symrec symrec;

extern symrec *sym_table;

void init_table(void);

symrec *putsym (char const *name, int sym_type);
symrec *getsym (char const *name);

double var_declarada(symrec *id);
double funcion_existente(symrec *funcion, double const valor);
double asignacion(symrec *id, double valor);
double declarar_var(symrec *id);

#endif

/* posible solucion, tenemos que resolver algunos temas de compilacion jej :{
%%
sesion:
    %empty
    | sesion linea                      {printf("\n");}
    ;

linea:
    NL                                  {printf("\n");}
    | expresion NL                      {printf("Expresion\n");}
    | PR_VAR ID NL                      {$$ = declarar_var($2);}
    | PR_VAR ID IGUAL expresion NL      {printf("Define ID como variable con valor inicial\n");}
    | PR_SALIR                          {;}
    ;

expresion:
    termino
    | ID IGUAL expresion                {$$ = var_modificable($1, $3);}
    | ID MAS_IGUAL expresion            {$$ = var_modificable($1, $1->value.var += $3);}
    | ID MENOS_IGUAL expresion          {$$ = var_modificable($1, $1->value.var -= $3);}
    | ID POR_IGUAL expresion            {$$ = var_modificable($1, $1->value.var *= $3);}
    | ID DIV_IGUAL expresion            {$$ = var_modificable($1, $1->value.var /= $3);}
    ;

termino:
    primaria
    | termino MAS termino             {$$ = $1 + $3;}
    | termino MENOS termino           {$$ = $1 - $3;}
    | termino POR termino             {$$ = $1 * $3;}
    | termino DIV termino             {$$ = $1 / $3;}
    | termino POT termino             {$$ = $1 ^ $3;}
    ;

primaria:
    ID                                  {$$ = var_declarada($1);}
    | NUM                               {$$ = $1}
    | MENOS primaria %prec NEG          {$$ = -$2;}
    | PAR_IZQ expresion PAR_DER         {$$ = $2;}
    | ID PAR_IZQ expresion PAR_DER      {$$ = funcion_existente($1, $3)}
    ;
%%
*/