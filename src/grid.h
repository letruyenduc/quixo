#ifndef GRID_H
#define GRID_H

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

#endif // GRID_H