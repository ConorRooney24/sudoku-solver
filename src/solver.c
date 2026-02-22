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