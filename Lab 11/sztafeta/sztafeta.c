#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int LAST = size - 1;

    int prev = rank == 0 ? size - 1 : rank - 1;
    int next = rank == size - 1 ? 0 : rank + 1;

    int message = 0;
    int receivedMsg;

    if (rank == 0) {
        // Pierwszy proces
        MPI_Send(&message, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    } else if (rank != LAST) {
        // Procesy srodkowe
        MPI_Recv(&receivedMsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        message = receivedMsg + 5;
        MPI_Send(&message, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    }

    // Ostatni proces
    if (rank == LAST)
        MPI_Recv(&receivedMsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    if (rank != 0)
        printf("Proces: %d, odebral liczbe: %d, od procesu: %d\n", rank, receivedMsg, prev);

    MPI_Finalize();

    return 0;
}
