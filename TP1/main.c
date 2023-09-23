#include <stdio.h>
#include "scanner.h"

void mostrar_salida(enum token salida){
    printf("%s es un %s \n", lexema, casting_token(salida));
}

int main() {
    enum token salida;
    salida = scanner();

    while(salida != EOFILE) {

        mostrar_salida(salida);
        salida = scanner();
    }

    return 0;
}