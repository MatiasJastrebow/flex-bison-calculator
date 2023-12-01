#include "calc.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parser.h"

struct symrec *sym_table;

struct symrec *putsym (char const *name, int sym_type)
{
  struct symrec *res = (struct symrec *) malloc (sizeof (struct symrec));
  res->name = strdup (name);
  res->type = sym_type;
  res->value.var = 0;
  res->next = sym_table;
  sym_table = res;
  return res;
}

struct symrec *getsym (char const *name)
{
  for (struct symrec *p = sym_table; p; p = p->next)
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

struct initNum
{
  char const *name;
  double valor;
};

struct initNum const nums[] =
{
  { "pi", 3.14 },
  { "e",  2.76  },
  {0, 0},
};

void init_table (void)
{
  for (int i = 0; funs[i].name; i++)
    {
      struct symrec *ptr = putsym(funs[i].name, FUN);
      ptr->value.fun = funs[i].fun;
    }
  for (int i = 0; nums[i].name; i++)
    {
      struct symrec *ptr = putsym(nums[i].name, ID);
      ptr->value.var = nums[i].valor;
    }
}

int declarar_var(struct symrec *id){
    if(getsym(id->name) == NULL){
      return 1;
    } else {
        yyerror("La variable ya esta declarada");
        return 0;
    }
}

// double asignacion(symrec *id, double const valor){
//     if(getsym(id->name) != NULL){
//         id->value.var = valor;
//         return id->value.var;
//     }
//     else{
//         yyerror("la variable no fue declarada");
//         return 0;
//     }
// }

// double declarar_var(symrec *id){
//     if(getsym(id->name) == NULL){
//         putsym(id->name, ID);
//         return id->value.var;
//     }
//     else{
//         yyerror("la variable ya fue declarada");
//         return 0;
//     }
// }