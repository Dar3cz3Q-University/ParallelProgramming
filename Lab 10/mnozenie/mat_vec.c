#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void mat_vec_row(double *a, double *x, double *y, int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++) {
            y[i] += a[n * i + j] * x[j];
        }
    }
}

void mat_vec_row_row_decomp(double *a, double *x, double *y, int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++) {
            y[i] += a[n * i + j] * x[j];
        }
    }
}

void mat_vec_row_col_decomp(double *a, double *x, double *y, int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++) {
            y[i] += a[n * i + j] * x[j];
        }
    }
}

void mat_vec_col(double *a, double *x, double *y, int n) {

    int i, j;

    for (i = 0; i < n; i++)
        y[i] = 0.0;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            y[i] += a[i + j * n] * x[j];
        }
    }
}

void mat_vec_col_col_decomp(double *a, double *x, double *y, int n) {

    int i, j;

    for (i = 0; i < n; i++)
        y[i] = 0.0;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            y[i] += a[i + j * n] * x[j];
        }
    }
}

void mat_vec_col_row_decomp(double *a, double *x, double *y, int n) {

    int i, j;

    for (i = 0; i < n; i++)
        y[i] = 0.0;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            y[i] += a[i + j * n] * x[j];
        }
    }
}
