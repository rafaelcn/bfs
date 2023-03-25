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
#include "bfs_macros.h"

uint32_t bfs_uid_index = 0;

static int check_pointer(void *p) {
    return p == NULL;
}

BFSTree *bfs_tree_init(void) {
    BFSTree *root = malloc(sizeof(BFSTree));

    if(check_pointer(root)) {
        return EMPTY_TREE;
    }
    else {
        *root = bfs_tree_create_path(BFS_ROOT_PATH);
    }

    return root;
}

BFSTree *bfs_tree_insert(BFSTree *root, char path[BFS_PATH_SIZE]) {
    if(check_pointer(root)) {
        return EMPTY_TREE;
    }
    else if(check_pointer(*root)) {
        // Even though the empty tree macro is being returned here,
        // it is actually an empty node.
        return EMPTY_TREE;
    }



    int i, levels = bfs_count_delim(path, '/');

    char fstring[BFS_MAX_NAME_LENGTH];

    BFSNode *walker = *root;

    // Walks through the tree looking for the path and creates if necessary.
    for(i = 1; i <= levels; i++) {
        strcpy(fstring, bfs_strsplit(path, "/", i));

        if(bfs_tree_search_child(walker->child, fstring)) {
            if(bfs_strchr(fstring, '.') == -1) {
                // The path already exist, so it's not needed to create

                walker = bfs_tree_get_child(walker, fstring);
            }
            else {
                bfs_pferror(stderr, "There's already a file with the \
same given name.", __LINE__, __FILE__,
                            BFS_WARNING);
            }
        }
        else {
            // The path doesn't exist

            BFSNode *node;

            if(walker->child != NULL) {
                walker = walker->child;

                while(walker->next != NULL) {
                    walker = walker->next;
                }

                if(bfs_strchr(fstring, '.') == -1) {
                    node = bfs_tree_create_path(fstring);
                }
                else {
                    node = bfs_tree_create_file(fstring);
                }

                walker->next = node;
                node->father = walker->father;
            }
            else {
                if(bfs_strchr(fstring, '.') == -1) {
                    node = bfs_tree_create_path(fstring);
                }
                else {
                    node = bfs_tree_create_file(fstring);
                }

                walker->child = node;
                node->father = walker;
            }
            walker = bfs_tree_get_child(walker, fstring);
        }
    }

    return root;
}

BFSNode *bfs_tree_create_path(char *fname) {
    if (strlen(fname) > BFS_MAX_NAME_LENGTH) {
        bfs_pferror(stderr,
                    "filename bigger than max name length",
                    __LINE__,
                    __FILE__,
                    BFS_CRITICAL);
        exit(EXIT_FAILURE);
    }

    BFSNode *node = (BFSNode*) malloc(sizeof(BFSNode));

    if(check_pointer(node)) {
        bfs_pferror(stderr, "Node allocation failed", __LINE__, __FILE__,
                    BFS_CRITICAL);
        exit(EXIT_FAILURE);
    }

    else {
        strcpy(node->fname, fname);
        node->fcreated = time(NULL);
        node->fmodified = time(NULL);
        node->uid = bfs_uid_index;
        node->fpermissions |= BFS_NODE_IS_DIR;
        node->father = NULL;
        node->next = NULL;
        node->child = NULL;
    }

    bfs_uid_index++;

    return node;
}

BFSNode *bfs_tree_create_file(char *fname) {
    if (strlen(fname) > BFS_MAX_NAME_LENGTH) {
        bfs_pferror(stderr,
                    "filename bigger than max name length",
                    __LINE__,
                    __FILE__,
                    BFS_CRITICAL);
        exit(EXIT_FAILURE);
    }

    BFSNode *node = (BFSNode*) malloc(sizeof(BFSNode));

    if(check_pointer(node)) {
        bfs_pferror(stderr, "Node allocation failed", __LINE__, __FILE__,
                    BFS_CRITICAL);
        exit(EXIT_FAILURE);
    }
    else {
        strcpy(node->fname, fname);
        node->fcreated = time(NULL);
        node->fmodified = time(NULL);
        node->uid = bfs_uid_index;
        node->fpermissions |= BFS_NODE_IS_FILE;
        node->father = NULL;
        node->next = NULL;
        node->child = NULL;
    }

    bfs_uid_index++;

    return node;
}

