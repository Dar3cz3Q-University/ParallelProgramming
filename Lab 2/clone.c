#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/sched.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "pomiar_czasu.h"

// Problem z alokacją stosu podczas pomiaru czasu

int zmienna_globalna = 0;

#define ROZMIAR_STOSU 1024 * 67 // Przy 1024 * 67 nie ma
// #define STACK_SIZE 8192
// #define CUSTOM_PROGRAM
#define FILE_SYSTEM

int funkcja_watku(void *argument) {

    zmienna_globalna++;

#ifdef CUSTOM_PROGRAM
    int wynik;
    char *arg[] = {"./program", "Dariusz Homa", "-1", NULL};
    wynik = execv("./program", arg);
#endif

#ifdef STACK_SIZE
    // 1024 * 64 = 65 536 bytes
    // 8 * 8192 = 65 536 bytes
    double table[STACK_SIZE];

    for (int i = 0; i < STACK_SIZE; i++)
        table[i] = 1;

    printf("%lf\n", table[STACK_SIZE - 2]);

    printf("%ld\n", sizeof(table));
#endif

#ifdef FILE_SYSTEM
    chdir("/tmp");

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    printf("Katalog roboczy w watku: %s\n", cwd);
#endif

    return 0;
}

int main() {

    void *stos;
    pid_t pid;
    int i;

    stos = malloc(ROZMIAR_STOSU);
    if (stos == 0) {
        printf("Proces nadrzędny - blad alokacji stosu\n");
        exit(1);
    }

    inicjuj_czas();

#ifdef STACK_SIZE
    pid = clone(funkcja_watku, (void *)stos + ROZMIAR_STOSU,
                CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);

    waitpid(pid, NULL, __WCLONE);
#elif defined(FILE_SYSTEM)
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    printf("Katalog roboczy przed watkiem: %s\n", cwd);

    pid = clone(&funkcja_watku,
                (void *)stos + ROZMIAR_STOSU,
                CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0); // Po dodaniu CLONE_FS watek zmienia cwd w main

    waitpid(pid, NULL, __WCLONE);

    getcwd(cwd, sizeof(cwd));

    printf("Katalog roboczy po watku: %s\n", cwd);
#else
    for (i = 0; i < 1000; i++) {

        pid = clone(
            funkcja_watku,
            (void *)stos + ROZMIAR_STOSU,
            CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM,
            0);

        waitpid(pid, NULL, __WCLONE);
    }
#endif

    drukuj_czas();

    free(stos);
}
