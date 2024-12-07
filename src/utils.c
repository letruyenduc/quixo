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
 * Traitement :
 * On initialise le nombre de lignes à 1 et un tableau d'entiers de taille 1 avec la valeur 0
 * On parcours la chaine de caractères jusqu'à atteindre un caractère NUL
 * - Si le caractère actuel est un retour à la ligne, on incrémente le nombre de lignes et on ajoute une case au tableau que l'on initialise à 0
 * - Sinon, on incrémente la dernière case du tableau.
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


/**
 * Description : Affiche une chaine de caractères larges à une certaine position en alignant les lignes
 * Auteur : Kevin Carletto
 * Paramètres :
 * - line : La ligne à laquelle afficher la première ligne de la chaine de caractère
 * - col : La colonne à laquelle afficher le début de chaque ligne
 * - str : La chaine de caractères larges à afficher
 * Retour : La prochaine ligne sur laquelle rien n'a été affiché. Utilisable pour combiner avec d'autres affichages ensuite
 * Traitement :
 * On parcours la chaine de caractères jusqu'à atteindre un caractère NUL.
 * - Si le caractère actuel est un retour à la ligne, on incrémente la ligne d'affichage et on réinitialise la colonne à celle passée initialement en argument
 * - Sinon, on affiche le caractère et on incrémente la colonne.
 * Enfin, on retourne la prochaine ligne sur laquelle rien n'a été affiché
 */
int mvprintwLines(int line, int col, wchar_t *str)
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
    return line;
}