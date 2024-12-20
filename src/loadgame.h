#include "structures.h"
#ifndef LOADGAME_H
#define LOADGAME_H

int loadSave(char *filepath, Grid **grid, Player **playerList, int *playerCount);
int listSaves(Save **files, int *count);
int selectSave(Save *files, int filesCount, char **selected_option);
#endif // LOADGAME_H
