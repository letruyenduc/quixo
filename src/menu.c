#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include <wchar.h>
#include "loadgame.h"
#include "grid.h"
#include "constants.h"
#include "structures.h"
#include "utils.h"
#include "message.h"

/**
 * Auteur : Kevin
 * Description : Vérifie si le nom du joueur est valide
 * Paramètres :
 * - playerName : Le nom du joueur
 * Retour :
 * - '\0' si le nom est valide
 * - '\1' si le nom est vide
 * - '\2' si le nom est trop long (plus de 20 caractères)
 * - Le caractère interdit si le nom contient un caractère interdit. Les caractères interdits sont : ./\*?:"><|
 * Traitement :
 * - Vérifie si le nom est vide
 * - Vérifie si le nom est trop long
 * - Parcourse chaque caractère du nom pour vérifier s'il contient un caractère interdit
 */
char checkPlayerName(char *playerName)
{
    if (playerName == NULL || playerName[0] == '\0')
    {
        return CHECK_PLAYER_NAME_EMPTY;
    }
    int len = strlen(playerName);
    if (len > 20)
    {
        return CHECK_PLAYER_NAME_TOO_LONG;
    }
    const char *invalidChars = "./\\*?:\"<>|";
    for (int i = 0; i < len; i++)
    {
        if (strchr(invalidChars, playerName[i]) != NULL)
        {
            return playerName[i];
        }
    }
    return CHECK_PLAYER_NAME_OK;
}

/**
 * Auteurs : Duc & Kevin
 * Description : Permet de saisir le nom du joueur
 * Paramètres :
 * - playerSymbol : Le symbole du joueur
 * - line : La ligne où afficher le message
 * Retour : Le joueur créé
 * Traitement :
 * - On affiche un message pour demander le nom du joueur
 * - On récupère le nom du joueur
 * - On vérifie si le nom est valide; on redemande tant qu'il n'est pas valide
 */
Player *inputPlayerName(char playerSymbol, int line)
{
    Player *player = malloc(sizeof(Player));
    player->playerSymbol = playerSymbol;

    clearLine(line);
    mvprintw(line, 0, "Nom du joueur %c : ", playerSymbol);

nameCheck:
    refresh();
#ifdef __APPLE__ // POUR MACOS
    player->playerName = malloc(22);
    scanw("%21s", player->playerName);
#else // POUR LE RESTE
    scanw("%ms", &player->playerName);
#endif
    char checkStatus = checkPlayerName(player->playerName);
    if (checkStatus != CHECK_PLAYER_NAME_OK) // Changement de la fonction "verifierNomJoueur" en anglais
    {
        free(player->playerName);
        clearLine(line);
        wchar_t errorMessage[80];

        switch (checkStatus)
        {
        case CHECK_PLAYER_NAME_EMPTY:
            wcscpy(errorMessage, L"Le nom ne doit pas être vide. Veuillez réessayer.");
            break;
        case CHECK_PLAYER_NAME_TOO_LONG:
            wcscpy(errorMessage, L"Le nom ne doit pas dépasser 20 caractères. Veuillez réessayer.");
            break;
        default:
            wcscpy(errorMessage, L"Le nom ne doit pas contenir le caractère suivant : ' ' . Veuillez réessayer.");
            errorMessage[52] = (wchar_t)checkStatus; // Position précise dans la chaine précédente
            break;
        }
        mvprintw(line, 0, "%ls Nom du joueur %c : ", errorMessage, playerSymbol);
        goto nameCheck;
    }

    return player;
}

