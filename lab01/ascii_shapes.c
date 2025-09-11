/*******************************************************************************
 *                                                                             *
 *  @file   ascii_shapes.c                                                     *
 *  @author Christos Kaldis                                                    *
 *  @date   11 Sept 2025                                                       *
 *  @brief  A utility to print ASCII art shapes of various chars and sizes.    *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXIT -1
#define SQUARE 1
#define RHOMBUS 2
#define RIGHT_TRIANGLE 3
#define EQUILATERAL_TRIANGLE 4

#define INNER_CHAR '-'
#define OUTER_CHAR ' '

int get_shape_choice(void);
int get_shape_size(void);
char get_shape_char(void);

void print_square(int size, char ch);
void print_rhombus(int size, char ch);
void print_right_triangle(int size, char ch);
void print_equilateral_triangle(int size, char ch);

void print_filled_line(int len, char fill_char, int new_line);
void print_hollow_line(int len, char edge_char, char inner_char);
void print_center_line(int len, char edge_char, char inner_char, char center_char);
int distance_from_center(int index, int length);


int main(void) {
    int choice, size;
    char shape_ch;

    while ((choice = get_shape_choice()) != EXIT)
    {
        size = get_shape_size();
        shape_ch = get_shape_char();
        switch (choice)
        {
        case SQUARE:
            print_square(size, shape_ch);
            break;
        case RHOMBUS:
            print_rhombus(size, shape_ch);
            break;
        case RIGHT_TRIANGLE:
            print_right_triangle(size, shape_ch);
            break;
        case EQUILATERAL_TRIANGLE:
            print_equilateral_triangle(size, shape_ch);
            break;
        default:
            puts("Invalid shape number.");
            break;
        }
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Prompts the user to select a shape from a list.
 * 
 * @return The integer corresponding to the user's choice, or -1 to exit.
 */
int get_shape_choice(void) {
    int shape;

    puts("\nSelect shape (-1 for exit).");
    puts("1) Square\t\t2) Rhombus\n3) Right Triangle\t4) Equilateral Triangle");
    scanf("%d", &shape);

    return shape;
}

/**
 * @brief Prompts the user to enter a size for the shape.
 * 
 * @return The integer size entered by the user.
 */
int get_shape_size(void) {
    int size;

    puts("\nGive the size of the selected shape.");
    scanf(" %d", &size);

    return size;
}


/**
 * @brief Prompts the user to enter a character for drawing the shape.
 * 
 * @return The character entered by the user.
 */
char get_shape_char(void) {
    char ch;

    puts("\nGive the character the shape will be printed.");
    scanf(" %c", &ch);

    return ch;
}

/**
 * @brief Prints a square of a given size and character.
 * @details The square has a filled top and bottom edge. The center row and
 * column are also filled, creating a cross in the middle.
 * 
 * @param size The height and width of the square.
 * @param ch The character to use for the square's outline and center cross.
 */
void print_square(int size, char ch) {
    int i;

    for (i = 0; i < size; i++) {
        if (i == 0 || i == size - 1)
            print_filled_line(size, ch, 1);
        else if (distance_from_center(i, size) == 0)
            print_center_line(size, ch, INNER_CHAR, ch);
        else
            print_hollow_line(size, ch, INNER_CHAR);
    }

    return;
}

/**
 * @brief Prints a rhombus of a given size and character.
 * @details The rhombus is symmetric around its horizontal center. 
 * The center row is also marked with a cross pattern.
 * 
 * @param size The height of the rhombus (must be an odd number for best results).
 * @param ch The character to use for the rhombus's outline.
 */
void print_rhombus(int size, char ch) {
    int i, dist;
    int inner_line_size = 1;
    int outer_line_size = abs(distance_from_center(0, size));

    for (i = 0; i < size; i++) {
        dist = distance_from_center(i, size);
        print_filled_line(outer_line_size, OUTER_CHAR, 0);
        if (i == 0 || i == size - 1)
            print_filled_line(inner_line_size, ch, 1);
        else if (dist == 0)
            print_center_line(inner_line_size, ch, INNER_CHAR, ch);
        else
            print_hollow_line(inner_line_size, ch, INNER_CHAR);

        if (dist < 0) {
            outer_line_size--;
            inner_line_size += 2;
        }
        /* Start the reverse lengths calculation after passing the center. */
        else if (i >= size/2) {
            outer_line_size++;
            inner_line_size -= 2;
        }
    }

    return;
}

/**
 * @brief Prints a right-angled triangle of a given size and character.
 * @details The triangle has a filled base. The first two lines are also
 * filled to give the top point a more solid appearance.
 * 
 * @param size The height and base width of the triangle.
 * @param ch The character to use for the triangle's outline.
 */
void print_right_triangle(int size, char ch) {
    int i;

    for (i = 0; i < size; i++) {
        if (i == 0 || i == 1 || i == size-1)
            print_filled_line(i+1, ch, 1);
        else
            print_hollow_line(i+1, ch, INNER_CHAR);
    }

    return;
}

/**
 * @brief Prints a equilateral triangle of a given size and character.
 * 
 * @param size The height of the triangle.
 * @param ch The character to use for the triangle's outline.
 */
void print_equilateral_triangle(int size, char ch) {
    int i;
    int inner_line_size = 1;
    int outer_line_size = size - 1;

    for (i = 0; i < size; i++) {
        print_filled_line(outer_line_size, OUTER_CHAR, 0);
        if (i == 0 || i == size - 1)
            print_filled_line(inner_line_size, ch, 1);
        else
            print_hollow_line(inner_line_size, ch, INNER_CHAR);

        outer_line_size--;
        inner_line_size += 2;
    }

    return;
}

/**
 * @brief Prints a line filled with the current character. 
 * 
 * @param len The length of the line.
 * @param fill_char The character to fill the line with.
 * @param new_line If it's non zero value it changes line.
 */
void print_filled_line(int len, char fill_char, int new_line) {
    int i;

    for (i = 0; i < len; ++i) {
        putchar(fill_char);
    }
    if (new_line)
        putchar('\n');

    return;
}

/**
 * @brief Prints a line with a specific character on the edges and another inside.
 * 
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
 * 
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
        else if (distance_from_center(i, len) == 0)
            putchar(center_char);
        else
            putchar(inner_char);
    }
    putchar('\n');

    return;
}

/**
 * @brief Calculates the signed, symmetric distance from the center of a sequence.
 * @details For a sequence of a given length, this function calculates an
 * index's distance from the middle. For even lengths, the two
 * center elements are both considered distance 0.
 * 
 * @param index The current index in the sequence.
 * @param length The total length of the sequence.
 * @return The signed distance from the center. Negative values are to the left,
 * positive are to the right.
 */
int distance_from_center(int index, int length) {
    int middle = length / 2;
    int center_dist = index - middle;

    /* For even lengths, adjust the indices left of the center. */
    if (length % 2 == 0 && index < middle)
        center_dist++;

    return center_dist;
}
