#include "../include/io.h"
#include <stdio.h>

int io_read(const char *file_name, Grid *g)
{
        FILE *file = fopen(file_name, "r");
        if (!file)
        {
                printf("Error: Unable to read file '%s'\n", file_name);
                return 1;
        }

        int index = 0; // The current cell we are parsing for - also a counter of the number of cells we have passed
        int y, x;      // we will derive y and x values from the index using the following: y = floor(n/9), x = n mod 9

        int c; // Has to be an int for EOF to be read properly
        while ((c = fgetc(file)) != EOF)
        {
                printf("Index %d\n", index);
                if (index > 80)
                {
                        printf("Warning: More than 81 specified characters in file '%s'.\n", file_name);
                        break;
                }
                
                if (c == ' ' || c == '\n') continue; // Hopefully add a little bit of speed

                if (c == '0' || c == '.')
                {
                        y = index / 9;
                        x = index % 9;

                        (*g)[y][x].number = 0;

                        index++;
                }
                else if (c >= '1' && c <= '9')
                {
                        y = index / 9;
                        x = index % 9;

                        (*g)[y][x].number = c - '0'; // This works because of character encoding. zero is 48 in decimal, one is 49 and so on.

                        index++;
                }
                else continue;
        }

        fclose(file);

        if (index < 80 + 1) // We plus one because after parsing a specified char, we increment the index.
        {
                printf("Error: not enough specified characters in file '%s'\n", file_name);
                return 1;
        }

        return 0;
}

int io_write(const char *file_name, const Grid g)
{
        FILE *file = fopen(file_name, "w");
        if (!file)
        {
                printf("Error: Unable to write to file '%s'\n", file_name);
                return 1;
        }

        for (int y = 0; y < 9; y++)
        {
                for (int x = 0; x < 9; x++)
                {
                        fprintf(file, "%d", g[y][x].number);

                        if ((x+1) % 3 == 0 && (x+1) != 9) fputc(' ', file); // Split into thirds, dont add a space the last index
                }

                if ((y+1) != 9) fputc('\n', file);

                if ((y+1) % 3 == 0 && (y+1) != 9) fputc('\n', file);
        }

        fclose(file);

        return 0;
}