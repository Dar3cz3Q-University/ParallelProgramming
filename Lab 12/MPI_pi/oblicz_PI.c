#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCALAR double

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(void) {
    int max_liczba_wyrazow = 0;

    printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
    scanf("%d", &max_liczba_wyrazow);

    SCALAR suma_plus = 0.0;
    SCALAR suma_minus = 0.0;
    int i = 0;
    for (i = 0; i < max_liczba_wyrazow; i++) {
        int j = 1 + 4 * i;
        suma_plus += 1.0 / j;
        suma_minus += 1.0 / (j + 2.0);
    }
    double pi_approx = 4 * (suma_plus - suma_minus);

    printf("PI obliczone: \t\t\t%20.15lf\n", pi_approx);
    printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
}
