/*******************************************************************************
 *                                                                             *
 *  @file   plate_heat_simulation.c                                            *
 *  @author Christos Kaldis                                                    *
 *  @date   17 Sept 2025                                                       *
 *                                                                             *
 *  @brief      Simulates heat distribution on a 2D metal plate.               *
 *  @details    This program provides a numerical solution to the              *
 *  2D heat equation to model the steady-state temperature distribution across *
 *  a rectangular metal plate.                                                 *
 *                                                                             *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ROWS 10
#define COLS 20

#define TEMP_TOP 2.0
#define TEMP_BOTTOM 3.0
#define TEMP_LEFT 4.0
#define TEMP_RIGHT -5.0
#define TEMP_INNER 1.0

#define HEAT_LEVELS 10
#define THRESHOLD 1.0

void init_plate(double plate[ROWS][COLS]);
void init_row_plate(
    double plate[ROWS][COLS], int row_index, 
    double left_edge_temp, double inner_temp, double right_edge_temp
);
double calc_temp(double plate[ROWS][COLS]);
void copy_plate(
    const double plate[ROWS][COLS], double copied_plate[ROWS][COLS]
);
void normalize_plate(
    const double plate[ROWS][COLS], int norm_plate[ROWS][COLS]
);
void find_min_and_max(
    const double plate[ROWS][COLS], double * max, double * min
);
void create_histogram(
    const int norm_plate[ROWS][COLS], int histogram[HEAT_LEVELS]
);
void print_plate(const double plate[ROWS][COLS], int time);
void print_norm_plate(const int norm_plate[ROWS][COLS]);
void print_histogram(const int histogram[HEAT_LEVELS]);
int get_user_timestep(void);


int main(void) {
    double plate_temp[ROWS][COLS];
    int norm_plate_temp[ROWS][COLS];
    int histogram[HEAT_LEVELS];
    double delta_temp;
    int time_print, time = 0;

    init_plate(plate_temp);
    time_print = get_user_timestep();
    do {
        time++;
        delta_temp = calc_temp(plate_temp);
        if (time_print == time) {
            print_plate(plate_temp, time);
            normalize_plate(plate_temp, norm_plate_temp);
            print_norm_plate(norm_plate_temp);
            create_histogram(norm_plate_temp, histogram);
            print_histogram(histogram);
        }
    } while (delta_temp >= THRESHOLD) ;
    puts("Final State.");
    print_plate(plate_temp, time);

    return EXIT_SUCCESS;
}

/**
 * @brief Initializes the entire plate with boundary and inner temperatures.
 * @details Sets the edge temperatures and calculates corner temperatures as the
 * average of adjacent edges. The inner part of the plate is set to a
 * default temperature.
 * 
 * @param[out] plate The 2D array representing the plate to be initialized.
 */
void init_plate(double plate[ROWS][COLS]) {
    /* Calculate corner temperatures as the average of adjacent edges. */
    double top_left_edge = (TEMP_LEFT + TEMP_TOP) / 2;
    double top_right_edge = (TEMP_RIGHT + TEMP_TOP) / 2;
    double bottom_left_edge = (TEMP_LEFT + TEMP_BOTTOM) / 2;
    double bottom_right_edge = (TEMP_RIGHT + TEMP_BOTTOM) / 2;
    int i;

    /*  There is a minor performance overhead from function calls.
        This for loop is small so we don't care but usually, in HPC you 
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

/**
 * @brief Initializes a single row of the plate with specified temperatures.
 * 
 * @param[out] plate The 2D array representing the plate.
 * @param[in] row_index The index of the row to initialize.
 * @param[in] left_edge_temp The temperature for the leftmost cell of the row.
 * @param[in] inner_temp The temperature for the inner cells of the row.
 * @param[in] right_edge_temp The temperature for the rightmost cell of the row.
 */
void init_row_plate(
    double plate[ROWS][COLS],
    int row_index,
    double left_edge_temp,
    double inner_temp,
    double right_edge_temp
) {
    int i;

    plate[row_index][0] = left_edge_temp;
    for (i = 1; i < COLS - 1; i++) {
        plate[row_index][i] = inner_temp;
    }
    plate[row_index][COLS-1] = right_edge_temp;

    return;
}

/**
 * @brief Calculates one time step of the heat diffusion.
 * @details Updates each inner cell's temperature based on the average of 
 * its neighbors from the previous timestep (t-1).
 * 
 * * @param[in,out] plate The 2D array representing the plate, which will be
 * updated to the next time step (t).
 * 
 * @return The total absolute change in temperature across the plate during
 * this time step.
 */
double calc_temp(double plate[ROWS][COLS]) {
    double tmp_plate[ROWS][COLS];
    double delta_temp = 0;
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

            delta_temp += fabs(plate[i][j] - tmp_plate[i][j]);
        }
    }

    return delta_temp;
}

