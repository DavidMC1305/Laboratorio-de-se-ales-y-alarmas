#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Función que maneja la señal SIGINT
void sigint_handler(int sig) {
    printf("El usuario presionó CTRL+C\n");
    sleep(3);  // Pausa el programa por 3 segundos
}

int main() {
    // Configura el manejador de la señal SIGINT
    signal(SIGINT, sigint_handler);

    // Imprime el ID del proceso infinitamente
    while (1) {
        printf("Mi ID es %d\n", getpid());
        sleep(1);
    }

    return 0;
}


