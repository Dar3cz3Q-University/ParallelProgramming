#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "czytelnia.h"

/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(cz_t *cz_p) {
    pthread_mutex_lock(&cz_p->mutex);

    if (cz_p->l_p > 0 || cz_p->waiting_writers > 0) {
        cz_p->waiting_readers++;
        pthread_cond_wait(&cz_p->read_cond, &cz_p->mutex);
        cz_p->waiting_readers--;
    }

    cz_p->l_c++;
    pthread_cond_signal(&cz_p->read_cond);
    pthread_mutex_unlock(&cz_p->mutex);
}

int my_read_lock_unlock(cz_t *cz_p) {

    pthread_mutex_lock(&cz_p->mutex);

    cz_p->l_c--;

    if (cz_p->l_c == 0)
        pthread_cond_signal(&cz_p->write_cond);

    pthread_mutex_unlock(&cz_p->mutex);
}

int my_write_lock_lock(cz_t *cz_p) {

    pthread_mutex_lock(&cz_p->mutex);

    if (cz_p->l_p > 0 || cz_p->l_c > 0) {
        cz_p->waiting_writers++;
        pthread_cond_wait(&cz_p->write_cond, &cz_p->mutex);
        cz_p->waiting_writers--;
    }

    cz_p->l_p++;
    pthread_mutex_unlock(&cz_p->mutex);
}

int my_write_lock_unlock(cz_t *cz_p) {

    pthread_mutex_lock(&cz_p->mutex);

    cz_p->l_p--;

    if (cz_p->waiting_readers > 0)
        pthread_cond_broadcast(&cz_p->read_cond);
    else
        pthread_cond_signal(&cz_p->write_cond);

    pthread_mutex_unlock(&cz_p->mutex);
}

void inicjuj(cz_t *cz_p) {

    cz_p->l_p = 0;
    cz_p->l_c = 0;
    pthread_mutex_init(&cz_p->mutex, NULL);
    pthread_cond_init(&cz_p->read_cond, NULL);
    pthread_cond_init(&cz_p->write_cond, NULL);
    cz_p->waiting_readers = 0;
    cz_p->waiting_writers = 0;
}

void czytam(cz_t *cz_p) {
    printf("\t\t\t\t\tczytam:  l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p);

    if (cz_p->l_p > 1 || (cz_p->l_p == 1 && cz_p->l_c > 0) || cz_p->l_p < 0 || cz_p->l_c < 0) {
        printf("Blad: ....\n");
        exit(0);
    }

    usleep(rand() % 3000000);
}

void pisze(cz_t *cz_p) {
    printf("\t\t\t\t\tpisze:   l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p);

    if (cz_p->l_p > 1 || (cz_p->l_p == 1 && cz_p->l_c > 0) || cz_p->l_p < 0 || cz_p->l_c < 0) {
        printf("Blad: ....\n");
        exit(0);
    }

    usleep(rand() % 3000000);
}
