#include <stdio.h>
#include <ctype.h>
#include "scanner.h"

int fila , colum , estado ;
char c;

char lexema[200];


int TT [12][8] = {
                    {1 , 1 , 1 , 2 , 3 , 0 , 8 , 10},
                    {1 , 1 , 1 , 1 , 1 , 5 , 8 , 10},
                    {9 , 4 , 9 , 3 , 3 , 6 , 8 , 10},
                    {8 , 8 , 8 , 3 , 3 , 6 , 8 , 10},
                    {11,11 , 4 , 4 , 4 , 7 , 8 , 10},
                    {8 , 8 , 8 , 8 , 8 , 8 , 8 , 10},  // a partir de acá comienzan las columnas de los estados de salida (aceptores)
                    {8 , 8 , 8 , 8 , 8 , 8 , 8 , 10},
                    {8 , 8 , 8 , 8 , 8 , 8 , 8 , 10},
                    {8 , 8 , 8 , 8 , 8 , 8 , 8 , 10},
                    {8 , 8 , 8 , 8 , 8 , 8 , 8 , 10},
                    {8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 },  // si luego de leer un EOF seguimos leyendo caracteres es que tenemos un problema ...
                    {8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 }   // para completar la tabla se agrega una fila para el estado centinela
                };

void mostrar_lexema(char lexema[200] , int i){
    printf("'");
    for (int d = 0; d < i; d++) {
        printf("%c", lexema[d]);
    }
    printf("' ");
}



// comprobar la correcta definición de esta función
int tipoC(char c){
    enum tipoChar tipo;
    if (c == EOF){
        tipo = FIN;
    }
    else{
        if(isalnum(c)){
            if(c == '0'){
                tipo =  CERO;
            }
            else{
                tipo = DIG;
            }
        }
        else{
            if (isalpha(c)){
                if(c == 'x' || c == 'X'){
                    tipo = X;
                }
                else{
                    if((c >= 'a' && c <= 'f' ) || (c >= 'A' && c <= 'F')){
                        tipo = A_F;
                    }
                    else{
                        tipo = G_W_YZ;
                    }
                }
            }
            else{
                if(isspace(c)){
                    tipo = SPACE;
                }
                else{
                    tipo = OTRO;
                }
            }
        }
    }
    return tipo;
}



enum token scanner(int* index){
    enum token token;
    estado = 0;
    (*index)  = 0;
    while(estado < 5){  // mientras que no se toque un estado aceptor
        c = getchar();
        colum = tipoC(c);
        if(TT[estado][colum] == 11){  // ANTES DE ASIGNARLE EL VALOR DE TT AL ESTADO, SE CONSULTA QUE ESTE NO SEA EL ESTADO CENTINELA
            ungetc(c  ,stdin);
            break;
        }

        estado = TT[estado][colum]; 
        
        if(!isspace(c) && c != EOF){  // no escribe contenido en el lexema si se trata de un FDT
            lexema[(*index)] = c;
            (*index) ++;
        }

    }
    switch(estado){

        case 5:
            token = IDENTIFICADOR;
            break;

        case 6:
            token = ENTERO;
            break;

        case 7:
            token = HEXADECIMAL;
            break;

        case 8:
            token = ERROR_GEN;
            break;

        case 9:
            token = ERROR_ENTERO;
            break;

        case 10:
            token = EOFILE;
            break;

        // como esta función nunca va a devolver un estado = 11, no tiene ningún sentido declarar un token CENTINELA  

        //default:  // Esto no es obligatorio, pero sirve para apegarse a las buenas prácticas de la programación
        //    token = UNEXPECTED_ERROR;   
        //    break;
    }
    return token;
}

