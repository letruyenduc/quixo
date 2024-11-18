#include <stdlib.h>
#include <time.h>
#include "grid.h"
#ifdef _WIN32
#include <ncursesw/ncurses.h>
#include <windows.h>
#endif
int main()
{
    srand(time(NULL));
    // Définir l'encodage de la console en UTF-8
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

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