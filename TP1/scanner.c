#include <stdio.h>
#include <ctype.h>
#include "scanner.h"

int fila , colum , estado ;
int c;

char lexema[200];


int TT [11][8] = {
                    {1 , 1 , 1 , 2 , 3 , 0 , 5 , 99},
                    {1 , 1 , 1 , 1 , 1 , 7 , 12, 99},
                    {6 , 4 , 6 , 3 , 3 , 8 , 12, 99},
                    {6 , 6 , 6 , 3 , 3 , 8 , 12, 99},
                    {12, 12, 4 , 4 , 4 , 9 , 12, 99},
                    {12, 12, 12, 12, 12, 10, 5 , 99},  // a partir de acá comienzan las columnas de los estados de salida (aceptores)
                    {6 , 6 , 6 , 6 , 6 , 11, 12, 99},
                    {10, 10, 10, 10, 10, 10, 10, 10},
                    {10, 10, 10, 10, 10, 10, 10, 10},
                    {10, 10, 10, 10, 10, 10, 10, 10},
                    {10, 10, 10, 10, 10, 10, 10, 10}  // si luego de leer un EOF seguimos leyendo caracteres es que tenemos un problema ...  // para completar la tabla se agrega una fila para el estado centinela
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
        if(isdigit(c)){
            if(c == '0'){
                tipo =  CERO;
            }
            else{
                tipo = DIG;
            }
        }
        else{
            if(isalpha(c)){
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
    (*index) = 0;
    while(estado < 7){  // mientras que no se toque un estado aceptor
        c = getchar();
        colum = tipoC(c);
        if(TT[estado][colum] == 12){  // ANTES DE ASIGNARLE EL VALOR DE TT AL ESTADO, SE CONSULTA QUE ESTE NO SEA EL ESTADO CENTINELA
            ungetc(c, stdin);
            break;
        }
        
        estado = TT[estado][colum]; 
        
        if(!isspace(c) && c != EOF){  // no escribe contenido en el lexema si se trata de un FDT
            lexema[(*index)] = c;
            (*index)++;
        }

    }
    switch(estado){

        case 7:
            token = IDENTIFICADOR;
            break;

        case 8:
            token = ENTERO;
            break;

        case 9:
            token = HEXADECIMAL;
            break;

        case 10:
            token = ERROR_GEN;
            break;

        case 11:
            token = ERROR_ENTERO;
            break;

        case 99:
            token = EOFILE;
            break;

        // como esta función nunca va a devolver un estado = 11, no tiene ningún sentido declarar un token CENTINELA  

        //default:  // Esto no es obligatorio, pero sirve para apegarse a las buenas prácticas de la programación
        //    token = UNEXPECTED_ERROR;   
        //    break;
    }
    return token;
}

