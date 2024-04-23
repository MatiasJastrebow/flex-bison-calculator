#include "calc.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "parser.h"

char buffer2[200];

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
  { "ln",  log  },
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
  { "pi", M_PI },
  { "e",  M_E },
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
        yysemantics++;
        sprintf(buffer2, "Error: la variable %s ya fue declarada", id->name);
        yyerror(buffer2);
        return 0;
    }
}

int var_existente(struct symrec *id){
  if(getsym(id->name) == NULL){
    yysemantics++;
    sprintf(buffer2, "Error: el identificador %s no fue declarado", id->name);
    yyerror(buffer2);
    return 0;
  }
  else {
    return 1;
  }
}