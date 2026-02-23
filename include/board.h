#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stdint.h>
#include "../include/tui.h"

#define CELL_PRINT_WIDTH 11
#define CELL_PRINT_HEIGHT 5

typedef struct Cell
{
        bool is_possible[9]; // Every possible number that this cell could be. if 0 is true, then it is possible for this cell to be 1
        uint8_t number;      // The confirmed number. set to 0 if the cell has not yet been solved. any non 0 number means that this is the solved number for this cell.
} Cell;

typedef Cell Grid[9][9]; // 9 by 9 grid of cells in y, x. Y increases down, x increases right.

int grid_init(Grid *g);
int cell_init(Cell *c);

void grid_print(const Grid g);                                  // Prints the grid showing solved numbers and possible numbers for each cell.
void grid_print_simple(const Grid g);                           // Prints the grid displaying only the solved or unsolved numbers.
void grid_print_cell_info(const Grid g);                        // Calls Cell_print for every cell on a grid and displays cell coordinates beside each cells information.
void cell_print(const Cell c, Colour background, int offset_x); // Prints cell information in a formatted way showing solved number if solved, and possible numbers if unsolved. It will move the cursor by the given offset. offset_x of 10 means move the cursor 10 times right before each print.
void cell_print_simple(const Cell c);                           // Prints a cells information. If it has been solved or not, And its possible numbers.

#endif // BOARD_H