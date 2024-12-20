#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include "grid.h"
#include "display.h"
/*
 * Auteur : Duc
 * Description : Affiche l'écran de fin de partie
 * Paramètres :
 * - grid : La grille de jeu
 * - winner : Le joueur gagnant
 */
void displayEndScreen(Grid *grid, Player *winner)
{
    displayGrid(grid, -1, -1, 0);
    mvprintw(getOffsetLine(grid) + 4, getTextOffsetCol(grid), "%s (%c) gagne!", winner->playerName, winner->playerSymbol);
    mvprintw(getOffsetLine(grid) + 6, getTextOffsetCol(grid), "Appuyez sur n'importe quelle touche pour quitter");
    refresh();
    getch();
}