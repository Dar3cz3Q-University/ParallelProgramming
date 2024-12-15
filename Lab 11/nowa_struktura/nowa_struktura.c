#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_OF_ELEMENTS 5

typedef struct {
    int key;
    int name_length;
    char name[50];
} PackedData;

void processData(int rank, PackedData *data) {
    if (rank == 1) {
        data->key = 5;
    } else if (rank == 2) {
        data->name_length = strlen(data->name);
    } else if (rank == 3) {
        for (int i = 0; i < data->name_length; i++)
            data->name[i] += data->key;
    }
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int LAST = size - 1;
    const int TERMINATION_TAG = 99;

    int prev = rank == 0 ? size - 1 : rank - 1;
    int next = rank == size - 1 ? 0 : rank + 1;

    MPI_Datatype CUSTOM_PACKED_DATA;
    int block_lengths[3] = {1, 1, 50};
    MPI_Aint displacements[3];
    MPI_Datatype types[3] = {MPI_INT, MPI_INT, MPI_CHAR};

    displacements[0] = offsetof(PackedData, key);
    displacements[1] = offsetof(PackedData, name_length);
    displacements[2] = offsetof(PackedData, name);

    MPI_Type_create_struct(3, block_lengths, displacements, types, &CUSTOM_PACKED_DATA);
    MPI_Type_commit(&CUSTOM_PACKED_DATA);

    PackedData messages[NUMBER_OF_ELEMENTS];

    MPI_Status status;
    PackedData receivedMsg;

    if (rank == 0) {
        for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
            messages[i].key = 0;
            messages[i].name_length = 0;
            strcpy(messages[i].name, "Darek");

            int tag = i == NUMBER_OF_ELEMENTS - 1 ? TERMINATION_TAG : 0;
            MPI_Send(&messages[i], 1, CUSTOM_PACKED_DATA, next, tag, MPI_COMM_WORLD);

            printf("Proces %d wysłał dane: key = %d, name length = %d, name = %s\n", rank, messages[i].key, messages[i].name_length, messages[i].name);
        }
    } else if (rank != LAST) {
        while (1) {
            MPI_Recv(&receivedMsg, 1, CUSTOM_PACKED_DATA, prev, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            printf("Proces %d odebrał dane: key = %d, name length = %d, name = %s\n", rank, receivedMsg.key, receivedMsg.name_length, receivedMsg.name);
            processData(rank, &receivedMsg);
            printf("Proces %d zmienił dane: key = %d, name length = %d, name = %s\n", rank, receivedMsg.key, receivedMsg.name_length, receivedMsg.name);

            MPI_Send(&receivedMsg, 1, CUSTOM_PACKED_DATA, next, status.MPI_TAG, MPI_COMM_WORLD);

            if (status.MPI_TAG == TERMINATION_TAG)
                break;
        }
    }

    if (rank == LAST) {
        while (1) {
            MPI_Recv(&receivedMsg, 1, CUSTOM_PACKED_DATA, prev, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            printf("Proces %d odebrał dane: key = %d, name length = %d, name = %s\n", rank, receivedMsg.key, receivedMsg.name_length, receivedMsg.name);

            if (status.MPI_TAG == TERMINATION_TAG)
                break;
        }
    }

    MPI_Type_free(&CUSTOM_PACKED_DATA);
    MPI_Finalize();

    return 0;
}
