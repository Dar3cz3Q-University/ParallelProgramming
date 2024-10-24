#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Sprawozdanie do zrobienia

#include "pomiar_czasu.h"

#define CUSTOM_PROGRAM

int zmienna_globalna = 0;

int main() {

    int pid, wynik, i;

    inicjuj_czas();

    for (i = 0; i < 1000; i++) {

        pid = fork();

        if (pid == 0) {

            zmienna_globalna++;

#ifdef CUSTOM_PROGRAM
            char buf[10];
            sprintf(buf, "%d", pid);
            char *arg[] = {"./program", "Dariusz Homa", buf, NULL};
            wynik = execv("./program", arg);
#else
            char arg1[] = "/bin/ls";
            char arg2[] = ".";
            char *arg[] = {"/bin/ls", ".", NULL};
            wynik = execv("/bin/ls", arg);
#endif
            if (wynik == -1)
                printf("Proces potomny nie wykonal programu\n");

            exit(0);

        } else {

            wait(NULL);
        }
    }

    drukuj_czas();
}
