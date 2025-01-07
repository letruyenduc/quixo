#include <stdio.h>
#ifndef UTILS_H
#define UTILS_H

int randInt(int min, int max);
void getLinesLength(wchar_t *str, int *linesCount, int **linesLength);
int maxTab(int *tab, int tabLength);
void mvprintwLinesKnownCount(int line, int col, wchar_t *str, int *messageLinesLength, int messageLineCount);
int mvprintwLines(int line, int col, wchar_t *str);
int strEndsWith(const char *str, const char *suffix);
int maxi(int a, int b);
void clearLine(int line);
int skipLine(FILE *file);
void sortStrings(char **strings, int stringsCount);

#endif // UTILS_H