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

    PackedData messages[NUMBER_OF_ELEMENTS];

    MPI_Status status;
    PackedData receivedMsg;

    if (rank == 0) {
        int position;
        char buffer[100];

        for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
            position = 0;
            messages[i].key = 0;
            messages[i].name_length = 0;
            strcpy(messages[i].name, "Darek");

            MPI_Pack(&messages[i].key, 1, MPI_INT, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);
            MPI_Pack(&messages[i].name_length, 1, MPI_INT, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);
            MPI_Pack(messages[i].name, strlen(messages[i].name), MPI_CHAR, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);

            int tag = i == NUMBER_OF_ELEMENTS - 1 ? TERMINATION_TAG : 0;
            MPI_Send(buffer, position, MPI_PACKED, next, tag, MPI_COMM_WORLD);

            printf("Proces %d wysłał dane: key = %d, name length = %d, name = %s\n", rank, messages[i].key, messages[i].name_length, messages[i].name);
        }
    } else if (rank != LAST) {
        int position;
        char buffer[100];
        while (1) {
            MPI_Recv(buffer, sizeof(buffer), MPI_PACKED, prev, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            position = 0;
            MPI_Unpack(buffer, sizeof(buffer), &position, &receivedMsg.key, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer, sizeof(buffer), &position, &receivedMsg.name_length, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer, sizeof(buffer), &position, receivedMsg.name, sizeof(receivedMsg.name), MPI_CHAR, MPI_COMM_WORLD);

            printf("Proces %d odebrał dane: key = %d, name length = %d, name = %s\n", rank, receivedMsg.key, receivedMsg.name_length, receivedMsg.name);

            processData(rank, &receivedMsg);

            printf("Proces %d zmienił dane: key = %d, name length = %d, name = %s\n", rank, receivedMsg.key, receivedMsg.name_length, receivedMsg.name);

            position = 0;
            MPI_Pack(&receivedMsg.key, 1, MPI_INT, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);
            MPI_Pack(&receivedMsg.name_length, 1, MPI_INT, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);
            MPI_Pack(receivedMsg.name, strlen(receivedMsg.name), MPI_CHAR, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);

            MPI_Send(buffer, position, MPI_PACKED, next, status.MPI_TAG, MPI_COMM_WORLD);

            if (status.MPI_TAG == TERMINATION_TAG)
                break;
        }
    }

    if (rank == LAST) {
        int position;
        char buffer[100];

        while (1) {
            MPI_Recv(buffer, sizeof(buffer), MPI_PACKED, prev, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            position = 0;
            MPI_Unpack(buffer, sizeof(buffer), &position, &receivedMsg.key, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer, sizeof(buffer), &position, &receivedMsg.name_length, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer, sizeof(buffer), &position, receivedMsg.name, sizeof(receivedMsg.name), MPI_CHAR, MPI_COMM_WORLD);

            printf("Proces %d odebrał dane: key = %d, name length = %d, name = %s\n", rank, receivedMsg.key, receivedMsg.name_length, receivedMsg.name);

            if (status.MPI_TAG == TERMINATION_TAG)
                break;
        }
    }

    MPI_Finalize();

    return 0;
}
