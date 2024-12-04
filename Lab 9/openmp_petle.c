#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define WYMIAR 10

int main() {
    double a[WYMIAR][WYMIAR];

    for (int i = 0; i < WYMIAR; i++)
        for (int j = 0; j < WYMIAR; j++)
            a[i][j] = 1.02 * i + 1.01 * j;

    // podwójna pętla - sekwencyjnie
    double suma = 0.0;
    for (int i = 0; i < WYMIAR; i++) {
        for (int j = 0; j < WYMIAR; j++) {
            suma += a[i][j];
        }
    }

    printf("Suma wyrazów tablicy: %lf\n", suma);

    omp_set_nested(1);

    //
    // Sumowanie po wierszach
    //

    double suma_parallel = 0.0;
#pragma omp parallel for default(none) reduction(+ : suma_parallel) shared(a) schedule(static, 2) ordered
    for (int i = 0; i < WYMIAR; ++i) {
        for (int j = 0; j < WYMIAR; ++j) {
            suma_parallel += a[i][j];
        }
#pragma omp ordered
        printf("i: %d\tthread_id: %d\n", i, omp_get_thread_num());
    }

    printf("Suma wyrazów tablicy równolegle (wiersze): %lf\n", suma_parallel);

    //
    // Sumowanie po kolumnach
    //

    suma_parallel = 0.0;
#pragma omp parallel for default(none) reduction(+ : suma_parallel) shared(a) schedule(dynamic) ordered
    for (int i = 0; i < WYMIAR; ++i) {
        for (int j = 0; j < WYMIAR; ++j) {
            suma_parallel += a[j][i];
        }
#pragma omp ordered
        printf("i: %d\tthread_id: %d\n", i, omp_get_thread_num());
    }

    printf("Suma wyrazów tablicy równolegle (kolumny): %lf\n", suma_parallel);

    //
    // Sumowanie po kolumnach z sekcją krytyczną
    //

    suma_parallel = 0.0;
#pragma omp parallel for default(none) shared(suma_parallel, a) ordered
    for (int j = 0; j < WYMIAR; ++j) {
        double local_sum = 0.0;
        for (int i = 0; i < WYMIAR; ++i) {
            local_sum += a[i][j];
        }
#pragma omp critical
        {
            suma_parallel += local_sum;
        }
#pragma omp ordered
        printf("j: %d\tthread_id: %d\n", j, omp_get_thread_num());
    }

    printf("Suma wyrazów tablicy równolegle (kolumny z sekcją krytyczną): %lf\n", suma_parallel);

    //
    // Dekompozycja 2D
    //

    omp_set_nested(1);
    double tab[3][2];

#pragma omp parallel for schedule(static, 2) default(none) shared(a, tab) ordered
    for (int i = 0; i < WYMIAR; ++i) {
        int thread_id_outer = omp_get_thread_num();
#pragma omp parallel for schedule(static, 2) num_threads(2) default(none) shared(a, tab, i) firstprivate(thread_id_outer) ordered
        for (int j = 0; j < WYMIAR; ++j) {
            int thread_id_inner = omp_get_thread_num();
            tab[thread_id_outer][thread_id_inner] += a[i][j];
#pragma omp ordered
            {
                printf("(%d, %d): %d, ", i, j, omp_get_thread_num());
            }
        }
#pragma omp ordered
        {
            printf("outer_thread_id: %d \n", omp_get_thread_num());
        }
    }

    suma_parallel = 0.0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            suma_parallel += tab[i][j];
        }
    }

    omp_set_nested(0);

    printf("Suma wyrazów tablicy równolegle (2D): %lf\n", suma_parallel);

    //
    // Dodatkowa tablica
    //

    const int threads_count = 5;
    omp_set_num_threads(threads_count);
    double additional_array[threads_count];

#pragma omp parallel for default(none) shared(additional_array, a)
    for (int i = 0; i < WYMIAR; ++i) {
        int thread_id = omp_get_thread_num();
        for (int j = 0; j < WYMIAR; ++j) {
            additional_array[thread_id] += a[i][j];
        }
    }

    suma_parallel = 0.0;
    for (int i = 0; i < threads_count; ++i)
        suma_parallel += additional_array[i];

    printf("Suma wyrazów tablicy równolegle (dodatkowa tablica): %lf\n", suma_parallel);
}
