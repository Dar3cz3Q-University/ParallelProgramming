#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define WYMIAR 18

// export OMP_NUM_THREADS=4
// omp_set_num_threads(4);
// ... num_threads(4)

int main() {
    double a[WYMIAR];

#pragma omp parallel for default(none) shared(a)
    for (int i = 0; i < WYMIAR; i++)
        a[i] = 1.02 * i;

    //
    // pętla sekwencyjna
    //

    double suma = 0.0;
    for (int i = 0; i < WYMIAR; i++) {
        suma += a[i];
    }

    printf("Suma wyrazów tablicy: %lf\n", suma);

    //
    // rownolegle (static)
    //

    double suma_parallel = 0.0;
#pragma omp parallel for default(none) shared(a) reduction(+ : suma_parallel) schedule(static) ordered
    for (int i = 0; i < WYMIAR; i++) {
        int id_w = omp_get_thread_num();
        suma_parallel += a[i];
#pragma omp ordered
        printf("a[%2d]->W_%1d  \n", i, id_w);
    }

    printf("\nSuma wyrazów tablicy równolegle (z klauzulą - (static)): %lf\n", suma_parallel);

    //
    // rownolegle (static, 3)
    //

    suma_parallel = 0.0;
#pragma omp parallel for default(none) shared(a) reduction(+ : suma_parallel) schedule(static, 3) ordered
    for (int i = 0; i < WYMIAR; i++) {
        int id_w = omp_get_thread_num();
        suma_parallel += a[i];
#pragma omp ordered
        printf("a[%2d]->W_%1d  \n", i, id_w);
    }

    printf("\nSuma wyrazów tablicy równolegle (z klauzulą - (static, 3)): %lf\n", suma_parallel);

    //
    // rownolegle (dynamic)
    //

    suma_parallel = 0.0;
#pragma omp parallel for default(none) shared(a) reduction(+ : suma_parallel) schedule(dynamic) ordered
    for (int i = 0; i < WYMIAR; i++) {
        int id_w = omp_get_thread_num();
        suma_parallel += a[i];
#pragma omp ordered
        printf("a[%2d]->W_%1d  \n", i, id_w);
    }

    printf("\nSuma wyrazów tablicy równolegle (z klauzulą - (dynamic)): %lf\n", suma_parallel);

    //
    // rownolegle (dynamic, 3)
    //

    suma_parallel = 0.0;
#pragma omp parallel for default(none) shared(a) reduction(+ : suma_parallel) schedule(dynamic, 3) ordered
    for (int i = 0; i < WYMIAR; i++) {
        int id_w = omp_get_thread_num();
        suma_parallel += a[i];
#pragma omp ordered
        printf("a[%2d]->W_%1d  \n", i, id_w);
    }

    printf("\nSuma wyrazów tablicy równolegle (z klauzulą - (dynamic, 3)): %lf\n", suma_parallel);
}
