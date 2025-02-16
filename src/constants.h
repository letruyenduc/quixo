#ifndef CONSTANTS_H
#define CONSTANTS_H

#define TURN_STATUS_OK 0
#define TURN_STATUS_OTHER_PLAYER 1
#define TURN_STATUS_INVALID_FUNCTION 2

#define FUNCTION_SHIFT_ROW_RIGHT 0
#define FUNCTION_SHIFT_ROW_LEFT 1
#define FUNCTION_SHIFT_COLUMN_DOWN 2
#define FUNCTION_SHIFT_COLUMN_UP 3
#define FUNCTION_QUIT_GAME 4

#define NO_ERROR 0

#define SELECT_SAVE_QUIT 1

#define LOAD_SAVE_INVALID_CONTENT 1
#define LOAD_SAVE_FILE_ERROR 2

#define CHECK_PLAYER_NAME_OK '\0'
#define CHECK_PLAYER_NAME_EMPTY '\1'

#define COLOR_CYAN_ON_BLACK 1
#define COLOR_RED_ON_BLACK 2
#define PLAYER_COLOR_START 3

#ifdef _WIN32
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif
#define SAVES_DIR "saves"

#endif // CONSTANTS_H