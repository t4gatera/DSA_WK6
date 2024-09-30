#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100  // Maximum number of nodes
#define N 4            // Maximum number of children for N-ary tree

// Structure for an N-ary Tree node
struct Node {
    int data;
    int children[N];  // Array to store indices of child nodes
    int childCount;   // Number of children
};

// Array to store all tree nodes
struct Node tree[MAX_NODES];
int nodeCount = 0;  // Number of nodes in the tree

// Function to create a new node
int createNode(int data) {
    if (nodeCount >= MAX_NODES) {
        printf("Tree is full!\n");
        return -1;
    }
    tree[nodeCount].data = data;
    tree[nodeCount].childCount = 0;  // No children initially
    return nodeCount++;
}

// Function to add a child to a node
void addChild(int parentIndex, int childData) {
    if (tree[parentIndex].childCount >= N) {
        printf("Node %d has reached the maximum number of children.\n", 	 tree[parentIndex].data);
        return;
    }
    int childIndex = createNode(childData);
    if (childIndex != -1) {
        tree[parentIndex].children[tree[parentIndex].childCount++] = childIndex;
    }
}

// Function for pre-order traversal (Depth-First Search)
void preOrderTraversal(int nodeIndex) {
    if (nodeIndex == -1) return;

    // Print the current node's data
    printf("%d ", tree[nodeIndex].data);

    // Recur for each child
    for (int i = 0; i < tree[nodeIndex].childCount; i++) {
        preOrderTraversal(tree[nodeIndex].children[i]);
    }
}

int main() {
    // Create root node
    int root = createNode(1);

    // Add children to root node
    addChild(root, 2);
    addChild(root, 3);
    addChild(root, 4);

    // Add children to node 2
    addChild(1, 5);
    addChild(1, 6);
    addChild(1, 20);

    // Add children to node 3
    addChild(2, 7);
    addChild(2, 19);

    // Perform pre-order traversal
    printf("Pre-order Traversal: ");
    preOrderTraversal(root);
    printf("\n");

    return 0;
}

