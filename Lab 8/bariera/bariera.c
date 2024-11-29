#include <pthread.h>
#include <stdio.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t overflow_cond = PTHREAD_COND_INITIALIZER;

static int thread_count;
static int counter;

void bariera_init(int n) {
    thread_count = n;
    counter = 0;
}

void bariera(void) {
    pthread_mutex_lock(&mutex);

    counter++;
    if (counter == thread_count) {
        counter = 0;
        pthread_cond_broadcast(&overflow_cond);
    } else {
        pthread_cond_wait(&overflow_cond, &mutex);
    }

    pthread_mutex_unlock(&mutex);
}
