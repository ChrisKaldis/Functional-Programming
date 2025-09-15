/*******************************************************************************
 *                                                                             *
 *  @file   text_analyzer.c                                                    *
 *  @author Christos Kaldis                                                    *
 *  @date   14 Sept 2025                                                       *
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

#define WORDS 30000
#define WORD_LENGTH 20
#define FILENAME_MAX_LEN 100
#define DICTIONARY_SIZE 1000

int get_choice(void);
int get_int(void);
char get_char(void);
int insert_text(char text_words[WORDS][WORD_LENGTH+1]);
int insert_dictionary(char dictionary[DICTIONARY_SIZE][WORD_LENGTH+1]);
void correct_text(void);
void save_text(void);
void calculate_stats(void);

int display_insert_options(void);
int process_input_stream(
    FILE *stream, char text_words[WORDS][WORD_LENGTH + 1], int is_terminal
);
void print_text(char text[WORDS][WORD_LENGTH+1], int count);


int main(void) {
    char text_words[WORDS][WORD_LENGTH+1];
    char dictionary[DICTIONARY_SIZE][WORD_LENGTH + 1];
    int choice;
    int text_length = 0;
    int dictionary_length = 0;

    while ((choice = get_choice()) != EXIT) {
        switch (choice)
        {
        case INSERT_TEXT:
            text_length = insert_text(text_words);
            break;
        case INSERT_DICTIONARY:
            dictionary_length = insert_dictionary(dictionary);
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

    choice = get_int();
    
    return choice;
}

int insert_text(char text_words[WORDS][WORD_LENGTH+1]) {
    char filename[FILENAME_MAX_LEN];
    FILE *file_ptr;
    int choice;
    int word_count = 0;
    char print_choice;

    choice = display_insert_options();

    switch (choice)
    {
    case 1:
        word_count = process_input_stream(stdin, text_words, 1);
        break;
    case 2:
        {
            printf("Enter the filename: ");
            /* assumes no spaces in filename. */
            if (scanf("%99s", filename) != 1) {
                puts("Invalid filename input.");
                break;
            }
            while (getchar() != '\n')
                ;

            file_ptr = fopen(filename, "r");
            if (file_ptr == NULL) {
                perror("Error opening file");
                break;
            }

            printf("Reading from file '%s'...\n", filename);
            word_count = process_input_stream(file_ptr, text_words, 0);
            fclose(file_ptr);
            break;
        }
    case 3:
        break;
    default:
        puts("Invalid option.");
        break;
    }

    if (word_count > 0) {
        printf("\nInsertion completed. %d words were added.\n", word_count);
        printf("Do you want to print the text? (y/n): ");
        print_choice = get_char();

        if (print_choice == 'y' || print_choice == 'Y') {
            print_text(text_words, word_count);
        }
    }

    return word_count;
}

int insert_dictionary(char dictionary[DICTIONARY_SIZE][WORD_LENGTH+1]) {
    int word_count = 0;

    return word_count;
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

int display_insert_options(void) {
    int option;

    puts("\n1) Insert words from terminal.");
    puts("2) Insert words from file.");
    puts("3) Return to the main menu.");
    
    option = get_int();

    return option;
}

int process_input_stream(
    FILE *stream, char text_words[WORDS][WORD_LENGTH + 1], int is_terminal
) {
    const char end_word[] = "*T*E*L*O*S*";
    const char delimiters[] = " \t\n\r";
    char line_buffer[256];
    int word_idx = 0;
    int finished = 0;

    if (is_terminal) {
        puts("Give words, write *T*E*L*O*S* when you finish.");
    }

    while (word_idx < WORDS && !finished && fgets(line_buffer, sizeof(line_buffer), stream) != NULL) {
        char *token = strtok(line_buffer, delimiters);
        while (token != NULL) {
            /* Check for end word only if input is from terminal. */
            if (is_terminal && strcmp(token, end_word) == 0) {
                finished = 1;
                break;
            }

            /* Store the word only if it fits in memory. */
            if (strlen(token) <= WORD_LENGTH) {
                strcpy(text_words[word_idx++], token);
            }
            else {
                printf("Word:'%s' is too big (max %d) and was skipped.\n", token, WORD_LENGTH);
            }

            /* Check if the array is full after the last insertion. */
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

void print_text(char text_words[WORDS][WORD_LENGTH + 1], int count) {
    int i;

    for (i = 0; i < count; i++) {
        printf("%d: %s\n", i + 1, text_words[i]);
    }

    return;
}

int get_int(void) {
    int choice;

    /* Check if user didn't gave a number. */
    if (scanf("%d", &choice) != 1)
        choice = 0;

    /* Clear input buffer in order to be ready for the next scanf(). */
    while (getchar() != '\n')
        ;
    
    return choice;
}

char get_char(void) {
    char choice;

    if (scanf(" %c", &choice) != 1)
        choice = 'n';

    while (getchar() != '\n')
        ;
    
    return choice;
}