char inputPlayerSymbol(Player **playerList, int playerIndex, int line)
{
    char playerSymbol;
    clearLine(line);
    mvprintw(line, 0, "Symbole du joueur %d : ", playerIndex + 1);
    refresh();
    scanw("%c", &playerSymbol);
    for (int i = 0; i < playerIndex; i++)
    {
        if (playerList[i]->playerSymbol == playerSymbol)
        {
            clearLine(line);
            wchar_t errorMessage[] = L"Le symbole   est déjà utilisé. Veuillez en choisir un autre : ";
            errorMessage[11] = playerSymbol; // Position précise dans la chaine précédente
            mvprintw(line, 0, "%ls", errorMessage);
            refresh();
            scanw("%c", &playerSymbol);
            i = -1; // Recommencer la boucle pour vérifier tous les joueurs
        }
    }
    return playerSymbol;
}

/**
 * Auteurs : Duc
 * Description : Permet de saisir le nombre de joueurs et leurs noms
 * Paramètres :
 * - playerList : La liste des joueurs
 * - playerCount : Le nombre de joueurs
 */
void inputUsers(Player ***playerList, int *playerCount)
{
    clear();
    mvprintw(0, 0, "======================================");
    mvprintw(2, 0, "======================================");
    mvprintw(1, 0, "Veuillez entrer le nombre de joueurs : ");

checkPlayerCount:
    refresh();
    scanw("%d", playerCount);

    if (*playerCount < 2 || *playerCount > 8)
    {
        clearLine(1);
        mvprintw(1, 0, "Veuillez entrer un nombre de joueurs entre 2 et 8 : ");
        goto checkPlayerCount;
    }

    *playerList = (Player **)malloc(sizeof(Player *) * (*playerCount));
    for (int i = 0; i < *playerCount; i++)
    {
        char playerSymbol = inputPlayerSymbol(*playerList, i, 4 + i * 3);
        (*playerList)[i] = inputPlayerName(playerSymbol, 5 + i * 3);
    }
}

/**
 * Auteurs : Duc
 * Description : Permet de saisir la taille de la grille
 * Paramètres :
 * - width : La largeur de la grille
 * - height : La hauteur de la grille
 */
void inputSize(int *width, int *height)
{
    clear();
    mvprintw(0, 0, "======================================");
    mvprintw(2, 0, "======================================");
    mvprintw(1, 0, "Veuillez entrer la largeur de la grille : ");

checkWidth:
    refresh();
    scanw("%d", width);

    if (*width < 3 || *width > 15)
    {
        clearLine(1);
        mvprintw(1, 0, "Veuillez entrer une largeur entre 3 et 15 : ");
        goto checkWidth;
    }

    clearLine(1);
    mvprintw(1, 0, "Veuillez entrer la hauteur de la grille : ");

checkHeight:
    refresh();
    scanw("%d", height);

    if (*height < 3 || *height > 15)
    {
        clearLine(1);
        mvprintw(1, 0, "Veuillez entrer une hauteur entre 3 et 15 : ");
        goto checkHeight;
    }
}

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
    Player **playerList;
    int playerCount;
    int savesCount;
    int width, height;
    int selectedOption;

    switch (choix)
    {
    case 0:
        selectedOption = showMessage(L"Souhaitez-vous faire une partie par défaut ou personnalisée ?",
                                     (wchar_t *[]){L"Par défaut", L"Personnalisée"}, 2, 1);
        if (selectedOption != -1)
        {
            echo();
            curs_set(1);
            if (selectedOption == 1)
            {
                inputUsers(&playerList, &playerCount);
                inputSize(&width, &height);
            }
            else
            {
                clear();
                playerList = (Player **)malloc(sizeof(Player *) * 2);
                playerCount = 2;
                playerList[0] = inputPlayerName('X', 0);
                playerList[1] = inputPlayerName('O', 0);
                width = 5;
                height = 5;
            }
            noecho();
            curs_set(0);
            startNewGame(playerList, playerCount, width, height);
        }
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
        case 27: // Touche Echap
            execution = 0;
            break;
        case '\n':                                          // Touche Entrée
            treatChoice(choix, &execution, &statusMessage); // Appelle la fonction de traitement
            // Pas de break car on veut également exécuter le clear à la fin du traitement du choix
        default:
            clear();
            break;
        }
    }
}
