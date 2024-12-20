#include "grid.h"

#ifndef GAME_H
#define GAME_H

// Fonction pour lancer une nouvelle partie
void startNewGame(Player** playerList, int playerCount, int width, int height);
void startGameFromSave(char *saveStatus, wchar_t **statusMessage);

#endif // GAME_H
