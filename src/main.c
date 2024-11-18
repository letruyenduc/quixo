#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "display.h"

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#include <windows.h>
#else
#include <ncurses.h>
#endif
int main()
{
    srand(time(NULL));
// Définir l'encodage de la console en UTF-8
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    Grid *grid = createGrid(5, 5);
    initGrid();

    int row, column, function, status;
    char player;

    while (1)
    {
        status = 0;
        clear();
        displayGrid(grid);
        handleInput(&row, &column, &function, &player);
        switch (function)
        {
        case 0:
            status = shiftRowRight(grid, row, column, player);
            break;
        case 1:
            status = shiftRowLeft(grid, row, column, player);
            break;
        case 2:
            status = shiftColumnDown(grid, row, column, player);
            break;
        case 3:
            status = shiftColumnUp(grid, row, column, player);
            break;
        default:
            printf("Fonction invalide !");
            break;
        }

        printf("\n\n\n\n\n\n\nStatut : %d\n", status);
        refresh();
    }

    freeGrid(grid);
    grid = NULL;
    endwin();
    return 0;
}