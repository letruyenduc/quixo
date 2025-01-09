#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <dirent.h> // For DIR, struct dirent, opendir, readdir, closedir
#include <sys/stat.h>
#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include "constants.h"
#include "grid.h"
#include "save.h"
#include "utils.h"
#include "structures.h"

/**
 * Description : Trouver un joueur par son symbole
 * Auteurs : Kevin
 * Paramètres :
 * - playerList : La liste des joueurs
 * - playerCount : Le nombre de joueurs
 * - symbol : Le symbole du joueur à trouver
 * Retour : Le joueur trouvé, ou NULL si aucun joueur n'a été trouvé
 * Traitement : On parcourt la liste des joueurs, et on compare le symbole du joueur actuel avec le symbole recherché.
 * Si on trouve un joueur avec le symbole recherché, on le retourne.
 * Sinon, on retourne NULL.
 */
Player *findPlayerBySymbol(Player **playerList, int playerCount, char symbol)
{
    if (symbol == ' ')
    {
        return NULL;
    }
    for (int i = 0; i < playerCount; i++)
    {
        if (playerList[i]->playerSymbol == symbol)
        {
            return playerList[i];
        }
    }
    return NULL;
}

/*
 * Auteur : Duc et Kevin
 * Description : Charger la grille depuis un fichier
 * Paramètres :
 * - filepath : Le chemin du fichier de sauvegarde
 * Retour (par paramètres pointeurs):
 * - grid : La grille de jeu
 * - playerList : La liste des joueurs
 * - playerCount : Le nombre de joueurs
 * Retour (via instruction return) : 0 si la fonction s'est terminée, ou un code de statut en fonction de l'erreur
 * Traitement :
 * - On ouvre le fichier en lecture
 * - On lit la largeur, la hauteur et le nombre de joueurs
 * - On lit la liste des joueurs
 * - On lit la grille
 * - On ferme le fichier
 */
int loadSave(char *filepath, Grid **grid, Player ***playerList, int *playerCount)
{
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        return LOAD_SAVE_FILE_ERROR;
    }

    // Lire la largeur, la hauteur et le nombre de joueurs
    int width, height;
    if (fscanf(file, "%d %d %d", &width, &height, playerCount) != 3)
    {
        fclose(file);
        return LOAD_SAVE_INVALID_CONTENT;
    }

    assert(width > 0 && height > 0);

    char *line = malloc(sizeof(char) * (width + 2)); // +2 pour le caractère de fin de ligne et le caractère nul

    // Continuer à lire jusqu'à un retour à la ligne, sinon la première ligne de la grille n'est pas lue correctement
    if (skipLine(file))
    {
        free(line);
        fclose(file);
        return LOAD_SAVE_FILE_ERROR;
    }

    // Lire la liste des joueurs
    *playerList = malloc(sizeof(Player *) * (*playerCount));
    for (int i = 0; i < *playerCount; i++)
    {
        (*playerList)[i] = malloc(sizeof(Player));
        char buffer[32];
        if (fscanf(file, "%c %31s", &(*playerList)[i]->playerSymbol, buffer) != 2)
        {
            free(*playerList);
            free(line);
            fclose(file);
            return LOAD_SAVE_INVALID_CONTENT;
        }
        (*playerList)[i]->playerName = strdup(buffer);

        // Continuer à lire jusqu'à un retour à la ligne, sinon la première ligne de la grille n'est pas lue correctement
        if (skipLine(file))
        {
            free(line);
            fclose(file);
            return LOAD_SAVE_FILE_ERROR;
        }
    }

    // Lire la grille - on commence par créer la grille
    *grid = createGrid(width, height);

    // Lire chaque ligne
    for (int i = 0; i < height; i++)
    {
        if (fgets(line, width + 2, file) == NULL)
        {
            freeGrid(*grid);
            free(playerList);
            free(line);
            fclose(file);
            return LOAD_SAVE_FILE_ERROR;
        }

        for (int j = 0; j < width; j++)
        {
            Player *player = findPlayerBySymbol(*playerList, *playerCount, line[j]);
            (*grid)->rows[i][j] = player;
        }
    }

    free(line);
    fclose(file);
    return NO_ERROR;
}

/**
 * Description : Fonction pour lister les fichiers de sauvegarde et retourner la liste des fichiers
 * Auteurs : Kevin et Duc
 * Retours (par paramètres pointeurs) :
 * - files : La liste des sauvegardes trouvées
 * - count : Le nombre de fichiers trouvés
 * Traitement : On ouvre le répertoire et on parcours la liste des fichiers.
 * - On ignore les fichiers s'appelant '.', '..' et ne terminant pas par '.txt'.
 * - On ajoute à un tableau une structure contenant le nom de la sauvegarde et son chemin.
 * */
