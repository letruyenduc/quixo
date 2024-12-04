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
#include "constants.h"

#define OFFSET_LINE 5
#define OFFSET_COL 10

/**
 * Auteurs : Duc et Kevin
 * Description : Affiche la grille de jeu
 * Paramètres : 
 * - nextPlayer : Le prochain joueur qui doit jouer
 * - statusMessage : Le message de statut
 * - grid : La grille de jeu
 * - row : Position actuelle du curseur (ligne)
 * - column : Position actuelle du curseur (colonne)
 */
void displayGrid(Grid *grid, char nextPlayer, wchar_t* statusMessage, int row, int column)
{
    clear(); // Efface tout pour un nouvel affichage

    // Affichage des bordures et contenu de la grille
    for (int i = 0; i < grid->height; i++)
    {
        for (int j = 0; j < grid->width; j++)
        {
            // Curseur sur la position actuelle
            if (i == row && j == column)
            {
                attron(A_REVERSE); // Surligne la case courante
                mvprintw(OFFSET_LINE + i * 2 + 1, OFFSET_COL + j * 2 + 1, "%c", grid->rows[i][j]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(OFFSET_LINE + i * 2 + 1, OFFSET_COL + j * 2 + 1, "%c", grid->rows[i][j]);
            }
        }
    }

    // Affichage des lignes horizontales
    for (int j = 0; j < grid->width; j++)
    {
        mvprintw(OFFSET_LINE + 0, OFFSET_COL + j * 2, "+");
        mvprintw(OFFSET_LINE + 0, OFFSET_COL + j * 2 + 1, "-");
    }
    mvprintw(OFFSET_LINE + 0, OFFSET_COL + grid->width * 2, "+");

    // Affichage des lignes verticales
    for (int i = 0; i < grid->height; i++)
    {
        mvprintw(OFFSET_LINE + i * 2 + 1, OFFSET_COL + 0, "|");
        for (int j = 0; j < grid->width; j++)
        {
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
 * Auteurs : Zeid
 * Description : Permet à l'utilisateur de naviguer avec les flèches et d'effectuer une sélection
 * Paramètres :
 * - grid : La grille de jeu
 * - row : Position de la ligne sélectionnée
 * - column : Position de la colonne sélectionnée
 * - function : Action choisie par l'utilisateur
 */
void handleInput(Grid *grid, char nextPlayer, wchar_t* statusMessage, int *row, int *column, int *function)
{
    int key;
    *row = 0;
    *column = 0;

    while (1)
    {
        // Affiche la grille + le curseur
        displayGrid(grid, nextPlayer, statusMessage, *row, *column);

        mvprintw(OFFSET_LINE + grid->height * 2 + 4, OFFSET_COL, "Utilisez les fleches pour naviguer.");
        mvprintw(OFFSET_LINE + grid->height * 2 + 5, OFFSET_COL, "Appuyez sur Entree pour selectionner une case.");
        refresh(); 

        // touches utili
        key = getch();

        switch (key)
        {
        case KEY_UP: // Flèche haut
            if (*row > 0)
                (*row)--;
            break;
        case KEY_DOWN: // Flèche bas
            if (*row < grid->height - 1)
                (*row)++;
            break;
        case KEY_LEFT: // Flèche gauche
            if (*column > 0)
                (*column)--;
            break;
        case KEY_RIGHT: // Flèche droite
            if (*column < grid->width - 1)
                (*column)++;
            break;
        case '\n': // Entrée
            // Vérification d'autorisation de déplacement de case, modifier statusMessage
            // if () 

            displayGrid(grid, nextPlayer, statusMessage, *row, *column);
            mvprintw(OFFSET_LINE + grid->height * 2 + 4, OFFSET_COL, "0=shiftRowRight, 1=shiftRowLeft, 2=shiftColumnDown, 3=shiftColumnUp, 4=quitter");
            mvprintw(OFFSET_LINE + grid->height * 2 + 5, OFFSET_COL, "%ls", L"Choisissez une fonction (0 à 4) : ");
            refresh();
            scanw("%d", function);
            return; 
        case 27: 
            *function = FUNCTION_QUIT_GAME;
            return;
        default:
            break;
        }

    }
}
