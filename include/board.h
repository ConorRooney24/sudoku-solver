#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stdint.h>

typedef struct Cell
{
        bool is_possible[9]; // Every possible number that this cell could be. if 0 is true, then it is possible for this cell to be 1
        uint8_t number;      // The confirmed number. set to 0 if the cell has not yet been solved. any non 0 number means that this is the solved number for this cell.
} Cell;

typedef Cell Grid[9][9]; // 9 by 9 grid of cells in y, x. Y increases down, x increases right.

int grid_init(Grid *g);
int cell_init(Cell *c);

#endif // BOARD_H