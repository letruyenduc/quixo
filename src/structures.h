#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 * Description : Structure qui contient les informations d'un joueur
 * Auteur : Kevin Carletto
 * Champs :
 * - playerSymbol : Le symbole du joueur
 * - playerName : Le nom du joueur
 * - colorIndex : L'index de la couleur du joueur
 */
typedef struct
{
    char playerSymbol;
    char *playerName;
    int colorIndex;
} Player;

/**
 * Description : Structure qui contient la grille de jeu
 * Auteur : Kevin Carletto
 * Champs :
 * - width : La largeur de la grille
 * - height : La hauteur de la grille
 * - rows : Un tableau à 2 dimensions de pointeurs de joueurs pour chaque case de la grille
 */
typedef struct
{
    int width;
    int height;
    Player ***rows;
} Grid;

/**
 * Description : Structure qui contient les informations d'une sauvegarde
 * Auteur : Kevin Carletto
 * Champs :
 * - saveName : Le nom de la sauvegarde
 * - filePath : Le chemin du fichier de sauvegarde
 */
typedef struct
{
    char *saveName;
    char *filePath;
} Save;

#endif // STRUCTURES_H