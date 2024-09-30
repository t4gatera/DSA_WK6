#include <stdio.h>
#include <stdlib.h>

// Structure for an N-ary Tree node
struct Node {
    int data;
    struct Node* firstChild;  // Pointer to the first child
    struct Node* nextSibling; // Pointer to the next sibling
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Function to add a child to a node
void addChild(struct Node* parent, int childData) {
    struct Node* child = createNode(childData);
    
    if (parent->firstChild == NULL) {
        // If the parent has no children, add the new child as the first child
        parent->firstChild = child;
    } else {
        // Find the last sibling in the parent's children list
        struct Node* temp = parent->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

// Function to print the tree in a structured format
void printTree(struct Node* root, int level) {
    if (root == NULL) return;

    // Print indentation for the current level
    for (int i = 0; i < level; i++) {
        printf("    ");  // Print 4 spaces for each level
    }

    // Print the current node's data
    printf("|- %d\n", root->data);

    // Recur for the first child (going down one level)
    printTree(root->firstChild, level + 1);

    // Recur for the next sibling (on the same level)
    printTree(root->nextSibling, level);
}

int main() {
    // Create root node
    struct Node* root = createNode(1);

    // Add children to root node
    addChild(root, 2);
    addChild(root, 3);
    addChild(root, 4);

    // Add children to node 2
    addChild(root->firstChild, 5);
    addChild(root->firstChild, 6);

    // Add children to node 3
    addChild(root->firstChild->nextSibling, 7);

    // Add 3 children to node 7
    struct Node* node7 = root->firstChild->nextSibling->firstChild;
    addChild(node7, 8);
    addChild(node7, 9);
    addChild(node7, 10);

    // Print the tree structure
    printf("Tree Structure:\n");
    printTree(root, 0);  // Start at root with level 0

    return 0;
}

