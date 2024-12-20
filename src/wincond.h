#ifndef WINCON_H
#define WINCON_H
int winCondHorizontal(Grid *grid, Player *player);
int winCondVertical(Grid *grid, Player *player);
int winCondDiagonal(Grid *grid, Player *player);
int winCondPlayer(Grid *grid, Player *player);
Player *winCond(Grid *grid, Player *playerList, int playerCount);
#endif // WINCON_H