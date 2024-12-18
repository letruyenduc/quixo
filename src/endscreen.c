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
 * Retour : 0 qui indique la fin du jeu, on peut donc quitter le programme
 */
void displayEndScreen(Grid *grid, char winner)
{
    char key;
    refresh();
    mvprintw(getTextOffsetCol(grid), getOffsetLine(grid), "Le joueur %c gagne!", winner);
    mvprintw(getTextOffsetCol(grid), getOffsetLine(grid) + 2, "Appuyez sur n'importe quelle touche pour quitter");
    refresh();
    getch();
}