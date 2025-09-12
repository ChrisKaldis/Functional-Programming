/*******************************************************************************
 *                                                                             *
 *  @file   text_analyzer.c                                                    *
 *  @author Christos Kaldis                                                    *
 *  @date   12 Sept 2025                                                       *
 *  @brief  Perform basic edit and stats calculation in a text.                *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define INSERT_TEXT 1
#define INSERT_DICTIONARY 2
#define CORRECT_TEXT 3
#define SAVE_TEXT 4
#define CALCULATE_STATS 5
#define EXIT 6

int get_choice(void);
void insert_text(void);
void insert_dictionary(void);
void correct_text(void);
void save_text(void);
void calculate_stats(void);


int main(void) {
    int choice;

    while ((choice = get_choice()) != EXIT) {
        switch (choice)
        {
        case INSERT_TEXT:
            insert_text();
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

void insert_text(void) {
    puts("Insert text.");

    return;
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
