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


/**
 * Auteur : Kevin
 * Description : Récupère le décalage de la ligne pour centrer la grille
 * Paramètres :
 * - grid : La grille de jeu
 * Retour : Le décalage de la ligne
 * Traitement :
 * - On récupère la hauteur de la grille
 * - On calcule le décalage en fonction de la hauteur de la grille
 * - On retourne le décalage
 */
int getOffsetLine(Grid *grid)
{
    return LINES / 2 - grid->height;
}

/**
 * Auteur : Kevin
 * Description : Récupère le décalage de la colonne pour positionner la grille
 * Paramètres :
 * - grid : La grille de jeu
 * Retour : Le décalage de la colonne
 * Traitement :
 * - On récupère la largeur de la grille
 * - On calcule le décalage en fonction de la largeur de la grille
 * - On retourne le décalage
 */
int getOffsetCol(Grid *grid)
{
    return COLS / 2 - grid->width * 2 - TEXT_CENTERING;
}


/**
 * Auteur : Kevin
 * Description : Récupère le décalage de la colonne pour positionner le texte
 * Paramètres :
 * - grid : La grille de jeu
 * Retour : Le décalage de la colonne
 * Traitement :
 * - On récupère la largeur de la grille
 * - On calcule le décalage en fonction de la largeur de la grille
 * - On retourne le décalage
 */
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
 * - selectingFunction : Valeur booléenne définissant s'il s'agit de la sélection du mouvement de déplacement
 */
