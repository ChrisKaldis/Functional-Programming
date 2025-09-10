/*******************************************************************************
 *                                                                             *
 *  @file   lab02_step2.c                                                      *
 *  @author Christos Kaldis                                                    *
 *  @date   10 Sept 2025                                                       *
 *  @brief  Handling small strings (below 10 char) using an array.             *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define W 5

void clear_words(char text[W][9 + 1]);
void print_words(const char text[W][9 + 1]);
void load_reversed_words(const char text[W][9 + 1], char text_reversed[W][9 + 1]);
int char_is_vowel(char ch, int index);
void append_another_word(char text[W][9 + 1]);
int count_words(const char text[W][9 + 1]);
int get_new_word(char word[9 + 1]);


int main() {
    char words[W][9 + 1];
    char words_reversed[W][9 + 1];
    char test[9 + 1];
    char endword[9 + 1] = "end";
    int i = 0;

    clear_words(words);
    while (scanf("%9s", test), strcmp(test, endword)) {
        strcpy(words[i++], test);
        if (i == W)
            break;
    }

    puts("\nNormal words.");
    print_words(words);

    clear_words(words_reversed);
    load_reversed_words(words, words_reversed);
    append_another_word(words_reversed);

    puts("\nReversed words.");
    print_words(words_reversed);

    return 0;
}

/**
 * @brief Initializes a 2D array with empty strings.
 * 
 * @param text The 2D array that needs to be cleared.
 */
void clear_words(char text[W][9 + 1]) {
    int i;

    for (i = 0; i < W; i++) {
        text[i][0] = '\0';
    }

    return;
}

/**
 * @brief Prints all non-empty strings in the array along with their index.
 * 
 * @param text The 2D array that prints.
 */
void print_words(const char text[W][9 + 1]) {
    int i;

    for (i = 0; i < W; i++) {
        if (text[i][0] != 0) {
            printf("%d: %s\n", i, text[i]);
        }
    }

    return;
}

/**
 * @brief Reverse words and keep only consonants in uppercase form.
 * @details For each word in text, transpose chars into lowercase and
 * iterate through backwards, erase vowels, then convert the consonants to 
 * uppercase and store them into text_reversed array.
 * 
 * @param[in] text The 2D array containing the initial words.
 * @param[out] text_reversed The 2D array with the edited words. 
 */
void load_reversed_words(const char text[W][9 + 1], char text_reversed[W][9 + 1]) {
    int i, len, ch_idx, r_ch_idx;

    for (i = 0; i < W; i++) {
        len = strlen(text[i]);
        /* We want the word reversed so, we start checking the chars of 
        the source word backwards (using ch_idx) and the destination word 
        forward (using r_ch_idx).*/
        for (ch_idx = len-1, r_ch_idx = 0; ch_idx >= 0; ch_idx--) {
            if (char_is_vowel(tolower(text[i][ch_idx]), ch_idx) == 0) {
                text_reversed[i][r_ch_idx++] = toupper(text[i][ch_idx]);
            }
        }
        /* Add the string the termination symbol. */
        text_reversed[i][r_ch_idx] = '\0';
    }

    return;
}

/**
 * @brief Checks if a given character is a vowel.
 * @details It works only for lowercase characters. Character y is considered 
 * a vowel only if it isn't the first character of a word.
 * 
 * @param ch The lowercase character that needs to be checked.
 * @param index The 0-based index of the character in its original word.
 * 
 * @return Returns 1 if the character is a vowel, 0 otherwise.
 */
int char_is_vowel(char ch, int index) {
    int is_vowel;

    switch (ch) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            is_vowel = 1;
            break;
        case 'y':
            if (index > 0) {
                is_vowel = 1;
            }
            break;
        default:
            is_vowel = 0;
            break;
    }
    
    return is_vowel;
}

/**
 * @brief Appends a new word to an array in a certain index.
 * @details After checking if the array is not full. It prompts the user 
 * for a new word and then for the index it will append it. It then shifts 
 * existing elements to make space and inserts the new word.
 * 
 * @param text The 2D array to which the word will be added.
 */
void append_another_word(char text[W][9 + 1]) {
    char new_word[9 + 1];
    int i, num_words, new_word_idx;
    
    num_words = count_words(text);
    if (num_words < W) {
        new_word_idx = get_new_word(new_word);
        /* Shift every word with bigger index to the right. In order to not lose 
        a word (overwrite it), starts from the end and move everything one index. */
        for (i = num_words; i > new_word_idx; i--) {
            strcpy(text[i], text[i-1]);
        }
        strcpy(text[new_word_idx], new_word);
    }

    return;
}

/**
 * @brief Counts the number of non-empty strings in an array.
 * 
 * @param text The 2D array for counting.
 * 
 * @return The number of words that are stored in the array.
 */
int count_words(const char text[W][9 + 1]) {
    int num_words;

    for (num_words = 0; text[num_words][0] != 0 && num_words < W; num_words++)
        ;

    return num_words;
}

/**
 * @brief Prompts the user to enter a new word and an index.
 * 
 * @param  word A string to store the new word.
 * 
 * @return The index user gave.
 * 
 * @warning It trusts the user about giving an in range index.
 */
int get_new_word(char word[9 + 1]) {
    int index;

    puts("The array is not full, add another word.");
    scanf("%9s", word);

    puts("Select the index you want to insert it (0-based).");
    scanf(" %d", &index);

    return index;
}
