#include "bfs_screen.h"

#include <stdlib.h>

void bfs_clear_screen(void) {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#elif defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}