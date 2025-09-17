#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARS 10

typedef struct text_t {
    char ** t;
    int words;
} Text_t;

Text_t readText(void);

struct charact { 
    char ch; 
    int sec;
}; 
typedef struct charact Char; 

void letters(char name[50], Char chars[50]);
void report(Char chars[50]);


int main(void) {
    Text_t text;
    Char chars[50];
    int i;

    text = readText();

    for (i = 0; i < text.words; i++) {
        letters(text.t[i], chars);
        report(chars);
    }

    return 0;
}

Text_t readText(void) {
	Text_t mytext;
	mytext.t = NULL;
	mytext.words = 0;
    char *word;
    char filename[50];
	FILE * ptr;

	puts("give the path of the file:");
	scanf("%50s", filename);
	ptr = fopen(filename, "r");
	if(ptr == NULL){
		puts("oups file didn't exist.");
	} 
	
	while (!feof(ptr)) {
		(mytext.words) ++;
		fscanf(ptr,"%s", word = malloc(CHARS * sizeof(char)));		
 		mytext.t = realloc(mytext.t, (mytext.words) * sizeof(char *));
		mytext.t[mytext.words-1] = word;
 	}

    return mytext;
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

void report(Char chars[50]) {
    size_t i;

    for (i = 0; chars[i].ch != 0; i++) {
        printf("%c: %d\n", chars[i].ch, chars[i].sec);
    }
    putchar('\n');

    return;
}
