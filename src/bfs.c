/**
 *                Universidade Tecnológica Federal do Paraná
 *
 * Copyright (c) 2017 Rafael Nunes <rafaelnunes@engineer.com>
 * Copyright (c) 2017 Mikael Messias <mikaelmessias@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#include <string.h>

#include "bfs.h"
#include "bfs_string.h"
#include "bfs_errors.h"
#include "bfs_macros.h"
#include "bfs_tree.h"

void bfs_init(BFSStruct *fs) {
    // inits the BFS filesystem.
    BFS_Global = malloc(sizeof(BFS_Global));

    BFS_Global->bfs_fs = bfs_tree_init();
}

int bfs_load(FILE* vfs) {
    if (BFS_Global == NULL) {
        bfs_pferror(stderr, "Initialize the BFS_Global first", __LINE__,
                    __FILE__, BFS_CRITICAL);
        exit(EXIT_FAILURE);
    }

    // List of the paths read;
    // 1MiB of memory to store everything, considering a fs of 1MiB.
    char *plist =  calloc(BFS_PATH_SIZE*BFS_PATH_SIZE, 1);
    // The path string read by the parser
    char path[BFS_PATH_SIZE];

    unsigned int i = 0;

    while (fgets(path, BFS_PATH_SIZE, vfs)) {
        if (strlen(path) > BFS_PATH_SIZE) {
            char error_buffer[BFS_MAX_ERROR_LENGTH];

            sprintf(error_buffer, "Path %s read is to big to load in the BFS",
                    path);

            bfs_pferror(stderr, error_buffer,
                        __LINE__,
                        __FILE__,
                        BFS_PARSER_ERROR);
            exit(EXIT_FAILURE);
        }

        if (i >= BFS_PATH_SIZE) {
            bfs_pferror(stderr, "File is too big to be loaded in the BFS",
                        __LINE__,
                        __FILE__,
                        BFS_PARSER_ERROR);
            exit(EXIT_FAILURE);
        }

        int p = bfs_strchr(path, '\n');
        path[p] = '\0';

        printf("\nCreating node %s...", path);
        bfs_tree_insert(BFS_Global->bfs_fs, path);

        i++;
    }

    printf("\n\n%sFile system ready.\n%s", ANSI_COLOR_GREEN,
           ANSI_COLOR_RESET);

    // Since it is already loaded, now we free the list.
    free(plist);

    return 0;
}


int bfs_close(FILE *fs) {
    return fclose(fs);
}


unsigned int bfs_count_delim(const char *s, const char c) {
    unsigned int n = 0;
    unsigned int i = 0;

    while (i < strlen(s)) {
        if (s[i] == c) {
            n++;
        }
    }

    // There'is n+1 levels of a path with n slash.
    return n+1;
}
