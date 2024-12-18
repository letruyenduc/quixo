#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include <string.h>
#include <dirent.h> // For DIR, struct dirent, opendir, readdir, closedir
#include "grid.h"
#include "save.h"
#ifdef _WIN32
#include <direct.h> // Pour _mkdir sur Windows
#define SEPARATEUR "\\"
#define mkdir _mkdir // Alias pour uniformiser les appels
#else
#include <sys/stat.h> // Pour mkdir sur Linux/macOS
#define SEPARATEUR "/"
#endif
#define ligne 10
#define MAX_PATH_LENGTH 256

/*
 * Auteur : Duc et Kevin
 * Description : Charger la grille depuis un fichier
 * Paramètres :
 * - filename : Le nom du fichier de sauvegarde
 * Retour :
 * - La grille chargée
 */
Grid *loadSave(char *filename) {
    char filepath[MAX_PATH_LENGTH];
    snprintf(filepath, sizeof(filepath), ".%ssaves%s%s", SEPARATEUR, SEPARATEUR, filename);

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    int width, height;
    if (fscanf(file, "%d %d\n", &width, &height) != 2) {
        perror("Erreur lors de la lecture des dimensions de la grille");
        fclose(file);
        return NULL;
    }

    Grid *grid = createGrid(width, height);
    if (grid == NULL) {
        perror("Erreur lors de la création de la grille");
        fclose(file);
        return NULL;
    }

    char line[MAX_PATH_LENGTH];
    for (int i = 0; i < height; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            for (int j = 0; j < width; j++) {
                if (j < strlen(line) && line[j] != '\n') {
                    grid->rows[i][j] = line[j];
                } 
                else {
                    grid->rows[i][j] = ' '; // Remplir avec des espaces si la ligne est trop courte
                }
            }
        } 
        else {
            perror("Erreur lors de la lecture de la grille");
            freeGrid(grid);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return grid;
}

/*
 * Auteur : Duc
 * Description : Affiche la liste des sauvegardes et permet de charger une sauvegarde
 * Paramètres :
 * - Aucun
 * Retour :
 * - Le nom du fichier de sauvegarde sélectionné
 */
char *list_saves(char **selected_option)
{
    Grid *grid;
    DIR *d;
    struct dirent *dir;
    char path[256];
    snprintf(path, sizeof(path), ".%ssaves", SEPARATEUR);
    d = opendir(path);
    if (d)
    {
        int row = 0;
        int count = 0;
        char *options[100]; // Tableau pour stocker les noms de fichiers
        mvprintw(ligne + row++, 0, "Liste de sauvegarde:                                                            ");
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                options[count] = strdup(dir->d_name); // Copier le nom du fichier dans le tableau
                mvprintw((row++) + ligne, 0, "%s", dir->d_name);
                count++;
            }
        }
        if (count == 0)
        {
            refresh();
            getch();
            return NULL;
        }
        int selected = 0;
        int key;
        while (1)
        {
            attron(A_REVERSE); // Activer l'attribut de surlignage
            mvprintw(ligne + selected + 1, 0, "%s", options[selected]);
            attroff(A_REVERSE); // Désactiver l'attribut de surlignage
            refresh();

            key = getch();
            mvprintw(ligne + selected + 1, 0, "%s", options[selected]);
            switch (key)
            {
            case KEY_UP:
                selected = (selected - 1 + count) % count;
                break;
            case KEY_DOWN:
                selected = (selected + 1) % count;
                break;
            case 10:      // Touche Entrée
                refresh(); // Rafraîchir l'écran
                *selected_option = strdup(options[selected]);
                for (int i = 0; i < count; i++)
                {
                    free(options[i]); // Libérer la mémoire allouée
                }
                closedir(d);
                return *selected_option;
            case 27:      // Touche Echap
                refresh(); // Rafraîchir l'écran
                for (int i = 0; i < count; i++)
                {
                    free(options[i]); // Libérer la mémoire allouée
                }
                closedir(d);
                return NULL;
            }
        }
    }
    else
    {
        return NULL;
    }
}