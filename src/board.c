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
        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        
                        cell_print(g[y][x], ((y/3) + (x/3)) % 2 == 0 ? BOARD_BLOCK_SECONDARY : BOARD_BLOCK_PRIMARY, CELL_PRINT_WIDTH * x);
                        cursor_move('u', CELL_PRINT_HEIGHT);
                }

                cursor_move('d', CELL_PRINT_HEIGHT);
                cursor_move('l', CELL_PRINT_WIDTH * 9);
        }

        printf("\n");
}

void grid_print_simple(const Grid g)
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
                        cell_print_simple(g[y][x]);
                }
        }
}

void cell_print(const Cell c, Colour background, int offset_x)
{
        if (c.number != 0) // if solved
        {
                cursor_move('r', offset_x); colour_fore_set(BOARD_FONT_PRIMARY); colour_back_set(background); printf("           ");            colour_reset(); printf("\n");
                cursor_move('r', offset_x); colour_fore_set(BOARD_FONT_PRIMARY); colour_back_set(background); printf("           ");            colour_reset(); printf("\n");
                cursor_move('r', offset_x); colour_fore_set(BOARD_FONT_PRIMARY); colour_back_set(background); printf("     %d     ", c.number); colour_reset(); printf("\n");
                cursor_move('r', offset_x); colour_fore_set(BOARD_FONT_PRIMARY); colour_back_set(background); printf("           ");            colour_reset(); printf("\n");
                cursor_move('r', offset_x); colour_fore_set(BOARD_FONT_PRIMARY); colour_back_set(background); printf("           ");            colour_reset(); printf("\n");
                return;
        }

        // if not solved
        cursor_move('r', offset_x); colour_fore_set(BOARD_FONT_SECONDARY); colour_back_set(background); printf("           "); colour_reset(); printf("\n");
        cursor_move('r', offset_x); colour_fore_set(BOARD_FONT_SECONDARY); colour_back_set(background); printf("   %c %c %c   ", c.is_possible[0] ? '1' : ' ' , c.is_possible[1] ? '2' : ' ' , c.is_possible[2] ? '3' : ' '); colour_reset(); printf("\n");
        cursor_move('r', offset_x); colour_fore_set(BOARD_FONT_SECONDARY); colour_back_set(background); printf("   %c %c %c   ", c.is_possible[3] ? '4' : ' ' , c.is_possible[4] ? '5' : ' ' , c.is_possible[5] ? '6' : ' '); colour_reset(); printf("\n");
        cursor_move('r', offset_x); colour_fore_set(BOARD_FONT_SECONDARY); colour_back_set(background); printf("   %c %c %c   ", c.is_possible[6] ? '7' : ' ' , c.is_possible[7] ? '8' : ' ' , c.is_possible[8] ? '9' : ' '); colour_reset(); printf("\n");
        cursor_move('r', offset_x); colour_fore_set(BOARD_FONT_SECONDARY); colour_back_set(background); printf("           "); colour_reset(); printf("\n");
}

void cell_print_simple(const Cell c)
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