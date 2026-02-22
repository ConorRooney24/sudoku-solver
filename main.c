#include <stdio.h>

#include "include/global_include.h"

int main(void)
{
        Grid grid;
        grid_init(&grid);

        grid_print(grid);
        grid_print_cell_info(grid);

        return 0;
}