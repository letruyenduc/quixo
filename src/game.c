#include <stdlib.h>
#include "grid.h"
#include "display.h"
#include "utils.h"
#include "constants.h"
#include "wincond.h"
#include "endscreen.h"
#include "loadgame.h"
#include "save.h"
#include "message.h"

/**
 * Description : Modifie la liste des joueurs pour passer au tour suivant
 * Auteur : Kevin Carletto
 * Paramètres :
 * - playerList : La liste des caractères des joueurs
 * - playerCount : Le nombre de joueurs dans la liste
 * Traitement : Le prochain joueur doit se retrouver à la première position.
 * Le joueur qui vient de jouer se donc retrouve à la fin, et chaque autre joueur avance d'une position dans la liste
 */
void nextPlayer(Player *playerList[], int playerCount)
{
    Player *lastPlaying = playerList[0];
    for (int i = 1; i < playerCount; i++)
    {
        playerList[i - 1] = playerList[i];
    }
    playerList[playerCount - 1] = lastPlaying;
}

/**
 * Description : Appelle la fonction de déplacement en fonction de son identifiant
 * Auteur : Kevin Carletto
 * Paramètres :
 * - grid: La grille de jeu
 * - row : L'indice de la ligne du cube sélectionné
 * - column : L'indice de la colonne du cube sélectionné
 * - function : L'indentifiant de la fonction à appeler
 * - playerList : La liste des caractères des joueurs
 * - playerCount : Le nombre de joueurs dans la liste
 */
int handlePlayerTurn(Grid *grid, int row, int column, int function, Player *playerList[], int playerCount)
{
    switch (function)
    {
    case FUNCTION_SHIFT_ROW_RIGHT:
        return shiftRowRight(grid, row, column, playerList[0]);
    case FUNCTION_SHIFT_ROW_LEFT:
        return shiftRowLeft(grid, row, column, playerList[0]);
    case FUNCTION_SHIFT_COLUMN_DOWN:
        return shiftColumnDown(grid, row, column, playerList[0]);
    case FUNCTION_SHIFT_COLUMN_UP:
        return shiftColumnUp(grid, row, column, playerList[0]);
    default:
        return TURN_STATUS_INVALID_FUNCTION;
    }
}

/**
 * Effectue les actions en fonction du statut retourné par la fonction handlePlayerTurn
 * Auteur : Kevin Carletto
 * Paramètres :
 * - status : Le statut retourné par la fonction handlePlayerTurn
 * - playerList : La liste des caractères des joueurs
 * - playerCount : Le nombre de joueurs dans la liste
 * - statusMessage : Le pointeur vers une variable contenant le texte du statut
 * Traitement :
 * On vérifie le statut retourné :
 * - Si l'action est correctement exécutée, on passe au joueur suivant et on réinitialise le message de statut.
 * - Sinon on affiche un message d'erreur en fonction du statut et on fait rejouer le même joueur.
 */
void handleTurnStatus(int status, Player *playerList[], int playerCount, wchar_t **statusMessage)
{
    switch (status)
    {
    case TURN_STATUS_OK:
        nextPlayer(playerList, playerCount);
        break;
    case TURN_STATUS_OTHER_PLAYER:
        *statusMessage = L"Ce cube appartient à un autre joueur. Vous ne pouvez pas le déplacer. Veuillez rejouer.";
        break;
    case TURN_STATUS_INVALID_FUNCTION:
        *statusMessage = L"La fonction demandée n'existe pas. Veuillez rejouer.";
        break;
    default:
        *statusMessage = L"Veuillez rejouer.";
        break;
    }
}

/**
 * Description : Exécute la boucle de jeu
 * Auteur : Kevin Carletto
 * Paramètres :
 * - grid : La grille de jeu
 * - playerList : La liste des caractères des joueurs
 * - playerCount : Le nombre de joueurs dans la liste
 * Traitement : On boucle tant que la partie est en cours. À chaque itération, on affiche la grille, on récupère les entrées utilisateur,
 * on exécute l'action demandée. On effectue ensuite les actions de fin de tour en fonction du statut retourné.
 * Si un joueur a gagné, on arrête la boucle.
 */
