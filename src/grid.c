#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "constants.h"
#include "structures.h"

/**
 * Description : Fonction de création d'une grille de jeu
 * Auteur : Kevin Carletto
 * Paramètres :
 * - width : La largeur de la grille
 * - height : La hauteur de la grille
 * Retour : On retourne une structure contenant la grille de jeu.
 * Traitement :
 * - On commence par créer un tableau qui contiendra les lignes de la grille.
 * - On crée ensuite chaque ligne et on les remplie de cases vides.
 * - Enfin, on crée une structure qui contiendra la taille (largeur et hauteur) et le contenu de la grille.
 */
Grid *createGrid(int width, int height)
{
    Player ***gridLines = malloc(sizeof(Player **) * height);
    for (int i = 0; i < height; i++)
    {
        gridLines[i] = malloc(sizeof(Player *) * width);
        for (int j = 0; j < width; j++)
        {
            gridLines[i][j] = NULL;
        }
    }

    Grid *grid = malloc(sizeof(Grid));
    grid->width = width;
    grid->height = height;
    grid->rows = gridLines;

    return grid;
}

/**
 * Description : Fonction pour vérifier si un déplacement est autorisé pour un jouuer
 * Auteur : Kevin Carletto
 * Paramètres :
 * - grid : La structure de la grille de jeu
 * - row : L'indice de la ligne du cube à déplacer
 * - column : L'indice de la colonne du cube à déplacer
 * - player : Un pointeur vers le joueur qui joue.
 * Retour : Une valeur booléenne (1 = autorisé, 0 = interdit)
 * Traitement : On récupère le cube modifié. On retourne 1 si le cube est vide ou si il appartient au joueur, 0 sinon.
 */
int isMoveAllowed(Grid *grid, int row, int column, Player *player)
{
    assert(row >= 0 && row < grid->height && column >= 0 && column < grid->width);
    Player *movingCube = grid->rows[row][column];
    return movingCube == NULL || movingCube == player;
}

/**
 * Description : Permet de déplacer une ligne vers la droite
 * Auteur : Kevin Carletto
 * Paramètres :
 * - grid : La structure de la grille de jeu
 * - removedCuberow : L'indice de la ligne du cube à déplacer
 * - removedCubeColumn : L'indice de la colonne du cube à déplacer
 * - player : Un pointeur vers le joueur qui joue.
 * Retour : Le code de statut de réussite
 * Traitement :
 * - On vérifie que le déplacement de la dernière case de la ligne est autorisé, sinon on retourne un code d'erreur.
 * - On parcours ensuite la ligne en partant de la fin en déplaçant le contenu de chaque case vers la suivante.
 * - Enfin, on définit la première case de la ligne avec le caractère du joueur qui joue.
 */
int shiftRowRight(Grid *grid, int removedCuberow, int removedCubecolumn, Player *player)
{
    assert(removedCuberow >= 0 && removedCuberow < grid->height);

    if (!isMoveAllowed(grid, removedCuberow, removedCubecolumn, player))
    {
        return TURN_STATUS_OTHER_PLAYER;
    }

    for (int i = removedCubecolumn; i > 0; i--)
    {
        grid->rows[removedCuberow][i] = grid->rows[removedCuberow][i - 1];
    }
    grid->rows[removedCuberow][0] = player;

    return TURN_STATUS_OK;
}

/**
 * Description : Permet de déplacer une ligne vers la gauche
 * Auteur : Kevin Carletto
 * Paramètres :
 * - grid : La structure de la grille de jeu
 * - removedCuberow : L'indice de la ligne du cube à déplacer
 * - removedCubeColumn : L'indice de la colonne du cube à déplacer
 * - player : Un pointeur vers le joueur qui joue.
 * Retour : Le code de statut de réussite
 * Traitement :
 * - On vérifie que le déplacement de la première case de la ligne est autorisé, sinon on retourne un code d'erreur.
 * - On parcours ensuite la ligne en partant du début en déplaçant le contenu de chaque case vers la précédente.
 * - Enfin, on définit la dernière case de la ligne avec le caractère du joueur qui joue.
 */
