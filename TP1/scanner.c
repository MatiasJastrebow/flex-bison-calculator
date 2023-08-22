#include <stdio.h>
#include <ctype.h>
#include "scanner.h"

int estado = 0;
int fila , colum , ult_estado;
char c; // c = caracter

int TT [8][7] = {
                    {1 , 1 , 1 , 2 , 3 , 0 , 6},
                    {1 , 1 , 1 , 1 , 1 , 5 , 6},
                    {7 , 4 , 7 , 3 , 3 , 5 , 6},
                    {7 , 7 , 7 , 3 , 3 , 5 , 6},
                    {5 , 5 , 4 , 4 , 4 , 5 , 6},
                    {99, 99, 99, 99, 99, 99, 99},
                    {99, 99, 99, 99, 99, 99, 99},
                    {99, 99, 99, 99, 99, 99, 99}
                };

int tipoC (char c){
    int tipo;
    if (isalnum(c)) {
        if (isdigit(c)) {
            if (c == '0') {
                tipo = 3;
            } else {
                tipo = 4;
            }
        }
        if (isalpha(c)) {
            if (c == 'x' || c == 'X') {
                tipo = 1;
            } else if (c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F') {
                tipo = 2;
            } else {
                tipo = 0;
            }
        }
    } else if (isspace(c)){
        tipo = 5;
    } else {
        tipo = 6;
    }
    
    return tipo;
}

scanner(void){
    while(estado < 5){
        c = getchar();
        colum = tipoC(c);
        ult_estado = estado;
        estado = TT[estado][colum];
    }
}