#include <ncurses.h>
#include <stdlib.h>
#include "menu.h"





void traiterChoix(int choix) {
    switch (choix) {
        case 1:
            printf("Nouvelle Partie sélectionnée !\n");
            // Ajouter la logique pour démarrer une nouvelle partie
            break;
        case 2:
            printf("Charger une Partie sélectionnée !\n");
            // Ajouter la logique pour charger une partie
            break;
        case 3:
            printf("Options sélectionnées !\n");
            // Ajouter la logique pour afficher les options
            break;
        case 4:
            printf("Merci d'avoir joué. À bientôt !\n");
            exit(0); // Quitte le programme
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            break;
    }
}




// Fonction pour afficher le menu principal
int afficherMenu() {
    const char *options[] = {
        "Nouvelle Partie",
        "Charger une Partie",
        "Options",
        "Quitter"
    };
    int nbOptions = sizeof(options) / sizeof(options[0]);
    int choix = 0; // Index de l'option sélectionnée
    int touche;

    // Initialisation de ncurses
    initscr();
    clear();
    cbreak();
    curs_set(0); // Masque le curseur

    // Activer les touches fléchées
    keypad(stdscr, TRUE);

    // Affichage du menu
    while (1) {
        clear();
        mvprintw(0, 0, "======================================");
        mvprintw(1, 0, "       Bienvenue sur le Quixo !       ");
        mvprintw(2, 0, "======================================");

        // Affichage des options
        for (int i = 0; i < nbOptions; i++) {
            if (i == choix) {
                attron(A_REVERSE); // Surligner l'option sélectionnée
                mvprintw(4 + i, 2, "%s", options[i]); // Ajout de "%s"
                attroff(A_REVERSE);
            } else {
                mvprintw(4 + i, 2, "%s", options[i]); // Ajout de "%s"
            }
        }

        mvprintw(4 + nbOptions + 1, 0, "Utilisez les flèches pour naviguer, Entrée pour valider.");

        // Lecture de l'entrée utilisateur
        touche = getch();

        switch (touche) {
            case KEY_UP:
                choix = (choix - 1 + nbOptions) % nbOptions;
                break;
            case KEY_DOWN:
                choix = (choix + 1) % nbOptions;
                break;
            case '\n': // Touche Entrée
                traiterChoix(choix + 1); // Appelle la fonction de traitement
                return 1;
            default:
                break;
        }
    }
}



