#include "grid.h"
#ifndef LOADGAME_H
#define LOADGAME_H

typedef struct
{
    char *saveName;
    char *filePath;
} Save;

int loadSave(char *filepath, Grid** grid, char** playerList, int* playerCount);
int listSaves(Save **files, int *count);
int selectSave(Save *files, int filesCount, char **selected_option);
#endif // LOADGAME_H
