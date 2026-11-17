#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "tree_graph.h"


static void GenNode(const tr_node *node, FILE* gr_file) {
    assert(node); assert(gr_file);

    if (node->left == NULL && node->right == NULL) {
        fprintf(gr_file, "\tnode%ld [ shape = Mrecord; style = filled; fillcolor = \"#ffff00\"; color = \"#0000ff\";\n"
                         "\t\tlabel = \" { data = " PRINT_ELEM " | parent = %p | { left = %p | right = %p } } \"; ]\n",
                         (long) node, node->data, node->parent, node->left, node->right);
    } else if (node->parent == NULL) {
        fprintf(gr_file, "\tnode%ld [ shape = Mrecord; style = filled; fillcolor = \"#0088ff\"; color = \"#ffff00\";\n"
                         "\t\tlabel = \" { data = " PRINT_ELEM " | parent = %p | { left = %p | right = %p } } \"; ]\n",
                         (long) node, node->data, node->parent, node->left, node->right);
    } else {
        fprintf(gr_file, "\tnode%ld [ shape = Mrecord; style = filled; fillcolor = \"#00ff88\"; color = \"#000000\";\n"
                         "\t\tlabel = \" { data = " PRINT_ELEM " | parent = %p | { left = %p | right = %p } } \"; ]\n",
                         (long) node, node->data, node->parent, node->left, node->right);
    }

    if (node->parent != NULL) {
        fprintf(gr_file, "\tnode%ld -> node%ld\n", (long) node->parent, (long) node);
    }

    if (node->left != NULL) {
        GenNode(node->left, gr_file);
    }
    if (node->right != NULL) {
        GenNode(node->right, gr_file);
    }
}


static void GenText(const tr_node *tree_root, FILE* gr_file) {
    assert(tree_root); assert(gr_file);

    fprintf(gr_file, "digraph {\n");
    fprintf(gr_file, "\tedge [ color = \"#ff00ff\"; ]\n");

    GenNode(tree_root, gr_file);

    fprintf(gr_file, "}\n");
}


int TreeGenGraphTxt(const tr_node *tree_root, const char* filename) {
    assert(tree_root); assert(filename);

    size_t len = strlen(filename) + sizeof(".txt");
    char* fullname = (char*) calloc(len, sizeof(char));
    if (fullname == NULL) {OUTPUT_ERROR("Can't allocate fullname\n");}
    snprintf(fullname, len, "%s.txt", filename);

    FILE* gr_file = fopen(fullname, "w");
    if (gr_file == NULL) {OUTPUT_ERROR("Can't open file %s\n", fullname);}

    GenText(tree_root, gr_file);

    fclose(gr_file);
    return 0;
}


int TreeGenGraphPng(const tr_node *tree_root, const char* filename) {
    assert(tree_root); assert(filename);

    TreeGenGraphTxt(tree_root, filename);

    size_t len = 2 * strlen(filename) + sizeof("dot -Tpng .txt -o .png");
    char* cmd = (char*) calloc(len, sizeof(char));
    if (cmd == NULL) {OUTPUT_ERROR("Can't allocate cmd\n");}
    snprintf(cmd, len, "dot -Tpng %s.txt -o %s.png\n", filename, filename);
    if (system(cmd)) {
        OUTPUT_ERROR("Can't create %s.png\n", filename);
    }
    return 0;
}
