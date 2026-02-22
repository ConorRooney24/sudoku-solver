#ifndef IO_H
#define IO_H

#include "board.h"

int io_read(const char *file_name, Grid *g);       // Reads a puzzle from file and writes the numbers to a grid.
int io_write(const char *file_name, const Grid g); // Writes the numbers of each cell on a grid to a file.

#endif