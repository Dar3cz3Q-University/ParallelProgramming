#include <pthread.h>
#include <stdio.h>

#define LICZBA_WATKOW 20

#define TABLE_ATTEMPT

void *zadanie_watku(void *arg_wsk) {
    int arg = *((int *)arg_wsk);

    int tid = pthread_self();

    printf("Id w watku: %d, argument: %d\n", tid, arg);
}

int main(int argc, char **argv) {
    pthread_t threads_ids[LICZBA_WATKOW];
    void *result;
    int i = 0;

#ifdef TABLE_ATTEMPT

    int args[LICZBA_WATKOW];

    for (i = 0; i < LICZBA_WATKOW; i++) {
        args[i] = i;
        pthread_create(&threads_ids[i], NULL, zadanie_watku, (void *)&args[i]);
    }

#else

    for (i = 0; i < LICZBA_WATKOW; i++)
        pthread_create(&threads_ids[i], NULL, zadanie_watku, (void *)&i);

#endif

    for (i = 0; i < LICZBA_WATKOW; i++)
        pthread_join(threads_ids[i], &result);
}
