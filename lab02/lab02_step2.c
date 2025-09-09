#include <stdio.h>

#define N 10

int load(double x[N]);
int print(const double x[N]);
double computeprod(const double x[N]);
int printprod(double product);


int main() {
    double data[N];
    double prod = 1.0;

    load(data);
    print(data);
    prod = computeprod(data);
    printprod(prod);

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

double computeprod(const double x[N]) {
    int i;
    double product = 1.0;

    for (i = 0; i < N; i++) {
        product *= x[i];
    }

    return product;
}

int printprod(double product) {
    printf("\n The product of the array is:%g\n", product);

    return 0;
}
