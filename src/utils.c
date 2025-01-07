#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
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
 * Description : Affiche une chaine de caractères larges à une certaine position en alignant les lignes, avec la taille des lignes connue
 * Auteur : Kevin Carletto
 * Paramètres :
 * - line : La ligne à laquelle afficher la première ligne de la chaine de caractère
 * - col : La colonne à laquelle afficher le début de chaque ligne
 * - str : La chaine de caractères larges à afficher
 * - messageLinesLength : Le nombre de caractères pour chaque ligne de la chaine de caractères
 * - messageLineCount : Le nombre de lignes de la chaine de caractères
 * Traitement :
 * On alloue un tableau de caractères larges de la taille de la ligne la plus longue
 * On parcours chaque ligne de la chaine de caractères
 * - On copie les caractères de la ligne actuelle dans le tableau alloué
 * - On affiche le tableau
 * On libère la mémoire allouée pour le tableau
 */
void mvprintwLinesKnownCount(int line, int col, wchar_t *str, int *messageLinesLength, int messageLineCount)
{
    wchar_t *lineBuffer = calloc(maxTab(messageLinesLength, messageLineCount) + 1, sizeof(wchar_t));
    int strOffset = 0;
    for (int i = 0; i < messageLineCount; i++)
    {
        for (int j = 0; j < messageLinesLength[i]; j++)
        {
            lineBuffer[j] = str[strOffset + j];
        }
        mvprintw(line + i, col, "%ls", lineBuffer);
        strOffset += messageLinesLength[i] + 1;
    }
    free(lineBuffer);
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
 * On récupère la longueur de chaque ligne de la chaine de caractères
 * On appelle la fonction mvprintwLinesKnownCount avec les paramètres donnés
 * On libère la mémoire allouée pour le tableau de longueurs des lignes
 * On retourne la prochaine ligne sur laquelle rien n'a été affiché
 */
int mvprintwLines(int line, int col, wchar_t *str)
{
    int *messageLinesLength, messageLineCount;
    getLinesLength(str, &messageLineCount, &messageLinesLength);
    mvprintwLinesKnownCount(line, col, str, messageLinesLength, messageLineCount);
    free(messageLinesLength);
    return line + messageLineCount;
}

/**
 * Description : Vérifie si une chaine de caractères se termine par un certain suffixe
 * Auteur : Kevin Carletto
 * Paramètres :
 * - str : La chaine de caractères
 * - suffix : Le suffixe à vérifier
 * Retour : 1 si str se termine par suffix, 0 sinon
 * Traitement : On obtient la taille de str et de suffix.
 * Si suffix est plus long que str, alors str ne peut pas se terminer par suffix.
 * Sinon, on compare str à partir de la fin moins la taille de suffix à suffix
 */
int strEndsWith(const char *str, const char *suffix)
{
    int strLen = strlen(str);
    int suffixLen = strlen(suffix);

    if (suffixLen > strLen)
    {
        return 0;
    }

    return strcmp(str + strLen - suffixLen, suffix) == 0;
}

/**
 * Description : Retourne le maximum entre deux entiers
 * Auteur : Kevin Carletto & Valentin Verneuil
 * Paramètres :
 * - a : Le premier entier
 * - b : Le second entier
 * Retour : Le plus grand des deux entiers
 */
int maxi(int a, int b)
{
    return a > b ? a : b;
}

/**
 * Description : Supprime une ligne de la console
 * Auteur : Kevin Carletto
 * Paramètres :
 * - line : La ligne à supprimer
 * Traitement : On parcours la ligne en affichant un espace à chaque caractère pour la supprimer
 */
void clearLine(int line)
{
    for (int i = 0; i < COLS; i++)
    {
        mvprintw(line, i, " ");
    }
}

/**
 * Description : Permet de sauter une ligne dans un fichier
 * Auteur : Kevin Carletto
 * Paramètres :
 * - file : Le fichier dans lequel sauter une ligne
 * Retour : 0 si la ligne a été sautée, 1 si on est arrivé à la fin du fichier
 * Traitement : On lit un caractère à chaque fois jusqu'à atteindre un retour à la ligne
 * Si on atteint la fin du fichier, on retourne 1
 * Sinon, on retourne 0
 */
int skipLine(FILE *file)
{
    char buff[2];
    do
    {
        if (fgets(buff, 2, file) == NULL)
        {
            return 1;
        }
    } while (buff[0] != '\n');
    return 0;
}


/**
 * Auteur : Kevin Carletto
 * Description : Permet de trier un tableau de chaines de caractères
 * Paramètres :
 * - strings : Le tableau de chaines de caractères
 * - stringsCount : Le nombre de chaines de caractères dans le tableau
 * Traitement :
 * On parcourt chaque élément du tableau
 * - On parcourt chaque élément suivant
 *  - Si l'élément actuel est plus grand que l'élément suivant, on les échange
 */
void sortStrings(char **strings, int stringsCount)
{
    for (int i = 0; i < stringsCount - 1; i++)
    {
        for (int j = i + 1; j < stringsCount; j++)
        {
            if (strcmp(strings[i], strings[j]) > 0)
            {
                char *save = strings[i];
                strings[i] = strings[j];
                strings[j] = save;
            }
        }
    }
}