#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Définir le séparateur de chemin selon l'OS
#ifdef _WIN32
    #include <direct.h> // Pour _mkdir sur Windows
    #define SEPARATEUR "\\"
    #define mkdir _mkdir // Alias pour uniformiser les appels
#else
    #include <sys/stat.h> // Pour mkdir sur Linux/macOS
    #define SEPARATEUR "/"
#endif

#include "grid.h"
#include "save.h"

void save_grid(Grid *grid) {
    // Définir le dossier de sauvegarde
    const char *dossier = "saves";
    char cheminFichier[256];

    // Vérifier si le dossier existe, sinon le créer
    struct stat st = {0};
    if (stat(dossier, &st) == -1) { // Si le dossier n'existe pas
        if (mkdir(dossier, 0700) == 0) { // Créer le dossier avec les permissions
            printf("Dossier '%s' créé avec succès.\n", dossier);
        } else {
            printf("Erreur : Impossible de créer le dossier '%s'.\n", dossier);
            exit(1); // Quitter si la création du dossier échoue
        }
    }

    // Définition des variables du temps actuel avec <time.h>
    time_t maintenant = time(NULL);
    struct tm *tempsLocal = localtime(&maintenant);

    // Générer le nom du fichier avec le chemin complet
    snprintf(cheminFichier, sizeof(cheminFichier), "%s%s%s", dossier, SEPARATEUR, "sauvegarde_");
    strftime(cheminFichier + strlen(cheminFichier), sizeof(cheminFichier) - strlen(cheminFichier),
             "%Y-%m-%d_%H-%M-%S.txt", tempsLocal);

    // Ouvre le fichier en écriture
    FILE *fichier = fopen(cheminFichier, "w");

    // Vérifie si le fichier est ouvert
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier : %s\n", cheminFichier);
        exit(1);
    }

    // Écriture des données de la grille dans le fichier
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            fprintf(fichier, "%c", grid->rows[i][j]);
        }
        fprintf(fichier, "\n"); // Fin de ligne après chaque rangée
    }

    // Fermeture du fichier
    fclose(fichier);
}