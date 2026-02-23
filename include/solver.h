#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include <stdbool.h>

bool is_solved_grid(const Grid g); // Returns true if a grid is solved, false if not
int num_possibilities_cell(const Cell c); // returns the number of possibilities a given cell has
int sum_possibilities_num_in_block(const Grid g, int block_y, int block_x, int num); // Takes grid, the coordinates of a block, and a number, returns how many cells have a possibility of being the given number
bool is_cell_in_block(int cell_y, int cell_x, int block_y, int block_x);             // Returns true if the coordinates of the given cell are inside of the coordinates of the given block, and false if not

void remove_possibles_grid           (Grid *g);                         // Goes over every cell in the grid and calls the remove_possibles_cell function.
void remove_possibles_cell           (Grid *g, int cell_y, int cell_x); // Takes a cell, calls all remove_possible functions for row, column, and block. Basically this will look at all of the neighbour solved cells that correspond to the target cell and will remove possibilities from the target cell if it finds solved numbers. 
void remove_possibles_cell_by_row    (Grid *g, int cell_y, int cell_x); // Takes a cell, checks for solved neighbors on the same row and removes possibilities from the target cell based on what is found.
void remove_possibles_cell_by_column (Grid *g, int cell_y, int cell_x); // Takes a cell, checks for solved neighbors on the same column and removes possibilities from the target cell based on what is found.
void remove_possibles_cell_by_block  (Grid *g, int cell_y, int cell_x); // Takes a cell, checks for solved neighbors on the same block and removes possibilities from the target cell based on what is found.

void set_sole_possibilities_solved     (Grid *g);                         // Calls set_sole_possibilities_solved_cell for every cell in a grid
void set_sole_possibilities_solved_cell(Grid *g, int cell_y, int cell_x); // Looks at a single cell and checks how many possibilities it has. If it only has one possible number, we set it to solved.

void solve_hidden_singles_grid (Grid *g);                           // Calls solve_hidden_singles_block for every block on the grid
void solve_hidden_singles_block(Grid *g, int block_y, int block_x); // Takes a grid and the coordinates of a block (0-2) and looks at the unsolved cells. For each number 1-9, it counts how many cells have that number as a possibility. If a given number only has one possible cell in a block, it sets that cell to solved.

void solve_pointing_groups_grid (Grid *g);                                  // Calls solve_pointing_group functions for both columns and rows for every block in the grid.
void solve_pointing_groups_row_block(Grid *g, int block_y, int block_x);    // FOR A ROW: Takes a grid and the coordinates of a block, attempts to find pointing pairs or pointing triplets and then removes possibilities from corresponding cells outside of the block. For example, if we look in a block and find that only two of the unsolved squares have a possibility of being 2, if those cells are on the same row (or column), we know that there will not be a 2 on that row (or column) outside of this block.
void solve_pointing_groups_column_block(Grid *g, int block_y, int block_x); // Same as above but for columns instead of rows

#endif