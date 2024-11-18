#ifndef GRID_H
#define GRID_H

#define SHIFT_STATUS_OK 0
#define SHIFT_STATUS_OTHER_PLAYER 1

struct Grid
{
    int width;
    int height;
    char **rows;
} typedef Grid;

Grid *createGrid(int width, int height);
int shiftRowRight(Grid *grid, int removedCubeRow, int removedCubeColumn, char player);
int shiftRowLeft(Grid *grid, int removedCubeRow, int removedCubeColumn, char player);
int shiftColumnDown(Grid *grid, int removedCubeRow, int removedCubeColumn, char player);
int shiftColumnUp(Grid *grid, int removedCubeRow, int removedCubeColumn, char player);
void freeGrid(Grid *grid);
void printGrid(Grid *grid);

#endif // GRID_H