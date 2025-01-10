#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define SCALAR double

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(int argc, char **argv) {

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int max_liczba_wyrazow = 0;

    if (rank == 0) {
        printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
        scanf("%d", &max_liczba_wyrazow);
    }

    MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (max_liczba_wyrazow <= 0) {
        MPI_Finalize();
        return 1;
    }

    SCALAR suma_plus = 0.0;
    SCALAR suma_minus = 0.0;

    int start = (int)ceil((SCALAR)max_liczba_wyrazow / size) * rank;
    int end = 0;
    if (rank == size - 1)
        end = max_liczba_wyrazow;
    else
        end = (int)ceil((SCALAR)max_liczba_wyrazow / size) * (rank + 1);

    for (int i = start; i < end; i++) {
        int j = 1 + 4 * i;
        suma_plus += 1.0 / j;
        suma_minus += 1.0 / (j + 2.0);
    }

    SCALAR subtotal = suma_plus - suma_minus;

    SCALAR result = 0.0;

    MPI_Reduce(&subtotal, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    printf("Before all reduce - Rank: %d, result: %lf\n", rank, result);

    MPI_Allreduce(&subtotal, &result, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    printf("After all reduce - Rank: %d, result: %lf\n", rank, result);

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        SCALAR pi_approx = 4 * result;

        printf("PI obliczone: \t\t\t%20.15lf\n", pi_approx);
        printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
    }

    MPI_Finalize();
}
