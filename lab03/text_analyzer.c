/*******************************************************************************
 *                                                                             *
 *  @file   text_analyzer.c                                                    *
 *  @author Christos Kaldis                                                    *
 *  @date   13 Sept 2025                                                       *
 *  @brief  Perform basic edit and stats calculation in a text.                *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT_TEXT 1
#define INSERT_DICTIONARY 2
#define CORRECT_TEXT 3
#define SAVE_TEXT 4
#define CALCULATE_STATS 5
#define EXIT 6

#define WORDS 10
#define WORD_LENGTH 20

int get_choice(void);
int insert_text(char text_words[WORDS][WORD_LENGTH+1]);
void insert_dictionary(void);
void correct_text(void);
void save_text(void);
void calculate_stats(void);

void print_text(char text[WORDS][WORD_LENGTH+1], int count);


int main(void) {
    char text_words[WORDS][WORD_LENGTH+1];
    int choice, text_length = 0;

    while ((choice = get_choice()) != EXIT) {
        switch (choice)
        {
        case INSERT_TEXT:
            text_length = insert_text(text_words);
            print_text(text_words, text_length);
            break;
        case INSERT_DICTIONARY:
            insert_dictionary();
            break;
        case CORRECT_TEXT:
            correct_text();
            break;
        case SAVE_TEXT:
            save_text();
            break;
        case CALCULATE_STATS:
            calculate_stats();
            break;
        default:
            puts("Invalid option.");
            break;
        }
    }

    return EXIT_SUCCESS;
}

int get_choice(void) {
    int choice;

    puts("\t\t ~*~ Menu ~*~ ");
    printf("%d) Insert text\t", INSERT_TEXT);
    printf("%d) Insert dictionary\t", INSERT_DICTIONARY);
    printf("%d) Correct text\n", CORRECT_TEXT);
    printf("%d) Save text\t", SAVE_TEXT);
    printf("%d) Calculate text stats\t", CALCULATE_STATS);
    printf("%d) Exit\n", EXIT);

    /* Check if user gave a number. */
    if (scanf("%d", &choice) != 1) {
        choice = 0;
    }
    /* Clear input buffer. */
    while (getchar() != '\n')
        ;
    
    return choice;
}

int insert_text(char text_words[WORDS][WORD_LENGTH+1]) {
    const char end_word[] = "*T*E*L*O*S*";
    const char delimiters[] = " \t\n\r";
    char line_buffer[256];
    static int word_idx = 0;
    int finished = 0;

    puts("Give a words, write *T*E*L*O*S* when you finish.");

    while (word_idx < WORDS && !finished) {
        if (fgets(line_buffer, sizeof(line_buffer), stdin) == NULL) {
            break;
        }

        char *token = strtok(line_buffer, delimiters);
        while (token != NULL) {
            if (strcmp(token, end_word) == 0) {
                finished = 1;
                break;
            }

            if (strlen(token) <= WORD_LENGTH) {
                strcpy(text_words[word_idx++], token);
            }
            else {
                printf("Word:%s is too big (max %d).\n", token, WORD_LENGTH);
            }

            if (word_idx >= WORDS) {
                printf("Text array is full (%d words).\n", WORDS);
                finished = 1;
                break;
            }

            token = strtok(NULL, delimiters);
        }
    }

    return word_idx;
}

void insert_dictionary(void) {
    puts("Insert dictionary");

    return;
}

void correct_text(void) {
    puts("Correct text.");

    return;
}

void save_text(void) {
    puts("Save text");

    return;
}

void calculate_stats(void) {
    puts("Calculate stats");

    return;
}

void print_text(char text_words[WORDS][WORD_LENGTH + 1], int count) {
    int i;

    for (i = 0; i < count; i++) {
        printf("%d: %s\n", i + 1, text_words[i]);
    }

    return;
}
