#ifndef WINCON_H
#define WINCON_H
int winCondHorizontal(Grid *grid, char player);
int winCondVertical(Grid *grid, char player);
int winCondDiagonal(Grid *grid, char player);
int winCondPlayer(Grid *grid, char player);
char winCond(Grid *grid, char* playerList, int playerCount);
#endif // WINCON_H