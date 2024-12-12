#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

#ifdef _OPENMP
    printf("\nKompilator rozpoznaje dyrektywy OpenMP\n");
#endif

    omp_set_num_threads(5);

    int liczba_watkow;

    int a_shared = 1;
    int b_private = 2;
    int c_firstprivate = 3;
    int e_atomic = 5;

    int static f_threadprivate = 0;
#pragma omp threadprivate(f_threadprivate)

    printf("przed wejsciem do obszaru rownoleglego -  nr_threads %d, thread ID %d\n",
           omp_get_num_threads(), omp_get_thread_num());
    printf("\ta_shared \t= %d\n", a_shared);
    printf("\tb_private \t= %d\n", b_private);
    printf("\tc_firstprivate \t= %d\n", c_firstprivate);
    printf("\te_atomic \t= %d\n", e_atomic);
    printf("\tf_threadprivate = %d\n", f_threadprivate);

#pragma omp parallel default(none) shared(a_shared, e_atomic) private(b_private) firstprivate(c_firstprivate)
    {
        int i;
        int d_local_private;
        d_local_private = a_shared + c_firstprivate; // WAR [40 linia zmieni nam a_shared po zapisaniu d_local_private]

#pragma omp barrier

#pragma omp critical
        {
            for (i = 0; i < 10; i++) {
                a_shared++; // RAW, WAW, WAR [zależność w lini 34, po rozpisaniu pętli i inkrementacji]
            }
        }

        for (i = 0; i < 10; i++) {
            c_firstprivate += omp_get_thread_num();
        }

        for (i = 0; i < 10; i++) {
#pragma omp atomic
            e_atomic += omp_get_thread_num(); // RAW, WAW, WAR [zależność w lini 42, po rozpisaniu pętli i inkrementacji]
        }

        f_threadprivate = omp_get_thread_num();

#pragma omp barrier

#pragma omp critical
        {

            printf("\nw obszarze równoległym: aktualna liczba watkow %d, moj ID %d\n",
                   omp_get_num_threads(), omp_get_thread_num());

            printf("\ta_shared \t= %d\n", a_shared);
            printf("\tb_private \t= %d\n", b_private);
            printf("\tc_firstprivate \t= %d\n", c_firstprivate);
            printf("\td_local_private = %d\n", d_local_private);
            printf("\te_atomic \t= %d\n", e_atomic);
            printf("\td_local_private \t= %d\n", d_local_private);
        }
    }

#pragma omp parallel default(none)
    {
#pragma omp critical
        {
            printf("\nw obszarze równoległym (drugim): aktualna liczba watkow %d, moj ID %d\n",
                   omp_get_num_threads(), omp_get_thread_num());
            printf("\tf_threadprivate = %d\n", f_threadprivate);
        }
    }

    printf("\npo zakonczeniu obszaru rownoleglego:\n");
    printf("\ta_shared \t= %d\n", a_shared);
    printf("\tb_private \t= %d\n", b_private);
    printf("\tc_firstprivate \t= %d\n", c_firstprivate);
    printf("\te_atomic \t= %d\n", e_atomic);
    printf("\tf_threadprivate = %d\n", f_threadprivate);
}
