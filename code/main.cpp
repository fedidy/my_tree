#include "tree.h"

int main() {
    tr_node* tree_root = TreeCtor(10);

    TreeDump(tree_root, stdout);

    TreeInsertRight(tree_root, 15, tree_root->data);
    TreeDump(tree_root, stdout);
    TreeCmpAdd(tree_root, 5);
    TreeCmpAdd(tree_root, 8);
    TreeCmpAdd(tree_root, 100);

    TreeDump(tree_root, stdout);

    TreeGenGraphPng(tree_root, "gra");
    TreeGenGraphSvg(tree_root, "ahah");
}
