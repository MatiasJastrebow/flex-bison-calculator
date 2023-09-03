#include <stdio.h>
#include "scanner.h"

int main(){ 
    enum token salida;
    do{
        salida = scanner();

        if(salida == IDENTIFICADOR){
            printf("ES UN IDENTIFICADOR\n");
        }
        if(salida == ENTERO){
            printf("ES UN ENTERO\n");
        }
        if(salida == HEXADECIMAL){
            printf("ES UN HEXADECIMAL\n");
        }
        if(salida == FDT){
            printf("ES UN FDT\n");
        }
        if(salida == ERROR_GEN){
            printf("ERROR_GEN\n");
        }
        if(salida == ERROR_ENTERO){
            printf("ERROR_ENTERO\n");
        }

    }while(salida != EOFILE);
    return 0;
}