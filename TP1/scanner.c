#include <stdio.h>
#include <ctype.h>
#include "scanner.h"

char lexema[200];

int TT [15][8] = {
                    {1 , 1 , 1 , 2 , 3 , 0 , 5 , 99},
                    {1 , 1 , 1 , 1 , 1 , 7 , 12, 12},
                    {6 , 4 , 6 , 3 , 3 , 8 , 13, 13},
                    {6 , 6 , 6 , 3 , 3 , 8 , 13, 13},
                    {14, 14, 4 , 4 , 4 , 9 , 14, 14},
                    {12, 12, 12, 13, 13, 10, 5 , 10},  
                    {6 , 6 , 6 , 6 , 6 , 11, 11, 11},
                    {10, 10, 10, 10, 10, 10, 10, 10},  
                    {10, 10, 10, 10, 10, 10, 10, 10},   
                    {10, 10, 10, 10, 10, 10, 10, 10},   
                    {10, 10, 10, 10, 10, 10, 10, 10},
                    {10, 10, 10, 10, 10, 10, 10, 10},
                    {10, 10, 10, 10, 10, 10, 10, 10},   
                    {10, 10, 10, 10, 10, 10, 10, 10},   
                    {10, 10, 10, 10, 10, 10, 10, 10}    
                };

char* casting_token(enum token salida){
    switch(salida){
            case IDENTIFICADOR:
                return "IDENTIFICADOR";
                break;
            case ENTERO:
                return "ENTERO";
                break;
            case HEXADECIMAL:
                return "HEXADECIMAL";
                break;
            case ERROR_GEN:
                return "ERROR GENERAL";
                break;
            case ERROR_ENTERO:
                return "ENTERO MAL FORMADO";
                break;
            default:
                return "UNEXPECTED_ERROR";
                break;
        }
}
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

enum token scanner(void){
    int colum, estado;
    int c;
    enum token token;
    estado = 0;
    int index = 0;

    while(estado < 7){  // mientras que no se toque un estado aceptor 
        c = getchar();
        colum = tipoC(c);
        
        if(TT[estado][colum] >= 12){  // ANTES DE ASIGNARLE EL VALOR DE TT AL ESTADO, SE CONSULTA QUE ESTE NO SEA EL ESTADO CENTINELA
            ungetc(c, stdin);
            estado = TT[estado][colum];
            break; 
        }

        estado = TT[estado][colum]; 
        
        if(!isspace(c) && c != EOF){  // no escribe contenido en el lexema si se trata de un FDT
            lexema[index] = c;
            index++;
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

        case 12:
            token = IDENTIFICADOR;
            break;
            
        case 13:
            token = ENTERO;
            break;
            
        case 14:
            token = HEXADECIMAL;
            break;
    
        case 99:
            token = EOFILE;
            break;

        default:
            token = UNEXPECTED_ERROR;
            break;
    }
    
    lexema[index++] = '\0';
    return token;
}