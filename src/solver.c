#include "../include/solver.h"

int solve_strip_possibilities(Grid *g, int y, int x)
{
        // Check row
        for (int i = 0; i < 9; i++)
        {
                if (i == x) continue; // If we are on the target block
                if ((*g)[y][i].number == 0) continue; // if we are on an unsolved block

                // Only executes if we are on a solved block that is not the target block:
                (*g)[y][x].is_possible[(*g)[y][i].number - 1] = false; // it is not possible for the target cell to be the value of the solved cell on the same row

        }
        
        // Check column
        for (int i = 0; i < 9; i++)
        {
                if (i == y) continue;
                if ((*g)[i][x].number == 0) continue;

                (*g)[y][x].is_possible[(*g)[i][x].number - 1] = false;
        }
        

        // Check block (little bit of a mess but it works)
        int block_y, block_x; // the coords of the block of the target cell. so the top left block is 0,0, the middle is 1,1, and the bottom right is 2,2.
        block_y = y/3;
        block_x = x/3;

        int actual_y, actual_x; // coordinates on the board rather than coordinates in the block (i and j are coordinates in the block). So we are using for loops from 0 to 2 to search in a block pattern but we need to scale the numbers based on which block we are searching

        for (int i = 0; i < 3; i++)
        {
                actual_y = i + (3 * block_y);

                for (int j = 0; j < 3; j++)
                {
                        actual_x = j + (3 * block_x);

                        if (actual_x == x && actual_y == y) continue; // If we are on the target block
                        if ((*g)[actual_y][actual_x].number == 0) continue; // if we are on an unsolved block
                        
                        (*g)[y][x].is_possible[(*g)[actual_y][actual_x].number - 1] = false; 

                }
        }

        return 0;
}

void solve_set_solved(Grid *g)
{
        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        if (solve_sum_possibilities((*g)[y][x]) == 1)
                        {
                                for (int i = 0; i < 9; i++)
                                {
                                        if ((*g)[y][x].is_possible[i]) (*g)[y][x].number = i + 1;
                                }
                        }
                }
        }
}

int solve_sum_possibilities(const Cell c)
{
        int n = 0;
        for (int i = 0; i < 9; i++)
        {
                if (c.is_possible[i]) n++;
        }

        return n;
}

void solve_block_hidden_single(Grid *g, int block_y, int block_x)
{
        // block_y and block_x are coordinates of a block from 0-2
        // cell_y and cell_x are coordinates of a cell in that block from 0-2
        // actual_x and actual_y are coordinates on the grid

        int actual_y, actual_x;
        int counter;                    // Counting how many times the current number shows up as possible.
        int last_found_y, last_found_x; // The last location in which we found a match for the current number

        for (int n = 0; n < 9; n++) // for every possible number 1-9
        {
                counter = 0;

                for (int cell_y = 0; cell_y < 3; cell_y++)
                {
                        actual_y = cell_y + (block_y * 3);

                        for (int cell_x = 0; cell_x < 3; cell_x++)
                        {
                                actual_x = cell_x + (block_x * 3);
                                
                                if ((*g)[actual_y][actual_x].number != 0) continue; // If solved continue

                                if ((*g)[actual_y][actual_x].is_possible[n])
                                {
                                        counter++;
                                        last_found_y = actual_y;
                                        last_found_x = actual_x;
                                }
                                
                        }
                        
                }

                if (counter == 1) // If this current number has only one possible spot in this block
                {
                        (*g)[last_found_y][last_found_x].number = n + 1;
                }
        }
}