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

#include <time.h>
#include <string.h>

#include "bfs.h"
#include "bfs_tree.h"
#include "bfs_errors.h"
#include "bfs_node.h"
#include "bfs_string.h"
#include "bfs_errors.h"

uint32_t bfs_uid_index = 0;

BFSTree *bfs_tree_init() {
    BFSTree *root = malloc(sizeof(BFSTree));

    if(root == NULL) {
        return EMPTY_TREE;
    }
    else {
        *root = bfs_tree_create_node(BFS_ROOT_PATH);
    }

    return root;
}

BFSNode *bfs_tree_create_node(char fname[BFS_MAX_NAME_LENGTH]) {
    BFSNode *node = (BFSNode*) malloc(sizeof(BFSNode));

    if(node == NULL) {
        bfs_pferror(stderr, "Node allocation failed", __LINE__, __FILE__,
                    BFS_CRITICAL);
        exit(EXIT_FAILURE);
    }

    else {
        strcpy(node->fname, fname);
        node->fcreated = time(NULL);
        node->fmodified = time(NULL);
        node->uid = bfs_uid_index;

        if(bfs_strchr(fname, '.') != -1) {
            node->fpermissions |= BFS_NODE_IS_FILE;
        }
        else {
            node->fpermissions |= BFS_NODE_IS_DIR;
        }

        node->father = NULL;
        node->next = NULL;
        node->child = NULL;
    }

    bfs_uid_index++;

    return node;
}

BFSNode *bfs_tree_create_path(BFSTree root, char path[BFS_PATH_SIZE]) {
    if(root == NULL) {
        return EMPTY_NODE;
    }
    
    char fname[BFS_MAX_NAME_LENGTH] = "";
    char next_path[BFS_PATH_SIZE] = "";

    if(bfs_count_delim(path, '/') < 2) {
        return root;
    }
    else {
        int j = 1;

        // Get the name of directory in evidence.
        strcat(fname, bfs_strsplit(path, "/", j));

        for(j = 2; j <= bfs_count_delim(path, '/'); j++) {
            if(j > 2 && j <= bfs_count_delim(path, '/')) {
                // Adds slashes between strings
                strcat(next_path, "/");            
            }

            // Starting in the 2-th string, concatenates the remain directories
            // in the new_path string.
            strcat(next_path, bfs_strsplit(path, "/", j));
        }
    }

    if(root->child == NULL) {           
        // Empty subtree

        BFSNode *node = bfs_tree_create_node(fname);

        if(node == NULL) {
            return EMPTY_NODE;
        }
        else {
            // Connects the new directory to its father.
            root->child = node;
            node->father = root;

            // Continues the search within the new directory.
            bfs_tree_create_path(node, next_path);
        }
    }
    else {
        // Enter the subtree
        root = root->child;

        while(root->next != NULL && root->fname != fname) {
            // Searches for a brother whose name's equal fname
            root = root->next;
        }

        if(root->fname == fname) {
            // Founded directory
            bfs_tree_create_path(root, next_path);
        }
        else {
            // Directory not found, it must be created first
            BFSNode *node = bfs_tree_create_node(fname);

            if(node == NULL) {
                return EMPTY_NODE;
            }
            else {
                // Connects the new directory to it's parent and left brother.
                root->next = node;
                node->father = root->father;

                // Continues the search within the new directory.
                bfs_tree_create_path(node, next_path);
            }
        }

    }
}

int bfs_tree_insert(BFSTree *root, char path[BFS_PATH_SIZE]) {
    if(root == NULL) {
        return 0;
    }

    int levels = bfs_count_delim(path, '/');

    char fname[BFS_MAX_NAME_LENGTH];
    strcpy(fname, bfs_strsplit(path, "/", levels));

    // Returns the father of the subtree where the new node will be inserted
    BFSNode *father = bfs_tree_create_path(*root, path);
    BFSNode *node = bfs_tree_create_node(fname);

    if (father == NULL) {
        return 0;
    }

    if (father->child == NULL) {
        // Empty sub-tree
        father->child = node;
        node->father = father;
    } else {
        // Walks the sub-tree and inserts the new node on the end

        BFSNode *walker = father->child;

        while(walker->next != NULL) {
            walker = walker->next;
        }

        walker->next = node;
        node->father = father;
    }

    return 1;
}

int bfs_tree_remove(BFSTree root, char path[BFS_PATH_SIZE]) {
    if (root == NULL) {
        bfs_pferror(stdout, "File was not found or unable to remove",
                    __LINE__, __FILE__, BFS_WARNING);
        return -1;
    }

    char fmeta[BFS_MAX_NAME_LENGTH];
    strcpy(fmeta, bfs_strsplit(path, "/", 1));


    if (strcmp(root->child->fname, fmeta) == 0) {
        // the node to be removed is the first child.
        // does the child has more childs to be removed?
        // TODO: Improve removal of the child nodes
        free (root->child);
    } else {
        // the node to be removed isn't the first child.
        BFSNode *walker = root->child;
        while (root->child->next != NULL) {

            if (strcmp(walker->fname, fmeta) == 0) {
                break;
            }

            walker = walker->next;
        }

        free(walker);
    }
    return 0;
}

BFSNode *bfs_tree_search(BFSTree root, char path[BFS_PATH_SIZE]) {

}
