#include <mpi.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    float value;
    char name[50];
} PackedData;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int LAST = size - 1;

    int prev = rank == 0 ? size - 1 : rank - 1;
    int next = rank == size - 1 ? 0 : rank + 1;

    PackedData message;
    message.id = rank;
    message.value = 3.14;
    strcpy(message.name, "Darek");

    PackedData receivedMsg;

    if (rank == 0) {
        // Pierwszy proces
        int position = 0;
        char buffer[100];

        MPI_Pack(&message.id, 1, MPI_INT, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);
        MPI_Pack(&message.value, 1, MPI_FLOAT, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);
        MPI_Pack(&message.name, strlen(message.name), MPI_CHAR, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);

        MPI_Send(buffer, position, MPI_PACKED, next, 0, MPI_COMM_WORLD);

        printf("Proces %d wysłał dane: id = %d, value = %.2f, name = %s\n", rank, message.id, message.value, message.name);
    } else if (rank != LAST) {
        // Procesy srodkowe
        int position = 0;
        char buffer[100];

        MPI_Recv(buffer, sizeof(buffer), MPI_PACKED, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MPI_Unpack(buffer, sizeof(buffer), &position, &receivedMsg.id, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, sizeof(buffer), &position, &receivedMsg.value, 1, MPI_FLOAT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, sizeof(buffer), &position, receivedMsg.name, sizeof(receivedMsg.name), MPI_CHAR, MPI_COMM_WORLD);

        printf("Proces %d odebrał dane: id = %d, value = %.2f, name = %s\n", rank, receivedMsg.id, receivedMsg.value, receivedMsg.name);

        receivedMsg.id += 1;
        receivedMsg.value *= 2;
        strcat(receivedMsg.name, "+");

        printf("Proces %d zmienił dane na: id = %d, value = %.2f, name = %s\n", rank, receivedMsg.id, receivedMsg.value, receivedMsg.name);

        position = 0;

        MPI_Pack(&receivedMsg.id, 1, MPI_INT, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);
        MPI_Pack(&receivedMsg.value, 1, MPI_FLOAT, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);
        MPI_Pack(&receivedMsg.name, strlen(receivedMsg.name), MPI_CHAR, buffer, sizeof(buffer), &position, MPI_COMM_WORLD);

        MPI_Send(buffer, position, MPI_PACKED, next, 0, MPI_COMM_WORLD);
    }

    // Ostatni proces
    if (rank == LAST) {
        int position = 0;
        char buffer[100];

        MPI_Recv(buffer, sizeof(buffer), MPI_PACKED, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MPI_Unpack(buffer, sizeof(buffer), &position, &receivedMsg.id, 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, sizeof(buffer), &position, &receivedMsg.value, 1, MPI_FLOAT, MPI_COMM_WORLD);
        MPI_Unpack(buffer, sizeof(buffer), &position, receivedMsg.name, sizeof(receivedMsg.name), MPI_CHAR, MPI_COMM_WORLD);

        printf("Proces %d odebrał dane: id = %d, value = %.2f, name = %s\n", rank, receivedMsg.id, receivedMsg.value, receivedMsg.name);
    }

    MPI_Finalize();

    return 0;
}