int bfs_tree_search(BFSNode *root, char *s) {
    if(check_pointer(root)) {
        return 0;
    }

    if(strcmp(root->fname, s) == 0) {
        return 1;
    }

    return bfs_tree_search(root->child, s) + bfs_tree_search(root->next, s);
}

int bfs_tree_search_child(BFSNode *child, char *s) {
    if(check_pointer(child)) {
        return 0;
    }

    if(strcmp(child->fname, s) == 0) {
        return 1;
    }

    return bfs_tree_search_child(child->next, s);
}


BFSNode *bfs_tree_get_child(BFSNode *root, char *s) {
    static BFSNode *child;

    if(check_pointer(root)) {
        return EMPTY_NODE;
    }
    else if(strcmp(root->fname, s) == 0) {
        child = root;
    }
    else {
        bfs_tree_get_child(root->next, s);
        bfs_tree_get_child(root->child, s);
    }

    return child;
}

void bfs_tree_print(BFSTree root, char *arg) {
    if(root == NULL) {
        return;
    }
    else if(root->child == NULL && root->fpermissions == BFS_NODE_IS_DIR) {
        return;
    }

    root = root->child;

    if(arg == NULL) {
        while(root != NULL) {
            if(root->fpermissions == BFS_NODE_IS_DIR) {
                printf("%s%s%s    ", ANSI_COLOR_BLUE, root->fname,
                    ANSI_COLOR_RESET);
            }
            else {
                printf("%s   ", root->fname);
            }

            root = root->next;
        }
        newline;
        return;
    }
    else if(strcmp(arg, "-i") == 0) {
        printf("Type\tName\t\t\tCreated on\n\n");

        while(root != NULL) {
            if(root->fpermissions == BFS_NODE_IS_DIR) {
                printf("-d-\t%s%-20s%s\t%s",
                    ANSI_COLOR_BLUE, root->fname, ANSI_COLOR_RESET,
                    asctime(gmtime(&(root->fcreated))));
            }
            else {
                printf("-f-\t%-20s\t%s", root->fname,
                       asctime(gmtime(&(root->fcreated))));
            }

            root = root->next;
        }
        return;
    }
    else {
        if(strcmp(arg, "-h") != 0) {
            bfs_pferror(stderr, "Invalid argument", __LINE__, __FILE__,
                        BFS_WARNING);
            newline;
        }
        printf("\nAvailable arguments:\n\n");
        printf("    -i\tPrints file informations\n");
        printf("    -h\tPrints this guide\n");
    }

    return;
}

static void bfs_tree_free_nodes(BFSNode *node) {
    if(check_pointer(node)) {
        return;
    }

    bfs_tree_free_nodes(node->child);
    bfs_tree_free_nodes(node->next);

    free(node);

    node = NULL;
}

int bfs_tree_remove(BFSTree root, char path[BFS_PATH_SIZE]) {
    if (root == NULL) {
        bfs_pferror(stdout, "Given argument is invalid",
                    __LINE__, __FILE__, BFS_WARNING);
        return -1;
    }

    char fmeta[BFS_MAX_NAME_LENGTH];
    strcpy(fmeta, bfs_strsplit(path, "/", bfs_count_delim(path, '/')));

    if(bfs_tree_search(root, fmeta)) {
        BFSNode *walker = bfs_tree_get_child(root, fmeta);

        if(walker != walker->father->child) {
            BFSNode *prev = walker->father->child;
            while(prev->next != walker) {
                prev = prev->next;
            }
            prev->next = walker->next;
        }
        else {
            walker->father->child = walker->next;
        }

        bfs_tree_free_nodes(walker->child);

        free(walker);
    }
    else {
        bfs_pferror(stdout, "File was not found or unable to remove",
                    __LINE__, __FILE__, BFS_WARNING);

        newline;
        return -1;
    }
    return 0;
}

BFSTree *bfs_tree_free(BFSTree *root) {
    if(check_pointer(root)) {
        return EMPTY_TREE;
    }

    bfs_tree_free_nodes(*root);

    free(root);

    root = NULL;

    return EMPTY_TREE;
}
