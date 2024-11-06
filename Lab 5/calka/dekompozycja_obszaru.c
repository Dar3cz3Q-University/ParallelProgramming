#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    double a, b, dx;
} struktura;

double funkcja(double x);

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w);

void *calka_podobszar_w(void *arg_wsk);

double calka_sekw(double a, double b, double dx);

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w) {

    // printf("a %lf, b %lf, dx %lf\n", a, b, dx);

    double calka_suma_local = 0.0;

    // tworzenie struktur danych do obsługi wielowątkowości
    pthread_t *pid = malloc(l_w * sizeof(pthread_t));
    struktura *structs = malloc(l_w * sizeof(struktura));

    double step = (b - a) / l_w;

    // tworzenie wątków
    for (int i = 0; i < l_w; i++) {
        structs[i].pid = i;
        structs[i].a = i * step;
        structs[i].b = (i + 1) * step;
        structs[i].dx = dx;
        pthread_create(&pid[i], NULL, calka_podobszar_w, (void *)&structs[i]);
    }

    // oczekiwanie na zakończenie pracy wątków
    double *calka_part;
    for (int i = 0; i < l_w; i++) {
        pthread_join(pid[i], (void *)&calka_part);
        calka_suma_local += *calka_part;
        free(calka_part);
    }

    free(pid);
    free(structs);

    return (calka_suma_local);
}

void *calka_podobszar_w(void *arg_wsk) {
    double a_local, b_local, dx;
    // rozpakowanie danych przesłanych do wątku
    struktura data = *((struktura *)arg_wsk);

    a_local = data.a;
    b_local = data.b;
    dx = data.dx;

    int N = ceil((b_local - a_local) / dx);
    dx = (b_local - a_local) / N;

    int my_id = data.pid;
    // printf("\nWątek %d: a_local %lf, b_local %lf, dx %lf\n", my_id, a_local, b_local, dx);

    // wywołanie zadania do wykonania: całkowanie w zadanym przedziale
    double *calka = malloc(sizeof(double));
    *calka = calka_sekw(a_local, b_local, dx);

    pthread_exit(calka);
}
