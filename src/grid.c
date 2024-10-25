#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SHIFT_STATUS_OK 0
#define SHIFT_STATUS_OTHER_PLAYER 1

/**
 * Description : Structure qui contient la grille de jeu
 * Auteur : Kevin Carletto
 * Champs : width contient la largeur de la grille, height la hauteur, et lines les lignes qui elle-mêmes contiennent les cases.
 */
typedef struct
{
    int width;
    int height;
    char **lines;
} Grid;

/**
 * Description : Fonction de création d'une grille de jeu
 * Auteur : Kevin Carletto
 * Paramètres : width est la largeur de la grille, height la hauteur
 * Traitement : On commence par créer un tableau qui contiendra les lignes de la grille.
 * On crée ensuite chaque ligne et on les remplie de cases vides.
 * Enfin, on crée une structure qui contiendra la taille (largeur et hauteur) et le contenu de la grille.
 * Retour : On retourne une structure contenant la grille de jeu.
 */
Grid *createGrid(int width, int height)
{
    char **gridLines = malloc(sizeof(char *) * height);
    for (int i = 0; i < height; i++)
    {
        gridLines[i] = malloc(sizeof(char) * width);
        memset(gridLines[i], ' ', width);
    }

    Grid *grid = malloc(sizeof(Grid));
    grid->width = width;
    grid->height = height;
    grid->lines = gridLines;

    return grid;
}

/**
 * Description : Fonction pour vérifier si un déplacement est autorisé pour un jouuer
 * Auteur : Kevin Carletto
 * Paramètres : grid est la structure de la grille de jeu, row l'indice de la ligne à déplacer, column l'indice de la colonne à déplacer, et player le caractère du joueur qui joue.
 * Traitement : On récupère le cube modifié. On retourne 1 si le cube est vide ou si il appartient au joueur, 0 sinon.
 * Retour : Une valeur booléenne (1 = autorisé, 0 = interdit)
 */

int isMoveAllowed(Grid *grid, int row, int column, char player)
{
    assert(row >= 0 && row < grid->height && column >= 0 && column < grid->width);
    char movingCube = grid->lines[row][column];
    return movingCube == ' ' || movingCube == player;
}

/**
 * Description : Permet de déplacer une ligne vers la droite
 * Auteur : Kevin Carletto
 * Paramètres : grid est la structure de la grille de jeu, row l'indice de la ligne à déplacer, et player le caractère du joueur qui joue.
 * Traitement : On vérifie que le déplacement de la dernière case de la ligne est autorisé, sinon on retourne un code d'erreur.
 * On parcours ensuite la ligne en partant de la fin en déplaçant le contenu de chaque case vers la suivante.
 * Enfin, on définit la première case de la ligne avec le caractère du joueur qui joue.
 * Retour : Le code de statut de réussite (1 = le joueur n'a pas le droit de déplacer ce cube, 0 = Tout s'est bien passé)
 */
int shiftRowRight(Grid *grid, int row, char player)
{
    assert(row >= 0 && row < grid->height);

    if (!isMoveAllowed(grid, row, grid->width - 1, player))
    {
        return SHIFT_STATUS_OTHER_PLAYER;
    }

    for (int i = grid->width - 1; i > 0; i--)
    {
        grid->lines[row][i] = grid->lines[row][i - 1];
    }
    grid->lines[row][0] = player;

    return SHIFT_STATUS_OK;
}

/**
 * Description : Permet de déplacer une ligne vers la gauche
 * Auteur : Kevin Carletto
 * Paramètres : grid est la structure de la grille de jeu, row l'indice de la ligne à déplacer, et player le caractère du joueur qui joue.
 * Traitement : On vérifie que le déplacement de la première case de la ligne est autorisé, sinon on retourne un code d'erreur.
 * On parcours ensuite la ligne en partant du début en déplaçant le contenu de chaque case vers la précédente.
 * Enfin, on définit la dernière case de la ligne avec le caractère du joueur qui joue.
 * Retour : Le code de statut de réussite (1 = le joueur n'a pas le droit de déplacer ce cube, 0 = Tout s'est bien passé)
 */
