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

#ifndef BFS_H
#define BFS_H

#include <stdlib.h>
#include <stdio.h>


/**
 * @brief Holds everything that BFS needs to work properly.
 */
struct bfs_fs {
    // In this version of BFS, it won't use the real FS behind it.
    char *bfs_root_path; /* The path to the physical fs */
    struct bfs_node **bfs_fs; /* File system holder */
};

typedef struct bfs_fs BFSStruct;

BFSStruct *BFS_Global;

/**
 * The BFS graph can only support a depth of 15 levels with at least
 * paths/files with 64 characters.
 */

// Name of the root path under BFS.
#define BFS_ROOT_PATH "/"
// Paths on BFS are limited to 1024 characters.
#define BFS_PATH_SIZE 1024
// Path/File names have a maximum of 64 characters.
#define BFS_MAX_NAME_LENGTH 64
// Determines how many sub nodes can exist on a given node.
#define BFS_MAX_NODES 20


/**
 * @brief
 */
void bfs_init();


/**
 * @brief
 * @param fs
 */
int bfs_load(FILE *fs);

/**
 * @brief
 * @param fs
 */
int  bfs_close(FILE *fs);

/**
 * @brief Count how slash there are in a path string
 */
unsigned int bfs_count_delim(const char *s, const char c);

#endif // BFS_H
