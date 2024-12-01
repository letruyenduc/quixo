#ifndef DISPLAY_H
#define DISPLAY_H

void displayGrid(Grid *grid, char nextPlayer, wchar_t *statusMessage);
void handleInput(Grid *grid, int *row, int *column, int *function);
#endif // DISPLAY_H