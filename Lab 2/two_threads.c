#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/sched.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "pomiar_czasu.h"

int zmienna_globalna = 0;

#define ROZMIAR_STOSU 1024 * 64
#define LICZBA_ITERACJI 10000000

int funkcja_watku(void *argument) {

    int zmienna_lokalna = *((int *)argument);

    for (int i = 0; i < LICZBA_ITERACJI; i++) {
        zmienna_globalna++;
        zmienna_lokalna++;
    }

    printf("Zmienna globalna w funkcji watku: %d\n", zmienna_globalna);
    printf("Zmienna na stosie w funkcji watku: %d\n", zmienna_lokalna);

    return 0;
}

int main() {

    void *stos1, *stos2;
    pid_t pid1, pid2;
    int i;

    int zmienna_na_stosie = 0;

    stos1 = malloc(ROZMIAR_STOSU);
    stos2 = malloc(ROZMIAR_STOSU);
    if (stos1 == 0 || stos2 == 0) {
        printf("Proces nadrzędny - blad alokacji stosu\n");
        exit(1);
    }

    pid1 = clone(&funkcja_watku, (void *)stos1 + ROZMIAR_STOSU,
                 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void *)&zmienna_na_stosie);

    pid2 = clone(&funkcja_watku, (void *)stos2 + ROZMIAR_STOSU,
                 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void *)&zmienna_na_stosie);

    waitpid(pid1, NULL, __WCLONE);
    waitpid(pid2, NULL, __WCLONE);

    printf("Zmienna globalna w funkcji main: %d\n", zmienna_globalna);
    printf("Zmienna na stosie w funkcji main: %d\n", zmienna_na_stosie);

    free(stos1);
    free(stos2);
}
