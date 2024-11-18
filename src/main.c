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

    int row, column, function, status;
    char player;

    while (1)
    {
        status = 0;
        printGrid(grid);
        printf("Ligne : ");
        fflush(stdin);
        scanf("%d", &row);
        printf("Colonne : ");
        fflush(stdin);
        scanf("%d", &column);
        printf("\n0=shiftRowRight\n1=shiftRowLeft\n2=shiftColumnDown\n3=shiftColumnUp\nFonction : ");
        fflush(stdin);
        scanf("%d", &function);
        printf("Joueur : ");
        fflush(stdin);
        scanf("%c", &player);
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
    }

    freeGrid(grid);
    grid = NULL;

    return 0;
}