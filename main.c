#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//TREE STRUCT
typedef struct Tree {
    char key;
    struct Tree* left;
    struct Tree* right;
} Tree;

// NODE CREATION AND INSERTION
Tree* createNode(char key) {
    Tree* newNode = (Tree*)malloc(sizeof(Tree));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Tree* insert(Tree* root, char key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    }
    else {
        root->right = insert(root->right, key);
    }

    return root;
}

// PRINT FUNCTION OF THE THREE ORDERS
void preorder(Tree* root) {
    if (root != NULL) {
        printf("%c ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(Tree* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%c ", root->key);
        inorder(root->right);
    }
}

void postorder(Tree* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->key);
    }
}

// RECURSIVE SEARCH FUNCTION
bool search(Tree* root, char key) {
    if (root == NULL) {
        return false;
    }

    if (root->key == key) {
        return true;
    }

    if (key < root->key) {
        return search(root->left, key);
    }
    else {
        return search(root->right, key);
    }
}

// FREE MEMORY
void freeTree(Tree* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Tree* root = NULL;
    char line[100];
    char command[10];
    char element;

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%s %c", command, &element);
    root = insert(root, element);
    
    //WHILE LOOP TO FIND THE DESIRED COMMAND
    while (fgets(line, sizeof(line), stdin) != NULL) {
        sscanf(line, "%s", command);

        if (strcmp(command, "I") == 0) {
            sscanf(line, "%s %c", command, &element);
            root = insert(root, element);
        }
        else if (strcmp(command, "PREFIXA") == 0) {
            preorder(root);
            printf("\n");
        }
        else if (strcmp(command, "INFIXA") == 0) {
            inorder(root);
            printf("\n");
        }
        else if (strcmp(command, "POSFIXA") == 0) {
            postorder(root);
            printf("\n");
        }
        else if (strcmp(command, "P") == 0) {
            sscanf(line, "%s %c", command, &element);
            if (search(root, element)) {
                printf("%c existe\n", element);
            }
            else {
                printf("%c nao existe\n", element);
            }
        }
    }
    freeTree(root);
    return 0;
}