#include <stdio.h>
#include "scanner.h"


int main(){

    enum token salida = scanner();

    if(salida == IDENTIFICADOR){
        printf("ES UN IDENTIFICADOR\n");
    }
    if(salida == ENTERO){
        printf("ES UN ENTERO\n");
    }

    if(salida == HEXA){
        printf("ES UN HEXA\n");
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

    else{
        printf("ES OTRA COSA\n");
    }

    return 0;
}