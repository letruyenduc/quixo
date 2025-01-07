#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

// Définir le séparateur de chemin selon l'OS
#ifdef _WIN32
#include <direct.h> // Pour _mkdir sur Windows
#define SEPARATEUR "\\"
#else
#include <sys/stat.h> // Pour mkdir sur Linux/macOS
#define SEPARATEUR "/"
#endif

#include "grid.h"
#include "save.h"
#include "constants.h"
#include "utils.h"

int createSavesDirectory()
{
#ifdef _WIN32
    // Sous Windows, on utilise _mkdir
    return _mkdir(SAVES_DIR) != 0 && errno != EEXIST;
#else
    // Sous Linux et MacOS, on utilise mkdir avec le flag 0777 pour les droits d'accès
    return mkdir(SAVES_DIR, 0777) != 0 && errno != EEXIST;
#endif
}

char **getPlayerNames(Player *playerList[], int playerCount)
{
    char **playerNames = malloc(playerCount * sizeof(char *));
    for (int i = 0; i < playerCount; i++)
    {
        playerNames[i] = playerList[i]->playerName;
    }
    return playerNames;
}

char *createFilePath(Player *playerList[], int playerCount)
{
    int saveFileLength = strlen(SAVES_DIR) + strlen(PATH_SEP) + playerCount + 4; // Un caractère de séparation entre chaque nom de joueur + le null-terminator
    char **playerNames = getPlayerNames(playerList, playerCount);
    sortStrings(playerNames, playerCount);

    for (int i = 0; i < playerCount; i++)
    {
        saveFileLength += strlen(playerNames[i]);
    }
    char *fileName = calloc(saveFileLength, sizeof(char));
    strcat(fileName, SAVES_DIR);
    strcat(fileName, PATH_SEP);
    for (int i = 0; i < playerCount; i++)
    {
        if (i > 0)
        {
            strcat(fileName, "+");
        }
        strcat(fileName, playerNames[i]);
    }
    strcat(fileName, ".txt");
    return fileName;
}

int save_grid(Grid *grid, Player *playerList[], int playerCount)
{
    char *filePath = createFilePath(playerList, playerCount);
    // Essayer de créer le répertoire
    if (createSavesDirectory())
    {
        return 1;
    }

    // Ouvre le fichier en écriture
    FILE *fichier = fopen(filePath, "w");

    // Vérifie si le fichier est ouvert
    if (fichier == NULL)
    {
        return 1;
    }

    // Écriture de la largeur, la hauteur et le nombre de joueurs dans le fichier
    fprintf(fichier, "%d %d %d\n", grid->width, grid->height, playerCount);

    // Écriture de la liste des joueurs dans le fichier
    for (int i = 0; i < playerCount; i++)
    {
        fprintf(fichier, "%c %s\n", playerList[i]->playerSymbol, playerList[i]->playerName);
    }

    // Écriture de la grille dans le fichier
    for (int i = 0; i < grid->height; i++)
    {
        for (int j = 0; j < grid->width; j++)
        {
            Player *player = grid->rows[i][j];
            fprintf(fichier, "%c", player == NULL ? ' ' : player->playerSymbol);
        }
        fprintf(fichier, "\n"); // Fin de ligne après chaque rangée
    }

    // Fermeture du fichier
    fclose(fichier);
    return 0;
}