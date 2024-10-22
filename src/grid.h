struct Grid
{
    int width;
    int height;
    char **content;
} typedef Grid;

Grid *createGrid(int width, int height);
int shiftRowRight(Grid *grid, int row, char player);
int shiftRowLeft(Grid *grid, int row, char player);
void freeGrid(Grid *grid);
void printGrid(Grid *grid);