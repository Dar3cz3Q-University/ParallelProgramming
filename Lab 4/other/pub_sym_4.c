#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 3

struct struktura_t {
    int l_wkf;
    pthread_mutex_t *tab_kuf;
    int l_kr;
    pthread_mutex_t *tab_kran;
};
struct struktura_t pub_wsk;

void *watek_klient(void *arg);

int main(void) {
    pthread_t *tab_klient;
    int *tab_klient_id;

    int l_kl, l_kf, l_kr, i;

    printf("\nLiczba klientow: ");
    scanf("%d", &l_kl);

    printf("\nLiczba kufli: ");
    scanf("%d", &l_kf);
    pub_wsk.l_wkf = l_kf;

    printf("\nLiczba kranow: ");
    scanf("%d", &l_kr);
    pub_wsk.l_kr = l_kr;

    tab_klient = (pthread_t *)malloc(l_kl * sizeof(pthread_t));
    tab_klient_id = (int *)malloc(l_kl * sizeof(int));
    for (i = 0; i < l_kl; i++)
        tab_klient_id[i] = i;

    pub_wsk.tab_kuf = (pthread_mutex_t *)malloc(l_kf * sizeof(pthread_mutex_t));
    for (i = 0; i < l_kf; i++)
        pthread_mutex_init(&pub_wsk.tab_kuf[i], NULL);

    pub_wsk.tab_kran = (pthread_mutex_t *)malloc(l_kr * sizeof(pthread_mutex_t));
    for (i = 0; i < l_kr; i++)
        pthread_mutex_init(&pub_wsk.tab_kran[i], NULL);

    printf("\nOtwieramy pub (simple)!\n");
    printf("\nLiczba wolnych kufli %d\n", l_kf);

    for (i = 0; i < l_kl; i++) {
        pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]);
    }
    for (i = 0; i < l_kl; i++) {
        pthread_join(tab_klient[i], NULL);
    }
    printf("\nZamykamy pub!\n");

    for (i = 0; i < l_kf; i++)
        pthread_mutex_destroy(&pub_wsk.tab_kuf[i]);

    for (i = 0; i < l_kr; i++)
        pthread_mutex_destroy(&pub_wsk.tab_kran[i]);

    free(tab_klient);
    free(tab_klient_id);
    free(pub_wsk.tab_kuf);
    free(pub_wsk.tab_kran);
}

void *watek_klient(void *arg_wsk) {

    int moj_id = *((int *)arg_wsk);

    int i, i_wypite, kran, kufel, result;

    int ile_musze_wypic = ILE_MUSZE_WYPIC;

    printf("\nKlient %d, wchodzę do pubu\n", moj_id);

    for (i_wypite = 0; i_wypite < ile_musze_wypic; i_wypite++) {

        printf("\nKlient %d, wybieram kufel\n", moj_id);

        result = 0;
        do {
            for (i = 0; i < pub_wsk.l_wkf; i++) {
                if (pthread_mutex_trylock(&pub_wsk.tab_kuf[i]) == 0) {
                    kufel = i;
                    result = 1;
                    break;
                }
            }
        } while (result == 0);

        printf("\nKlient %d, wybrałem kufel %d\n", moj_id, kufel);

        printf("\nKlient %d, wybieram kran\n", moj_id);

        result = 0;
        do {
            for (i = 0; i < pub_wsk.l_kr; i++) {
                if (pthread_mutex_trylock(&pub_wsk.tab_kran[i]) == 0) {
                    kran = i;
                    result = 1;
                    break;
                }
            }
        } while (result == 0);

        printf("\nKlient %d, nalewam z kranu %d\n", moj_id, kran);
        usleep(100);

        pthread_mutex_unlock(&pub_wsk.tab_kran[kran]);

        if (kran == 0)
            printf("\nKlient %d, pije piwo Guinnessz z kufla: %d\n", moj_id, kufel);
        else if (kran == 1)
            printf("\nKlient %d, pije piwo Żywiec z kufla: %d\n", moj_id, kufel);
        else if (kran == 2)
            printf("\nKlient %d, pije piwo Heineken z kufla: %d\n", moj_id, kufel);
        else if (kran == 3)
            printf("\nKlient %d, pije piwo Okocim z kufla: %d\n", moj_id, kufel);
        else if (kran == 4)
            printf("\nKlient %d, pije piwo Karlsberg z kufla: %d\n", moj_id, kufel);
        // itd., itp.

        usleep(100);

        pthread_mutex_unlock(&pub_wsk.tab_kuf[kufel]);

        printf("\nKlient %d, odkladam kufel %d\n", moj_id, kufel);
    }

    return (NULL);
}
