#include <stdio.h>

void printnchars(int n, char ch);
void squaren(int n);

int main() {
    squaren(3);

    return 0;
}

/* Prints char ch n times. */
void printnchars(int n, char ch) {
    int i;

    for (i = 0; i < n; ++i) {
        printf("%c", ch);
    }
    printf("\n");

    return;
}

/* Prints a square with n char length using printnchars func. */
void squaren(int n) {
    int i;

    for (i = 0; i < n; ++i) {
        printnchars(n, '!');
    }

    return;
}
