#include <stdio.h>

#include "include/global_include.h"

int main(void)
{
        Grid grid;
        grid_init(&grid);

        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        grid[y][x].number = (x + y) % 10;
                }
                
        }

        grid_print(grid);
        grid_print_cell_info(grid);

        io_write("output.txt", grid);

        return 0;
}