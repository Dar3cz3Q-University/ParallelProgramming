#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t resultex;

double funkcja(double x);

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w);

static int l_w_global = 0;

static double calka_global = 0.0;
static double a_global;
static double b_global;
static double dx_global;
static int N_global;

void *calka_fragment_petli_w(void *arg_wsk);

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w) {

    int N = ceil((b - a) / dx);
    double dx_adjust = (b - a) / N;

    printf("Obliczona liczba trapezów: N = %d, dx_adjust = %lf\n", N, dx_adjust);
    // printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);

    l_w_global = l_w;
    a_global = a;
    b_global = b;
    dx_global = dx_adjust;
    N_global = N;

    // tworzenie struktur danych do obsługi wielowątkowości
    pthread_t *pid = malloc(l_w * sizeof(pthread_t));
    int *custom_id = malloc(l_w * sizeof(int));

    pthread_mutex_init(&resultex, NULL);

    // tworzenie wątków
    for (int i = 0; i < l_w; i++) {
        custom_id[i] = i;
        pthread_create(&pid[i], NULL, calka_fragment_petli_w, (void *)&custom_id[i]);
    }

    // oczekiwanie na zakończenie pracy wątków
    for (int i = 0; i < l_w; i++)
        pthread_join(pid[i], NULL);

    free(pid);
    free(custom_id);

    pthread_mutex_destroy(&resultex);

    return (calka_global);
}

void *calka_fragment_petli_w(void *arg_wsk) {

    int my_id = *((int *)arg_wsk);

    double a, b, dx; // skąd pobrać dane a, b, dx, N, l_w ?
    int N, l_w;      // wariant 1 - globalne

    a = a_global; // itd. itp. - wartości globalne nadaje calka_zrownoleglenie_petli
    b = b_global;
    dx = dx_global;
    N = N_global;
    l_w = l_w_global;

    // dekompozycja cykliczna
    // double my_start = my_id;
    // double my_end = N;
    // double my_stride = l_w;

    // dekompozycja blokowa
    double per_thread = ceil((float)N / l_w);
    double my_start = per_thread * my_id;
    double my_end = per_thread * (my_id + 1);
    my_end = my_end > N ? N : my_end;
    double my_stride = 1;

    // something else ? (dekompozycja blokowo-cykliczna)

    // printf("\nWątek %d: my_start %f, my_end %f, my_stride %f\n", my_id, my_start, my_end, my_stride);

    double i;
    double calka = 0.0;
    for (i = my_start; i < my_end; i += my_stride) {

        double x1 = a + i * dx;
        calka += 0.5 * dx * (funkcja(x1) + funkcja(x1 + dx));
        // printf("i %f, x1 %lf, funkcja(x1) %lf, całka = %.15lf\n", i, x1, funkcja(x1), calka);
    }

    pthread_mutex_lock(&resultex);
    calka_global += calka;
    pthread_mutex_unlock(&resultex);
}
