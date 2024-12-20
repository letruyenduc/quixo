#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 * Description : Structure qui contient la grille de jeu
 * Auteur : Kevin Carletto
 * Champs : width contient la largeur de la grille, height la hauteur, et rows les lignes qui elle-mêmes contiennent les cases.
 */
typedef struct
{
    int width;
    int height;
    char **rows;
} Grid;

/**
 * Description : Structure qui contient les informations d'une sauvegarde
 * Auteur : Kevin Carletto
 * Champs : saveName contient le nom de la sauvegarde, et filePath le chemin du fichier de sauvegarde
 *         saveName est le nom du fichier sans l'extension .txt
 *        filePath est le chemin complet du fichier
 */
typedef struct
{
    char *saveName;
    char *filePath;
} Save;

#endif // STRUCTURES_H