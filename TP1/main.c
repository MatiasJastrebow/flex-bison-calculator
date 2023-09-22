#include <stdio.h>
#include "scanner.h"

int main(){ 
    int i;
    enum token salida;
    do{
        salida = scanner(&i);  // cada vez que termina la ejecución se utiliza el valor "pasado por referencia" del índice

        mostrar_lexema(lexema , i);

        if(salida == IDENTIFICADOR){
            printf("ES UN IDENTIFICADOR\n");
        }
        else if(salida == ENTERO){
            printf("ES UN ENTERO\n");
        }
        else if(salida == HEXADECIMAL){
            printf("ES UN HEXADECIMAL\n");
        }

        else if(salida == ERROR_GEN){
            printf("ERROR_GEN\n");
        }
        else if(salida == ERROR_ENTERO){
            printf("ERROR_ENTERO\n");
        }
        
        else{
            printf("OCURRIO UN ERROR INESPERADO\n");
        }
        

    }while(salida != EOFILE);
    return 0;
}