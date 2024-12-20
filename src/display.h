#ifndef DISPLAY_H
#define DISPLAY_H
int getOffsetLine(Grid *grid);
int getOffsetCol(Grid *grid);
int getTextOffsetCol(Grid *grid);

void displayGrid(Grid *grid, int row, int column, int selectingFunction);
void displayGridAndStatus(Grid *grid, Player *nextPlayer, wchar_t *statusMessage, int row, int column, int selectingFunction);
void handleInput(Grid *grid, Player *nextPlayer, wchar_t *statusMessage, int *row, int *column, int *function);

#endif // DISPLAY_H