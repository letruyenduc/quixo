#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main() {
    srand(time(NULL));
    // Définir l'encodage de la console en UTF-8
    SetConsoleOutputCP( CP_UTF8 );

    return 0;
}