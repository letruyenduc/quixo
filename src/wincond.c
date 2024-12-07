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
        if (grid->rows[i][0] == grid->rows[i][1] && grid->rows[i][1] == grid->rows[i][2] && grid->rows[i][2] == grid->rows[i][3] && grid->rows[i][3] == grid->rows[i][4]){
            return grid->rows[i][0];
        }
        else{
            return ' ';
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
        if (grid->rows[0][i] == grid->rows[1][i] && grid->rows[1][i] == grid->rows[2][i] && grid->rows[2][i] == grid->rows[3][i] && grid->rows[3][i] == grid->rows[4][i]){
            return grid->rows[0][i];
        }
        else{
            return ' ';
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
    char winner = ' ';
    if (winCondHorizontal(grid) != ' '){
        winner = winCondHorizontal(grid);
    }
    else if (winCondVertical(grid) != ' '){
        winner = winCondVertical(grid);
    }
    else if (winCondDiagonal(grid) != ' '){
        winner = winCondDiagonal(grid);
    }
    else{
        winner = ' ';
    }
    return winner;
}