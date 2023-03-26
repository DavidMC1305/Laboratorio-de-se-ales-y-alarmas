#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigusr1_handler(int signum);
void sigusr2_handler(int signum);

pid_t pid_A, pid_C;

int main() {
    printf("Soy el proceso M con ID %d\n", getpid());
   
    // Configurar el manejador de SIGUSR1
    signal(SIGUSR1, sigusr1_handler);
   
    // Crear proceso A
    pid_A = fork();
    if (pid_A < 0) {
        perror("Error al crear proceso A");
        exit(1);
    } else if (pid_A == 0) {
        // Soy el proceso A
        printf("Soy el proceso A con ID %d y mi padre es M con ID %d\n", getpid(), getppid());
       
        // Configurar el manejador de SIGUSR1
        signal(SIGUSR1, sigusr1_handler);
       
        // Esperar la señal SIGUSR1
        pause();
       
        // Enviar la señal SIGUSR2 a C
        kill(pid_C, SIGUSR2);
       
        // Esperar a que C termine
        int status;
        wait(&status);
       
        printf("Soy el proceso A con ID %d y he terminado\n", getpid());
        exit(0);
    }
   
    // Crear proceso C
    pid_C = fork();
    if (pid_C < 0) {
        perror("Error al crear proceso C");
        exit(1);
    } else if (pid_C == 0) {
        // Soy el proceso C
        printf("Soy el proceso C con ID %d y mi padre es M con ID %d\n", getpid(), getppid());
       
        // Configurar el manejador de SIGUSR2
        signal(SIGUSR2, sigusr2_handler);
       
        // Esperar a recibir una señal
        pause();
       
        printf("Soy el proceso C con ID %d y he terminado\n", getpid());
        exit(0);
    }
   
    // Esperar 3 segundos y luego enviar la señal SIGUSR1 a A
    sleep(3);
    printf("Soy el proceso M con ID %d y envío la señal SIGUSR1 a A con ID %d\n", getpid(), pid_A);
    kill(pid_A, SIGUSR1);
   
    // Esperar a que ambos hijos terminen su ejecución
    int status1, status2;
    waitpid(pid_A, &status1, 0);
    waitpid(pid_C, &status2, 0);
   
    printf("Soy el proceso M con ID %d y mis hijos han terminado\n", getpid());
    exit(0);
}

void sigusr1_handler(int signum) {
    printf("Recibí la señal SIGUSR1 en el proceso %d con padre %d\n", getpid(), getppid());
}

void sigusr2_handler(int signum) {
    printf("Recibí la señal SIGUSR2 en el proceso %d con padre %d\n", getpid(), getppid());
}