int listSaves(Save **files, int *count)
{
    *count = 0;
    *files = NULL;

    // Ouvrir le répertoire
    DIR *dir = opendir(SAVES_DIR);
    if (dir == NULL)
    {
        return 1;
    }

    // Lire les entrées du répertoire
    struct dirent *entry;
    struct stat entry_info;
    while ((entry = readdir(dir)) != NULL)
    {
        // Ignorer les entrées "." et ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || !strEndsWith(entry->d_name, ".txt"))
        {
            continue;
        }

        int filenameLen = strlen(entry->d_name);
        int entryPathSize = strlen(SAVES_DIR) + strlen(PATH_SEP) + filenameLen + 1;
        char *entryPath = calloc(entryPathSize, sizeof(char));

        // Construire le chemin complet de l'entrée
        snprintf(entryPath, entryPathSize, "%s%s%s", SAVES_DIR, PATH_SEP, entry->d_name);

        // Récupérer les informations sur l'entrée et vérifier s'il s'agit d'un fichier
        if (stat(entryPath, &entry_info) != 0 || !S_ISREG(entry_info.st_mode))
        {
            continue;
        }

        // Allouer de l'espace pour le nouveau fichier
        *files = realloc(*files, (*count + 1) * sizeof(Save));

        // On crée une variable saveName qui contiendra le nom du fichier sans l'extension
        char *saveName = calloc(filenameLen - 3, sizeof(char));
        strncpy(saveName, entry->d_name, filenameLen - 4);

        (*files)[(*count)++] = (Save){saveName, entryPath};
    }

    // Fermer le répertoire
    closedir(dir);
    return 0;
}

/*
 * Auteur : Duc et Kevin
 * Description : Affiche la liste des sauvegardes et permet d'en sélectionner une
 * Paramètres :
 * - files : La liste des sauvegardes trouvées
 * - filesCount : Le nombre de fichiers trouvés
 * Retour (par paramètres pointeurs):
 * - selectedFilePath : Le chemin de la sauvegarde sélectionnée
 * Retour (par instruction return): Le statut de sélection
 * Traitement : On affiche la liste des sauvegardes et les instructions. Ensuite, tant qu'on n'a pas sélectionné une option :
 * - On surligne la sauvegarde sélectionnée, on récupère les entrées utilisateur
 *   - Les flèches haut et bas permettent de changer la sauvegarde sélectionnée
 *   - La touche entrée modifie la valeu du paramètre pointeur avec le chemin de la sauvegarde, et retourne un statut indiquant que la sélection s'est bien passée
 *   - La touche echap permet de revenir au menu précédent en retournant un statut différent
 */
int selectSave(Save *files, int filesCount, char **selectedFilePath)
{
    assert(filesCount > 0);
    clear();
    mvprintw(0, 0, "======================================");
    mvprintw(1, 4, "%ls", L"Sélectionnez une sauvegarde :");
    mvprintw(2, 0, "======================================");
    for (int i = 0; i < filesCount; i++)
    {
        mvprintw(4 + i, 0, "%s", files[i].saveName);
    }
    mvprintw(5 + filesCount, 0, "%ls", L"Utilisez les flèches pour naviguer, Entrée pour valider,");
    mvprintw(6 + filesCount, 0, "%ls", L"Echap pour revenir au menu principal");

    int selected = 0;
    int key;
    while (1)
    {
        attron(A_REVERSE); // Activer l'attribut de surlignage
        mvprintw(4 + selected, 0, "%s", files[selected].saveName);
        attroff(A_REVERSE); // Désactiver l'attribut de surlignage
        refresh();

        key = getch();
        mvprintw(4 + selected, 0, "%s", files[selected].saveName);
        switch (key)
        {
        case KEY_UP:
            selected = (selected - 1 + filesCount) % filesCount;
            break;
        case KEY_DOWN:
            selected = (selected + 1) % filesCount;
            break;
        case '\n': // Touche Entrée
            *selectedFilePath = files[selected].filePath;
            for (int i = 0; i < filesCount; i++)
            {
                free(files[i].saveName);
                if (i != selected)
                {
                    free(files[i].filePath);
                }
            }
            free(files);
            return NO_ERROR;
        case 27: // Touche Echap
            for (int i = 0; i < filesCount; i++)
            {
                free(files[i].saveName);
                free(files[i].filePath);
            }
            free(files);
            return SELECT_SAVE_QUIT;
        }
    }
}