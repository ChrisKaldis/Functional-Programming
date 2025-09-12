/*******************************************************************************
 *                                                                             *
 *  @file   plate_heat_simulation.c                                            *
 *  @author Christos Kaldis                                                    *
 *  @date   12 Sept 2025                                                       *
 *                                                                             *
 *  @brief      Simulates heat distribution on a 2D metal plate.               *
 *  @details    This program provides a numerical solution to the              *
 *  2D heat equation to model the steady-state temperature distribution across *
 *  a rectangular metal plate.                                                 *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 10
#define COLS 20

#define TEMP_TOP 2.0
#define TEMP_BOTTOM 3.0
#define TEMP_LEFT 4.0
#define TEMP_RIGHT -5.0
#define TEMP_INNER 1.0

#define SECONDS 37

#define HEAT_LEVELS 10

void init_plate(double plate[ROWS][COLS]);
void init_row_plate(
    double plate[ROWS][COLS], int row_index, 
    double left_edge_temp, double inner_temp, double right_edge_temp
);
void print_plate(const double plate[ROWS][COLS], int time);
void calc_temp(double plate[ROWS][COLS]);
void copy_plate(
    const double plate[ROWS][COLS], double copied_plate[ROWS][COLS]
);
void normalize_plate(
    const double plate[ROWS][COLS], int norm_plate[ROWS][COLS]
);
void find_min_and_max(
    const double plate[ROWS][COLS], double * max, double * min
);
void print_norm_plate(const int norm_plate[ROWS][COLS]);
void create_histogram(
    const int norm_plate[ROWS][COLS], int histogram[HEAT_LEVELS]
);
void print_histogram(const int histogram[HEAT_LEVELS]);


int main(void) {
    double plate_temp[ROWS][COLS];
    int norm_plate_temp[ROWS][COLS];
    int histogram[HEAT_LEVELS];
    int time = 0;

    init_plate(plate_temp);
    print_plate(plate_temp, time);
    for (time = 1; time <= SECONDS; time++) {
        calc_temp(plate_temp);
    }
    print_plate(plate_temp, time);
    normalize_plate(plate_temp, norm_plate_temp);
    print_norm_plate(norm_plate_temp);
    create_histogram(norm_plate_temp, histogram);
    print_histogram(histogram);

    return EXIT_SUCCESS;
}

void init_plate(double plate[ROWS][COLS]) {
    double top_left_edge = (TEMP_LEFT + TEMP_TOP) / 2;
    double top_right_edge = (TEMP_RIGHT + TEMP_TOP) / 2;
    double bottom_left_edge = (TEMP_LEFT + TEMP_BOTTOM) / 2;
    double bottom_right_edge = (TEMP_RIGHT + TEMP_BOTTOM) / 2;
    int i;

    /*  There is a minor performance overhead from function calls.
        This for loop is small so we don't care but, usually in HPC you 
        avoid function calls inside large loops, this way you sacrifice 
        clarity for efficiency. */
    for (i = 0; i < ROWS; i++) {
        if (i == 0)
            init_row_plate(
                plate, i, top_left_edge, TEMP_TOP, top_right_edge
            );
        else if (i == ROWS - 1)
            init_row_plate(
                plate, i, bottom_left_edge, TEMP_BOTTOM, bottom_right_edge
            );
        else
            init_row_plate(
                plate, i, TEMP_LEFT, TEMP_INNER, TEMP_RIGHT
            );
    }
    
    return;
}

void init_row_plate(
    double plate[ROWS][COLS],
    int row_index, 
    double left_edge_temp,
    double inner_temp,
    double right_edge_temp
) {
    int i;

    for (i = 0; i < COLS; i++) {
        if (i == 0)
            plate[row_index][i] = left_edge_temp;
        else if (i == COLS - 1)
            plate[row_index][i] = right_edge_temp;
        else
            plate[row_index][i] = inner_temp;
    }

    return;
}

void print_plate(const double plate[ROWS][COLS], int time) {
    int i, j;

    printf(" || Time in seconds: %d ||\n", time);
    putchar('\n');
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%6.2f ", plate[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');

    return;
}

void calc_temp(double plate[ROWS][COLS]) {
    double tmp_plate[ROWS][COLS];
    int i, j;

    /*  Copies the plate temperatures in another array in order to 
        create an array that holds the (t-1) values of the plate.  */
    copy_plate(plate, tmp_plate);
    /*  Calculates the temperature for the current state (t).  */
    for (i = 1; i < ROWS - 1; i++) {
        for (j = 1; j < COLS - 1; j++) {
            plate[i][j] = 0.1 * (
                tmp_plate[i-1][j-1] +
                tmp_plate[i-1][j] +
                tmp_plate[i-1][j+1] +
                tmp_plate[i][j-1] +
                2 * tmp_plate[i][j] +
                tmp_plate[i][j+1] +
                tmp_plate[i+1][j-1] +
                tmp_plate[i+1][j] +
                tmp_plate[i+1][j+1]
            ) ;
        }
    }

    return;
}

void copy_plate(
    const double plate[ROWS][COLS],
    double copied_plate[ROWS][COLS]
) {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            copied_plate[i][j] = plate[i][j];
        }
    }

    return;
}

void normalize_plate(
    const double plate[ROWS][COLS], int norm_plate[ROWS][COLS]
) {
    double max_temp, min_temp, temp_step, threshold;
    int i, j, heat_level;

    find_min_and_max(plate, &max_temp, &min_temp);
    temp_step = (max_temp - min_temp) / HEAT_LEVELS;
    for (i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            threshold = min_temp + temp_step;
            for (heat_level = 0; plate[i][j] > threshold; heat_level++) {
                threshold += temp_step;
            }
            norm_plate[i][j] = heat_level;
        }
    }

    return;
}

void find_min_and_max(
    const double plate[ROWS][COLS], double * max, double * min
) {
    int i, j;

    *min = *max = plate[0][0];
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (*max < plate[i][j])
                *max = plate[i][j];
            else if (*min > plate[i][j])
                *min = plate[i][j];
        }
    }

    return;
}

void print_norm_plate(const int norm_plate[ROWS][COLS]) {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            printf(" %d ", norm_plate[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');

    return;
}

void create_histogram(
    const int norm_plate[ROWS][COLS],
    int histogram[HEAT_LEVELS]
) {
    int i, j, index;

    for (i = 0; i < HEAT_LEVELS; i++) {
        histogram[i] = 0;
    }

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            index = norm_plate[i][j];
            histogram[index]++;
        }
    }

    return;
}

void print_histogram(const int histogram[HEAT_LEVELS]) {
    int i, j;

    for (i = 0; i < HEAT_LEVELS; i++) {
        printf("%d: ", i);
        for (j = 0; j < histogram[i]; j++) {
            putchar('#');
        }
        putchar('\n');
    }

    return;
}