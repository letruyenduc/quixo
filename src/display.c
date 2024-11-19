#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include "grid.h"

void displayGrid(Grid *grid)
{
    for (int j = 0; j < grid->width; j++)
    {
        mvprintw(0, j * 2, "+");
        mvprintw(0, j * 2 + 1, "-");
    }
    mvprintw(0, grid->width * 2, "+");

    for (int i = 0; i < grid->height; i++)
    {
        mvprintw(i * 2 + 1, 0, "|");

        for (int j = 0; j < grid->width; j++)
        {
            mvprintw(i * 2 + 1, j * 2 + 1, "%c", grid->rows[i][j]);
            mvprintw(i * 2 + 1, j * 2 + 2, "|");
        }

        mvprintw(i * 2 + 2, 0, "+");
        for (int j = 0; j < grid->width; j++)
        {
            mvprintw(i * 2 + 2, j * 2 + 1, "-");
        }
        mvprintw(i * 2 + 2, grid->width * 2, "+");
    }

    refresh();
}

void handleInput(int *row, int *column, int *function, char *player)
{

    mvprintw(11, 0, "Ligne : ");
    refresh();
    scanw("%d", row);

    mvprintw(12, 0, "Colonne : ");
    refresh();
    scanw("%d", column);

    mvprintw(13, 0, "0=shiftRowRight, 1=shiftRowLeft, 2=shiftColumnDown, 3=shiftColumnUp ; Fonction : ");
    refresh();
    scanw("%d", function);

    mvprintw(14, 0, "Joueur : ");
    refresh();
    *player = (char)getch();

    // Nettoie les zones d'affichage des inputs
    mvprintw(11, 0, "                                                  ");
    mvprintw(12, 0, "                                                  ");
    mvprintw(13, 0, "                                                  ");
    mvprintw(14, 0, "                                                  ");
    refresh();
}