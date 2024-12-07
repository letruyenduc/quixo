#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <dirent.h> // For DIR, struct dirent, opendir, readdir, closedir
#include "grid.h"
#ifdef _WIN32
    #include <direct.h> // Pour _mkdir sur Windows
    #define SEPARATEUR "\\"
    #define mkdir _mkdir // Alias pour uniformiser les appels
#else
    #include <sys/stat.h> // Pour mkdir sur Linux/macOS
    #define SEPARATEUR "/"
#endif
#define ligne 10


void loadSave(Grid *grid, char *filename) {
    // Charger les données de la grille
    FILE *file = fopen(filename, "r");
    fscanf(file, "%d %d\n", &grid->width, &grid->height);
    grid->rows = malloc(grid->height * sizeof(char *));
    for (int i = 0; i < grid->height; i++) {
        grid->rows[i] = malloc(grid->width * sizeof(char));
        for (int j = 0; j < grid->width; j++) {
            fscanf(file, "%c ", &grid->rows[i][j]);
        }
    }
    fclose(file);
}

/*
* Auteur : Duc
* Description : Affiche la liste des sauvegardes et permet de charger une sauvegarde
* Paramètres :
* - grid : La grille de jeu
*/
void list_saves() {
    Grid *grid;
    DIR *d;
    struct dirent *dir;
    char path[256];
    snprintf(path, sizeof(path), ".%ssaves", SEPARATEUR);
    d = opendir(path);
    if (d) {
        int row = 0;
        int count = 0;
        char *options[100]; // Tableau pour stocker les noms de fichiers
        mvprintw(ligne + row++, 0, "List de sauvegardes:                                                            ");
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                options[count] = strdup(dir->d_name); // Copier le nom du fichier dans le tableau
                mvprintw((row++) + ligne, 0, "%s", dir->d_name);
                count++;
            }
        }
        int selected = 0;
        int key;
        while (1) {
            attron(A_REVERSE); // Activer l'attribut de surlignage
            mvprintw(ligne + selected + 1, 0, "%s", options[selected]);
            attroff(A_REVERSE); // Désactiver l'attribut de surlignage
            refresh();

            key = getch();
            mvprintw(ligne + selected + 1, 0, "%s", options[selected]); // Clear previous highlight
            switch (key) {
            case KEY_UP:
                selected = (selected - 1 + count) % count;
                break;
            case KEY_DOWN:
                selected = (selected + 1) % count;
                break;
            case 10: // Touche Entrée
                loadSave(grid, options[selected]); // On peut utiliser options[selected] ici
                endwin(); // End ncurses mode
                for (int i = 0; i < count; i++) {
                    free(options[i]); // Libérer la mémoire allouée
                }
                return;
            case 27: // Touche Echap
                endwin(); // End ncurses mode
                for (int i = 0; i < count; i++) {
                    free(options[i]); // Libérer la mémoire allouée
                }
                return;
            }
        }
    } else {
        perror("opendir");
    }
}