#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ncurses.h>
#include "grid.h"

void initGrid(){
    initscr();
    for (int i = 0; i < 5; i++)
    {
        for (int i = 0; i < 5; i++)
    {
        printw(" ");
        printw("-");
    }
    printw("\n");
    for (int i = 0; i < 6; i++)
    {
        printw("|");
        printw(" ");        
    }
    printw("\n");
    }
    for (int i = 0; i < 5; i++)
    {
        printw(" ");
        printw("-");
    }
    refresh();
    getch();
    endwin();  
}

void displayGrid(Grid *grid){
    for (int i = 0; i < grid->height; i++)
    {
        for (int j = 0; j < grid->width; j++)
        {
            mvaddch(i, j, grid->rows[i][j]);
        }
        printf("\n");
    }
}

void handleInput(int *row, int *column, int *function, char *player) {
    // Initialisation de ncurses
    initscr();
    cbreak(); // Désactive le buffering, entre les caractères immédiatement
    noecho(); // Désactive l'écho des touches
    keypad(stdscr, TRUE); // Permet d'utiliser les touches spéciales comme les flèches

    // Affichage des messages dans la fenêtre
    clear();
    mvprintw(0, 0, "Ligne : ");
    refresh();
    scanw("%d", row); // Utilisation de scanw() pour obtenir une entrée au lieu de scanf

    clear();
    mvprintw(1, 0, "Colonne : ");
    refresh();
    scanw("%d", column);

    clear();
    mvprintw(2, 0, "\n0=shiftRowRight\n1=shiftRowLeft\n2=shiftColumnDown\n3=shiftColumnUp\nFonction : ");
    refresh();
    scanw("%d", function);

    clear();
    mvprintw(3, 0, "Joueur : ");
    refresh();
    *player = (char) getch(); // Utilisation de getch() pour capturer une seule touche de clavier

    // Nettoyage et fin de ncurses
    endwin();
}