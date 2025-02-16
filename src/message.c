#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <wchar.h>
#include "utils.h"

/**
 * Description : Affiche un message et retourne l'indice de l'option sélectionné
 * Auteur : Kevin Carletto
 * Paramètres :
 * - message : Le message à afficher. Peut contenir plusieurs lignes
 * - options : Les options que l'utilisateur peut sélectionner
 * - optionsCount : Le nombre d'options passés avec l'argument précédent
 * - allowEscape : Indique si l'utilisateur peut quitter la sélection avec la touche Echap
 * Retour : L'indice de l'option sélectionnée
 * Traitement :
 * On commence par calculer la largeur de l'affichage :
 * - On trouve la longueur de la ligne la plus longue
 * - On trouve la longueur de chacune des options
 * - On prend le maximum des valeurs précédentes (+4 pour les bordures)
 * On trouve la hauteur de l'affichage (nombre des lignes du message + nombre d'options + 3 pour les bordures et la séparation)
 * On calcule des valeurs pour centrer l'affichage
 * On retire tout ce qui est actuellement affiché à l'écran
 * On dessine les bordures
 * On affiche le texte du message
 * Tant qu'une option n'a pas été sélectionnée :
 *   On affiche chacune des options, avec une surlignée
 *   On attend l'appui sur une touche par l'utilisateur.
 *   - S'il s'agit de la flèche haut, on surligne celle au dessus (ou la dernière si on était sur la première)
 *   - S'il s'agit de la flèche bas, on surligne celle en dessous (ou la première si on était sur la dernière)
 *   - S'il s'agit de la touche entrer, on valide la sélection en quittant la boucle
 * Enfin, on efface l'écran et on retourne l'indice de l'option sélectionnée
 */
int showMessage(wchar_t *message, wchar_t **options, int optionsCount, int allowEscape)
{
    assert(optionsCount > 0);

    // On récupère la longueur de chaque ligne du message
    int messageLineCount, *messageLinesLength;
    getLinesLength(message, &messageLineCount, &messageLinesLength);

    // On récupère la longueur de la plus grande ligne
    int messageMaxLength = maxTab(messageLinesLength, messageLineCount);

    // On initialise la largeur de l'affichage à la taille de la plus longue ligne
    int width = messageMaxLength;

    // On récupère la longueur de chaque option, et on augmente la taille de l'affichage si nécessaire
    int *optionsLength = calloc(optionsCount, sizeof(int)); // Chaque élément est initialisé à 0 avec calloc
    for (int i = 0; i < optionsCount; i++)
    {
        optionsLength[i] = wcslen(options[i]);
        if (optionsLength[i] > width)
        {
            width = optionsLength[i];
        }
    }
    width += 4; // 4 de largeur supplémentaire pour la bordure

    // On calcule les valeurs de position d'affichage
    int height = messageLineCount + optionsCount + 2;
    int startLine = (LINES - height) / 2;
    int startCol = (COLS - width) / 2;

    clear();

    // Dessiner les bordures
    for (int i = 0; i < width; i++)
    {
        mvprintw(startLine, startCol + i, "#");
        mvprintw(startLine + height, startCol + i, "#");
    }
    for (int i = 1; i < height; i++)
    {
        mvprintw(startLine + i, startCol, "#");
        mvprintw(startLine + i, startCol + width - 1, "#");
    }
#ifdef __linux
    // Raffraichir après l'affichage des bordures pour ne pas qu'elles se décalent en affichant des accents dans le texte
    // Ce problème n'est présent que sur Linux, donc on évite d'affecter les autres systèmes
    refresh();
#endif

    // Afficher le message, on utilise mvprintwLinesKnownCount car on connait déjà la longueur des lignes
    mvprintwLinesKnownCount(startLine + 1, startCol + (width - messageMaxLength) / 2, message, messageLinesLength, messageLineCount);

    // Le tableau de la variable messageLinesLength provient d'une allocation dynamique dans la fonction getLinesLength
    // On libère la mémoire allouée pour ce tableau car elle n'est plus nécessaire
    free(messageLinesLength);
    messageLinesLength = NULL;

    int selectedOption = 0;
    int selecting = 1;

    while (selecting)
    {
        // On affiche les options
        for (int i = 0; i < optionsCount; i++)
        {
            if (i == selectedOption)
                attron(A_REVERSE);
            mvprintw(startLine + messageLineCount + 2 + i, startCol + (width - optionsLength[i]) / 2, "%ls", options[i]);
            if (i == selectedOption)
                attroff(A_REVERSE);
        }

        refresh();

        // On récupère les entrées utilisateur et on effectue le traitement
        int key = getch();
        switch (key)
        {
        case KEY_UP:
            selectedOption = (selectedOption + optionsCount - 1) % optionsCount;
            break;
        case KEY_DOWN:
            selectedOption = (selectedOption + 1) % optionsCount;
            break;
        case 27: // Touche Echap
            if (allowEscape)
            {
                selecting = 0;
                selectedOption = -1;
            }
            break;
        case '\n': // Touche entrer
            selecting = 0;
            break;
        }
    }

    free(optionsLength);

    // On efface l'écran et on retourne l'option sélectionnée
    clear();
    return selectedOption;
}

/**
 * Description : Affiche un message avec une seule option "OK"
 * Auteur : Kevin Carletto
 * Paramètres :
 * - message : Le message à afficher. Peut contenir plusieurs lignes
 * - allowEscape : Indique si l'utilisateur peut quitter la sélection avec la touche Echap
 * Traitement : On appelle la fonction showMessage définie au dessus, avec le message passé en argument ici et la seule option "OK".
 */
void showMessageOkButton(wchar_t *message, int allowEscape)
{
    showMessage(message, (wchar_t *[]){L"Ok"}, 1, allowEscape);
}