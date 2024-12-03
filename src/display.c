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


/**
 * Auteurs : Duc et Kevin
 * Description : Affiche la grille de jeu
 * Paramètres : 
 * - grid : La grille de jeu
 * - nextPlayer : Le joueur qui doit jouer
 * - statusMessage : Le message de statut
 */
void displayGrid(Grid *grid, char nextPlayer, wchar_t* statusMessage)
{
    clear();
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

    if (statusMessage != NULL) {
        mvprintw(OFFSET_LINE + grid->height * 2 + 2, OFFSET_COL, "%ls", statusMessage);
    }

    mvprintw(OFFSET_LINE + grid->height * 2 + 3, OFFSET_COL, "Le joueur %c joue.", nextPlayer);

    refresh();
}

/**
 * Auteurs : Duc et Kevin
 * Description : Affiche les messages qui propose la ligne, la colonne et la fonction à l'utilisateur
 * Paramètres : 
 * - grid : La grille de jeu
 */
void handleInput(Grid* grid, int *row, int *column, int *function)
{

    mvprintw(OFFSET_LINE + grid->height * 2 + 5, OFFSET_COL + 0, "Ligne : ");
    refresh();
    scanw("%d", row);

    mvprintw(OFFSET_LINE + grid->height * 2 + 6, OFFSET_COL + 0, "Colonne : ");
    refresh();
    scanw("%d", column);

    mvprintw(OFFSET_LINE + grid->height * 2 + 7, OFFSET_COL + 0, "0=shiftRowRight, 1=shiftRowLeft, 2=shiftColumnDown, 3=shiftColumnUp, 4=quitter ; Fonction : ");
    refresh();
    scanw("%d", function);
}