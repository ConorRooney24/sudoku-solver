#ifndef TUI_H
#define TUI_H

#include <stdint.h>

#define BOARD_BLOCK_PRIMARY   ((Colour){226, 247, 255})
#define BOARD_BLOCK_SECONDARY ((Colour){200, 240, 255})
#define BOARD_FONT_PRIMARY    ((Colour){0, 0, 0})
#define BOARD_FONT_SECONDARY  ((Colour){200, 200, 200})

typedef struct Colour
{
        uint8_t r, g, b;
} Colour;

void clear_terminal();

void colour_fore_set(Colour c);
void colour_back_set(Colour c);
void colour_reset();

void cursor_move(char direction, int times); // Moves the cursor in the specified direction a given number of times. directions are 'u', 'd', 'l', and 'r'.

#endif