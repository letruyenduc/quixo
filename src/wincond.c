#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
/*
 * Auteur : Duc et Kevin
 * Description : Fonction qui vérifie si un joueur a gagné en alignant 5 cubes horizontalement
 * Paramètres :
 * - grid : La grille de jeu
 * - player : Le joueur à vérifier
 * Retour : 1 si le joueur a gagné, 0 sinon
 * Traitement :
 * - On parcourt chaque ligne de la grille
 * - On vérifie si chaque cube de la ligne est égal au joueur
 * - Si on a parcouru toute la ligne, on retourne 1, sinon on retourne 0
 */
int winCondHorizontal(Grid *grid, Player *player)
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
 * Auteur : Duc et Kevin
 * Description : Fonction qui vérifie si un joueur a gagné en alignant 5 cubes verticalement
 * Paramètres :
 * - grid : La grille de jeu
 * - player : Le joueur à vérifier
 * Retour : 1 si le joueur a gagné, 0 sinon
 * Traitement :
 * - On parcourt chaque colonne de la grille
 * - On vérifie si chaque cube de la colonne est égal au joueur
 * - Si on a parcouru toute la colonne, on retourne 1, sinon on retourne 0
 */
int winCondVertical(Grid *grid, Player *player)
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
 * Auteur : Duc et Kevin
 * Description : Fonction qui vérifie si un joueur a gagné en alignant 5 cubes diagonalement
 * Paramètres :
 * - grid : La grille de jeu
 * - player : Le joueur à vérifier
 * Retour : 1 si le joueur a gagné, 0 sinon
 * Traitement :
 * - On vérifie si la grille est un carré
 * - On parcourt la diagonale de gauche à droite
 * - On vérifie si chaque cube de la diagonale est égal au joueur
 * - Si on a parcouru toute la diagonale, on retourne 1, sinon on continue
 * - On parcourt la diagonale de droite à gauche
 * - On vérifie si chaque cube de la diagonale est égal au joueur
 * - Si on a parcouru toute la diagonale, on retourne 1, sinon on retourne 0
 */
int winCondDiagonal(Grid *grid, Player *player)
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

/**
 * Auteur : Duc et Kevin
 * Description : Fonction qui vérifie si un joueur a gagné
 * Paramètres :
 * - grid : La grille de jeu
 * - player : Le joueur à vérifier
 * Retour : 1 si le joueur a gagné, 0 sinon
 * Traitement : On vérifie si le joueur a gagné en alignant 5 cubes horizontalement, verticalement ou diagonalement
 */
int winCondPlayer(Grid *grid, Player *player)
{
    return winCondDiagonal(grid, player) || winCondHorizontal(grid, player) || winCondVertical(grid, player);
}

/*
 * Auteur : Duc
 * Description : Fonction qui vérifie si un joueur a gagné
 * Paramètres :
 * - grid : La grille de jeu
 * - playerList : La liste des joueurs
 * - playerCount : Le nombre de joueurs
 * Retour : Le joueur gagnant, ou NULL si aucun joueur n'a gagné
 * Traitement :
 * - On parcourt chaque joueur du plus ancien à avoir joué au plus récent
 * - On vérifie si le joueur a gagné
 * - Si un joueur a gagné, on retourne ce joueur
 * - Sinon on retourne NULL
 */
Player *winCond(Grid *grid, Player *playerList[], int playerCount)
{
    for (int i = 0; i < playerCount; i++)
    {
        if (winCondPlayer(grid, playerList[i]))
        {
            return playerList[i];
        }
    }
    return NULL;
}
