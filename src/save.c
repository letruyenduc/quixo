#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Définir le séparateur de chemin selon l'OS
#ifdef _WIN32
    #define SEPARATEUR "\\"
#else
    #define SEPARATEUR "/"
#endif

#include "grid.h"
#include "save.h"
/*
* Auteurs : Duc
* Description : Sauvegarde la grille dans un fichier texte
* Paramètres :
* - grid : La grille de jeu
*/
void save_grid(Grid *grid) {
    // Définition des variables du temps actuel avec <time.h>
    time_t maintenant = time(NULL);
    struct tm *tempsLocal = localtime(&maintenant);
    char cheminFichier[256];
    const char *dossier = "saves";

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

    printf("Grille sauvegardée avec succès dans le fichier : %s\n", cheminFichier);
}