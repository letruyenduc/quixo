#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

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

/**
 * Description : Trouver la taille d'une chaine de caractères larges
 * Auteur : Kevin Carletto
 * Paramètres :
 * - str : La chaine de caractères larges
 * Retour : La taille de la chaine
 * Traitement : On parcours la chaine de caractères jusqu'à atteindre un caractère NUL, en incrémentant à chaque fois un compteur.
 * Enfin, on retourne ce compteur.
 */
int Lstrlen(wchar_t *str)
{
    int length = 0;
    while (str[length] != 0)
        length++;
    return length - 1;
}

/**
 * Description : Calculer la longueur de la ligne la plus longue d'une chaine de caractères larges
 * Auteur : Kevin Carletto
 * Paramètres :
 * - str : La chaine de caractères larges
 * Retour (via paramètres pointeurs) :
 * - linesCount : Le nombre de lignes de la chaine de caractères
 * - linesLength : Le nombre de caractères pour chaque ligne
 */
void getLinesLength(wchar_t *str, int *linesCount, int **linesLength)
{
    *linesCount = 1;
    *linesLength = calloc(1, sizeof(int));

    for (int i = 0; str[i] != 0; i++)
    {
        if (str[i] == L'\n')
        {
            (*linesCount)++;
            *linesLength = realloc(*linesLength, sizeof(int) * (*linesCount));
            (*linesLength)[*linesCount - 1] = 0;
        }
        else
        {
            ((*linesLength)[*linesCount - 1])++;
        }
    }
}

/**
 * Description : Trouver la valeur maximale d'un tableau d'entiers
 * Auteur : Kevin Carletto
 * Paramètres :
 * - tab : Le tableau d'entiers
 * - tabLength : La taille du tableau
 * Retour : La valeur maximale du tableau
 * Traitement : On initialise une variable avec la première valeur du tableau.
 * On parcours ensuite la suite du tableau en vérifiant si la valeur de l'élément actuel est supérieure à cette variable.
 *   Si c'est le cas, on rempalce la valeur de la variable par celle de l'élément.
 * On retourne ensuite la valeur de la variable
 */
int maxTab(int *tab, int tabLength)
{
    assert(tabLength > 0);
    int maxVal = tab[0];
    for (int i = 1; i < tabLength; i++)
        if (tab[i] > maxVal)
            maxVal = tab[i];
    return maxVal;
}

void mvprintwLines(int line, int col, wchar_t *str)
{
    int currentCol = col;

    for (int i = 0; str[i] != 0; i++)
    {
        if (str[i] == L'\n')
        {
            line++;
            currentCol = col;
        }
        else
        {
            mvprintw(line, currentCol++, "%lc", str[i]);
        }
    }
}