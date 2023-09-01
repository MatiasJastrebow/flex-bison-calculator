#include <stdio.h>
#include <ctype.h>
#include "scanner.h"


int fila , colum , estado , ult_estado;
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


void mostrar_lexema(char lexema[200] , int i){
    printf("'");
    for (int d = 0; d < i -1; d++) {
        printf("%c", lexema[d]);
    }
    printf("' ");
}


// esta función cumple con su propósito
int tipoC (char c){

    int tipo;
    if(c == EOF){  // De esta forma se puede encontrar el límite de lo que se tiene que escanear
        tipo = -1;
    }
    else{
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
    }
    return tipo;
}







// el bucle no debería terminar cuando encuentra un fdt, ya que eso le quita la posibilidad de reconocer más de un token en la misma pasada

enum token scanner(void){
    estado = 0;
    char l[200]; // BORRAR ESTO QUE ESTA MAL, SOLO SE USA PARA PROBAR QUE LA LÓGICA ES CORRECTA
    enum token tipo_estado;
    int i = 0;
    while(estado != 5 && estado != 6 &&estado != 7){  // mientras que el estado no sea igual a 5 , 6  o 7 
        c = getchar();
        l[i] = c;
        i++;
        colum = tipoC(c);
        if (colum == -1){  // se rompe el bucle para dejar de escanear
            ult_estado = -1;
            break;
        }
        ult_estado = estado;    
        estado = TT[estado][colum];
    }
    
    
    //enum token {IDENTIFICADOR, ENTERO, HEXA, FDT, ERROR_GEN, ERROR_ENTERO};
    
    switch (ult_estado){
    
    case -1:
        tipo_estado = EOFILE;
        break;

    case 0:
        tipo_estado = ERROR_GEN; // ERROR (NO ACEPTOR)
        mostrar_lexema(l , i);

        break;

    case 1:
        tipo_estado = IDENTIFICADOR;
        mostrar_lexema(l , i);
        break;
    case 2:
        tipo_estado = ERROR_GEN;  // ERROR (NO ACEPTOR)
        mostrar_lexema(l , i);
        break;
    case 3:
        tipo_estado = ENTERO;
        mostrar_lexema(l , i);
        break;
    case 4:
        tipo_estado = HEXA;
        mostrar_lexema(l , i);
        break;
    case 5:
        tipo_estado = ERROR_GEN;  // ERR0R (NO INDICA EL TIPO DE DATO)
        mostrar_lexema(l , i);
        break;
    case 6:
        tipo_estado = ERROR_GEN;
        mostrar_lexema(l , i);
        break;

    case 7:
        tipo_estado = ERROR_ENTERO;
        mostrar_lexema(l , i);
        break;

    default:
        break;
    }
        
    return tipo_estado;
}
