#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "menu.h"
#include "utils.h"

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#include <windows.h>
#else
#include <ncurses.h>
#endif

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
    initscr();
    setlocale(LC_ALL, ""); // Permettre les caractères spéciaux avec ncurses sur Windows
    afficherMenu();
    endwin();
    return 0;
}