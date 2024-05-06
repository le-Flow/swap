#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>


void aufgaben_machen(int s) {
        sleep(1);
        char text[] = "\tIch habe die Aufgaben bekommen\n\tIch mache meine Aufgaben...\n\tIch bin fertig. Ich schick dir meine Aufgaben.\n";
        write(STDOUT_FILENO, text, sizeof(text));
}

void aufgaben_korrigieren(int s) {
        sleep(1);
        char text[] = "Ich habe deine Loesungen erhalten\nIch kontrolliere Deine Aufgaben...\nDeine Aufgaben sind falsch\n";
        write(STDOUT_FILENO, text, sizeof(text));
}

int main(void) {
    pid_t kind = fork();
    if (kind == 0) {
        signal(SIGUSR1, aufgaben_machen);
        pid_t vater = getppid();

        char k1[] = "\tIch bin der Kindprozess\n";
        write(STDOUT_FILENO, k1, sizeof(k1));
        while (1) {
            pause();
            kill(vater, SIGUSR1);
        }
    }
    else {
        char v1[] = "Ich bin der Vaterprozess\n";
        char v2[] = "Ich schicke dir neue Aufgaben\n";
        char v3[] = "Jetzt reichts. Geh raus!\n";
        sleep(1);
        signal(SIGUSR1, aufgaben_korrigieren);

        write(STDOUT_FILENO, v1, sizeof(v1));
        for (int k = 0; k < 5; ++k) {
            write(STDOUT_FILENO, v2, sizeof(v2));
            kill(kind, SIGUSR1);
            pause();
        }
        write(STDOUT_FILENO, v3, sizeof(v3));
        sleep(1);
        kill(kind, SIGKILL);
        exit(0);
    }

    return 0;
}
