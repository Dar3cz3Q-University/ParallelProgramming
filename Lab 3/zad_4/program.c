#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define LICZBA_WATKOW 3

size_t stack_size = 1024 * 1024;

void *zadanie_watku(void *arg_wsk) {

    int arg = *((int *)arg_wsk);

    sleep(1);

    pthread_attr_t attr;
    pthread_t tid = pthread_self();

    pthread_getattr_np(tid, &attr);

    size_t size;
    pthread_attr_getstacksize(&attr, &size);

    int detach_state;
    pthread_attr_getdetachstate(&attr, &detach_state);

    void *stack_address;
    pthread_attr_getstack(&attr, &stack_address, &stack_size);

    printf("%d: Wielkosc stosu: %ld\n", arg, size);
    printf("%d: Stan watku: %d\n", arg, detach_state);
    printf("%d: Adres stosu: %p\n", arg, stack_address);
}

int main(int argc, char **argv) {
    pthread_t threads_ids[LICZBA_WATKOW];
    pthread_attr_t thread_attr[LICZBA_WATKOW];
    int args[LICZBA_WATKOW];

    void *result;
    int i = 0;

    void *new_stack = malloc(stack_size);

    printf("Przygotowany adres stosu: %p\n", new_stack);

    for (i = 0; i < LICZBA_WATKOW; i++)
        pthread_attr_init(&thread_attr[i]);

    pthread_attr_setstacksize(&thread_attr[0], stack_size);
    pthread_attr_setstack(&thread_attr[2], new_stack, stack_size);

    for (i = 0; i < LICZBA_WATKOW; i++) {
        args[i] = i + 1;
        pthread_create(&threads_ids[i], &thread_attr[i], zadanie_watku, (void *)&args[i]);
    }

    pthread_detach(threads_ids[1]);

    for (i = 0; i < LICZBA_WATKOW; i++)
        pthread_join(threads_ids[i], &result);

    for (i = 0; i < LICZBA_WATKOW; i++)
        pthread_attr_destroy(&thread_attr[i]);

    free(new_stack);
}
