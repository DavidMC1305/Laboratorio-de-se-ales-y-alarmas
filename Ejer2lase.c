#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int sig) {
    printf("Transcurrieron 3 segundos.\n");
}

int main() {
    signal(SIGALRM, alarm_handler);  // Establece el manejador de señales para SIGALRM

    printf("Lanzando alarma para dentro de 3 segundos...\n");
    alarm(3);  // Configura la alarma para que suene dentro de 3 segundos
    pause();   // Espera una señal

    return 0;
}


