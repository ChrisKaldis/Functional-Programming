#include <stdio.h>

#define N 10

int load(double x[N]);
int print(const double x[N]);
double computeprodsum(const double x[N], double * sum);
int printprodsum(const double product, const double sum);


int main() {
    double data[N];
    double prod;
    double sum = 0.0;

    load(data);
    print(data);
    prod = computeprodsum(data, &sum);
    printprodsum(prod, sum);

    return 0;
}

int load(double x[N]) {
    int i;

    for (i = 0; i < N; i++) {
        x[i] = ((double) i + N) / N ;
    }

    return 0;
}

int print(const double x[N]) {
    int i;

    for (i = 0; i < N; i++) {
        printf(" %g ", x[i]);
    }

    return 0;
}

double computeprodsum(const double x[N], double * sum) {
    int i;
    double product = 1.0;

    for (i = 0; i < N; i++) {
        product *= x[i];
        *sum += x[i];
    }

    return product;
}

int printprodsum(const double product, const double sum) {
    printf("\n The product of the array is: %g\n", product);
    printf("\n The sum of the array is: %g\n", sum);

    return 0;
}
