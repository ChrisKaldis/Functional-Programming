/*******************************************************************************
 *                                                                             *
 *  @file   lab02_step2.c                                                      *
 *  @author Christos Kaldis                                                    *
 *  @date   09 Sept 2025                                                       *
 *  @brief  Perform basic calculations using arrays.                           *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* Array dimensions. */
#define N 10
#define M 5

int load_array(double x[N][M]);
int print_array(const double * x, int rows, int cols);
double compute_prod_sum(const double x[N][M], double * sum);
int print_prod_sum(const double product, const double sum);
int transpose_array(const double x[N][M], double xT[M][N]);


int main() {
    double data[N][M], dataT[M][N];
    double prod;
    double sum = 0.0;

    load_array(data);
    print_array(data, N, M);
    prod = compute_prod_sum(data, &sum);
    print_prod_sum(prod, sum);
    transpose_array(data, dataT);
    print_array(data, M, N);

    return EXIT_SUCCESS;
}

/**
 * @brief Initialize a 2D array.
 * 
 * @param x A 2 dimensional array.
 * 
 * @return Returns EXIT_SUCCESS upon successful completion.
 */
int load_array(double x[N][M]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            x[i][j] = ((double) i + j + N) / N ;
        }
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Prints a 2D array by calculating 1D indices.
 * 
 * @param x A 2 dimensional array.
 * @param rows Number of array's rows.
 * @param cols Number of array's columns.
 * 
 * @return Returns EXIT_SUCCESS upon successful completion.
 */
int print_array(const double * x, int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf(" %g\t", x[i * cols + j]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Computes the product and sum of a 2D array.
 * 
 * @param[in] x A 2 dimensional array.
 * @param[out] sum Points to the sum of an array.
 * 
 * @return The product of an array.
 * 
 * @note Implemented this way in order to see the use of a pointer.
 */
double compute_prod_sum(const double x[N][M], double * sum) {
    int i, j;
    double product = 1.0;

    /* Faster because we use one loop, separating them 
    can make the code easier to read and reuse.*/
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            product *= x[i][j];
            *sum += x[i][j];
        }
    }

    return product;
}

/**
 * @brief Prints the product and the sum of an array.
 * 
 * @param product The product of an array.
 * @param sum The sum of an array.
 * 
 * @return Returns EXIT_SUCCESS upon successful completion.
 */
int print_prod_sum(const double product, const double sum) {
    printf("\n The product of the array is: %g\n", product);
    printf("\n The sum of the array is: %g\n\n", sum);

    return EXIT_SUCCESS;
}

/**
 * @brief Computes the transpose of a 2D array (matrix).
 * @details This function takes an input matrix of size N x M and calculates its
 * transpose, storing the result in an output matrix of size M x N.
 * The transpose of a matrix is formed by interchanging its rows
 * and columns.
 * 
 * @param[in] x The original N x M source matrix to be transposed.
 * @param[out] xT The M x N destination matrix where the transposed result
 * will be stored.
 *
 * @return Returns EXIT_SUCCESS upon successful completion.
 */
int transpose_array(const double x[N][M], double xT[M][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            xT[j][i] = x[i][j];
        }
    }

    return EXIT_SUCCESS;
}
