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

#define TEXT_CENTERING 25

int getOffsetLine(Grid *grid)
{
    return LINES / 2 - grid->height;
}

int getOffsetCol(Grid *grid)
{
    return COLS / 2 - grid->width * 2 - TEXT_CENTERING;
}

int getTextOffsetCol(Grid *grid)
{
    return COLS / 2 + grid->width * 2 - TEXT_CENTERING + 5;
}

/**
 * Auteurs : Duc, Kevin et Zeid
 * Description : Affiche la grille de jeu
 * Paramètres :
 * - nextPlayer : Le prochain joueur qui doit jouer
 * - statusMessage : Le message de statut
 * - grid : La grille de jeu
 * - row : Position actuelle du curseur (ligne)
 * - column : Position actuelle du curseur (colonne)
 */
void displayGrid(Grid *grid, char nextPlayer, wchar_t *statusMessage, int row, int column)
{
    clear(); // Efface tout pour un nouvel affichage

    int offsetLine = getOffsetLine(grid), offsetCol = getOffsetCol(grid), textOffsetCol = getTextOffsetCol(grid);

    // Affichage du contenu de la grille
    for (int i = 0; i < grid->height; i++)
    {
        for (int j = 0; j < grid->width; j++)
        {
            // Curseur sur la position actuelle
            if (i == row && j == column)
            {
                attron(A_REVERSE); // Surligne la case courante
                mvprintw(offsetLine + i * 2 + 1, offsetCol + j * 4 + 2, "%c", grid->rows[i][j]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(offsetLine + i * 2 + 1, offsetCol + j * 4 + 2, "%c", grid->rows[i][j]);
            }
        }
    }

    // Affichage de la première ligne horizontale
    for (int j = 0; j < grid->width; j++)
    {
        mvprintw(offsetLine + 0, offsetCol + j * 4, "+");
        for (int i = 1; i < 4; i++)
        {
            mvprintw(offsetLine + 0, offsetCol + j * 4 + i, "-");
        }
    }
    mvprintw(offsetLine + 0, offsetCol + grid->width * 4, "+");

    // Affichage des lignes autres lignes
    for (int i = 0; i < grid->height; i++)
    {
        // Afficher les délimitations des cases
        for (int j = 0; j < grid->width; j++)
        {
            mvprintw(offsetLine + i * 2 + 1, offsetCol + j * 4, "|");
            mvprintw(offsetLine + i * 2 + 2, offsetCol + j * 4, "+");
            for (int k = 1; k < 4; k++)
            {
                mvprintw(offsetLine + i * 2 + 2, offsetCol + j * 4 + k, "-");
            }
        }
        // Afficher la délimitation de la dernière colonne
        mvprintw(offsetLine + i * 2 + 1, offsetCol + grid->width * 4, "|");
        mvprintw(offsetLine + i * 2 + 2, offsetCol + grid->width * 4, "+");
    }

    if (statusMessage != NULL)
    {
        mvprintw(offsetLine + 2, textOffsetCol, "%ls", statusMessage);
    }

    mvprintw(offsetLine + 3, textOffsetCol, "Le joueur %c joue.", nextPlayer);

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
void handleInput(Grid *grid, char nextPlayer, wchar_t *statusMessage, int *row, int *column, int *function)
{
    int offsetLine = getOffsetLine(grid), textOffsetCol = getTextOffsetCol(grid);

    int key;
    *row = 0;
    *column = 0;

    int selecting = 1;

    while (selecting)
    {
        if (!isMoveAllowed(grid, *row, *column, nextPlayer))
        {
            statusMessage = L"Ce cube appartient à un autre joueur. Vous ne pouvez pas le déplacer.";
        }
        else
        {
            statusMessage = NULL;
        }

        // Affiche la grille + le curseur
        displayGrid(grid, nextPlayer, statusMessage, *row, *column);

        mvprintw(offsetLine + 5, textOffsetCol, "%ls", L"Utilisez les flèches pour naviguer.");
        mvprintw(offsetLine + 6, textOffsetCol, "%ls", L"Appuyez sur Entrer pour sélectionner une case.");
        mvprintw(offsetLine + 7, textOffsetCol, "Echap pour quitter");
        refresh();

        // touches utili
        key = getch();

        switch (key)
        {
        case KEY_UP: // Flèche haut
            if (*row > 0)
            {
                if (*column > 0 && *column < grid->width - 1)
                {
                    *row = 0;
                }
                else
                {
                    (*row)--;
                }
            }
            else
            {
                *row = grid->width - 1;
            }
            break;
        case KEY_DOWN: // Flèche bas
            if (*row < grid->height - 1)
            {
                if (*column > 0 && *column < grid->width - 1)
                {
                    *row = grid->height - 1;
                }
                else
                {
                    (*row)++;
                }
            }
            else
            {
                *row = 0;
            }
            break;
        case KEY_LEFT: // Flèche gauche
            if (*column > 0)
            {
                if (*row > 0 && *row < grid->height - 1)
                {
                    *column = 0;
                }
                else
                {
                    (*column)--;
                }
            }
            else
            {
                *column = grid->height - 1;
            }
            break;
        case KEY_RIGHT: // Flèche droite
            if (*column < grid->width - 1)
            {
                if (*row > 0 && *row < grid->height - 1)
                {
                    *column = grid->width - 1;
                }
                else
                {
                    (*column)++;
                }
            }
            else
            {
                *column = 0;
            }
            break;
        case '\n': // Entrée
            // Si un message de statut est affiché, alors on bloque la sélection
            if (statusMessage != NULL)
            {
                break;
            }

            *function = -1;
            do
            {
                displayGrid(grid, nextPlayer, statusMessage, *row, *column);
                statusMessage = NULL;
                key = getch();
                switch (key)
                {
                case KEY_RIGHT:
                    *function = FUNCTION_SHIFT_ROW_RIGHT;
                    break;
                case KEY_LEFT:
                    *function = FUNCTION_SHIFT_ROW_LEFT;
                    break;
                case KEY_DOWN:
                    *function = FUNCTION_SHIFT_COLUMN_DOWN;
                    break;
                case KEY_UP:
                    *function = FUNCTION_SHIFT_COLUMN_UP;
                    break;
                case 27: // Echap pour quitter
                    *function = FUNCTION_QUIT_GAME;
                    break;
                }
                mvprintw(offsetLine + 5, textOffsetCol, "Flèche droite : Déplacer la ligne vers la droite");
                mvprintw(offsetLine + 6, textOffsetCol, "Flèche gauche : Déplacer la ligne vers la gauche");
                mvprintw(offsetLine + 7, textOffsetCol, "Flèche bas : Déplacer la colonne vers le bas");
                mvprintw(offsetLine + 8, textOffsetCol, "Flèche haut : Déplacer la colonne vers le haut");
                mvprintw(offsetLine + 9, textOffsetCol, "Echap pour quitter");
                refresh();
            } while (statusMessage != NULL);

            selecting = 0;
            break;
        case 27: // Echap pour quitter
            *function = FUNCTION_QUIT_GAME;
            selecting = 0;
            break;
        default:
            break;
    
        }
    }
}