void gameLoop(Grid *grid, Player *playerList[], int playerCount)
{
    int row = 0, column = 0, function;
    int playing = 1;
    wchar_t *statusMessage = NULL;

    while (playing)
    {
        handleInput(grid, playerList[0], statusMessage, &row, &column, &function);
        statusMessage = NULL; // On réinitialise le message de statut après l'avoir affiché
        // Cas particulier pour la fonction quitter, on n'effectue pas de tour de jeu
        if (function == FUNCTION_QUIT_GAME)
        {
            int selectedOption = showMessage(
                L"Le jeu a été mis en pause\nSouhaitez-vous continuer la partie, sauvegarder, ou quitter sans sauvegarder ?",
                (wchar_t *[]){L"Continuer", L"Sauvegarder", L"Quitter sans sauvegarder"},
                3);

            switch (selectedOption)
            {
            case 1:
                if (save_grid(grid, playerList, playerCount))
                {
                    selectedOption = showMessage(
                        L"Une erreur est survenue lors de la sauvegarde de l'état du jeu !\nSouhaitez vous quitter sans sauvegarder ou continuer à jouer ?",
                        (wchar_t *[]){L"Quitter sans sauvegarder", L"Continuer à jouer"},
                        2);
                    if (selectedOption == 0) // Quitter sans sauvegarder, dans le cas contraire on ne modifie pas l'état de la variable playing
                    {
                        playing = 0;
                    }
                }
                else
                {
                    showMessageOkButton(L"L'état du jeu a été sauvegardé");
                    playing = 0;
                }
                break;
            case 2:
                playing = 0;
                break;
            }
        }
        else
        {
            int status = handlePlayerTurn(grid, row, column, function, playerList, playerCount);
            handleTurnStatus(status, playerList, playerCount, &statusMessage);
            if (status == TURN_STATUS_OK)
            {
                Player *winner = winCond(grid, playerList, playerCount);
                if (winner != NULL)
                {
                    displayEndScreen(grid, winner); // On affiche l'écran de fin de partie
                    playing = 0;
                }
            }
        }
    }
}

/**
 * Description : Permet de mélanger la liste des joueurs dans un ordre aléatoire
 * Auteur : Kevin Carletto
 * Paramètres :
 * - playerList : La liste des caractères des joueurs
 * - playerCount : Le nombre de joueurs dans la liste
 * Traitement : On parcourt chaque indice possible de la liste, et on échange la position du caractère à cet endroit avec une autre position choisie aléatoirement.
 */
void shufflePlayerList(Player *playerList[], int playerCount)
{
    for (int i1 = 0; i1 < playerCount; i1++)
    {
        int i2 = randInt(0, playerCount);
        if (i1 != i2)
        {
            Player *save = playerList[i1];
            playerList[i1] = playerList[i2];
            playerList[i2] = save;
        }
    }
}

/**
 * Description : Permet de lancer une nouvelle partie
 * Auteur : Kevin Carletto
 * Traitement : On initialise une grille, on crée la liste des joueurs triée de manière aléatoire, puis on lance la boucle de jeu.
 * Enfin, on libère la mémoire utilisée par la grille.
 */
void startNewGame()
{
    Grid *grid = createGrid(5, 5);
    const int playerCount = 2;
    Player *playerList[playerCount];
    for (int i = 0; i < 2; i++)
    {
        playerList[i] = malloc(sizeof(Player));
    }
    Player player1 = {'O', "Joueur 1"};
    Player player2 = {'X', "Joueur 2"};
    playerList[0] = &player1;
    playerList[1] = &player2;

    shufflePlayerList(playerList, playerCount);

    gameLoop(grid, playerList, playerCount);
    freeGrid(grid);
    grid = NULL;
}

/*
 * Auteur : Duc
 * Description : Charger une partie sauvegardée
 * Paramètres : Aucun
 * Retour : Aucun
 */
void startGameFromSave(char *saveFilePath, wchar_t **statusMessage)
{
    Grid *grid;
    Player **playerList;
    int playerCount;
    int loadStatus = loadSave(saveFilePath, &grid, playerList, &playerCount);
    free(saveFilePath);

    switch (loadStatus)
    {
    case LOAD_SAVE_FILE_ERROR:
        *statusMessage = L"Une erreur est survenue lors du chargement du fichier";
        return;
    case LOAD_SAVE_INVALID_CONTENT:
        *statusMessage = L"Le contenu du fichier est invalide";
        return;
    }

    gameLoop(grid, playerList, playerCount);
    for (int i = 0; i < playerCount; i++)
    {
        free(playerList[i]->playerName);
        free(playerList[i]);
    }
    free(playerList);
    freeGrid(grid);
    grid = NULL;
}