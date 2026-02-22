#include "../include/io.h"
#include <stdio.h>

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
}