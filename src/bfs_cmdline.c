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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bfs_errors.h"
#include "bfs_cmdline.h"
#include "utils/bfs_screen.h"


#define newline printf("\n");

void cmdline_start(BFSTree *root) {
    bfs_clear_screen();

    printf("BFS - Branch Filesystem 0.0.1\n");
    printf("Copyright © 2017 UTFPR SH\n");
    printf("License: MIT License <https://opensource.org/licenses/MIT> \n");
    printf("This is a free open-source software.\n");
    printf("THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND.\n");
    printf("\nType \"help\" to see the available commands.\n");
    newline

    BFSTree *btree = root;

    while (1) {
        char option[CMDLINE_READ_BUFFER];

        printf(">>> ");
        fgets(option, CMDLINE_READ_BUFFER, stdin);

        // TODO: Some of the options needs to verify whether the directory is
        // valid or not. I think it can be done with the search function.

        if (strncmp(option, "cd", 2) == 0) {
            if (option[3] == '\0'){
                bfs_pferror(stderr, "Given directory is invalid", __LINE__,
                    __FILE__, BFS_WARNING);
                newline
            }
            else {
                newline
                char dir[CMDLINE_READ_BUFFER-2];
                int i;
                int j = 0;

                for (i = 3; i < CMDLINE_READ_BUFFER; i++) {
                    if (option[i] != '\n'){
                        dir[j] = option[i];
                        j++;
                    }
                }

                // btree = bfs_tree_get_dir(btree, dir);

                printf("Entered into: /%s.\n", dir);
            }
            newline
        }
        else if (strncmp(option, "search", 5) == 0) {

            if (option[7] == '\0') {
                bfs_pferror(stderr, "Given argument is invalid", __LINE__,
                    __FILE__, BFS_WARNING);
                newline
            }
            else {
                newline

                char arg[CMDLINE_READ_BUFFER-5];
                int i;
                int j = 0;

                for(i = 7; i < CMDLINE_READ_BUFFER; i++) {
                    if(option[i] != '\n'){
                        arg[j] = option[i];
                        j++;
                    }
                }

                // printf("Founded on: %s", bfs_tree_search(root,arg));
                printf("Searching the \"%s\" file/folder.\n", arg);
            }

            newline
        }
        else if (strncmp(option, "rm", 2) == 0) {
            if (option[3] == '\0') {
                bfs_pferror(stderr, "Given directory is invalid", __LINE__,
                    __FILE__, BFS_WARNING);
                newline
            }
            else {
                newline

                char dir[CMDLINE_READ_BUFFER-2];
                int i;
                int j = 0;

                for (i = 3; i < CMDLINE_READ_BUFFER; i++) {
                    if (option[i] != '\n'){
                        dir[j] = option[i];
                        j++;
                    }
                }

                // bfs_tree_remove(btree,dir);
                printf("Removing \"%s\" folder and its content.\n", dir);
            }

            newline
        }
        else if (strncmp(option, "list", 4) == 0) {
            newline

            // bfs_tree_print(btree,arg);
            // TODO: Print in a table way, like ls

            newline
        }
        else if (strncmp(option, "mkdir", 5) == 0) {
            if (option[6] == '\0') {
                bfs_pferror(stderr, "Given argument is invalid", __LINE__,
                    __FILE__, BFS_WARNING);
                newline
            }
            else {
                newline
                char arg[CMDLINE_READ_BUFFER-6];
                int i;
                int j = 0;

                for (i = 6; i < CMDLINE_READ_BUFFER; i++) {
                    if (option[i] != '\n'){
                        arg[j] = option[i];
                        j++;
                    }
                }

                // bfs_tree_insert(btree,arg);
                printf("Node %s created.\n", arg);

            }

            newline
        }
        else if (strncmp(option, "clear", 5) == 0) {
            bfs_clear_screen();
        }
        else if (strncmp(option, "help", 4) == 0) {
            newline
            printf("This is the Branch Filesystem command line. Usage:\n");
            newline
            printf("\t[option]\n\t[option] <arg>\n\t[option] <dir>\n");
            newline
            printf("Available options:");
            newline
            printf("\n - cd <dir>\t\tChange the command line working\
            \n\t\t\tdirectory.");
            printf("\n - search <arg>\t\tSearches for a file or folder whose\
            \n\t\t\tname is the same as the given argument.");
            printf("\n - rm <dir>\t\tRemoves recursively a folder and its\
            \n\t\t\tcontent.");
            printf("\n - list\t\t\tPrints everything inside the current folder.");
            printf("\n - mkdir <arg>\t\tCreates a new folder in the current\
            \n\t\t\tdirectory with the given argument as the name.");
            printf("\n - clear\t\tClears the current screen.");
            printf("\n - help\t\t\tDisplay this help.");
            printf("\n - exit\t\t\tQuits the BFS command line.\n");
            newline
        }
        else if (strncmp(option, "exit", 4) == 0 ||
                 strncmp(option, "quit", 4) == 0) {
            break;
        }
    }
}
