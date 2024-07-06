// Ahmed Atef Mohamed - 20220024 - S10

#pragma once

#include "Tree.h" // Include the base Tree class
#include <algorithm> // Include necessary standard libraries
#include <iostream>
#include <vector>

using namespace std;

// Define a template class for an AVL Tree
template <typename T>
class AVLTree : public Tree<T> {
private:
    // Define a nested struct for the nodes of the AVL Tree
    struct Node {
        T data; // Data stored in the node
        Node* left; // Pointer to the left child
        Node* right; // Pointer to the right child
        int height; // Height of the node in the AVL Tree
        Node(T item) : data(item), left(nullptr), right(nullptr), height(1) {} // Constructor for creating a node
    };

    Node* root; // Pointer to the root of the AVL Tree

    // Helper function to get the height of a node
    int height(Node* node) {
        if (node == nullptr) return 0; // Height of null node is 0
        return node->height; // Return the height of the node
    }

    // Helper function to get the balance factor of a node
    int getBalance(Node* node) {
        if (node == nullptr) return 0; // Balance factor of null node is 0
        return height(node->left) - height(node->right); // Return the balance factor of the node
    }

    // Helper function for right rotation
    Node* rightRotate(Node* y) {
        Node* x = y->left; // Store the left child of y as x
        Node* T = x->right; // Store the right child of x as T

        // Perform rotation
        x->right = y;
        y->left = T;

        // Update heights
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        return x; // Return the new root after rotation
    }

    // Helper function for left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right; // Store the right child of x as y
        Node* T = y->left; // Store the left child of y as T

        // Perform rotation
        y->left = x;
        x->right = T;

        // Update heights
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        return y; // Return the new root after rotation
    }

    // Helper function to insert a node into the AVL tree
    Node* insert(Node* node, T item) {
        if (node == nullptr) return new Node(item); // Create a new node if the current node is null

        // Perform standard BST insertion
        if (item < node->data) {
            node->left = insert(node->left, item);
        }
        else if (item > node->data) {
            node->right = insert(node->right, item);
        }
        else {
            return node; // Duplicate keys are not allowed in AVL Tree
        }

        // Update height of the current node
        node->height = 1 + max(height(node->left), height(node->right));

        // Get the balance factor of the current node
        int balance = getBalance(node);

        // Perform rotations if necessary to balance the tree

        // Left Left Case
        if (balance > 1 && item < node->left->data) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && item > node->right->data) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && item > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && item < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // Return the unchanged node
    }

    // Helper function to find the node with the minimum value
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Helper function to remove a node from the AVL tree
    Node* remove(Node* root, T data) {
        if (root == nullptr) return root; // If the tree is empty, return null

        // Perform standard BST delete
        if (data < root->data) {
            root->left = remove(root->left, data);
        }
        else if (data > root->data) {
            root->right = remove(root->right, data);
        }
        else {
            // Node with only one child or no child
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right; // Save the child of the node to be deleted
                if (temp == nullptr) {
                    temp = root; // If the node has no child, it can be deleted directly
                    root = nullptr;
                }
                else {
                    *root = *temp; // If the node has one child, copy the child to the node and delete the child
                }
                delete temp; // Delete the node
            }
            else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                Node* temp = minValueNode(root->right);
                // Copy the inorder successor's data to this node
                root->data = temp->data;
                // Delete the inorder successor
                root->right = remove(root->right, temp->data);
            }
        }

        // If the tree had only one node then return
        if (root == nullptr) return root;

        // Update height of the current node
        root->height = 1 + max(height(root->left), height(root->right));

        // Get the balance factor of this node
        int balance = getBalance(root);

        // Perform rotations if necessary to balance the tree

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0) {
            return rightRotate(root);
        }

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0) {
            return leftRotate(root);
        }

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root; // Return the unchanged root
    }

    // Helper function for in-order traversal of the AVL tree
    void inOrder(Node* current, vector<T>& items) const {
        if (current != nullptr) {
            inOrder(current->left, items);
            items.push_back(current->data);
            inOrder(current->right, items);
        }
    }

    // Helper function to recursively destroy the AVL tree
    void destroy(Node* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    // Constructor
    AVLTree() : root(nullptr) {}

    // Method to insert an item into the AVL tree
    void insert(T item) override {
        root = insert(root, item);
    }

    // Method to remove an item from the AVL tree
    void remove(T item) override {
        root = remove(root, item);
    }

    // Method to search for an item in the AVL tree
    bool search(const T& item) override {
        Node* current = root;
        while (current != nullptr) {
            if (current->data == item) {
                return true;
            }
            else if (current->data < item) {
                current = current->right;
            }
            else {
                current = current->left;
            }
        }
        return false;
    }

    // Method to print an item
    void print(const T& item) const override {
        cout << item << endl;
    }

    // Method to perform in-order traversal of the AVL tree
    void inOrder() override {
        vector<T> items;
        inOrder(root, items);
        for (const auto& item : items) {
            cout << item << endl;
        }
    }

    // Method to perform reverse in-order traversal of the AVL tree
    void rightInOrder() override {
        vector<T> items;
        inOrder(root, items);
        sort(items.rbegin(), items.rend());
        for (const auto& item : items) {
            cout << item << endl;
        }
    }

    // Method to display items by price in ascending order
    void displayByPriceAscending() override {
        vector<T> items;
        inOrder(root, items);
        sort(items.begin(), items.end(), [](const T& a, const T& b) {
            return a.getPrice() < b.getPrice();
            });
        for (const auto& item : items) {
            cout << item << endl;
        }
    }

    // Method to display items by price in descending order
    void displayByPriceDescending() override {
        vector<T> items;
        inOrder(root, items);
        sort(items.begin(), items.end(), [](const T& a, const T& b) {
            return a.getPrice() > b.getPrice();
            });
        for (const auto& item : items) {
            cout << item << endl;
        }
    }

    // Destructor
    ~AVLTree() {
        destroy(root);
    }
};
