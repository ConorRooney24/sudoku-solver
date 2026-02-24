#include "../include/solver.h"
//#include <stdio.h>

bool are_different_grids(const Grid g1, const Grid g2)
{
        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        if (g1[y][x].number != g2[y][x].number) return true;
                        
                        if (g1[y][x].number == 0) // if unsolved check possibles
                        {
                                for (int i = 0; i < 9; i++)
                                {
                                        if (g1[y][x].is_possible[i] != g2[y][x].is_possible[i]) return true;
                                }
                        }
                }
        }

        return false;
}

bool is_solved_grid(const Grid g)
{
        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        if (g[y][x].number == 0) return false;
                }
        }

        int tally[9] = {0};
        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        for (int i = 0; i < 9; i++)
                        {
                                if (g[y][x].is_possible[i]) tally[i]++;
                                if (tally[i] > 9) return false;
                        }
                }
        }

        return true;
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

void remove_possibles_and_set_soles_solved_until_stable(Grid *g, int limit)
{
        Grid before;
        int iteration = 0;
        while (iteration < limit)
        {
                // Copy g into before
                for (int y = 0; y < 9; y++)
                {
                        for (int x = 0; x < 9; x++)
                        {
                                before[y][x].number = (*g)[y][x].number;

                                for (int i = 0; i < 9; i++)
                                {
                                        before[y][x].is_possible[i] = (*g)[y][x].is_possible[i]; 
                                }
                        }
                }
                
                remove_possibles_and_set_soles_solved(g);

                if(!are_different_grids(before, *g)) break;
        }
}

void remove_possibles_and_set_soles_solved(Grid *g)
{
        remove_possibles_grid(g);
        set_sole_possibilities_solved(g);
}

void remove_possibles_grid(Grid *g)
{
        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        remove_possibles_cell(g, y, x);
                }
        }
}

void remove_possibles_cell(Grid *g, int cell_y, int cell_x)
{
        remove_possibles_cell_by_row(g, cell_y, cell_x);
        remove_possibles_cell_by_column(g, cell_y, cell_x);
        remove_possibles_cell_by_block(g, cell_y, cell_x);
}

void remove_possibles_cell_by_row(Grid *g, int cell_y, int cell_x)
{
        for (int current_x = 0; current_x < 9; current_x++)
        {
                if (current_x == cell_x) continue; // If we are on the target block
                if ((*g)[cell_y][current_x].number == 0) continue; // if we are on an unsolved block

                // Only executes if we are on a solved block that is not the target block:
                (*g)[cell_y][cell_x].is_possible[(*g)[cell_y][current_x].number - 1] = false; // it is not possible for the target cell to be the value of the solved cell on the same row
        }
}

void remove_possibles_cell_by_column(Grid *g, int cell_y, int cell_x)
{
        for (int current_y = 0; current_y < 9; current_y++)
        {
                if (current_y == cell_y) continue;
                if ((*g)[current_y][cell_x].number == 0) continue;

                (*g)[cell_y][cell_x].is_possible[(*g)[current_y][cell_x].number - 1] = false;
        }
}

void remove_possibles_cell_by_block(Grid *g, int cell_y, int cell_x)
{
        int block_y, block_x;   // the coords of the block of the target cell. so the top left block is 0,0, the middle is 1,1, and the bottom right is 2,2.
        int actual_y, actual_x; // coordinates on the board rather than coordinates in the block (i and j are coordinates in the block). So we are using for loops from 0 to 2 to search in a block pattern but we need to scale the numbers based on which block we are searching

        block_y = cell_y/3;
        block_x = cell_x/3;

        for (int current_y = 0; current_y < 3; current_y++)
        {
                actual_y = current_y + (3 * block_y);

                for (int current_x = 0; current_x < 3; current_x++)
                {
                        actual_x = current_x + (3 * block_x);

                        if (actual_x == cell_x && actual_y == cell_y) continue; // If we are on the target block
                        if ((*g)[actual_y][actual_x].number == 0) continue; // if we are on an unsolved block
                        
                        (*g)[cell_y][cell_x].is_possible[(*g)[actual_y][actual_x].number - 1] = false; 

                }
        }
}

void set_sole_possibilities_solved(Grid *g)
{
        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        set_sole_possibilities_solved_cell(g, y, x);
                }
        }
}

void set_sole_possibilities_solved_cell(Grid *g, int cell_y, int cell_x)
{
        if (num_possibilities_cell((*g)[cell_y][cell_x]) == 1)
        {
                for (int i = 0; i < 9; i++)
                {
                        if ((*g)[cell_y][cell_x].is_possible[i]) (*g)[cell_y][cell_x].number = i + 1;
                }
        }
}

