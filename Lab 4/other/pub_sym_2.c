#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 3

int l_kf;

pthread_mutex_t blokada;

void *watek_klient(void *arg);

int main(void) {

    pthread_t *tab_klient;
    int *tab_klient_id;

    pthread_mutex_init(&blokada, NULL);

    int l_kl, l_kr, i;

    printf("\nLiczba klientow: ");
    scanf("%d", &l_kl);

    printf("\nLiczba kufli: ");
    scanf("%d", &l_kf);

    // printf("\nLiczba kranow: "); scanf("%d", &l_kr);
    l_kr = 1000000000; // wystarczająco dużo, żeby nie było rywalizacji

    tab_klient = (pthread_t *)malloc(l_kl * sizeof(pthread_t));
    tab_klient_id = (int *)malloc(l_kl * sizeof(int));
    for (i = 0; i < l_kl; i++)
        tab_klient_id[i] = i;

    printf("\nOtwieramy pub (simple)!\n");
    printf("\nLiczba wolnych kufli %d\n", l_kf);

    for (i = 0; i < l_kl; i++) {
        pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]);
    }
    for (i = 0; i < l_kl; i++) {
        pthread_join(tab_klient[i], NULL);
    }
    printf("\nZamykamy pub!\n");

    printf("Liczba kufli: %d\n", l_kf);

    pthread_mutex_destroy(&blokada);

    free(tab_klient);
    free(tab_klient_id);
}

void *watek_klient(void *arg_wsk) {

    int moj_id = *((int *)arg_wsk);

    int i, j, kufel, result;
    int ile_musze_wypic = ILE_MUSZE_WYPIC;

    long int wykonana_praca = 0;

    printf("\nKlient %d, wchodzę do pubu\n", moj_id);

    for (i = 0; i < ile_musze_wypic; i++) {

        printf("\nKlient %d, wybieram kufel\n", moj_id);

        result = 0;

        do {
            pthread_mutex_lock(&blokada);
            if (l_kf > 0) {
                l_kf--;
                result = 1;
            }
            pthread_mutex_unlock(&blokada);

            if (result == 0) {
                printf("\nKlient %d, czekanie na wolny kufel...\n", moj_id);
                usleep(300);
            }

        } while (result == 0);

        printf("\nKlient %d, liczba kufli po pobraniu: %d\n", moj_id, l_kf);

        j = 0;
        printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j);
        usleep(30);

        printf("\nKlient %d, pije\n", moj_id);
        nanosleep((struct timespec[]){{0, 50000000L}}, NULL);

        printf("\nKlient %d, odkladam kufel\n", moj_id);

        pthread_mutex_lock(&blokada);
        l_kf++;
        pthread_mutex_unlock(&blokada);

        printf("\nKlient %d, liczba kufli po odlozeniu: %d\n", moj_id, l_kf);
    }

    printf("\nKlient %d, wychodzę z pubu; wykonana praca %ld\n",
           moj_id, wykonana_praca);

    return (NULL);
}
