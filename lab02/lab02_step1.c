/*******************************************************************************
 *                                                                             *
 *  @file   lab02_step1.c                                                      *
 *  @author Christos Kaldis                                                    *
 *  @date   09 Sept 2025                                                       *
 *  @brief  First step is about understanding basic operations of arrays.      *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>

#define N 10
#define M 5

int main() {
    int i, j;
    double data[N][M];
    double prod = 1.0;

    /* The three double for below can be combined into one. */
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            data[i][j] = ((double) i+j+N) / N ;
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            printf(" %g\t", data[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            prod *= data[i][j];
        }
    }

    printf("\n%g\n", prod);

    return 0;
}
