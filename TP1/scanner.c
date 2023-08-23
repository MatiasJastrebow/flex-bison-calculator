#include <stdio.h>
#include <ctype.h>
#include "scanner.h"

int estado = 0;
int fila , colum , ult_estado;
char c; // c = caracter

// tabla de transiciones
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
            } else if ((c >= 'a' && c <= 'f' )|| (c >= 'A' && c <= 'F')) {
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



enum token scanner(void){
    enum token tipo_estado;

    while(estado < 5){
        c = getchar();
        colum = tipoC(c);
        ult_estado = estado;
        estado = TT[estado][colum];
    }
    
    //enum token {IDENTIFICADOR, ENTERO, HEXA, FDT, ERROR_GEN, ERROR_ENTERO};
    
    switch (ult_estado){
    
    case 0:
        tipo_estado = IDENTIFICADOR; // ERROR (NO ACEPTOR)
        break;

    case 1:
        tipo_estado = IDENTIFICADOR;
        break;
    case 2:
        tipo_estado = ERROR_GEN;  // ERROR (NO ACEPTOR)
        break;
    case 3:
        tipo_estado = ENTERO;
        break;
    case 4:
        tipo_estado = HEXA;
        break;
    case 5:
        tipo_estado = ERROR_GEN;  // ERR0R (NO INDICA EL TIPO DE DATO)
        break;
    case 6:
        tipo_estado = ERROR_GEN;
        break;

    case 7:
        tipo_estado = ERROR_ENTERO;
        break;

    default:
        break;
    }
        
    return tipo_estado;
}
