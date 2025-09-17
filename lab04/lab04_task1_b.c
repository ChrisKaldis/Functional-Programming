#include <stdio.h>
#include <string.h>

struct charact {
    char ch;
    int sec;
};
typedef struct charact Char;

void letters(char name[50], Char chars[50]);
void report(Char chars[50]);


int main(void) {
    char name[50];
    Char chars[50];

    scanf("%49s", name);

    letters(name, chars);
    report(chars);

    return 0;
}

void letters(char name[50], Char chars[50]) {
    size_t i, j;

    memset(chars, 0, 50 * sizeof(Char) );
    for (i = 0; i < strlen(name); i++) {
        chars[i].ch = name[i];
        for (j = i + 1; j < strlen(name); j++) {
            if (chars[i].ch == name[j]) {
                chars[i].sec = j - i;
                break;
            }
        }
    }

    return;
}

void report(Char t[50]) {
    size_t i;

    for (i = 0; t[i].ch != 0; i++) {
        printf("%c: %d\n", t[i].ch, t[i].sec);
    }

    return;
}
