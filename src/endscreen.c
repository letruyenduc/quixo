#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include "grid.h"
#include "endscreen.h"
#include "wincond.h"
/*
* Auteur : Duc
* Description : Affiche l'écran de fin de partie
* Paramètres :
* - grid : La grille de jeu
* - winner : Le joueur gagnant
* Retour : 0 qui indique la fin du jeu, on peut donc quitter le programme
*/
void displayEndScreen(Grid *grid, int winner)
{
    char key;
    initscr();
    clear();
    if (winner == winCond(grid)) {
        mvprintw(LINES / 2, (COLS - strlen("Le joueur 1 gagne!")) / 2, "Le joueur %c gagne!", winCond(grid));
    } else if (winner == 2) {
        mvprintw(LINES / 2, (COLS - strlen("Le joueur 2 gagne!")) / 2, "Le joueur %c gagne!", winCond(grid));
    } else {
        mvprintw(LINES / 2, (COLS - strlen("Égalité!")) / 2, "Égalité!");
    }
    mvprintw(LINES / 2 + 2, (COLS - strlen("Appuyez sur n'importe quelle touche pour quitter")) / 2, "Appuyez sur n'importe quelle touche pour quitter");
    refresh();
    getch();

}