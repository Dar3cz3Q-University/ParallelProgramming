#include <pthread.h>
#include <stdio.h>

#define LICZBA_WATKOW 10

typedef struct {
    double a, b, wynik;
} struktura;

void *zadanie_watku(void *arg_wsk) {
    // struktura arg = *((struktura *)arg_wsk);

    struktura *arg = (struktura *)arg_wsk;

    arg->wynik = (arg->b - arg->a) * 4.0;
}

int main(int argc, char **argv) {
    pthread_t threads_ids[LICZBA_WATKOW];
    void *result;
    int i = 0;

    struktura tablica[LICZBA_WATKOW];

    double a = 0;
    double b = 1;

    double dx = (b - a) / LICZBA_WATKOW;

    for (i = 0; i < LICZBA_WATKOW; i++) {
        tablica[i].a = dx * i;
        tablica[i].b = tablica[i].a + dx;
        tablica[i].wynik = 0.0;

        pthread_create(&threads_ids[i], NULL, zadanie_watku, (void *)&tablica[i]);
    }

    for (i = 0; i < LICZBA_WATKOW; i++)
        pthread_join(threads_ids[i], &result);

    double sum = 0.0;

    for (i = 0; i < LICZBA_WATKOW; i++)
        sum += tablica[i].wynik;

    printf("Obliczona suma: %lf\n", sum);
}
