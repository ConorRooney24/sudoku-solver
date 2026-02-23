#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include <stdbool.h>

int strip_possibilities_cell(Grid *g, int y, int x);                                 // Takes a given cell on a board and checks neighbors in its row, column, and block to remove its possibilities. For example, if a given cell has 2 as a possibility, and this function finds a solved cell with 2 as its value, it will remove 2 as a possibility from the target cell.
void set_sole_possibilities_solved(Grid *g);                                         // Looks through every cell on a grid for cells that only have one possibility and sets them to solved
int num_possibilities_cell(const Cell c);                                            // returns the sum of possibilities of a cell
void solve_hidden_singles_block(Grid *g, int block_y, int block_x);                  // Takes a grid and the coordinates of a block (0-2) and looks at the unsolved cells. For each number 1-9, it counts how many cells have that number as a possibility. If a given number only has one possible cell in a block, it sets that cell to solved.
void solve_pointing_groups_row_block(Grid *g, int block_y, int block_x);            // FOR A ROW: Takes a grid and the coordinates of a block, attempts to find pointing pairs or pointing triplets and then removes possibilities from corresponding cells outside of the block. For example, if we look in a block and find that only two of the unsolved squares have a possibility of being 2, if those cells are on the same row (or column), we know that there will not be a 2 on that row (or column) outside of this block.
void solve_pointing_groups_column_block(Grid *g, int block_y, int block_x);          // Same as above but for columns instead of rows
int sum_possibilities_num_in_block(const Grid g, int block_y, int block_x, int num); // Takes grid, the coordinates of a block, and a number, returns how many cells have a possibility of being the given number
bool is_cell_in_block(int cell_y, int cell_x, int block_y, int block_x);             // Returns true if the coordinates of the given cell are inside of the coordinates of the given block, and false if not

#endif