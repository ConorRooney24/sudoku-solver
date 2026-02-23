#include "../include/solver.h"
//#include <stdio.h>

int strip_possibilities_cell(Grid *g, int y, int x)
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

void set_sole_possibilities_solved(Grid *g)
{
        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        if (num_possibilities_cell((*g)[y][x]) == 1)
                        {
                                for (int i = 0; i < 9; i++)
                                {
                                        if ((*g)[y][x].is_possible[i]) (*g)[y][x].number = i + 1;
                                }
                        }
                }
        }
}

int num_possibilities_cell(const Cell c)
{
        int n = 0;
        for (int i = 0; i < 9; i++)
        {
                if (c.is_possible[i]) n++;
        }

        return n;
}

void solve_hidden_singles_block(Grid *g, int block_y, int block_x)
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

void solve_pointing_groups_row_block(Grid *g, int block_y, int block_x)
{
        for (int i = 0; i < 9; i++) // for every possible number
        {
                int num_possibilities_in_block = sum_possibilities_num_in_block(*g, block_y, block_x, i+1); 

                //printf("Scanning block [%d, %d] rows for possibilities of %d - found %d\n", block_y, block_x, i+1, num_possibilities_in_block);

                if (!(num_possibilities_in_block == 2 || num_possibilities_in_block == 3)) continue;
                

                int actual_y, actual_x;
                for (int cell_y = 0; cell_y < 3; cell_y++) // for every row
                {
                        int count_possibilities_in_row = 0; // The count of the current number found on this row

                        for (int cell_x = 0; cell_x < 3; cell_x++) // for every cell in this row (column)
                        {
                                actual_y = cell_y + (block_y * 3);
                                actual_x = cell_x + (block_x * 3);
                                

                                if ((*g)[actual_y][actual_x].number != 0) continue; // If solved continue
                                if ((*g)[actual_y][actual_x].is_possible[i]) count_possibilities_in_row++;

                                if (count_possibilities_in_row == num_possibilities_in_block) // If we have found all of the possibilities on the same row - then we remove the current number as a possibility from all unsolved cells on this row outside of this block.
                                {
                                        for (int x = 0; x < 9; x++) // For every cell on this row (where we have found a pointing pair/triple)
                                        {
                                                if ((*g)[actual_y][x].number != 0) continue; // if solved, continue
                                                
                                                if (is_cell_in_block(actual_y, x, block_y, block_x)) continue; // If the cell is in the block we are checking continue

                                                (*g)[actual_y][x].is_possible[i] = false;
                                        }
                                }
                        }
                }
        }
}

void solve_pointing_groups_column_block(Grid *g, int block_y, int block_x)
{
        for (int i = 0; i < 9; i++) // for every possible number
        {
                int num_possibilities_in_block = sum_possibilities_num_in_block(*g, block_y, block_x, i+1);

                //printf("Scanning block [%d, %d] columns for possibilities of %d - found %d\n", block_y, block_x, i+1, num_possibilities_in_block);

                if (!(num_possibilities_in_block == 2 || num_possibilities_in_block == 3)) continue;
                

                int actual_y, actual_x;
                for (int cell_x = 0; cell_x < 3; cell_x++) // for every column
                {
                        int count_possibilities_in_column = 0; // The count of the current number found on this column

                        for (int cell_y = 0; cell_y < 3; cell_y++) // for every cell in this column (row)
                        {
                                actual_y = cell_y + (block_y * 3);
                                actual_x = cell_x + (block_x * 3);
                                

                                if ((*g)[actual_y][actual_x].number != 0) continue; // If solved continue
                                if ((*g)[actual_y][actual_x].is_possible[i]) count_possibilities_in_column++;

                                if (count_possibilities_in_column == num_possibilities_in_block) // If we have found all of the possibilities on the same row - then we remove the current number as a possibility from all unsolved cells on this row outside of this block.
                                {
                                        for (int y = 0; y < 9; y++) // For every cell on this column (the column where we have found a pointing pair/triple)
                                        {
                                                if ((*g)[y][actual_x].number != 0) continue; // if solved, continue
                                                if (is_cell_in_block(y, actual_x, block_y, block_x)) continue; // If the cell is in the block we are checking continue

                                                (*g)[y][actual_x].is_possible[i] = false;
                                        }
                                }
                        }
                }
        }
}

int sum_possibilities_num_in_block(const Grid g, int block_y, int block_x, int num)
{
        int n = 0;

        int actual_y, actual_x;
        for (int cell_y = 0; cell_y < 3; cell_y++)
        {
                actual_y = cell_y + (block_y * 3);
                for (int cell_x = 0; cell_x < 3; cell_x++)
                {
                        actual_x = cell_x + (block_x * 3);
                        
                        if (g[actual_y][actual_x].number != 0) continue; // If solved continue

                        if (g[actual_y][actual_x].is_possible[num - 1]) n++;
                }
        }

        return n;
}

bool is_cell_in_block(int cell_y, int cell_x, int block_y, int block_x)
{
        if ((int)(cell_y/3) == block_y && (int)(cell_x/3) == block_x) return true;
        else return false;
}