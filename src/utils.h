#ifndef UTILS_H
#define UTILS_H

int randInt(int min, int max);
int Lstrlen(wchar_t *s);
void getLinesLength(wchar_t *str, int *linesCount, int **linesLength);
int maxTab(int *tab, int tabLength);
void mvprintwLines(int line, int col, wchar_t *str);

#endif // UTILS_H