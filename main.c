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

        printf("[1] Automatic mode\n");
        printf("[2] Manual mode\n");
        printf("[0] Exit\n");
        printf("$ ");
        scanf("%d", &user_input);

        if      (user_input == 0) return 0;
        else if (user_input == 1) goto automatic_mode_start;
        else if (user_input != 2) return 0;

        while (1)
        {
                clear_terminal();
                grid_print(grid);
                printf("----- %s -----\n", is_solved_grid(grid) ? "Grid solved!" : "Grid not solved");
                printf("[1] Strip Possibilities\n");
                printf("[2] Set Solved\n");
                printf("[3] Remove possibles and set sole solved\n");
                printf("[4] Remove possibles and set sole solved (loop)\n");
                printf("[5] Solve Hidden Singles\n");
                printf("[6] Solve pointing groups\n");
                printf("[7] Write to 'output.txt'\n");
                printf("[8] Toggle Auto Strip on 5 & 6 (%d)\n", auto_strip ? 1 : 0);
                printf("[9] Toggle Auto Set Solved on 5 & 6 (%d)\n", auto_set_solved ? 1 : 0);
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
                                remove_possibles_and_set_soles_solved(&grid);
                                break;

                        case 4:
                                remove_possibles_and_set_soles_solved_until_stable(&grid, 100);
                                break;

                        case 5:
                                if (auto_strip) remove_possibles_grid(&grid);
                                if (auto_set_solved) set_sole_possibilities_solved(&grid);
                                solve_hidden_singles_grid(&grid);
                                break;

                        case 6:
                                if (auto_strip) remove_possibles_grid(&grid);
                                if (auto_set_solved) set_sole_possibilities_solved(&grid); 
                                solve_pointing_groups_grid(&grid);
                                break;

                        case 7:
                                io_write("output.txt", grid);
                                break;

                        case 8:
                                if (auto_strip) auto_strip = false;
                                else auto_strip = true;
                                break;

                        case 9:
                                if (auto_set_solved) auto_set_solved = false;
                                else auto_set_solved = true;
                                break;
                        
                        default:
                                break;
                }
        }

        automatic_mode_start:

        
        
        return 0;
}