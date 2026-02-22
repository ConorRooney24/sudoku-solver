#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"

int solve_strip_possibilities(Grid *g, int y, int x); // Takes a given cell on a board and checks neighbors in its row, column, and block to remove its possibilities. For example, if a given cell has 2 as a possibility, and this function finds a solved cell with 2 as its value, it will remove 2 as a possibility from the target cell.
void solve_set_solved(Grid *g);                        // Looks through every cell on a grid for cells that only have one possibility and sets them to solved
int solve_sum_possibilities(const Cell c);            // returns the sum of possibilities of a cell
#endif