#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


tr_node* TreeCtor(const tr_elem_t root_data) {
    tr_node* tree_root = (tr_node *) calloc(1, sizeof(tr_node));

    ASSIGN_DATA(tree_root, root_data);

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

    ASSIGN_DATA(left_node, left_data);
    ASSIGN_DATA(right_node, tree_node->data);

    ASSIGN_DATA(tree_node, parent_data);

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

    ASSIGN_DATA(left_node, tree_node->data);
    ASSIGN_DATA(right_node, right_data);

    ASSIGN_DATA(tree_node, parent_data);

    return 0;
}


int TreeAddLeft(tr_node *tree_node, const tr_elem_t data) {
    assert(tree_node);
    if (tree_node->left != NULL) {OUTPUT_ERROR("Pointer to left node exists and equals %p\n", tree_node->left);}

    tr_node *left_node = (tr_node *) calloc(1, sizeof(tr_node));

    tree_node->left = left_node;
    left_node->parent = tree_node;
    ASSIGN_DATA(left_node, data);

    return 0;
}

int TreeAddRight(tr_node *tree_node, const tr_elem_t data) {
    assert(tree_node);
    if (tree_node->right != NULL) {OUTPUT_ERROR("Pointer to right node exists and equals %p\n", tree_node->right);}

    tr_node *right_node = (tr_node *) calloc(1, sizeof(tr_node));

    tree_node->right = right_node;
    right_node->parent = tree_node;
    ASSIGN_DATA(right_node, data);

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

void TreeDump(const tr_node *tree_root, FILE *fp) {
    assert(tree_root); assert(fp);

    DumpNode(tree_root, fp);

    fprintf(fp, "\n");
}


int WriteTreeInFile(const tr_node *tree_root, const char* filename) {
    assert(tree_root); assert(filename);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {OUTPUT_ERROR("Can't open file %s\n", filename);}

    TreeDump(tree_root, fp);

    fclose(fp);

    return 0;
}


static int ParseNumNodeFromFile(tr_node *node, FILE *fp) {
    assert(node); assert(fp);

    if (fscanf(fp, PRINT_ELEM, node->data) == EOF) {
        OUTPUT_ERROR("Can't scan data: node->data = " PRINT_ELEM "\n", node->data);
    }

    int brac = getc(fp);
    if (brac == '(') {
        node->left = (tr_node *) calloc(1, sizeof(tr_node));
        if (ParseNumNodeFromFile(node->left, fp)) {return -1;}

        brac = getc(fp);
        if (brac == '(') {
            node->right = (tr_node *) calloc(1, sizeof(tr_node));
            if (ParseNumNodeFromFile(node->right, fp)) {return -1;}
            brac = getc(fp);
        }
        if (brac != ')') {OUTPUT_ERROR("Got wrong symbol: %c\n", brac);}
        return 0;
    } else if (brac == ')') {
        return 0;
    } else {OUTPUT_ERROR("Got wrong symbol: %c\n", brac);}
}


tr_node * ParseNumTreeFromFile(const char* filename) {
    assert(filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {fprintf(stderr, "Can't open file %s\n", filename); return NULL;}

    tr_node *tree_root = (tr_node *) calloc(1, sizeof(tr_node));

    getc(fp);

    if (ParseNumNodeFromFile(tree_root, fp)) {return NULL;}

    return tree_root;
}


#include <ctype.h>
static int ParseStrNodeFromFile(tr_node *node, FILE *fp) {
    assert(node); assert(fp);

    int symb = 0;
    int i = 0;
    while (i < (MAX_DATA_LENGTH - 1)) {
        symb = getc(fp);
        if (symb == '(' || symb == ')') {
            break;
        }
        if (!isalpha(symb) && symb != '_') { OUTPUT_ERROR("Got wrong symbol with code: %d\n", symb); }
        node->data[i] = (char) symb;
        i++;
    }

    if (symb == '(') {
        node->left = (tr_node *) calloc(1, sizeof(tr_node));
        if (ParseStrNodeFromFile(node->left, fp)) {return -1;}

        symb = getc(fp);
        if (symb == '(') {
            node->right = (tr_node *) calloc(1, sizeof(tr_node));
            if (ParseStrNodeFromFile(node->right, fp)) {return -1;}
            symb = getc(fp);
        }
        if (symb != ')') {OUTPUT_ERROR("Got wrong symbol: %c\n", symb);}
        return 0;
    } else {
        assert(symb == ')');
        return 0;
    }
}


static void GenParents(tr_node *node, tr_node *parent) {
    assert(node);

    node->parent = parent;

    if (node->left) {
        GenParents(node->left, node);
    }
    if (node->right) {
        GenParents(node->right, node);
    }
}

tr_node * ParseStrTreeFromFile(const char* filename) {
    assert(filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {fprintf(stderr, "Can't open file %s\n", filename); return NULL;}

    tr_node *tree_root = (tr_node *) calloc(1, sizeof(tr_node));

    getc(fp);

    if (ParseStrNodeFromFile(tree_root, fp)) {return NULL;}

    GenParents(tree_root, 0);

    return tree_root;
}
