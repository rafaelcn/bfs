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

#include "bfs.h"
#include "bfs_tree.h"
#include "bfs_node.h"
#include "bfs_string.h"

BFSTree *bfs_tree_init() {
    BFSTree *root = malloc(sizeof(BFSTree));

    if(root == NULL) {
        return EMPTY_TREE;
    }
    else {
        *root = bfs_create_node(BFS_ROOT_PATH);
    }

    return root;
}

BFSNode bfs_tree_create_node(char fname[BFS_MAX_NAME_LENGHT]) {
    BFSNode *node = (BFSNode*) malloc(sizeof(BFSNode));

    if(node == NULL) {
        return EMPTY_TREE;
    }
    else {
        node->fname = fname;
        node->fcreated = time(NULL);
        node->uid = index;
        
        if(bfs_strchr(fname, ".") != -1) {
            node->fpermissions |= BFS_NODE_IS_FILE;
        }
        else {
            node->fpermissions |= BFS_NODE_IS_DIR;
        }

        node->father = NULL;
        node->next = NULL;
        node->child = NULL;
    }

    index++;

    return node;
}

BFSNode bfs_tree_create_path(BFSTree root, char path[BFS_PATH_SIZE]) {
    if(root == NULL) {
        return EMPTY_TREE;
    }
    
    int i = 1;

    // NULL subtree
    if(root->child == NULL) {        
        BFSNode *walker = root;

        // Create all the nodes of the given path
        while(i < bfs_fcount_delim(path, '/') {
            BFSNode *node = bfs_create_node(bfs_strnsplit(path, '/', i));
            walker->child = node;
            node->father = walker;
            walker = walker->child;
            i++;
        }

        return walker;
    }
    else {
        BFSNode *walker = root->child;

        while(walker->next != NULL && bfs_strnsplit(path, '/', i) != walker->fname) {
            walker = walker->next;                
        }

        while(i < bfs_fcount_delim(path, '/')) {
            if(bfs_strnsplit(path, '/', i) != walker->fname) {
                // The directory doesn't exist, so need to be created first
                BFSNode *node = bfs_create_node(bfs_strnsplit(path, '/', i));
                walker->next = node;
                node->father = walker->father;
            }
            else {
                if(walker->child == NULL) {
                    BFSNode *node = bfs_create_node(bfs_strnsplit(path, '/', i));
                    walker->child = node;
                    node->father = walker;
                }
            }


            i++;
        }
    }
    
    
    while(bfs_strnsplit(path, '/', 1) != walker->fname) && walker->next != NULL){
        walker = walker->next;
    }

    if(walker->next == NULL) {
        
    }
}

int bfs_tree_insert(BFSTree *root, char path[BFS_PATH_SIZE]) {
    if(root == NULL) {
        return 0;
    }
    
    int levels = bfs_fcount_delim(path, '/');

    // Armazena apenas a última parte do caminho dado (nome 
    // da pasta ou arquivo a ser criado).
    char fname[BFS_MAX_NAME_LENGTH] = bfs_strsplit(path, '/', levels);

    BFSNode *father = bfs_tree_create_path(*root, path); // Retorna o pai da sub-árvore onde será inserido o novo nó;
    BFSNode *node = bfs_create_node(fname); 
    
    if(father == NULL) {
        return 0;
    }
    if(father->child == NULL) {
        // Sub-árvore vazia
        father->child = node;
        node->father = father;
    }
    else {
        // Percorre a sub-árvore e insere o novo nó no fim

        BFSNode *walker = father->child;

        while(walker->next != NULL) {
            walker = walker->next;
        }

        walker->next = node;
        node->father = father;
    }

    return 1;
}

int bfs_tree_remove(BFSTree *root, char path[BFS_PATH_SIZE]) {
    
}

BFSNode bfs_tree_search(BFSNode root, char path[BFS_MAX_NAME_LENGTH]) {
    if(root == NULL) {
        return NULL;
    }

    int i = 1, j = 0, levels = 0;
    
    BFSNode *temp = root;

    if(root != NULL) {
        if(bfs_strsplit(path, "/", i) == root->fname) {
            root = root->nodes[0];
        }

        bfs_tree_search(root,path);
    }

    while(temp != NULL && i <= levels) {      
        
        else{
            j = 0;
            
            while(temp->nodes[j] != NULL && j < BFS_MAX_NODES) {
                if(bfs_strsplit(path, "/", i) != temp->nodes[j]->fname) {
                    j++;
                }
                else {
                    break;
                }
            }

            if (bfs_strsplit(path, "/", i) == temp->nodes[j]->fname){
                temp = root->nodes[j];
            }
            else if (j >= BFS_MAX_NODES) {
                // NOT FOUND
            }
            else {
                j++;
                root->nodes[j] = bfs_create_node();
                temp = root->nodes[j];
            }

        }

        i++;
    }

    
}
