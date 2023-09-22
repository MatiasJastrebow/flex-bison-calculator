#include <stdio.h>
#include "scanner.h"

int main() {
    int i;
    enum token salida;
    salida = scanner(&i);

    while(salida != EOFILE) {

        mostrar_lexema(lexema, i);

        switch(salida){
            case IDENTIFICADOR:
                printf("ES UN IDENTIFICADOR\n");
                break;

            case ENTERO:
                printf("ES UN ENTERO\n");
                break;

            case HEXADECIMAL:
                printf("ES UN HEXADECIMAL\n");
                break;

            case ERROR_GEN:
                printf("ERROR_GEN\n");
                break;

            case ERROR_ENTERO:
                printf("ERROR_ENTERO\n");
                break;
        }

        salida = scanner(&i);
    }

    return 0;
}