#include "pomiar_czasu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POMIAR_CZASU

const int liczba = 100000;

int main() {

    double a, b, c;
    int i, j, k, l;

    k = -50000;

#ifdef POMIAR_CZASU
    inicjuj_czas();
#endif

    for (i = 0; i < liczba; i++) {
        printf("%d ", k + i);
    }

#ifdef POMIAR_CZASU
    drukuj_czas();
#endif

    printf("\n");
    printf("Czas wykonania %d operacji wejscia/wyjscia: \n", liczba);

    a = 1.000001;

#ifdef POMIAR_CZASU
    double t1 = czas_zegara();
    double t2 = czas_CPU();
#endif

    for (i = 0; i < liczba * 100; i++) {
        a = 1.000001 * a + 0.000001;
    }

#ifdef POMIAR_CZASU
    t1 = czas_zegara() - t1;
    t2 = czas_CPU() - t2;

    printf("czas CPU         = %lf\n", t2);
    printf("czas zegarowy    = %lf\n", t1);
#endif

    printf("Wynik operacji arytmetycznych: %lf\n", a);
    printf("Czas wykonania %d operacji arytmetycznych: \n", liczba);
}
