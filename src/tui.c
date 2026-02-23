#include "../include/tui.h"
#include <stdio.h>

void clear_terminal()
{
        printf("\033[2J\033[H");
}

void colour_fore_set(Colour c)
{
        printf("\033[38;2;%d;%d;%dm", c.r, c.g, c.b);
}

void colour_back_set(Colour c)
{
        printf("\033[48;2;%d;%d;%dm", c.r, c.g, c.b);
}

void colour_reset()
{
        printf("\033[0m");
}

void cursor_move(char direction, int times)
{
        switch (direction)
        {
                case 'u':
                        printf("\033[%dA", times);
                        break;

                case 'd':
                        printf("\033[%dB", times);
                        break;

                case 'l':
                        printf("\033[%dD", times);
                        break;

                case 'r':
                        printf("\033[%dC", times);
                        break;
                
                default:
                        printf("Error: '%c' not a valid direction\n", direction);
                        break;
        }
}