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

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "bfs.h"
#include "bfs_string.h"
#include "bfs_cmdline.h"

int main(int argc, char **argv) {

    FILE *fs = NULL;
    char *fn = "fs.txt";

    if (argc > 1) {
        fn = argv[1];

        if (bfs_strncmpl(fn, ".txt", 3) == 1) {
            fprintf(stderr, "VFS describe file has to have a .txt extension");
            return 1;
        }
    }

    fs = fopen(fn, "r");

    if (fs == NULL) {
        char err[255];
        sprintf(err, "Failed to read file %s", fn);
        perror(err);

        exit(EXIT_FAILURE);
    }

    // Initializes the structure of the filesystem.
    bfs_init();
    // Load filesystem into memory.
    // Current layout of the filesystem is still being discussed.
    bfs_load(fs);

    bfs_cmdline_start(BFS_Global->bfs_fs);

    bfs_close(fs);

    return EXIT_SUCCESS;
}
