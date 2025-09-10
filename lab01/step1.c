/*******************************************************************************
 *                                                                             *
 *  @file   step1.c                                                            *
 *  @author Christos Kaldis                                                    *
 *  @date   08 Sept 2025                                                       *
 *  @brief  A utility to print ASCII art squares of various sizes.             *
 *                                                                             *
 *                                                                             *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/* Characters used for drawing a square. */
#define BORDER_CHAR   'q'
#define EDGE_CHAR     'a'
#define INNER_CHAR    '-'
#define CENTER_CHAR   '*'

void print_filled_line(int len, char fill_char);
void print_hollow_line(int len, char edge_char, char inner_char);
void print_center_line(int len, char edge_char, char inner_char, char center_char);
int is_at_center(int index, int length);
void print_square(int size);


int main() {
    print_square(5);
    putchar('\n');
    print_square(6);

    return EXIT_SUCCESS;
}

/**
 * @brief Prints a line filled with the current character. 
 * @param len The length of the line.
 * @param fill_char The character to fill the line with.
 */
void print_filled_line(int len, char fill_char) {
    int i;

    for (i = 0; i < len; ++i) {
        putchar(fill_char);
    }
    putchar('\n');

    return;
}

/**
 * @brief Prints a line with a specific character on the edges and another inside.
 * @param len The length of the line.
 * @param edge_char The character for the edges.
 * @param inner_char The character to fill the space between the edges.
 */
void print_hollow_line(int len, char edge_char, char inner_char) {
    int i;

    for (i = 0; i < len; ++i){
        if (i == 0 || i == len-1)
            putchar(edge_char);
        else
            putchar(inner_char);
    }
    putchar('\n');

    return;
}

/**
 * @brief Prints a line with different characters in the edges, inner and center.
 * @param len The length of the line.
 * @param edge_char The character for the edges.
 * @param inner_char The character for the non-center, non-edge parts.
 * @param center_char The character for the middle position(s).
 */
void print_center_line(int len, char edge_char, char inner_char, char center_char) {
    int i;

    for (i = 0; i < len; ++i) {
        if (i == 0 || i == len-1)
            putchar(edge_char);
        else if (is_at_center(i, len))
            putchar(center_char);
        else
            putchar(inner_char);
    }
    putchar('\n');

    return;
}

/**
 * @brief Checks if an index is at the center of a given length.
 * @param index The current index to check (0-based).
 * @param length The total length of the line.
 * @return 1 if the index is a center position, otherwise 0.
 * @note Works for both odd (one center) and even (two centers).
 */
int is_at_center(int index, int length) {
    int center_position = 0;

    if ((index == length/2) || (index == (length - 1) / 2))
        center_position = 1;

    return center_position;
}

/**
 * @brief Prints a square
 * @param size The length of the square's side.
 */
void print_square(int size) {
    int i;

    for (i = 0; i < size; ++i) {
        if (i == 0 || i == size-1)
            print_filled_line(size, BORDER_CHAR);
        else if (is_at_center(i, size))
            print_center_line(size, EDGE_CHAR, INNER_CHAR, CENTER_CHAR);
        else
            print_hollow_line(size, EDGE_CHAR, INNER_CHAR);
    }

    return;
}
