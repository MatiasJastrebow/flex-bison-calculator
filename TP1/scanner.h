#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

enum token {IDENTIFICADOR, ENTERO, HEXA, FDT, ERROR_GEN, ERROR_ENTERO};
extern char lexema[200];

void mostrar_lexema(char lexema[200] , int i);
 
enum token scanner(void);


#endif
