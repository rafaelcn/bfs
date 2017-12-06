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

#ifndef BFS_NODE_H
#define BFS_NODE_H

#include <time.h>
#include <stdint.h>

#include "bfs.h"

/**
 * A node representing a either a file of a path link to a file.
 */
struct bfs_node {
    char     fname[BFS_MAX_NAME_LENGTH]; /* The name of the given node */
    time_t   fcreated;                   /* What time the node was created */
    time_t   fmodifed;                   /* What time the node was modified */
    uint32_t uid;                        /* The current Unique Identifier */
    uint32_t fpermissions;           /* Permissions for the current node */

    struct bfs_node *father;
    struct bfs_node *nodes[BFS_MAX_NODES];
};


/**
 * Permission bits is just a 32 unsigned integer that contains the following
 * structure:
 *
 * 00000000 00000000 00000000 00000000
 *
 * The first byte group from right to left identifies if it's a directory
 * or not and can be represented by 0xFF. From that, the second byte ~nibble~
 * represent if it is a file or not, though not necessary it is present in
 * this project.
 *
 * Remaining bits would be used to identify the owner of the file inside BFS.
 */

#define BFS_NODE_IS_DIR  0xFF000000
#define BFS_NODE_IS_FILE 0x00F00000

#endif // BFS_NODE_H
