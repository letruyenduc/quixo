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

#define OFFSET_LINE 5
#define OFFSET_COL 10

void displayGrid(Grid *grid)
{
    for (int j = 0; j < grid->width; j++)
    {
        mvprintw(OFFSET_LINE + 0, OFFSET_COL + j * 2, "+");
        mvprintw(OFFSET_LINE + 0, OFFSET_COL + j * 2 + 1, "-");
    }
    mvprintw(OFFSET_LINE + 0, OFFSET_COL + grid->width * 2, "+");

    for (int i = 0; i < grid->height; i++)
    {
        mvprintw(OFFSET_LINE + i * 2 + 1, OFFSET_COL + 0, "|");

        for (int j = 0; j < grid->width; j++)
        {
            mvprintw(OFFSET_LINE + i * 2 + 1, OFFSET_COL + j * 2 + 1, "%c", grid->rows[i][j]);
            mvprintw(OFFSET_LINE + i * 2 + 1, OFFSET_COL + j * 2 + 2, "|");

            mvprintw(OFFSET_LINE + i * 2 + 2, OFFSET_COL + j * 2, "+");
            mvprintw(OFFSET_LINE + i * 2 + 2, OFFSET_COL + j * 2 + 1, "-");
        }
        mvprintw(OFFSET_LINE + i * 2 + 2, OFFSET_COL + grid->width * 2, "+");
    }

    refresh();
}

void handleInput(int *row, int *column, int *function, char *player)
{

    mvprintw(OFFSET_LINE + 12, OFFSET_COL + 0, "Ligne : ");
    refresh();
    scanw("%d", row);

    mvprintw(OFFSET_LINE + 13, OFFSET_COL + 0, "Colonne : ");
    refresh();
    scanw("%d", column);

    mvprintw(OFFSET_LINE + 14, OFFSET_COL + 0, "0=shiftRowRight, 1=shiftRowLeft, 2=shiftColumnDown, 3=shiftColumnUp ; Fonction : ");
    refresh();
    scanw("%d", function);

    mvprintw(OFFSET_LINE + 15, OFFSET_COL + 0, "Joueur : ");
    refresh();
    *player = (char)getch();
    refresh();
}