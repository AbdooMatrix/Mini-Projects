#include <bits/stdc++.h>
using namespace std;

// This structure represents a node in the Binary Search Tree.
// Each node contains a key (integer value) and pointers to its left and right children.
struct Node {
    int key;           // The value stored in the node
    Node* left;        // Pointer to the left child of the node
    Node* right;       // Pointer to the right child of the node

    // Constructor to initialize a new node. It takes a value as input and sets left and right to nullptr.
    Node(int value) {
        key = value;
        left = right = nullptr;
    }
};

// This class represents the Binary Search Tree itself.
// It provides methods for inserting, removing, searching, and traversing nodes.
class BinarySearchTree {
private:
    Node* root; // This is the root of the BST. It's the starting point for all operations.

    // This function inserts a new key into the tree, starting from a given node.
    // It returns the modified tree with the new node inserted.
    Node* insert(Node* node, int key) {
        if (node == nullptr) { // If the tree/subtree is empty, create a new node with the key.
            return new Node(key);
        }

        // If the key is less than the current node's key, insert it in the left subtree.
        if (key < node->key) {
            node->left = insert(node->left, key);
        }
            // If the key is greater, insert it in the right subtree.
        else if (key > node->key) {
            node->right = insert(node->right, key);
        }

        // Return the current node unchanged after insertion.
        return node;
    }

    // This function removes a key from the tree, starting from a given node.
    Node* remove(Node* node, int key) {
        if (node == nullptr) { // If the tree/subtree is empty, there's nothing to remove.
            return node;
        }

        // If the key is less than the current node's key, try removing it from the left subtree.
        if (key < node->key) {
            node->left = remove(node->left, key);
        }
            // If the key is greater, try removing it from the right subtree.
        else if (key > node->key) {
            node->right = remove(node->right, key);
        }
            // If the current node matches the key, delete it.
        else {
            // Case 1: Node has one or no children.
            if (node->left == nullptr) {
                Node* temp = node->right; // Replace the node with its right child.
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left; // Replace the node with its left child.
                delete node;
                return temp;
            }

            // Case 2: Node has two children. Replace its value with the smallest value in its right subtree.
            Node* temp = findMin(node->right); // Find the inorder successor.
            node->key = temp->key; // Copy the successor's value.
            node->right = remove(node->right, temp->key); // Remove the successor.
        }

        // Return the updated node after removal.
        return node;
    }

    // This function searches for a key in the tree, starting from a given node.
    // It returns true if the key is found, false otherwise.
    bool search(Node* node, int key) {
        if (node == nullptr) { // If the tree/subtree is empty, the key isn't found.
            return false;
        }

        // If the current node's key matches the search key, return true.
        if (key == node->key) {
            return true;
        }
            // If the key is less, search in the left subtree.
        else if (key < node->key) {
            return search(node->left, key);
        }
            // Otherwise, search in the right subtree.
        else {
            return search(node->right, key);
        }
    }

    // This helper function finds the node with the smallest key in a subtree.
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) { // Keep moving to the left child until it becomes null.
            node = node->left;
        }
        return node; // Return the node with the smallest key.
    }

    // This function performs an in-order traversal, starting from a given node.
    // It prints the keys in ascending order.
    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left); // Visit the left subtree.
            cout << node->key << ' ';    // Print the current node's key.
            inOrderTraversal(node->right); // Visit the right subtree.
        }
    }

    // This function performs a pre-order traversal, starting from a given node.
    // It prints the root first, then the left and right subtrees.
    void preOrderTraversal(Node* node) {
        if (node != nullptr) {
            cout << node->key << ' ';    // Print the current node's key.
            preOrderTraversal(node->left); // Visit the left subtree.
            preOrderTraversal(node->right); // Visit the right subtree.
        }
    }

    // This function performs a post-order traversal, starting from a given node.
    // It prints the left and right subtrees first, then the root.
    void postOrderTraversal(Node* node) {
        if (node != nullptr) {
            postOrderTraversal(node->left); // Visit the left subtree.
            postOrderTraversal(node->right); // Visit the right subtree.
            cout << node->key << ' ';    // Print the current node's key.
        }
    }

public:
    // Constructor to initialize an empty BST.
    BinarySearchTree() {
        root = nullptr;
    }

    // Wrapper function to insert a key into the BST.
    void insert(int key) {
        root = insert(root, key);
    }

    // Wrapper function to remove a key from the BST.
    void remove(int key) {
        root = remove(root, key);
    }

    // Wrapper function to search for a key in the BST.
    bool search(int key) {
        return search(root, key);
    }

    // Wrapper function for in-order traversal of the BST.
    void inOrderTraversal() {
        inOrderTraversal(root);
    }

    // Wrapper function for pre-order traversal of the BST.
    void preOrderTraversal() {
        preOrderTraversal(root);
    }

    // Wrapper function for post-order traversal of the BST.
    void postOrderTraversal() {
        postOrderTraversal(root);
    }
};

int main() {
    BinarySearchTree bst;

    // Add keys to the BST.
    bst.insert(20);
    bst.insert(40);
    bst.insert(30);

    // Check if a specific key is in the BST.
    if (bst.search(30))
        cout << "30 is found\n";
    else
        cout << "30 isn't found\n";

    // Print the tree using in-order traversal.
    bst.inOrderTraversal();
    cout << endl;

    // Remove a key and verify.
    bst.remove(30);
    if (bst.search(30))
        cout << "30 is found\n";
    else
        cout << "30 isn't found\n";

    // Print the tree again using in-order traversal.
    bst.inOrderTraversal();
    cout << endl;

    // Add more keys and demonstrate all traversal types.
    bst.insert(70);
    bst.insert(90);
    bst.insert(80);

    bst.inOrderTraversal();
    cout << endl;
    bst.preOrderTraversal();
    cout << endl;
    bst.postOrderTraversal();

    return 0;
}
