#include "../include/board.h"

int grid_init(Grid *g)
{
        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        cell_init(&(*g)[y][x]);
                }                
        }
        
        return 0;
}

int cell_init(Cell *c)
{
        for (int i = 0; i < 9; i++)
        {
                c->is_possible[i] = false;
                c->number = 0;
        }

        return 0;
}