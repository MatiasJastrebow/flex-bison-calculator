#include <stdio.h>
#include "scanner.h"

int main() {
    int i;
    enum token salida;
    salida = scanner(&i);

    while( salida!= EOFILE) {

        mostrar_lexema(lexema, i);

        switch(salida){
            case IDENTIFICADOR:
                printf("ES UN IDENTIFICADOR\n");

            case ENTERO:
                printf("ES UN ENTERO\n");

            case HEXADECIMAL:
                printf("ES UN HEXADECIMAL\n");

            case ERROR_GEN:
                printf("ERROR_GEN\n");

            case ERROR_ENTERO:
                printf("ERROR_ENTERO\n");
        }

        salida = scanner(&i);
    }

    return 0;
}
