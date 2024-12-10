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

// Définir le dossier de sauvegarde
const char *savesDirectory = "saves";

int createSavesDirectory()
{
#ifdef _WIN32
    // Sous Windows, on utilise _mkdir
    return _mkdir(savesDirectory) != 0 && errno != EEXIST;
#else
    // Sous Linux et MacOS, on utilise mkdir avec le flag 0777 pour les droits d'accès
    return mkdir(savesDirectory, 0777) != 0 && errno != EEXIST;
#endif
}

int save_grid(Grid *grid)
{
    char cheminFichier[256];

    // Essayer de créer le répertoire
    if (createSavesDirectory())
    {
        return 1;
    }

    // Définition des variables du temps actuel avec <time.h>
    time_t maintenant = time(NULL);
    struct tm *tempsLocal = localtime(&maintenant);

    // Générer le nom du fichier avec le chemin complet
    snprintf(cheminFichier, sizeof(cheminFichier), "%s%s%s", savesDirectory, SEPARATEUR, "sauvegarde_");
    strftime(cheminFichier + strlen(cheminFichier), sizeof(cheminFichier) - strlen(cheminFichier),
             "%Y-%m-%d_%H-%M-%S.txt", tempsLocal);

    // Ouvre le fichier en écriture
    FILE *fichier = fopen(cheminFichier, "w");

    // Vérifie si le fichier est ouvert
    if (fichier == NULL)
    {
        return 1;
    }

    // Écriture des données de la grille dans le fichier
    fprintf(fichier, "%d %d\n", grid->width, grid->height);
    for (int i = 0; i < grid->height; i++)
    {
        for (int j = 0; j < grid->width; j++)
        {
            fprintf(fichier, "%c", grid->rows[i][j]);
        }
        fprintf(fichier, "\n"); // Fin de ligne après chaque rangée
    }

    // Fermeture du fichier
    fclose(fichier);
    return 0;
}