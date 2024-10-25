#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "grid.h"

int main()
{
    srand(time(NULL));
    // Définir l'encodage de la console en UTF-8
    SetConsoleOutputCP(CP_UTF8);

    Grid *grid = createGrid(5, 5);

    printGrid(grid);

    shiftRowRight(grid, 0, 'X');

    printGrid(grid);

    shiftRowRight(grid, 0, 'O');

    printGrid(grid);

    shiftRowLeft(grid, 1, 'X');

    printGrid(grid);

    shiftRowLeft(grid, 1, 'O');

    printGrid(grid);

    shiftRowRight(grid, 2, 'X');

    printGrid(grid);

    shiftColumnDown(grid, 0, 'O');

    printGrid(grid);

    shiftColumnUp(grid, 4, 'X');

    printGrid(grid);

    freeGrid(grid);
    grid = NULL;

    return 0;
}