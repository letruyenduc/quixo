#include "grid.h"
#ifndef SAVE_H
#define SAVE_H

int save_grid(Grid *grid, Player *playerList[], int playerCount);
int createSavesDirectory();
void deleteSave(Player *playerList[], int playerCount);
#endif // SAVE_H