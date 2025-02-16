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
    const char *invalidChars = "./\\*?:\"<>|";
    for (int i = 0; playerName[i] != '\0'; i++)
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
    clearLine(line);
    mvprintw(line, 0, "Nom du joueur %c : ", playerSymbol);

    char playerNameInput[21] = {0};
nameCheck:
    refresh();
    wgetnstr(stdscr, playerNameInput, 20); // wgetnstr limite le nombre de caractères pouvant être tapés à 20, donc pas besoin de faire la vérification ensuite
    char checkStatus = checkPlayerName(playerNameInput);
    if (checkStatus != CHECK_PLAYER_NAME_OK)
    {
        clearLine(line);
        wchar_t errorMessage[80];

        switch (checkStatus)
        {
        case CHECK_PLAYER_NAME_EMPTY:
            wcscpy(errorMessage, L"Le nom ne doit pas être vide. Veuillez réessayer.");
            break;
        default:
            wcscpy(errorMessage, L"Le nom ne doit pas contenir le caractère suivant : ' ' . Veuillez réessayer.");
            errorMessage[52] = (wchar_t)checkStatus; // Position précise dans la chaine précédente
            break;
        }
        mvprintw(line, 0, "%ls Nom du joueur %c : ", errorMessage, playerSymbol);
        goto nameCheck;
    }

    Player *player = malloc(sizeof(Player));
    player->playerSymbol = playerSymbol;
    player->playerName = strdup(playerNameInput);
    return player;
}

char inputPlayerSymbol(Player **playerList, int playerIndex, int line)
{
    char playerSymbolInput[2];
    char playerSymbol;
    clearLine(line);
    mvprintw(line, 0, "Symbole du joueur %d : ", playerIndex + 1);

symbolCheck:
    refresh();

    wgetnstr(stdscr, playerSymbolInput, 1); // Limiter le nombre de caractères pouvant être tapés à 1
    playerSymbol = playerSymbolInput[0];
    if (playerSymbol == '\0')
    {
        clearLine(line);
        mvprintw(line, 0, "%ls", L"Le symbole ne peut pas être vide. Veuillez en choisir un autre : ");
        goto symbolCheck;
    }

    if (playerSymbol == ' ')
    {
        clearLine(line);
        mvprintw(line, 0, "%ls", L"Le symbole ne peut pas être un espace. Veuillez en choisir un autre : ");
        goto symbolCheck;
    }

    for (int i = 0; i < playerIndex; i++)
    {
        if (playerList[i]->playerSymbol == playerSymbol)
        {
            clearLine(line);
            wchar_t errorMessage[] = L"Le symbole   est déjà utilisé. Veuillez en choisir un autre : ";
            errorMessage[11] = playerSymbol; // Position précise dans la chaine précédente
            mvprintw(line, 0, "%ls", errorMessage);
            goto symbolCheck;
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

    if (scanw("%d", playerCount) != 1 || *playerCount < 2 || *playerCount > 8)
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
    mvprintw(1, 8, "Taille de la grille");
    mvprintw(2, 0, "======================================");

    mvprintw(4, 0, "Veuillez entrer la largeur de la grille : ");

checkWidth:
    refresh();
    scanw("%d", width);

    if (*width < 3 || *width > 15)
    {
        clearLine(4);
        mvprintw(4, 0, "Veuillez entrer une largeur entre 3 et 15 : ");
        goto checkWidth;
    }

    mvprintw(5, 0, "Veuillez entrer la hauteur de la grille : ");

checkHeight:
    refresh();
    scanw("%d", height);

    if (*height < 3 || *height > 15)
    {
        clearLine(5);
        mvprintw(5, 0, "Veuillez entrer une hauteur entre 3 et 15 : ");
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
    int width = 0, height = 0;
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
                playerList[1] = inputPlayerName('O', 1);
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
    int showInstructions = 1;
    int nbOptions = sizeof(options) / sizeof(options[0]);
    int choix = 0; // Index de l'option sélectionnée
    int execution = 1;
    int touche;

    // Affichage du menu
    while (execution)
    {
        clear();

        mvprintw((LINES - nbOptions) / 2 - 6, (COLS - 54) / 2, "######################################################");
        attron(A_BOLD);
        mvprintw((LINES - nbOptions) / 2 - 4, (COLS - 24) / 2, "Bienvenue sur le Quixo !");
        attroff(A_BOLD);
        mvprintw((LINES - nbOptions) / 2 - 2, (COLS - 54) / 2, "######################################################");

        for (int i = (LINES - nbOptions) / 2 - 5; i < (LINES + nbOptions) / 2 + 3; i++)
        {
            mvprintw(i, (COLS - 54) / 2, "#");
            mvprintw(i, (COLS - 54) / 2 + 53, "#");
        }
        // Affichage des options
        for (int i = 0; i < nbOptions; i++)
        {
            if (i == choix)
            {
                attron(A_REVERSE); // Surlignage pour l'option sélectionnée
                mvprintw((LINES - nbOptions) / 2 + i + 1, (COLS - strlen(options[i]) - 6) / 2, " > %s < ", options[i]);
                attroff(A_REVERSE);
            }
            else
            {
                mvprintw((LINES - nbOptions) / 2 + i + 1, (COLS - strlen(options[i])) / 2, "%s", options[i]);
            }
        }
        mvprintw((LINES + nbOptions) / 2 + 3, (COLS - 54) / 2, "######################################################");

        if (statusMessage == NULL)
        {
            if (showInstructions)
            {
                attron(COLOR_PAIR(COLOR_CYAN_ON_BLACK));
                mvprintw((LINES + nbOptions) / 2 + 5, (COLS - 56) / 2, "%ls", L"Utilisez les flèches pour naviguer, Entrée pour valider.");
                attroff(COLOR_PAIR(COLOR_CYAN_ON_BLACK));
            }
        }
        else
        {
            attron(COLOR_PAIR(COLOR_RED_ON_BLACK));
            mvprintw((LINES + nbOptions) / 2 + 5, (COLS - wcslen(statusMessage)) / 2, "%ls", statusMessage);
            attroff(COLOR_PAIR(COLOR_RED_ON_BLACK));
            statusMessage = NULL;
        }
        refresh();

        // Lecture de l'entrée utilisateur
        touche = getch();

        switch (touche)
        {
        case KEY_UP:
            choix = (choix - 1 + nbOptions) % nbOptions;
            showInstructions = 0;
            break;
        case KEY_DOWN:
            choix = (choix + 1) % nbOptions;
            showInstructions = 0;
            break;
        case 27: // Touche Echap
            execution = 0;
            break;
        case '\n':                                          // Touche Entrée
            treatChoice(choix, &execution, &statusMessage); // Appelle la fonction de traitement
            showInstructions = 1;                           // Afficher les instructions au réaffichage du menu
            // Pas de break car on veut également exécuter le clear à la fin du traitement du choix
        default:
            clear();
            break;
        }
    }
}
