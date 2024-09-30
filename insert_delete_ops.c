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
    if (!newNode) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Function to add a child to a parent node
void addChild(struct Node* parent, int childData) {
    if (parent == NULL) return;

    struct Node* child = createNode(childData);
    if (!child) return;

    if (parent->firstChild == NULL) {
        parent->firstChild = child;  // First child case
    } else {
        struct Node* temp = parent->firstChild;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;  // Traverse to the last sibling
        }
        temp->nextSibling = child;  // Add as the next sibling
    }
}

// Function to search for a node by data //searchNode
struct Node* check(struct Node* root, int data) {
    if (root == NULL) return NULL;

    if (root->data == data) return root;  // Node found

    // Recursively search in the children and siblings
    struct Node* found = check(root->firstChild, data);
    if (found != NULL) return found;

    return check(root->nextSibling, data);
}

// Function to find both the parent and node to delete
struct Node* findNodeAndParent(struct Node* root, int data, struct Node** parent) {
    if (root == NULL) return NULL;

    // If the first child matches the data
    if (root->firstChild && root->firstChild->data == data) {
        *parent = root;
        return root->firstChild;
    }

    // Traverse the siblings
    struct Node* temp = root->firstChild;
    while (temp != NULL) {
        if (temp->data == data) {
            *parent = root;
            return temp;
        }
        temp = temp->nextSibling;
    }

    // Recursively search in children
    struct Node* found = findNodeAndParent(root->firstChild, data, parent);
    if (found != NULL) return found;

    // Continue searching in siblings
    return findNodeAndParent(root->nextSibling, data, parent);
}

// Function to delete all children recursively
void deleteAllChildren(struct Node* node) {
    if (node == NULL) return;

    // Recursively delete the children
    deleteAllChildren(node->firstChild);
    deleteAllChildren(node->nextSibling);

    // Free the current node
    free(node);
}

// Function to delete a node and its subtree
void deleteNode(struct Node* root, int data) {
    struct Node* parent = NULL;
    struct Node* nodeToDelete = findNodeAndParent(root, data, &parent);

    if (nodeToDelete == NULL) {
        printf("Node with data %d not found.\n", data);
        return;
    }

    // If nodeToDelete is the first child of its parent
    if (parent->firstChild == nodeToDelete) {
        parent->firstChild = nodeToDelete->nextSibling;
    } else {
        // Traverse siblings and unlink the node
        struct Node* sibling = parent->firstChild;
        while (sibling->nextSibling != nodeToDelete) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = nodeToDelete->nextSibling;
    }

    // Delete the children of the node
    deleteAllChildren(nodeToDelete->firstChild);

    // Free the node itself
    free(nodeToDelete);
    printf("Node with data %d deleted.\n", data);
}

// Function to print the tree structure in a hierarchical format
void printTree(struct Node* root, int level) {
    if (root == NULL) return;

    // Print indentation for the current level
    for (int i = 0; i < level; i++) {
        printf("    ");  // Print 4 spaces for each level
    }

    // Print the current node's data
    printf("%d\n", root->data);

    // Recur for the first child
    printTree(root->firstChild, level + 1);

    // Recur for the next sibling
    printTree(root->nextSibling, level);
}

int main() {
    // Create root node
    struct Node* root = createNode(1);

    // Add children to root
    addChild(root, 2);
    addChild(root, 3);
    addChild(root, 4);

    // Add children to node 2
    addChild(root->firstChild, 5);
    addChild(root->firstChild, 6);

    // Add children to node 3
    addChild(root->firstChild->nextSibling, 7);

    // Print initial tree structure
    printf("Initial Tree Structure:\n");
    printTree(root, 0);

    // Insert a new node under node 2
    printf("\nInserting node 11 under node 2...\n");
    struct Node* node2 = check(root, 2);
    if (node2 != NULL) {
        addChild(node2, 11);
    }
    printTree(root, 0);

    // Delete node 7
    printf("\nDeleting node 7...\n");
    deleteNode(root, 7);
    printTree(root, 0);

    return 0;
}

