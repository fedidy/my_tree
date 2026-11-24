#ifndef TREE_H
#define TREE_H

#define MAX_DATA_LENGTH 128
typedef char tr_elem_t[MAX_DATA_LENGTH];
#define PRINT_ELEM "%s"
#define SCAN_ELEM "%[^()\n]"

//#define ASSIGN_DATA(node, new_data) (node)->data = (new_data)
#define ASSIGN_DATA(node, new_data) strcpy((node)->data, (new_data))

typedef struct _oliver_tree_node {
    tr_elem_t data;
    _oliver_tree_node *left;
    _oliver_tree_node *right;
    _oliver_tree_node *parent;
} tr_node;


#define OUTPUT_ERROR(text, ...)\
fprintf(stderr, "%s:%d:" text, __FILE__, __LINE__ __VA_OPT__(,) __VA_ARGS__); return -1


tr_node* TreeCtor(              const tr_elem_t root_data);
void TreeDtor(                  tr_node *tree_root);

int TreeCmpAdd(                 tr_node *tree_root,         const tr_elem_t data);
int TreeInsertLeft(             tr_node *tree_node,         const tr_elem_t left_data,  const tr_elem_t parent_data);
int TreeInsertRight(            tr_node *tree_node,         const tr_elem_t right_data, const tr_elem_t parent_data);

int TreeAddLeft(                tr_node *tree_node,         const tr_elem_t data);
int TreeAddRight(               tr_node *tree_node,         const tr_elem_t data);

#include <stdio.h>
void TreeDump(                  const tr_node *tree_root,   FILE* fp);

int WriteTreeInFile(            const tr_node *tree_root,   const char* filename);
tr_node * ParseNumTreeFromFile( const char* filename);
tr_node * ParseStrTreeFromFile( const char* filename);

int TreeGenGraphTxt(            const tr_node *tree_root,   const char* filename);
int TreeGenGraphPng(            const tr_node *tree_root,   const char* filename);
int TreeGenGraphSvg(            const tr_node *tree_root,   const char* filename);


#endif
