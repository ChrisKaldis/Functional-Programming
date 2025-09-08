#include <stdio.h>

void printnchars(int n, char ch);

int main() {
    int n;
    char ch;

    printf("Give the number of repeats (n):\n");
    scanf("%d", &n);
    printf("Give the character (ch) you want to print:\n");
    scanf(" %c", &ch);

    printnchars(n, ch);

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
