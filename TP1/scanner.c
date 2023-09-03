#include <stdio.h>
#include <ctype.h>
#include "scanner.h"

int fila , colum , estado , ult_estado;
char c;

char lexema[200];


int TT [9][7] = {
                    {1 , 1 , 1 , 2 , 3 , 0 , 6},
                    {1 , 1 , 1 , 1 , 1 , 5 , 6},
                    {7 , 4 , 7 , 3 , 3 , 5 , 6},
                    {7 , 7 , 7 , 3 , 3 , 5 , 7},
                    {8 , 5 , 4 , 4 , 4 , 5 , 6},
                    {5 , 5 , 5 , 5 , 5 , 5 , 5},
                    {6 , 6 , 6 , 6 , 6 , 5 , 6},
                    {7 , 7 , 7 , 7 , 7 , 5 , 7},
                    {8 , 8 , 8 , 8 , 8 , 5 , 8}
                };


void mostrar_lexema(char lexema[200] , int i){
    printf("'");
    for (int d = 0; d < i; d++) {
        printf("%c", lexema[d]);
    }
    printf("' ");
}

int tipoC (char c){

    enum tipoChar tipo;
    if(c == EOF){  
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
            tipo = OTRO;
        }
    }
    return tipo;
}

enum token scanner(void){
    static char aux = EOF;  // Variable estática que almacena el primer caracter del siguiente token cuando encuentra un centinela
    static int fin = 0;    
    estado = 0;
    enum token token;
    int i = 0;
    if(fin != 0){   // si el indicador de fin de escaneo es distinto de 0 "piratea" la función scanner para que saltee el while y devuelva el token EOFILE directamente
        estado = 5;
        ult_estado = -1;
    }
    while(estado != 5){ 
        if(aux !=EOF){
            c = aux;
            aux = EOF;
        }
        else{
            c = getchar();
        }

        colum = tipoC(c);
        if(c != EOF){      // para evitar que reconozca a EOF como un caracter fuera del alfabeto, se le impide reescribir el valor a ult_estado, así mantiene el estado anterior (último estado significativo)
            ult_estado = estado; 
        }
        estado = TT[estado][colum];
        if(estado == 8){
            aux = c;
            break;
        }
        if(!isspace(c) && c != EOF){
            lexema[i] = c;
            i++;
        }
        if (colum == -1){  
            fin = 1;  // Cuando el scanner lee el caracter EOF cambia el valor de fin, pero continúa con el bucle para que pueda devolver el token correspondiente a lo que reconoce
        }

    }
    
    switch (ult_estado){
    
    case -1:

        token = EOFILE;
        break;

    case 0:

        token = ERROR_GEN; 
        mostrar_lexema(lexema , i);
        break;

    case 1:

        token = IDENTIFICADOR;
        mostrar_lexema(lexema , i);
        break;

    case 2:
       
        token = ENTERO;  
        mostrar_lexema(lexema , i);
        break;

    case 3:
        
        token = ENTERO;
        mostrar_lexema(lexema , i);
        break;

    case 4:
        
        token = HEXADECIMAL;
        mostrar_lexema(lexema , i);
        break;

    case 5:

        token = ERROR_GEN;  
        mostrar_lexema(lexema , i);
        break;

    case 6:

        token = ERROR_GEN;
        mostrar_lexema(lexema , i);
        break;

    case 7:

        token = ERROR_ENTERO;
        mostrar_lexema(lexema , i);
        break;

    default:
        break;
    }
        
    return token;
}