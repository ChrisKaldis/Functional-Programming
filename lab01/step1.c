#include <stdio.h>

void printfivechars(void);

int main() {
    printfivechars();

    return 0;
}

void printfivechars(void) {
    int i;

    for (i = 0; i < 5; ++i) {
        printf("=");
    }
    printf("\n");

    return;
}
