#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <stdlib.h>
#include "game.h"
#include <wchar.h>
#include "loadgame.h"
#include "grid.h"
#include "constants.h"

/**
* Auteurs : Valentin et Kevin
* Description : Permet d'effectuer l'action du choix sélectionné.
* Paramètres :
- choix : Le choix sélectionné
- execution : Le pointeur vers une variable qui permet d'arrêter la boucle d'affichage du menu principal une fois mise à 0
- statusMessage : Le pointeur vers une variable contenant le texte du statut
 */
void treatChoice(int choix, int *execution, wchar_t **statusMessage) // Changement de la fonction "traiterChoix" en anglais
{
    char *fileStatus = NULL;
    Save *saves;
    int savesCount;

    switch (choix)
    {
    case 0:
        startNewGame();
        break;
    case 1:
        if (listSaves(&saves, &savesCount) == 0)
        {
            if (savesCount == 0)
            {
                *statusMessage = L"Aucune sauvegarde.";
            }
            else
            {
                char *selectedFilePath;
                if (selectSave(saves, savesCount, &selectedFilePath) == 0)
                {
                    startGameFromSave(selectedFilePath, statusMessage);
                }
            }
        }
        else
        {
            *statusMessage = L"Impossible de lister les sauvegardes";
        }
        break;
    case 2:
        *statusMessage = L"L'option pour modifier les options n'est pas encore implementée.";
        // Ajouter la logique pour afficher les options
        break;
    case 3:
        *statusMessage = L"Merci d'avoir joué. À bientôt !";
        *execution = 0; // Arrêter la boucle du menu
        break;
    default:
        *statusMessage = L"Choix invalide. Veuillez réessayer.";
        break;
    }
}

/**
 * Auteurs : Valentin et Kevin
 * Description : Affiche le menu principal. Le choix sélectionné est en surbrillance et on peut sélectionner un choix via les flèches haut et bas
 */
void displayMenu()
{
    const char *options[] = {
        "Nouvelle Partie",
        "Charger une Partie",
        "Options",
        "Quitter"};
    wchar_t *statusMessage = NULL;
    int nbOptions = sizeof(options) / sizeof(options[0]);
    int choix = 0; // Index de l'option sélectionnée
    int execution = 1;
    int touche;

    // Affichage du menu
    while (execution)
    {
        mvprintw(0, 0, "======================================");
        mvprintw(1, 0, "       Bienvenue sur le Quixo !       ");
        mvprintw(2, 0, "======================================");

        // Affichage des options
        for (int i = 0; i < nbOptions; i++)
        {
            if (i == choix)
            {
                attron(A_REVERSE);                    // Surligner l'option sélectionnée
                mvprintw(4 + i, 2, "%s", options[i]); // Ajout de "%s"
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw(4 + i, 2, "%s", options[i]); // Ajout de "%s"
            }
        }

        mvprintw(4 + nbOptions + 1, 0, "%ls", L"Utilisez les flèches pour naviguer, Entrée pour valider.");
        if (statusMessage != NULL)
        {
            mvprintw(4 + nbOptions + 2, 0, "%ls", statusMessage);
            statusMessage = NULL;
        }
        refresh();

        // Lecture de l'entrée utilisateur
        touche = getch();

        switch (touche)
        {
        case KEY_UP:
            choix = (choix - 1 + nbOptions) % nbOptions;
            break;
        case KEY_DOWN:
            choix = (choix + 1) % nbOptions;
            break;
        case '\n':                                          // Touche Entrée
            treatChoice(choix, &execution, &statusMessage); // Appelle la fonction de traitement
            // Pas de break car on veut également exécuter le clear à la fin du traitement du choix
        case 27: // Touche Echap
            execution = 0;
            break;
        default:
            clear();
            break;
        }
    }
}
