#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "tree.h"


tr_node* TreeCtor(const tr_elem_t root_data) {
    tr_node* tree_root = (tr_node *) calloc(1, sizeof(tr_node));

    tree_root->data = root_data;

    return tree_root;
}

//void TreeDtor(tr_node *tree_root);


static int TreeCmpInsert(tr_node *node, const tr_elem_t data) {
    assert(!node->left); assert(!node->right);

    if (data < node->data) {
        return TreeInsertLeft(node, data, node->data);
    }
    return TreeInsertRight(node, data, node->data);
}

int TreeCmpAdd(tr_node *tree_root, const tr_elem_t data) {
    assert(tree_root);

    tr_node *node = tree_root;

    while (node->left != NULL || node->right != NULL) {
        if (data < node->data) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    TreeCmpInsert(node, data);

    return 0;
}


int TreeInsertLeft(tr_node *tree_node, const tr_elem_t left_data, const tr_elem_t parent_data) {
    assert(tree_node);
    if (tree_node->left != NULL) {OUTPUT_ERROR("Pointer to left node exists and equals %p\n", tree_node->left);}
    if (tree_node->right != NULL) {OUTPUT_ERROR("Pointer to right node exists and equals %p\n", tree_node->right);}

    tr_node *left_node = (tr_node *) calloc(1, sizeof(tr_node));
    tr_node *right_node = (tr_node *) calloc(1, sizeof(tr_node));

    tree_node->left = left_node;
    tree_node->right = right_node;

    left_node->parent = tree_node;
    right_node->parent = tree_node;

    left_node->data = left_data;
    right_node->data = tree_node->data;

    tree_node->data = parent_data;

    return 0;
}

int TreeInsertRight(tr_node *tree_node, const tr_elem_t right_data, const tr_elem_t parent_data) {
    assert(tree_node);
    if (tree_node->left != NULL) {OUTPUT_ERROR("Pointer to left node exists and equals %p\n", tree_node->left);}
    if (tree_node->right != NULL) {OUTPUT_ERROR("Pointer to right node exists and equals %p\n", tree_node->right);}

    tr_node *left_node = (tr_node *) calloc(1, sizeof(tr_node));
    tr_node *right_node = (tr_node *) calloc(1, sizeof(tr_node));

    tree_node->left = left_node;
    tree_node->right = right_node;

    left_node->parent = tree_node;
    right_node->parent = tree_node;

    left_node->data = tree_node->data;
    right_node->data = right_data;

    tree_node->data = parent_data;

    return 0;
}


static void DumpNode(const tr_node *node, FILE *fp) {
    assert(node); assert(fp);

    if (node->left == NULL || node->right == NULL) {
        fprintf(fp, "(" PRINT_ELEM ")", node->data);
        return;
    }

    fprintf(fp, "(" PRINT_ELEM, node->data);
    DumpNode(node->left, fp);
    DumpNode(node->right, fp);
    fprintf(fp, ")");
}

void TreeDump(const tr_node *tree_root, FILE* fp) {
    assert(tree_root); assert(fp);

    DumpNode(tree_root, fp);

    fprintf(fp, "\n");
}


//int WriteTreeInFile(tr_node *tree_root, consst char* filename);
