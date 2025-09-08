#include <stdio.h>

void printnchars(int n, char ch);

int main() {
    printnchars(8, '=');
    printnchars(22, '!');

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
