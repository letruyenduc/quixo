#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Grid
{
    int width;
    int height;
    char *content;
} typedef Grid;

Grid *createGrid(int width, int height)
{
    char *gridContent = malloc(sizeof(char) * width * height);
    memset(gridContent, ' ', width * height);
    Grid *grid = malloc(sizeof(Grid));
    grid->width = width;
    grid->height = height;
    grid->content = gridContent;

    return grid;
}

int shiftRowRight(Grid *grid, int row, char player)
{
    int rowPos = row * grid->width;
    char movingBloc = grid->content[rowPos + grid->width - 1];
    if (movingBloc != ' ' && movingBloc != player)
    {
        return 1;
    }

    for (int i = grid->width - 1; i > 0; i--)
    {
        grid->content[rowPos + i] = grid->content[rowPos + i - 1];
    }
    grid->content[rowPos] = player;
    return 0;
}

int shiftRowLeft(Grid *grid, int row, char player)
{
    int rowPos = row * grid->width;
    char movingBloc = grid->content[rowPos];
    if (movingBloc != ' ' && movingBloc != player)
    {
        return 1;
    }

    for (int i = 1; i < grid->width; i++)
    {
        grid->content[rowPos + i - 1] = grid->content[rowPos + i];
    }
    grid->content[rowPos + grid->width - 1] = player;
    return 0;
}

void freeGrid(Grid *grid)
{
    free(grid->content);
    free(grid);
}

void printGrid(Grid *grid)
{
    for (int j = 0; j < grid->width + 2; j++)
    {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < grid->height; i++)
    {
        printf("|");
        for (int j = 0; j < grid->width; j++)
        {
            printf("%c", grid->content[i * grid->width + j]);
        }
        printf("|\n");
    }
    for (int j = 0; j < grid->width + 2; j++)
    {
        printf("-");
    }
    printf("\n");
}