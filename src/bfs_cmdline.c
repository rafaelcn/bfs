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

#include "bfs.h"
#include "bfs_errors.h"
#include "bfs_string.h"
#include "bfs_cmdline.h"
#include "utils/bfs_screen.h"

#define newline printf("\n")

void cmdline_start(BFSTree *root) {
    bfs_clear_screen();

    printf("BFS - Branch Filesystem 0.0.1\n");
    printf("Copyright © 2017 UTFPR SH\n");
    printf("License: MIT License <https://opensource.org/licenses/MIT> \n");
    printf("This is a free open-source software.\n");
    printf("THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND.\n");
    printf("\nType \"help\" to see the available commands.\n");
    newline;

    BFSTree bfs_tree = *root;
    char root_path[BFS_PATH_SIZE] = "";
    
    strcat(root_path, bfs_tree->fname);

    while (1) {
        char option[CMDLINE_READ_BUFFER];

        printf(">>> %s:  ", root_path);
        
        fgets(option, CMDLINE_READ_BUFFER, stdin);

        if (strncmp(option, "cd", 2) == 0) {
            if (option[3] == '\0'){
                bfs_tree = *root;
                strcpy(root_path, bfs_tree->fname);
            }
            else {
                char dir[CMDLINE_READ_BUFFER-2];
                
                int i = 3;
                int j = 0;

                while(option[i] != '\0') {
                    if(option[i] == '\n') {
                        break;
                    }
                    dir[j] = option[i];
                    i++;
                    j++;
                }

                dir[j] = '\0';

                if(strcmp(dir,"..") == 0) {
                    if(bfs_tree->father != NULL) {
                        bfs_tree = bfs_tree->father;

                        int levels = bfs_count_delim(root_path, '/');
                        
                        char tmp[BFS_PATH_SIZE];

                        strcpy(tmp, (*root)->fname);

                        for(i = 2; i < levels; i++) {
                            if(strcmp(tmp, "/") != 0) {
                                strcat(tmp, "/");
                            }
                            strcat(tmp, bfs_strsplit(root_path, "/", i));
                        }

                        strcpy(root_path, tmp);
                    }
                }
                else if(bfs_tree_search_child(bfs_tree->child, dir)) {
                    bfs_tree = bfs_tree_get_child(bfs_tree, dir);

                    if(bfs_tree->fpermissions == BFS_NODE_IS_DIR) {
                        if(strcmp(bfs_tree->father->fname,"/") != 0) {
                            strcat(root_path, "/");                    
                        }

                        strcat(root_path, bfs_tree->fname);
                    }
                    else {
                        bfs_pferror(stderr, "Not a directory", __LINE__, __FILE__,
                                BFS_WARNING);

                        newline;
                        bfs_tree = bfs_tree->father;
                    }
                }
                else {
                    bfs_pferror(stderr, "Couldn't find the directory", __LINE__,
                        __FILE__, BFS_LOG);
                    newline;
                }
            }

            newline;
        }
        else if (strncmp(option, "search", 6) == 0) {
            if (option[7] == '\0') {
                bfs_pferror(stderr, "Given argument is invalid", __LINE__,
                    __FILE__, BFS_WARNING);
                newline;
            }
            else {

                char arg[CMDLINE_READ_BUFFER-5];
                int i;
                int j = 0;

                for(i = 7; i < CMDLINE_READ_BUFFER; i++) {
                    if(option[i] != '\n'){
                        arg[j] = option[i];
                        j++;
                    }
                }

                if(bfs_tree_search(bfs_tree, arg)) {
                    newline;
                    BFSNode *tmp = bfs_tree_get_child(bfs_tree, arg);
                    
                    char arg_path[BFS_MAX_NODES][BFS_MAX_NAME_LENGTH]; 

                    i = 0;
                        
                    while(tmp->father != NULL) {
                        strcpy(arg_path[i], tmp->fname);
                        tmp = tmp->father;
                        i++;
                    }

                    char p[BFS_PATH_SIZE];

                    strcpy(p, "/");
                    for(i--; i >= 0; i--) {
                        if(strcmp(p,arg_path[i]) != 0) {
                            strcat(p,arg_path[i]);
                        }
                        if(i > 0) {
                            strcat(p, "/");                    
                        }
                    }

                    printf("Directory: %s\n", p);

                }
                else {
                    bfs_pferror(stderr, "Couldn't find the given argument", __LINE__,
                        __FILE__, BFS_LOG);
                    newline;
                }
            }

            newline;
        }
        else if (strncmp(option, "rm", 2) == 0) {
            if (option[3] == '\0') {
                bfs_pferror(stderr, "Given directory is invalid", __LINE__,
                    __FILE__, BFS_WARNING);
                newline;
            }
            else {
                char dir[CMDLINE_READ_BUFFER-2];
                int i;
                int j = 0;

                for (i = 3; i < CMDLINE_READ_BUFFER; i++) {
                    if (option[i] != '\n'){
                        dir[j] = option[i];
                        j++;
                    }
                }

                bfs_tree_remove(bfs_tree, dir);
            }

            newline;
        }
        else if(strncmp(option, "l", 1) == 0) {
            if(strncmp(option, "list", 4) == 0) {
                if(option[5] != '\0') {
                    char arg[2];
                    int i;
                    int j = 0;

                    for (i = 5; i < 9; i++) {
                        if (option[i] != '\n'){
                            arg[j] = option[i];
                            j++;
                        }
                    }

                    bfs_tree_print(bfs_tree, arg);
                }
                else {
                    bfs_tree_print(bfs_tree, NULL);
                }

                newline;
            }
            else if (strncmp(option, "ls", 2) == 0) {
                if(option[3] != '\0') {
                    char arg[2];
                    int i;
                    int j = 0;

                    for (i = 3; i < 7; i++) {
                        if (option[i] != '\n'){
                            arg[j] = option[i];
                            j++;
                        }
                    }

                    bfs_tree_print(bfs_tree, arg);
                }
                else {
                    bfs_tree_print(bfs_tree, NULL);
                }

                newline;
            }
        }
        else if (strncmp(option, "mkdir", 5) == 0) {
            if (option[6] == '\0') {
                bfs_pferror(stderr, "Given argument is invalid", __LINE__,
                    __FILE__, BFS_WARNING);
                newline;
            }
            else {
                char arg[CMDLINE_READ_BUFFER-6];
                int i;
                int j = 0;

                for (i = 6; i < CMDLINE_READ_BUFFER; i++) {
                    if (option[i] != '\n'){
                        arg[j] = option[i];
                        j++;
                    }
                }

                arg[j] = '\0';

                if(bfs_strchr(arg, '.') == -1) {  
                    bfs_tree_insert(&bfs_tree, arg);
                }
                else {
                    bfs_pferror(stderr, "mkdir command does not create files", 
                                __LINE__, __FILE__, BFS_WARNING);
                    newline;
                }
            }
            
            newline;
        }
        else if (strncmp(option, "clear", 5) == 0) {
            bfs_clear_screen();
        }
        else if (strncmp(option, "help", 4) == 0) {
            newline;
            printf("This is the Branch Filesystem command line. Usage:\n");
            newline;
            printf("\t[option]\n\t[option] <arg>\n\t[option] <dir>\n");
            newline;
            printf("Available options:");
            newline;
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
            newline;
        }
        else if (strncmp(option, "exit", 4) == 0 ||
                 strncmp(option, "quit", 4) == 0) {
            break;
        } else if (strncmp(option , "\n", 1) != 0) {
            char ebuffer[BFS_MAX_ERROR_LENGTH];
            // FIXME: Fix size of the option buffer
            sprintf(ebuffer, "Given command \"%s\" is invalid", option);

            // bfs_pferror(stderr, ebuffer, __LINE__, __FILE__, BFS_WARNING);
        }
    }

    bfs_tree_free(root);
}
