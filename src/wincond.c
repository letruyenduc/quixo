#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
/*
* Auteur : Duc
* Description : Fonction qui vérifie si un joueur a gagné en alignant 5 cubes horizontalement
* Paramètres : La grille de jeu
* Retour : Le joueur gagnant
*/
char winCondHorizontal(Grid *grid){
    for (int i = 0; i < grid->height; i++){
        char first = grid->rows[i][0];
        int j;
        for (j = 1; j < grid->width && grid->rows[i][j] == first; j++);
        if (j == grid->width) {
            return first;
        }
    }
    return ' ';
}

/*
* Auteur : Duc
* Description : Fonction qui vérifie si un joueur a gagné en alignant 5 cubes verticalement
* Paramètres : La grille de jeu
* Retour : Le joueur gagnant
*/
char winCondVertical(Grid *grid){
    for (int i = 0; i < grid->width; i++){
        char first = grid->rows[0][i];
        int j;
        for (j = 1; j < grid->height && grid->rows[j][i] == first; j++);
        if (j == grid->height){
            return first;
        }
    }
    return ' ';
}

/*
* Auteur : Duc
* Description : Fonction qui vérifie si un joueur a gagné en alignant 5 cubes diagonalement
* Paramètres : La grille de jeu
* Retour : Le joueur gagnant
*/
char winCondDiagonal(Grid *grid){
    if (grid->rows[0][0] == grid->rows[1][1] && grid->rows[1][1] == grid->rows[2][2] && grid->rows[2][2] == grid->rows[3][3] && grid->rows[3][3] == grid->rows[4][4]){
        return grid->rows[0][0];
    }
    else if (grid->rows[0][4] == grid->rows[1][3] && grid->rows[1][3] == grid->rows[2][2] && grid->rows[2][2] == grid->rows[3][1] && grid->rows[3][1] == grid->rows[4][0]){
        return grid->rows[0][4];
    }
    else{
        return ' ';
    }
}

/*
* Auteur : Duc
* Description : Fonction qui vérifie si un joueur a gagné
* Paramètres : La grille de jeu
* Retour : Le joueur gagnant
*/
char winCond(Grid *grid) {
    char winner = winCondHorizontal(grid);
    if (winner != ' '){
        return winner;
    }

    winner = winCondVertical(grid);
    if (winner != ' '){
        return winner;
    }

    return winCondDiagonal(grid);
}