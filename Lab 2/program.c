#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("Not enough arguments provided\n");
        return -1;
    }

    char *imie_nazwisko = argv[1];
    char *given_pid = argv[2];

    pid_t pid = getpid();

    printf("%s, pid w argv: %s, pid w program.c: %d\n", imie_nazwisko, given_pid, pid);
}
