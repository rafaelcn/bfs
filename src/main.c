/**
 *                Universidade Tecnológica Federal do Paraná
 *
 * Copyright (c) 2017 Rafael Nunes <rcamposnunes@outlook.com>
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

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "bfs.h"
#include "bfs_print.h"
#include "bfs_string.h"
#include "bfs_cmdline.h"

int main(int argc, char **argv) {

    FILE *fs = NULL;
    char *fn = "fs.txt";

    if (argc > 1) {
        fn = argv[1];

        if (bfs_strncmpl(fn, ".txt", 3) == 1) {
            bfs_pferror(stderr, "VFS (virtual file system) file has to have a .txt extension",
                        __LINE__, __FILE__, BFS_LOG);

            exit(EXIT_FAILURE);
        }
    } else {
        bfs_pferror(stderr, "you have to provide a VFS (virtual file system) file",
                    __LINE__, __FILE__, BFS_LOG);

        exit(EXIT_FAILURE);
    }

    fs = fopen(fn, "r");

    if (fs == NULL) {
        char err[255];
        sprintf(err, "failed to read file %s", fn);

        bfs_pferror(stderr, err, __LINE__, __FILE__, BFS_CRITICAL);

        exit(EXIT_FAILURE);
    }

    // initializes the structure of the filesystem.
    bfs_init();
    // load filesystem into memory.
    // current layout of the filesystem is still being discussed.
    bfs_load(fs);

    bfs_cmdline_start(BFS_Global->bfs_fs);

    bfs_close(fs);

    return EXIT_SUCCESS;
}
