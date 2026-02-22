#include "../include/board.h"
#include <stdio.h>

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
                c->is_possible[i] = true;
        }
        
        c->number = 0;

        return 0;
}

void grid_print(const Grid g)
{       
        printf("+---+---+---+---+---+---+---+---+---+\n");

        for (int y = 0; y < 9; y++)
        {
                printf("|");

                for (int x = 0; x < 9; x++)
                {
                        printf(" %d |", g[y][x].number);
                }

                printf("\n+---+---+---+---+---+---+---+---+---+\n");
                
        }
}

void grid_print_cell_info(const Grid g)
{       
        printf("[y, x] | Cell Information\n");
        printf("-------+-----------------\n");

        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        printf("[%d, %d] | ", y, x);
                        cell_print(g[y][x]);
                }
        }
}

void cell_print(const Cell c)
{
        if (c.number != 0) // If solved
        {
                printf("Cell Solved   - Number: %d\n", c.number);
        }
        else
        {
                printf("Cell Unsolved - Possible: ");

                for (int i = 0; i < 9; i++)
                {
                        if (c.is_possible[i])
                        {
                                printf("%d, ", i+1);
                        }
                }

                printf("\n");
        }
}