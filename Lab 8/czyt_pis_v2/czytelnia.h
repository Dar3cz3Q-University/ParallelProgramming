#define _OPEN_THREADS
#include <pthread.h>

#ifndef _czytelnia_
#define _czytelnia_

/*** Definicje typow zmiennych ***/
typedef struct {
    int l_p; // liczba piszacych
    int l_c; // liczba czytajacych
    pthread_mutex_t mutex;
    pthread_rwlock_t lock;
    int zasob;
} cz_t;

/*** Deklaracje procedur interfejsu ***/
void inicjuj(cz_t *czytelnia_p);
void czytam(cz_t *czytelnia_p);
void pisze(cz_t *czytelnia_p);

int my_read_lock_lock(cz_t *czytelnia_p);
int my_read_lock_unlock(cz_t *czytelnia_p);
int my_write_lock_lock(cz_t *czytelnia_p);
int my_write_lock_unlock(cz_t *czytelnia_p);

#endif