/**
 * @brief Copies the values of one plate to another using memcpy for efficiency.
 * @details This function performs a bulk memory copy of the entire 2D array.
 * As a 2D array in C is stored in a contiguous block of memory, a single
 * memcpy call is a highly efficient way to duplicate its contents.
 * 
 * @param[in] plate The source 2D array containing the temperature data.
 * @param[out] copied_plate The destination 2D array where the data will 
 * be copied.
 */
void copy_plate(
    const double plate[ROWS][COLS],
    double copied_plate[ROWS][COLS]
) {
    memcpy(copied_plate, plate, sizeof(double) * ROWS * COLS);

    return;
}

/**
 * @brief Normalizes the temperature plate to discrete integer levels (0-9).
 * @details Finds the min and max temperatures on the plate and scales all 
 * values linearly to fit within the defined number of HEAT_LEVELS.
 * 
 * @param[in] plate The 2D array of double-precision temperatures.
 * @param[out] norm_plate The 2D array of integers to store the normalized levels.
 */
void normalize_plate(
    const double plate[ROWS][COLS], int norm_plate[ROWS][COLS]
) {
    double max_temp, min_temp, temp_range;
    int i, j, heat_level;

    find_min_and_max(plate, &max_temp, &min_temp);
    temp_range = max_temp - min_temp;

    for (i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            /*  In case every temperature in the plate is the same, 
                we don't have to do any calculations. */
            if (temp_range == 0) {
                norm_plate[i][j] = 0;
                continue;
            }

            heat_level = (int) (
                ((plate[i][j] - min_temp) / temp_range) * HEAT_LEVELS
            );

            if (heat_level >= HEAT_LEVELS) {
                heat_level = HEAT_LEVELS - 1;
            }

            norm_plate[i][j] = heat_level;
        }
    }

    return;
}

/**
 * @brief Finds the minimum and maximum temperature values on the plate.
 * 
 * @param[in] plate The 2D array of temperatures to search through.
 * @param[out] max Pointer to a double where the maximum temperature will be
 * stored.
 * @param[out] min Pointer to a double where the minimum temperature will be
 * stored.
 */
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


/**
 * @brief Creates a histogram from the normalized plate data.
 * @details Counts the number of cells at each discrete heat level and stores
 * the counts in the histogram array.
 * 
 * @param[in] norm_plate The 2D array containing normalized heat levels (0-9).
 * @param[out] histogram An array to store the frequency of each heat level.
 */
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

/**
 * @brief Prints the plate's raw temperature values to the console.
 * 
 * @param[in] plate The 2D array of temperatures to print.
 * @param[in] time The current simulation time (in seconds) to display.
 */
void print_plate(const double plate[ROWS][COLS], int time) {
    int i, j;

    printf("\n || Time in seconds: %d ||\n", time);
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

/**
 * @brief Prints the plate with the normalized integer values.
 * 
 * @param[in] norm_plate The 2D array of integer heat levels to print.
 */
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

/**
 * @brief Prints a horizontal histogram of heat level distribution.
 * 
 * @param[in] histogram An array where each index represents a heat level and 
 * the value is the frequency of that level.
 */
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

/**
 * @brief Gets a valid, positive integer from the user for the timestep.
 * @details Prompts the user for input and validates that it is a single,
 * positive integer. It handles errors such as non-numeric text or
 * non-positive numbers by clearing the input buffer and re-prompting.
 * 
 * @return A positive integer representing the chosen timestep.
 * 
 * @warning In order to handle those errors it has an infinite loop.
 */
int get_user_timestep(void) {
    int second, result;

    puts("Select the second you want to see the plate temp infos.");

    while (1) {
        printf("> ");
        result = scanf("%d", &second);

        if (result != 1) {
            puts("Invalid input. Please enter a whole number.");
            while (getchar() != '\n')
                ; 
            continue;
        }

        if (second <= 0) {
            puts("Invalid input. Please enter a positive number.");
            continue;
        }

        /*  If we get here, the input is a valid positive integer.
            Clear any trailing characters (like "50xyz") before breaking. */
        while (getchar() != '\n')
            ;
        break;
    }

    return second;
}
