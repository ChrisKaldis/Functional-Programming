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

#define EXIT -1
#define SQUARE 1
#define RHOMBUS 2
#define RIGHT_TRIANGLE 3
#define EQUILATERAL_TRIANGLE 4

int get_shape_choice(void);
int get_shape_size(void);
char get_shape_char(void);

int print_square(int size, char ch);
int print_rhombus(int size, char ch);
int print_right_triangle(int size, char ch);
int print_equilateral_triangle(int size, char ch);


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
            puts("Invalid shape.");
            break;
        }
    }

    return EXIT_SUCCESS;
}

int get_shape_choice(void) {
    int shape;

    puts("\nSelect shape (-1 for exit).");
    puts("1) Square\t\t2) Rhombus\n3) Right Triangle\t4) Equilateral Triangle");
    scanf("%d", &shape);

    return shape;
}

int get_shape_size(void) {
    int size;

    puts("\nGive the size of the selected shape.");
    scanf(" %d", &size);

    return size;
}

char get_shape_char(void) {
    char ch;

    puts("\nGive the character the shape will be printed.");
    scanf(" %c", &ch);

    return ch;
}

int print_square(int size, char ch) {
    printf("Square of size:%d and with char:%c\n", size, ch);

    return EXIT_SUCCESS;
}

int print_rhombus(int size, char ch) {
    printf("Rhombus of size:%d and with char:%c\n", size, ch);

    return EXIT_SUCCESS;
}

int print_right_triangle(int size, char ch) {
    printf("Right triangle of size:%d and with char:%c\n", size, ch);

    return EXIT_SUCCESS;
}

int print_equilateral_triangle(int size, char ch) {
    printf("Equilateral triangle of size:%d and with char:%c\n", size, ch);

    return EXIT_SUCCESS;
}
