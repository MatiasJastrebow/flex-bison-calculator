#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

typedef double (func_t) (double);

struct symrec
{
  char *name;
  int type;
  union
  {
    double var;
    func_t *fun;
  } value;
  struct symrec *next;
};

void init_table(void);

extern struct symrec *sym_table;

struct symrec *putsym (char const *name, int sym_type);
struct symrec *getsym (char const *name);

extern int yysemantics;

int declarar_var(struct symrec *id);
int var_existente(struct symrec *id);

#endif