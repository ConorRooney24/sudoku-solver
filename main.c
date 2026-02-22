#include <stdio.h>

#include "include/global_include.h"

int main(void)
{
        Grid grid;
        grid_init(&grid);

        /*
        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        grid[y][x].number = (x + y) % 10;
                }
                
        }*/

        grid_print(grid);
        grid_print_cell_info(grid);

        io_write("output.txt", grid);

        io_read("data/puzzle_easy_1.txt", &grid);

        printf("--- before ---\n");
        grid_print(grid);
        grid_print_cell_info(grid);

        solve_strip_possibilities(&grid, 0, 0);

        printf("--- after ---\n");
        grid_print(grid);
        grid_print_cell_info(grid);


        return 0;
}