#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

#include "tree.h"
#include "akinator.h"


static void ClearInput() {
    int c = 0;
    while (c != '\n') {
        c = getchar();
    }
}


static int ParseAns(char* ans) {
    assert(ans);
    int c = 0;
    for (int i = 0; i < MAX_DATA_LENGTH; i++) {
        c = getchar();
        if (isalpha(c) || c == '_') {
            ans[i] = (char) c;
        } else if (c == ' ') {
            ans[i] = '_';
        } else if (c == '\n') {
            break;
        } else {
            printf("Wrong symbol with number %d\n", c);
            return -1;
        }
    }
    return 0;
}


static int AddNewElement(tr_node *node) {
    assert(node); assert(node->left == NULL); assert(node->right == NULL);

    char *new_data = (char*) calloc(MAX_DATA_LENGTH, sizeof(char));
    char *question = (char*) calloc(MAX_DATA_LENGTH, sizeof(char));

    printf("Than what is it?\n");
    while (ParseAns(new_data)) {
        ClearInput();
    }
    printf("What's the difference compared to %s?\n", node->data);
    while (ParseAns(question)) {
        ClearInput();
    }

    return TreeInsertLeft(node, new_data, question);
}


static int AskQuestion(tr_node *node) {
    assert(node); assert(node->data);
    int ans = 0;
    if (node->left && node->right) {
        printf("%s? (y/n)\n", node->data);
        while (ans != 'y' && ans != 'n') {
            ans = getchar();
            ClearInput();
            switch(ans) {
                case 'y':
                    return AskQuestion(node->left);
                case 'n':
                    return AskQuestion(node->right);
                default:
                    printf("Write 'y' or 'n'\n");
            }
        }
    } else if (node->left == NULL && node->right == NULL) {
        printf("is it %s? (y/n)\n", node->data);
        while (ans != 'y' && ans != 'n') {
            ans = getchar();
            ClearInput();
            switch(ans) {
                case 'y':
                    printf("Portyanki!!#@\n"); return 0;
                case 'n':
                    return AddNewElement(node);
                default:
                    printf("Write 'y' or 'n'\n");
            }
        }
    } else { OUTPUT_ERROR("Node got only 1 sonion! node: %p\n", node); }
    OUTPUT_ERROR("Shouldn't got there\n");
}


int StartAkinator(const char *filename) {
    assert(filename);
    tr_node *root = ParseStrTreeFromFile(filename);

    if (AskQuestion(root)) { return -1; }

    return WriteTreeInFile(root, filename);
}
