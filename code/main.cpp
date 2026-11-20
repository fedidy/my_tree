#include "tree.h"
#include "akinator.h"

int main() {
    /*
    tr_node* tree_root = TreeCtor("sffsd");

    TreeDump(tree_root, stdout);

    TreeInsertRight(tree_root, "fsf", "fsfsf");

    TreeDump(tree_root, stdout);

    TreeGenGraphPng(tree_root, "gra");
    TreeGenGraphSvg(tree_root, "ahah");
    WriteTreeInFile(tree_root, "zvuk_daly.txt");

    tr_node* new_tree = ParseStrTreeFromFile("zvuk_daly.txt");
    if (new_tree == NULL) {return -1;}

    TreeDump(new_tree, stdout);
    */
    StartAkinator("akinator.txt");

    tr_node* new_tree = ParseStrTreeFromFile("akinator.txt");
    if (new_tree == NULL) {return -1;}

    TreeGenGraphSvg(new_tree, "aki");
}
