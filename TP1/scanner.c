// #include <stdio.h>
// #include <ctype.h>
// #include "scanner.h"

// int estado = 0;
// int fila , colum , ult_estado;
// char c; // c = caracter

// int TT [8][7] = {
//                     {1 , 1 , 1 , 2 , 3 , 0 , 6},
//                     {1 , 1 , 1 , 1 , 1 , 5 , 6},
//                     {7 , 4 , 7 , 3 , 3 , 5 , 6},
//                     {7 , 7 , 7 , 3 , 3 , 5 , 6},
//                     {5 , 5 , 4 , 4 , 4 , 5 , 6},
//                     {99, 99, 99, 99, 99, 99, 99},
//                     {99, 99, 99, 99, 99, 99, 99},
//                     {99, 99, 99, 99, 99, 99, 99}
//                 };

// int tipoC (char c){
//     int tipo;
//     if (isalnum(c)) {
//         if (isdigit(c)) {
//             if (c == '0') {
//                 tipo = 3;
//             } else {
//                 tipo = 4;
//             }
//         }
//         if (isalpha(c)) {
//             if (c == 'x' || c == 'X') {
//                 tipo = 1;
//             } else if (c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F') {
//                 tipo = 2;
//             } else {
//                 tipo = 0;
//             }
//         }
//     } else if (isspace(c)){
//         tipo = 5;
//     } else {
//         tipo = 6;
//     }
    
//     return tipo;
// }

// // scanner(void){
// //     while(estado < 5){
// //         c = getchar();
// //         colum = tipoC(c);
// //         ult_estado = estado;
// //         estado = TT[estado][colum];
// //     }
// // }


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
    for (int d = 0; d < i - 1; d++) {
        printf("%c", lexema[d]);
    }
    printf("' ");
}

// esta función cumple con su propósito
int tipoC (char c){

    enum tipoChar tipo;
    if(c == EOF){  // De esta forma se puede encontrar el límite de lo que se tiene que escanear
        tipo = -1;
    }
    else{
        if (isalnum(c)) {
            if (isdigit(c)) {
                if (c == '0') {
                    tipo = CERO;
                } else {
                    tipo = DIG;
                }
            }
            if (isalpha(c)) {
                if (c == 'x' || c == 'X') {
                    tipo = X;
                } else if ((c >= 'a' && c <= 'f' ) || (c >= 'A' && c <= 'F')) {
                    tipo = A_F;
                } else {
                    tipo = INICIAL;
                }
            }
        } else if (isspace(c)){
            tipo = SPACE;
        } else {
            tipo = ERR;
        }
    }
    return tipo;
}

// el bucle no debería terminar cuando encuentra un fdt, ya que eso le quita la posibilidad de reconocer más de un token en la misma pasada

enum token scanner(void){
    estado = 0;
    char l[200]; // BORRAR ESTO QUE ESTA MAL, SOLO SE USA PARA PROBAR QUE LA LÓGICA ES CORRECTA
    enum token token;
    int i = 0;
    while(estado != 5 && estado != 6 && estado != 7){  // mientras que el estado no sea igual a 5 , 6  o 7 
        c = getchar();
        l[i] = c;
        i++; // lee los espacios tambien
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

        token = EOFILE;
        break;

    case 0:

        token = ERROR_GEN; // ERROR (NO ACEPTOR)
        mostrar_lexema(l , i);
        break;

    case 1:

        token = IDENTIFICADOR;
        mostrar_lexema(l , i);
        break;

    case 2:
       
        token = ERROR_GEN;  // ERROR (NO ACEPTOR)
        mostrar_lexema(l , i);
        break;

    case 3:
        
        token = ENTERO;
        mostrar_lexema(l , i);
        break;

    case 4:
        
        token = HEXADECIMAL;
        mostrar_lexema(l , i);
        break;

    case 5:

        token = ERROR_GEN;  // ERR0R (NO INDICA EL TIPO DE DATO)
        mostrar_lexema(l , i);
        break;

    case 6:

        token = ERROR_GEN;
        mostrar_lexema(l , i);
        break;

    case 7:

        token = ERROR_ENTERO;
        mostrar_lexema(l , i);
        break;

    default:
        break;
    }
        
    return token;
}
