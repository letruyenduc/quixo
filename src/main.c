#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "menu.h"
#include "utils.h"
#include "constants.h"

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#include <windows.h>
#else
#include <ncurses.h>
#endif

/**
 * Description : Initialise ncurses
 * Auteur : Valentin et Kevin
 * Traitement : On initialise l'affichage ncurses et on définit quelques propriétés
 */
void initNcurses()
{
    initscr();

    cbreak();             // Permettre l'entrée de caractères un par un
    noecho();             // Désactiver l'affichage des caractères tapés
    curs_set(0);          // Masque le curseur
    keypad(stdscr, TRUE); // Activer les touches fléchées
    start_color();        // Activer les couleurs
    init_pair(COLOR_CYAN_ON_BLACK, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
    ESCDELAY = 25;        // Réduire le délai d'attente après un appui sur la touche ESC
}

/**
 * Description : Programme principal
 * Traitement :
 * - On initialise le générateur de nombre aléatoires.
 * - On initialise la fenêtre ncurses
 * - On affiche le menu principal.
 * - À l'arrêt, on termine la fenêtre ncurses
 */
int main()
{
    srand(time(NULL));
    initNcurses();
    setlocale(LC_ALL, ""); // Permettre les caractères spéciaux avec ncurses sur Windows
    displayMenu();
    endwin();
    return 0;
}