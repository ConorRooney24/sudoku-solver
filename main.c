#include <stdio.h>

#include "include/global_include.h"

int main(void)
{
        Grid grid;
        grid_init(&grid);

        io_read("data/puzzle_medium_1.txt", &grid);

        bool auto_strip = true;
        bool auto_set_solved = true;

        int user_input = 0;
        while (1)
        {
                clear_terminal();
                grid_print(grid);
                printf("\n");
                printf("[1] Strip Possibilities\n");
                printf("[2] Set Solved\n");
                printf("\n");
                printf("[3] Solve Hidden Singles\n");
                printf("[4] Solve pointing groups (row)\n");
                printf("[5] Solve pointing groups (column)\n");
                printf("\n");
                printf("[6] Write to 'output.txt'\n");
                printf("\n");
                printf("[7] Toggle Auto Strip on 3, 4, 5 (%d)\n", auto_strip ? 1 : 0);
                printf("[8] Toggle Auto Set Solved on 3, 4, 5 (%d)\n", auto_set_solved ? 1 : 0);
                printf("\n");
                printf("[0] Exit\n");
                printf("$ ");
                scanf("%d", &user_input);

                switch (user_input)
                {
                        case 0:
                                return 0;
                                break;

                        case 1:
                                remove_possibles_grid(&grid);
                                break;

                        case 2:
                                set_sole_possibilities_solved(&grid);
                                break;

                        case 3:
                                if (auto_strip) remove_possibles_grid(&grid);
                                if (auto_set_solved) set_sole_possibilities_solved(&grid);

                                for (int y = 0; y < 3; y++)
                                {
                                        for (int x = 0; x < 3; x++)
                                        {
                                                solve_hidden_singles_block(&grid, y, x);
                                        }
                                        
                                }
                                
                                break;

                        case 4:
                                if (auto_strip) remove_possibles_grid(&grid);
                                if (auto_set_solved) set_sole_possibilities_solved(&grid); 

                                for (int y = 0; y < 3; y++)
                                {
                                        for (int x = 0; x < 3; x++)
                                        {
                                                solve_pointing_groups_row_block(&grid, y, x);
                                        }
                                        
                                }

                                break;

                        case 5:
                                if (auto_strip) remove_possibles_grid(&grid);
                                if (auto_set_solved) set_sole_possibilities_solved(&grid);

                                for (int y = 0; y < 3; y++)
                                {
                                        for (int x = 0; x < 3; x++)
                                        {
                                                solve_pointing_groups_column_block(&grid, y, x);
                                        }
                                        
                                }

                                break;

                        case 6:
                                io_write("output.txt", grid);
                                break;

                        case 7:
                                if (auto_strip) auto_strip = false;
                                else auto_strip = true;
                                break;

                        case 8:
                                if (auto_set_solved) auto_set_solved = false;
                                else auto_set_solved = true;
                                break;
                        
                        default:
                                break;
                }
        }
        
        return 0;
}