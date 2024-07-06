// Ahmed Abdulhakeem Salah - 20221010 - All-B
// Mohamed Sayed Shebl - 20220290 - S7

#pragma once // Include guard to prevent multiple inclusions

#include <iostream> // Input/output stream
#include <vector> // Dynamic array
#include <algorithm> // Algorithms like sorting
#include "Tree.h" // Include base Tree class header file

using namespace std; // Standard namespace

// Define a template class for a Binary Search Tree
template <typename T>
class BinarySearchTree : public Tree<T> {
private:
    Node<T>* root; // Root node pointer

    // Helper function to print items in order
    void printInOrder(Node<T>* current) {
        if (current != nullptr) {
            printInOrder(current->left);
            cout << current->data << endl;
            printInOrder(current->right);
        }
    }

    // Helper function to print items in reverse order
    void printRightInOrder(Node<T>* current) {
        if (current != nullptr) {
            printRightInOrder(current->right);
            cout << current->data << endl;
            printRightInOrder(current->left);
        }
    }

    // Helper function to populate vector with items in order
    void inOrderVector(Node<T>* current, vector<T>& items) {
        if (current != nullptr) {
            inOrderVector(current->left, items);
            items.push_back(current->data);
            inOrderVector(current->right, items);
        }
    }

    // Helper function to populate vector with items in reverse order
    void rightInOrderVector(Node<T>* current, vector<T>& items) {
        if (current != nullptr) {
            rightInOrderVector(current->right, items);
            items.push_back(current->data);
            rightInOrderVector(current->left, items);
        }
    }

    // Helper function to remove a node from the tree
    Node<T>* remove(Node<T>* root, T data) {
        if (root == nullptr) return root;

        if (data < root->data) {
            root->left = remove(root->left, data);
        }
        else if (data > root->data) {
            root->right = remove(root->right, data);
        }
        else {
            if (root->left == nullptr) {
                Node<T>* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node<T>* temp = root->left;
                delete root;
                return temp;
            }

            Node<T>* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
        return root;
    }

    // Helper function to find the node with the minimum value
    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Helper function to deallocate memory
    void destroy(Node<T>* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Method to insert an item into the tree
    void insert(T item) override {
        Node<T>* newNode = new Node<T>();
        newNode->data = item;
        if (root == nullptr) {
            root = newNode;
        }
        else {
            Node<T>* current = root;
            Node<T>* parent = nullptr;
            while (true) {
                parent = current;
                if (item < current->data) {
                    current = current->left;
                    if (current == nullptr) {
                        parent->left = newNode;
                        break;
                    }
                }
                else {
                    current = current->right;
                    if (current == nullptr) {
                        parent->right = newNode;
                        break;
                    }
                }
            }
        }
    }

    // Method to remove an item from the tree
    void remove(T item) override {
        root = remove(root, item);
    }

    // Method to search for an item in the tree
    bool search(const T& item) override {
        Node<T>* current = root;
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

    // Method to print items in order
    void inOrder() override {
        printInOrder(root);
    }

    // Method to print items in reverse order
    void rightInOrder() override {
        printRightInOrder(root);
    }

    // Method to display items by price in ascending order
    void displayByPriceAscending() override {
        vector<T> items;
        inOrderVector(root, items);
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
        inOrderVector(root, items);
        sort(items.begin(), items.end(), [](const T& a, const T& b) {
            return a.getPrice() > b.getPrice();
            });
        for (const auto& item : items) {
            cout << item << endl;
        }
    }

    // Destructor
    ~BinarySearchTree() {
        destroy(root);
    }
};
