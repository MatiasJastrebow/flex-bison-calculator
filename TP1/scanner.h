#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

enum token {IDENTIFICADOR, ENTERO, HEXADECIMAL, FDT, ERROR_GEN, ERROR_ENTERO, CENTINELA, EOFILE};
enum token scanner(void);
extern char lexema[200];


enum tipoChar {INICIAL, X, A_F, CERO, DIG, SPACE, OTRO};

void mostrar_lexema(char lexema[200] , int i);

#endif