int shiftRowLeft(Grid *grid, int row, char player)
{
    assert(row >= 0 && row < grid->height);

    if (!isMoveAllowed(grid, row, 0, player))
    {
        return SHIFT_STATUS_OTHER_PLAYER;
    }

    for (int i = 1; i < grid->width; i++)
    {
        grid->lines[row][i - 1] = grid->lines[row][i];
    }
    grid->lines[row][grid->width - 1] = player;

    return SHIFT_STATUS_OK;
}

/**
 * Description : Permet de déplacer une colonne vers le bas
 * Auteur : Kevin Carletto
 * Paramètres : grid est la structure de la grille de jeu, column l'indice de la colonne à déplacer, et player le caractère du joueur qui joue.
 * Traitement : On vérifie que le déplacement de la dernière case de la colonne est autorisé, sinon on retourne un code d'erreur.
 * On parcours ensuite la colonne en partant de la fin en déplaçant le contenu de chaque case vers la suivante.
 * Enfin, on définit la première case de la colonne avec le caractère du joueur qui joue.
 * Retour : Le code de statut de réussite (1 = le joueur n'a pas le droit de déplacer ce cube, 0 = Tout s'est bien passé)
 */
int shiftColumnDown(Grid *grid, int column, char player)
{
    assert(column >= 0 && column < grid->width);

    if (!isMoveAllowed(grid, column, grid->height-1, player))
    {
        return SHIFT_STATUS_OTHER_PLAYER;
    }

    for (int i = grid->height - 1; i > 0; i--)
    {
        grid->lines[i][column] = grid->lines[i - 1][column];
    }
    grid->lines[0][column] = player;

    return SHIFT_STATUS_OK;
}

/**
 * Description : Permet de déplacer une colonne vers le haut
 * Auteur : Kevin Carletto
 * Paramètres : grid est la structure de la grille de jeu, column l'indice de la colonne à déplacer, et player le caractère du joueur qui joue.
 * Traitement : On vérifie que le déplacement de la première case de la colonne est autorisé, sinon on retourne un code d'erreur.
 * On parcours ensuite la colonne en partant du début en déplaçant le contenu de chaque case vers la précédente.
 * Enfin, on définit la dernière case de la colonne avec le caractère du joueur qui joue.
 * Retour : Le code de statut de réussite (1 = le joueur n'a pas le droit de déplacer ce cube, 0 = Tout s'est bien passé)
 */
int shiftColumnUp(Grid *grid, int column, char player)
{
    assert(column >= 0 && column < grid->width);

    if (!isMoveAllowed(grid, column, 0, player))
    {
        return SHIFT_STATUS_OTHER_PLAYER;
    }

    for (int i = 1; i < grid->height; i++)
    {
        grid->lines[i - 1][column] = grid->lines[i][column];
    }
    grid->lines[grid->height - 1][column] = player;

    return SHIFT_STATUS_OK;
}

/**
 * Description : Permet de libérer la mémoire utilisée par la grille de jeu
 * Auteur : Kevin Carletto
 * Paramètres : grid est la structure de la grille de jeu.
 * Traitement : On libère chaque ligne de la grille, puis le tableau de lignes, et enfin la structure elle-même.
 * Penser à ne plus utiliser le pointeur après cette opération, de préférence le définir à NULL pour en être certain.
 */
void freeGrid(Grid *grid)
{
    for (int i = 0; i < grid->height; i++)
    {
        free(grid->lines[i]);
    }
    free(grid->lines);
    free(grid);
}

/**
 * Description : Fonction temporaire qui permet d'afficher la grille de jeu. À remplacer par celle utilisant ncurses
 * Auteur : Kevin Carletto
 * Paramètres : grid est la structure de la grille de jeu.
 * Traitement : On commence par afficher une délimitation au dessus de la grille
 * On parcours chaque ligne de la grille
 *     On affiche une délimitation sur la gauche de la ligne
 *     On affiche chaque case de la ligne
 *     On affiche une délimitation sur la droite de la ligne
 * On termine par afficher une délimitation en bas de la grille
 */
void printGrid(Grid *grid)
{
    for (int j = -2; j < grid->width; j++)
    {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < grid->height; i++)
    {
        printf("|");
        for (int j = 0; j < grid->width; j++)
        {
            printf("%c", grid->lines[i][j]);
        }
        printf("|\n");
    }
    for (int j = 0; j < grid->width + 2; j++)
    {
        printf("-");
    }
    printf("\n");
}