void solve_hidden_singles_grid(Grid *g)
{
        for (int y = 0; y < 3; y++)
        {
                for (int x = 0; x < 3; x++)
                {
                        solve_hidden_singles_block(g, y, x);
                }
        }
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

void solve_pointing_groups_grid(Grid *g)
{
        for (int y = 0; y < 3; y++)
        {
                for (int x = 0; x < 3; x++)
                {
                        solve_pointing_groups_column_block(g, y, x);
                        solve_pointing_groups_row_block(g, y, x);
                }
        }
}

void solve_pointing_groups_row_block(Grid *g, int block_y, int block_x)
{
        for (int i = 0; i < 9; i++) // for every possible number
        {
                int num_possibilities_in_block = sum_possibilities_num_in_block(*g, block_y, block_x, i+1); 
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

void solve_hidden_pairs_grid(Grid *g)
{
        for (int y = 0; y < 3; y++)
        {
                for (int x = 0; x < 3; x++)
                {
                        //printf("\n\n --- ENTERING SCAN OF BLOCK [%d, %d]\n", y, x);
                        solve_hidden_pairs_block(g, y, x);
                }
        }
}

void solve_hidden_pairs_block(Grid *g, int block_y, int block_x) // TODO This whole function needs refactored and heavily broken down. I need to make structs for things like coordinates, grid, cell and so on for more flexible functions. If we make a grid and cell struct, they should probably store pointers to their parent and also their own coordinates relative to their cell and maybe to the whole grid too.
{
        int cell_a_y, cell_a_x, cell_b_y, cell_b_x; // saved coordinates of the two member cells in the block (not on the board so they are 0-2)
        int possibility_a, possibility_b; // 0-8, the possible numbers that both cell a and cell b share (the ones we must remove from all unsolved cells in this grid which are not cell a or cell b)

        int actual_y, actual_x; // coordinates of the cell on the grid instead of coordinates of the cell in the block
        for (int cell_y = 0; cell_y < 3; cell_y++)
        {
                actual_y = cell_y + (block_y * 3);
                for (int cell_x = 0; cell_x < 3; cell_x++)
                {
                        actual_x = cell_x + (block_x * 3);

                        //printf("Cell A Scan starting for [%d, %d] (first loop)\n", actual_y, actual_x);


                        if ((*g)[actual_y][actual_x].number != 0) continue; // if solved, continue
                        
                        if (num_possibilities_cell((*g)[actual_y][actual_x]) == 2) // we have found a cell with only two possibles
                        {
                                // We set cell a to this cell
                                cell_a_y = actual_y;
                                cell_a_x = actual_x;

                                //printf("\nFound cell A [%d, %d]\n", cell_a_y, cell_a_x);

                                // and then we search the block again for another cell that is not cell a that matches cell a.
                                int second_actual_y, second_actual_x;
                                for (int second_cell_y = 0; second_cell_y < 3; second_cell_y++)
                                {
                                        second_actual_y = second_cell_y + (block_y * 3);
                                        for (int second_cell_x = 0; second_cell_x < 3; second_cell_x++)
                                        {
                                                second_actual_x = second_cell_x + (block_x * 3);

                                                //printf("Looking for cell B. Currently checking [%d, %d]\n", second_actual_y, second_actual_x);

                                                if ((*g)[second_actual_y][second_actual_x].number != 0) /*printf("Cell B candidate [%d, %d] exit because solved\n", second_actual_y, second_actual_x);*/ continue; // if solved, continue
                                                if (second_actual_y == cell_a_y && second_actual_x == cell_a_x) /*printf("Cell B candidate [%d, %d] exit because == cell a\n", second_actual_y, second_actual_x);*/ continue; // if cell a, continue
                                                
                                                //printf("Cell B candidate [%d, %d] is not solved, and is not cell A. Checking possibles...\n", second_actual_y, second_actual_x);
                                                bool cells_match = true;
                                                for (int n = 0; n < 9; n++)
                                                {
                                                        //printf("checking possible [%d]\n", n);
                                                        if ((*g)[cell_a_y][cell_a_x].is_possible[n] != (*g)[second_actual_y][second_actual_x].is_possible[n]) // if the cells do not match
                                                        {
                                                                cells_match = false;
                                                                //printf("Exit loop because cell a and cell b possibles do not match\n", second_actual_y, second_actual_x);
                                                                break;
                                                        }
                                                }
                                                

                                                if (cells_match)
                                                {
                                                        // record location of cell b
                                                        cell_b_y = second_actual_y;
                                                        cell_b_x = second_actual_x;

                                                        //printf("Found cell b [%d, %d]\n", cell_b_y, cell_b_x);

                                                        // record the two common numbers
                                                        int i = 0;
                                                        for (int n = 0; n < 9; n++)
                                                        {
                                                                if ((*g)[cell_a_y][cell_a_x].is_possible[n])
                                                                {
                                                                        if (i == 0)
                                                                        {
                                                                                possibility_a = n;
                                                                                i++;
                                                                        }
                                                                        else
                                                                        {
                                                                                possibility_b = n;
                                                                                break;
                                                                        }
                                                                }
                                                        }

                                                        // loop over the grid a third time removing the two common numbers as a possibility from unsolved cells that are not cell a or cell b
                                                        //printf("    Found Pair!   Looping over other cells in block and removing possibilities\n");
                                                        int third_actual_y, third_actual_x;
                                                        for (int third_cell_y = 0; third_cell_y < 3; third_cell_y++)
                                                        {
                                                                third_actual_y = third_cell_y + (block_y * 3);
                                                                for (int third_cell_x = 0; third_cell_x < 3; third_cell_x++)
                                                                {
                                                                        third_actual_x = third_cell_x + (block_x * 3);

                                                                        if ((*g)[third_actual_y][third_actual_x].number != 0) continue; // if solved, continue
                                                                        if((third_actual_y == cell_a_y && third_actual_x == cell_a_x) || (third_actual_y == cell_b_y && third_actual_x == cell_b_x)) continue; // If on cell a or cell b

                                                                        // if we are on a new cell that is not solved and is not cell or cell b
                                                                        (*g)[third_actual_y][third_actual_x].is_possible[possibility_a] = false;
                                                                        (*g)[third_actual_y][third_actual_x].is_possible[possibility_b] = false;

                                                                        //printf("Removed possibles from [%d, %d]\n", third_actual_y, third_actual_x);
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
}