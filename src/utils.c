#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Description : Retourne un nombre entier aléatoire entre deux bornes.
 * Auteur : Kevin Carletto
 * Paramètres :
 * - min : Le nombre minimum possible (inclut)
 * - max : Le nombre maximum possible (exclut)
 * Traitement : On utilise la fonction rand() de façon à générer un nombre aléatoire non borné.
 * On le prend modulo la différence entre max et min, et on ajoute min pour obtenir le nombre final
 */
int randInt(int min, int max)
{
    return rand() % (max - min) + min;
}