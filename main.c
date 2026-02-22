#include <stdio.h>

#include "include/global_include.h"

int main(void)
{
        Grid grid;
        grid_init(&grid);

        io_read("data/puzzle_easy_1.txt", &grid);

        printf("----------- BEFORE SOLVING -----------\n");
        grid_print(grid);
        grid_print_cell_info(grid);

        for (int i = 0; i < 100; i++) // For now we just loop 100 times, strip possibilities, set solved, and repeat.
        {
                for (int y = 0; y < 9; y++)
                {
                        for (int x = 0; x < 9; x++)
                        {
                                solve_strip_possibilities(&grid, y, x);
                        }
                        
                }

                solve_set_solved(&grid);
                
                for (int y = 0; y < 3; y++)
                {
                        for (int x = 0; x < 3; x++)
                        {
                                solve_block_hidden_single(&grid, y, x);
                        }
                        
                }

                solve_set_solved(&grid);

                for (int y = 0; y < 3; y++)
                {
                        for (int x = 0; x < 3; x++)
                        {
                                solve_block_pointing_groups_column(&grid, y, x);
                                solve_block_pointing_groups_row(&grid, y, x);
                        }
                        
                }

                solve_set_solved(&grid);
        }

        printf("----------- AFTER SOLVING -----------\n");
        grid_print(grid);
        grid_print_cell_info(grid);

        io_write("output.txt", grid);
        
        return 0;
}