void displayGrid(Grid *grid, int row, int column, int selectingFunction)
{
    clear(); // Efface tout pour un nouvel affichage

    int offsetLine = getOffsetLine(grid), offsetCol = getOffsetCol(grid);

    // Affichage du contenu de la grille
    for (int i = 0; i < grid->height; i++)
    {
        for (int j = 0; j < grid->width; j++)
        {
            Player *player = grid->rows[i][j];
            int isSelected = i == row && j == column;
            if (isSelected)
                attron(A_REVERSE); // Surligne la case courante

            if (player == NULL)
            {
                mvprintw(offsetLine + i * 2 + 1, offsetCol + j * 4 + 2, " ");
            }
            else
            {
                // showDebugMessage("Player %c with color %d at %d, %d", player->playerSymbol, player->colorIndex, i, j);
                attron(COLOR_PAIR(player->colorIndex));
                // Curseur sur la position actuelle
                if (i == row && j == column)
                {
                    attron(A_REVERSE); // Surligne la case courante
                    mvprintw(offsetLine + i * 2 + 1, offsetCol + j * 4 + 2, "%c", selectingFunction ? ' ' : player->playerSymbol);
                    attroff(A_REVERSE);
                }
                else
                {
                    mvprintw(offsetLine + i * 2 + 1, offsetCol + j * 4 + 2, "%c", player->playerSymbol);
                }
                attroff(COLOR_PAIR(player->colorIndex));
            }
            if (isSelected)
                attroff(A_REVERSE);
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
}

/*
 * Auteurs : Duc et Kevin
 * Description : Affiche la grille de jeu et le message de statut
 * Paramètres :
 * - grid : La grille de jeu
 * - nextPlayer : Le prochain joueur qui doit jouer
 * - statusMessage : Le message de statut
 * - row : Position actuelle du curseur (ligne)
 * - column : Position actuelle du curseur (colonne)
 * - selectingFunction : Valeur booléenne définissant s'il s'agit de la sélection du mouvement de déplacement
 */
void displayGridAndStatus(Grid *grid, Player *nextPlayer, wchar_t *statusMessage, int row, int column, int selectingFunction)
{
    int offsetLine = getOffsetLine(grid), textOffsetCol = getTextOffsetCol(grid);

    displayGrid(grid, row, column, selectingFunction);

    if (statusMessage != NULL)
    {
        mvprintw(offsetLine + 2, textOffsetCol, "%ls", statusMessage);
    }

    attron(COLOR_PAIR(nextPlayer->colorIndex));
    mvprintw(offsetLine + 3, textOffsetCol, "%s (%c) joue.", nextPlayer->playerName, nextPlayer->playerSymbol);
    attroff(COLOR_PAIR(nextPlayer->colorIndex));

    refresh();
}
/**
 * Auteurs : Duc et Kevin
 * Description : Permet à l'utilisateur de choisir une action à effectuer en fonction de la case sélectionnée
 * Paramètres :
 * - grid : La grille de jeu
 * - nextPlayer : Le prochain joueur qui doit jouer
 * - offsetLine : Décalage de la ligne
 * - textOffsetCol : Décalage de la colonne pour le texte
 * - row : Ligne de la grille de la case sélectionnée
 * - column : Colonne de la grille de la case sélectionnée
 * - statusMessage : Le message de statut
 * Retour (par paramètres pointeurs) :
 * - statusMessage : Le message de statut
 * - function : L'action choisie par l'utilisateur
 * Retour (par instruction return) : 0 si l'utilisateur a choisi une action, 1 sinon
 */
int handleFunctionSelection(Grid *grid, Player *nextPlayer, int offsetLine, int textOffsetCol, int row, int column, wchar_t **statusMessage, int *function)
{
    *function = -1;
    do
    {
        displayGridAndStatus(grid, nextPlayer, *statusMessage, row, column, 1);
        int textLine = 5;
        if (column != 0)
            mvprintw(offsetLine + textLine++, textOffsetCol, "%ls", L"Flèche droite : Réinsérer par la gauche et pousser vers droite");
        if (column != grid->width - 1)
            mvprintw(offsetLine + textLine++, textOffsetCol, "%ls", L"Flèche gauche : Réinsérer par la droite et pousser vers la gauche");
        if (row != 0)
            mvprintw(offsetLine + textLine++, textOffsetCol, "%ls", L"Flèche bas : Réinsérer par le haut et pousser vers le bas");
        if (row != grid->height - 1)
            mvprintw(offsetLine + textLine++, textOffsetCol, "%ls", L"Flèche haut : Réinsérer par le bas et pousser vers le haut");
        mvprintw(offsetLine + textLine, textOffsetCol, "%ls", L"Echap pour revenir à la sélection de la case");
        *statusMessage = NULL;
        int key = getch();
        switch (key)
        {
        case KEY_RIGHT:
            if (column != 0)
                *function = FUNCTION_SHIFT_ROW_RIGHT;
            else
                *statusMessage = L"Ce déplacement est interdit";
            break;
        case KEY_LEFT:
            if (column != grid->width - 1)
                *function = FUNCTION_SHIFT_ROW_LEFT;
            else
                *statusMessage = L"Ce déplacement est interdit";
            break;
        case KEY_DOWN:
            if (row != 0)
                *function = FUNCTION_SHIFT_COLUMN_DOWN;
            else
                *statusMessage = L"Ce déplacement est interdit";
            break;
        case KEY_UP:
            if (row != grid->height - 1)
                *function = FUNCTION_SHIFT_COLUMN_UP;
            else
                *statusMessage = L"Ce déplacement est interdit";
            break;
        case 27: // Echap pour revenir à la sélection de la case
            return 1;
        }
        refresh();
    } while (*function < 0 || *statusMessage != NULL);
    return 0;
}

/**
 * Auteurs : Zeid et Kevin
 * Description : Permet à l'utilisateur de naviguer avec les flèches et d'effectuer une sélection avec la touche Entrée
 * Et de choisir une action à effectuer avec les flèches directionnelles
 * Paramètres :
 * - grid : La grille de jeu
 * - nextPlayer : Le prochain joueur qui doit jouer
 * - statusMessage : Le message de statut
 * Retours (par paramètres pointeurs) :
 * - statusMessage : Le message de statut
 * - row : Position de la ligne sélectionnée
 * - column : Position de la colonne sélectionnée
 * - function : Action choisie par l'utilisateur
 * Retour (par instruction return) : 0 si l'utilisateur a choisi une action, 1 sinon
 * Traitement : On affiche les instructions, on récupère l'entrée utilisateur et on effectue les actions en fonction de la touche appuyée :
 * - Flèches pour naviguer
 * - Entrée pour sélectionner une case puis sélectionner un déplacement à effectuer
 * - Echap pour quitter
 */
int handleGridPointSelection(Grid *grid, Player *nextPlayer, wchar_t **statusMessage, int *row, int *column, int *function)
{
    int offsetLine = getOffsetLine(grid), textOffsetCol = getTextOffsetCol(grid);

    mvprintw(offsetLine + 5, textOffsetCol, "%ls", L"Utilisez les flèches pour naviguer.");
    mvprintw(offsetLine + 6, textOffsetCol, "%ls", L"Appuyez sur Entrer pour sélectionner une case.");
    mvprintw(offsetLine + 7, textOffsetCol, "Echap pour afficher le menu de jeu.");
    refresh();

    int key = getch();

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
            *row = grid->height - 1;
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
            *column = grid->width - 1;
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
        if (*statusMessage != NULL)
        {
            break;
        }

        return handleFunctionSelection(grid, nextPlayer, offsetLine, textOffsetCol, *row, *column, statusMessage, function);
    case 27: // Echap pour quitter
        *function = FUNCTION_QUIT_GAME;
        return 0;
        break;
    }
    return 1;
}

/**
 * Auteurs : Kevin et Zeid
 * Description : Permet à l'utilisateur de naviguer avec les flèches et d'effectuer une sélection avec la touche Entrée
 * Et de choisir une action à effectuer avec les flèches directionnelles
 * Paramètres :
 * - grid : La grille de jeu
 * - nextPlayer : Le prochain joueur qui doit jouer
 * - statusMessage : Le message de statut
 * Retours (par paramètres pointeurs) :
 * - row : Position de la ligne sélectionnée
 * - column : Position de la colonne sélectionnée
 * - function : Action choisie par l'utilisateur
 * Traitement : On boucle tant qu'une action n'a pas été sélectionnée.
 * - On affiche la grille et le curseur.
 * - On récupère l'entrée utilisateur et on effectue les actions en fonction de la touche appuyée.
 */
void handleInput(Grid *grid, Player *nextPlayer, wchar_t *statusMessage, int *row, int *column, int *function)
{
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
        displayGridAndStatus(grid, nextPlayer, statusMessage, *row, *column, 0);

        selecting = handleGridPointSelection(grid, nextPlayer, &statusMessage, row, column, function);
    }
}

/*
 * Auteur : Duc
 * Description : Affiche l'écran de fin de partie
 * Paramètres :
 * - grid : La grille de jeu
 * - winner : Le joueur gagnant
 */
void displayEndScreen(Grid *grid, Player *winner, Player *colorIndex)
{
    displayGrid(grid, -1, -1, 0);
    mvprintw(getOffsetLine(grid) + 4, getTextOffsetCol(grid), "%s (%c) gagne !", winner->playerName, winner->playerSymbol, winner-> colorIndex);
    mvprintw(getOffsetLine(grid) + 6, getTextOffsetCol(grid), "Appuyez sur n'importe quelle touche pour quitter");
    refresh();
    getch();
}
