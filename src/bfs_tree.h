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

#ifndef BFS_TREE_H
#define BFS_TREE_H

#include "bfs.h"
#include "bfs_node.h"

typedef struct bfs_node *BFSTree;
typedef struct bfs_node  BFSNode;

#define EMPTY_TREE (BFSTree *)0
#define EMPTY_NODE (BFSNode *)0

extern uint32_t bfs_uid_index;

BFSTree *bfs_tree_init();

BFSTree *bfs_tree_insert(BFSTree *root, char path[BFS_PATH_SIZE]);

BFSNode *bfs_tree_create_path(char fname[BFS_MAX_NAME_LENGTH]);

BFSNode *bfs_tree_create_file(char fname[BFS_MAX_NAME_LENGTH]);

int bfs_tree_search(BFSNode *root, char *s);

int bfs_tree_search_child(BFSNode *child, char *s);

BFSNode *bfs_tree_get_child(BFSNode *root, char *s);

int bfs_tree_remove(BFSTree root, char path[BFS_PATH_SIZE]);

void bfs_tree_print(BFSTree root, char *arg);

BFSTree *bfs_tree_free(BFSTree *root);

#endif // BFSTREE_H
