#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigalrm_handler(int sig);
void sigusr1_handler(int sig);

int main() {
    pid_t pid_b, pid_c;
    int status;

    // Definir manejador de señal SIGALRM
    signal(SIGALRM, sigalrm_handler);

    // Esperar 5 segundos
    alarm(5);

    // Crear proceso B
    pid_b = fork();
    if (pid_b == 0) {
        // Proceso B
        // Dormir 1 segundo
        sleep(1);

        // Matar proceso C
        pid_c = fork();
        if (pid_c == 0) {
            // Proceso C
            printf("Esperando una señal.\n");
            while (1) {
                // Esperar indefinidamente
                pause();
            }
        } else {
            // Proceso B
            // Esperar a recibir una señal
            signal(SIGUSR1, sigusr1_handler);
            pause();
            exit(0);
        }
    } else {
        // Proceso A
        // Esperar a que B termine
        wait(&status);
        printf("El proceso B ha terminado.\n");
    }

    return 0;
}

void sigalrm_handler(int sig) {
    printf("Alarma recibida.\n");
    exit(1);
}

void sigusr1_handler(int sig) {
    // No hace nada
}