int shiftRowLeft(Grid *grid, int removedCuberow, int removedCubeColumn, Player *player)
{
    assert(removedCuberow >= 0 && removedCuberow < grid->height);

    if (!isMoveAllowed(grid, removedCuberow, removedCubeColumn, player))
    {
        return TURN_STATUS_OTHER_PLAYER;
    }

    for (int i = removedCubeColumn + 1; i < grid->width; i++)
    {
        grid->rows[removedCuberow][i - 1] = grid->rows[removedCuberow][i];
    }
    grid->rows[removedCuberow][grid->width - 1] = player;

    return TURN_STATUS_OK;
}

/**
 * Description : Permet de déplacer une colonne vers le bas
 * Auteur : Kevin Carletto
 * Paramètres :
 * - grid : La structure de la grille de jeu
 * - removedCuberow : L'indice de la ligne du cube à déplacer
 * - removedCubeColumn : L'indice de la colonne du cube à déplacer
 * - player : Un pointeur vers le joueur qui joue.
 * Retour : Le code de statut de réussite
 * Traitement :
 * - On vérifie que le déplacement de la dernière case de la colonne est autorisé, sinon on retourne un code d'erreur.
 * - On parcours ensuite la colonne en partant de la fin en déplaçant le contenu de chaque case vers la suivante.
 * - Enfin, on définit la première case de la colonne avec le caractère du joueur qui joue.
 */
int shiftColumnDown(Grid *grid, int removedCuberow, int removedCubeColumn, Player *player)
{
    assert(removedCubeColumn >= 0 && removedCubeColumn < grid->width);

    if (!isMoveAllowed(grid, removedCuberow, removedCubeColumn, player))
    {
        return TURN_STATUS_OTHER_PLAYER;
    }

    for (int i = removedCuberow; i > 0; i--)
    {
        grid->rows[i][removedCubeColumn] = grid->rows[i - 1][removedCubeColumn];
    }
    grid->rows[0][removedCubeColumn] = player;

    return TURN_STATUS_OK;
}

/**
 * Description : Permet de déplacer une colonne vers le haut
 * Auteur : Kevin Carletto
 * Paramètres :
 * - grid : La structure de la grille de jeu
 * - removedCuberow : L'indice de la ligne du cube à déplacer
 * - removedCubeColumn : L'indice de la colonne du cube à déplacer
 * - player : Un pointeur vers le joueur qui joue.
 * Retour : Le code de statut de réussite
 * Traitement :
 * - On vérifie que le déplacement de la première case de la colonne est autorisé, sinon on retourne un code d'erreur.
 * - On parcours ensuite la colonne en partant du début en déplaçant le contenu de chaque case vers la précédente.
 * - Enfin, on définit la dernière case de la colonne avec le caractère du joueur qui joue.
 */
int shiftColumnUp(Grid *grid, int removedCuberow, int removedCubeColumn, Player *player)
{
    assert(removedCubeColumn >= 0 && removedCubeColumn < grid->width);

    if (!isMoveAllowed(grid, removedCuberow, removedCubeColumn, player))
    {
        return TURN_STATUS_OTHER_PLAYER;
    }

    for (int i = removedCuberow + 1; i < grid->height; i++)
    {
        grid->rows[i - 1][removedCubeColumn] = grid->rows[i][removedCubeColumn];
    }
    grid->rows[grid->height - 1][removedCubeColumn] = player;

    return TURN_STATUS_OK;
}

/**
 * Description : Permet de libérer la mémoire utilisée par la grille de jeu
 * Auteur : Kevin Carletto
 * Paramètres :
 * - grid : La grille de jeu
 * Traitement :
 * - On libère chaque ligne de la grille, puis le tableau de lignes, et enfin la structure elle-même.
 * Note: Penser à ne plus utiliser le pointeur après cette opération, de préférence le définir à NULL pour en être certain.
 */
void freeGrid(Grid *grid)
{
    for (int i = 0; i < grid->height; i++)
    {
        free(grid->rows[i]);
    }
    free(grid->rows);
    free(grid);
}