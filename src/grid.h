#ifndef GRID_H
#define GRID_H
#include "structures.h"

Grid *createGrid(int width, int height);
int isMoveAllowed(Grid *grid, int row, int column, Player *player);
int shiftRowRight(Grid *grid, int removedCubeRow, int removedCubeColumn, Player *player);
int shiftRowLeft(Grid *grid, int removedCubeRow, int removedCubeColumn, Player *player);
int shiftColumnDown(Grid *grid, int removedCubeRow, int removedCubeColumn, Player *player);
int shiftColumnUp(Grid *grid, int removedCubeRow, int removedCubeColumn, Player *player);
void freeGrid(Grid *grid);

#endif // GRID_H