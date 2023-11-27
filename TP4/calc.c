#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"
#include "parser.h"

symrec *putsym (char const *name, int sym_type)
{
  symrec *res = (symrec *) malloc (sizeof (symrec));
  res->name = strdup (name);
  res->type = sym_type;
  res->value.var = 0; /* Set value to 0 even if fun. */
  res->next = sym_table;
  sym_table = res;
  return res;
}

symrec *getsym (char const *name)
{
  for (symrec *p = sym_table; p; p = p->next)
    if (strcmp(p->name, name) == 0)
      return p;
  return NULL;
}

struct init
{
  char const *name;
  func_t *fun;
};

struct init const funs[] =
{
  { "atan", atan },
  { "cos",  cos  },
  { "exp",  exp  },
  { "ln",   log  },
  { "sin",  sin  },
  { "sqrt", sqrt },
  { 0, 0 },
};

void init_table (void)
{
  for (int i = 0; funs[i].name; i++)
    {
      symrec *ptr = putsym(funs[i].name, ID);
      ptr->value.fun = funs[i].fun;
    }
}

double var_declarada(symrec *id){
    if(getsym(id->name) != NULL){
        return id->value.var;
    }
    else{
        yyerror("la variable no fue declarada");
        return 0;
    }
}

double funcion_existente(symrec *funcion, double const valor){
    if(getsym(funcion->name) != NULL){
        return funcion->value.fun(valor);
    }
    else{
        yyerror("El identificador no es una funcion");
        return 0;
    }
}

double asignacion(symrec *id, double const valor){
    if(getsym(id->name) != NULL){
        id->value.var = valor;
        return id->value.var;
    }
    else{
        yyerror("la variable no fue declarada");
        return 0;
    }
}

double declarar_var(symrec *id){
    if(getsym(id->name) == NULL){
        putsym(id->name, ID);
        return id->value.var;
    }
    else{
        yyerror("la variable ya fue declarada");
        return 0;
    }
}