#ifndef GRID_H
#define GRID_H
#include "structures.h"

Grid *createGrid(int width, int height);
int isMoveAllowed(Grid *grid, int row, int column, char player);
int shiftRowRight(Grid *grid, int removedCubeRow, int removedCubeColumn, char player);
int shiftRowLeft(Grid *grid, int removedCubeRow, int removedCubeColumn, char player);
int shiftColumnDown(Grid *grid, int removedCubeRow, int removedCubeColumn, char player);
int shiftColumnUp(Grid *grid, int removedCubeRow, int removedCubeColumn, char player);
void freeGrid(Grid *grid);

#endif // GRID_H