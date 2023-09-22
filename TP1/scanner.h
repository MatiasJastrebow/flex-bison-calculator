#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

enum token {IDENTIFICADOR , ENTERO , HEXADECIMAL , ERROR_GEN, ERROR_ENTERO , EOFILE , UNEXPECTED_ERROR};

enum token scanner(int* index);

extern char lexema[200];

enum tipoChar {G_W_YZ , X , A_F , CERO , DIG , SPACE , OTRO , FIN};

void mostrar_lexema(char lexema[200] , int i);

#endif