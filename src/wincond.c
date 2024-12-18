#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
/*
 * Auteur : Duc
 * Description : Fonction qui vérifie si un joueur a gagné en alignant 5 cubes horizontalement
 * Paramètres : La grille de jeu
 * Retour : Le joueur gagnant
 */
int winCondHorizontal(Grid *grid, char player)
{
    for (int i = 0; i < grid->height; i++)
    {
        int j = 0;
        while (j < grid->width && grid->rows[i][j] == player)
        {
            j++;
        }
        if (j == grid->width)
        {
            return 1;
        }
    }
    return 0;
}

/*
 * Auteur : Duc
 * Description : Fonction qui vérifie si un joueur a gagné en alignant 5 cubes verticalement
 * Paramètres : La grille de jeu
 * Retour : Le joueur gagnant
 */
int winCondVertical(Grid *grid, char player)
{

    for (int i = 0; i < grid->width; i++)
    {
        int j = 0;
        while (j < grid->height && grid->rows[j][i] == player)
            j++;
        if (j == grid->height)
        {
            return 1;
        }
    }
    return 0;
}

/*
 * Auteur : Duc
 * Description : Fonction qui vérifie si un joueur a gagné en alignant 5 cubes diagonalement
 * Paramètres : La grille de jeu
 * Retour : Le joueur gagnant
 */
int winCondDiagonal(Grid *grid, char player)
{
    if (grid->width != grid->height)
    {
        return 0;
    }
    int j = 0;
    while (j < grid->height && grid->rows[j][j] == player)
        j++;
    if (j == grid->height)
    {
        return 1;
    }
    j = 0;
    while (j < grid->height && grid->rows[j][grid->height - j - 1] == player)
        j++;
    if (j == grid->height)
    {
        return 1;
    }
    return 0;
}

int winCondplayer(Grid *grid, char player)
{
    return winCondDiagonal(grid, player) || winCondHorizontal(grid, player) || winCondVertical(grid, player);
}
/*
 * Auteur : Duc
 * Description : Fonction qui vérifie si un joueur a gagné
 * Paramètres : La grille de jeu
 * Retour : Le joueur gagnant
 */
char winCond(Grid *grid, char *playerList, int playerCount)
{
    for (int i = playerCount - 1; i >= 0; i--)
    {
        if (winCondplayer(grid, playerList[i]))
        {
            return playerList[i];
        }
    }
    return ' ';
}
