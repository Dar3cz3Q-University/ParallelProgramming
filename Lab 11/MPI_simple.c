#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

int main(int argc, char **argv) {

    int rank, ranksent, size, source, dest, tag, i;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int nameLength;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Get_processor_name(hostname, &nameLength);

    char msg[MPI_MAX_PROCESSOR_NAME];

    snprintf(msg, MPI_MAX_PROCESSOR_NAME, "%s - rank: %d", hostname, rank);

    char receivedName[MPI_MAX_PROCESSOR_NAME];

    if (size > 1) {

        if (rank != 0) {
            dest = 0;
            tag = 0;

            MPI_Send(&rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
            MPI_Send(msg, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        } else {

            for (i = 1; i < size; i++) {

                MPI_Recv(&ranksent, 1, MPI_INT, MPI_ANY_SOURCE,
                         MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("Liczba od procesu o randze (status.MPI_SOURCE ->) %d: %d (i=%d)\n",
                       status.MPI_SOURCE, ranksent, i);

                MPI_Recv(receivedName, MPI_MAX_PROCESSOR_NAME, MPI_CHAR, status.MPI_SOURCE,
                         MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("Dane od procesu o randze (status.MPI_SOURCE ->) %d: %s (i=%d)\n",
                       status.MPI_SOURCE, receivedName, i);
            }
        }

    } else {
        printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
    }

    MPI_Finalize();

    return (0);
}
