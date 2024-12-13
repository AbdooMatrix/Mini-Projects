#include <bits/stdc++.h>
using namespace std;

// This structure represents a node in the AVL tree.
// Each node contains a key, pointers to its left and right children, and its height.
struct Node {
    int key;           // The value stored in the node.
    Node* left;        // Pointer to the left child.
    Node* right;       // Pointer to the right child.
    int height;        // Height of the node for balancing.

    // Constructor to initialize a node with a given key. Initially, height is set to 1.
    Node(int value) {
        key = value;
        left = right = nullptr;
        height = 1;
    }
};

// This class represents the AVL tree, a self-balancing binary search tree.
class AVLTree {
private:
    Node* root; // Root of the AVL tree.

    // Returns the height of a node. A null node has height 0.
    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    // Computes the balance factor of a node to check if it is balanced.
    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    // Performs a right rotation to rebalance the tree when needed.
    Node* rightRotate(Node* y) {
        Node* x = y->left;       // The left child becomes the new root.
        Node* T2 = x->right;     // The right subtree of x is preserved.

        x->right = y;            // Update pointers to perform the rotation.
        y->left = T2;

        // Update heights of the affected nodes.
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x; // Return the new root.
    }

    // Performs a left rotation to rebalance the tree when needed.
    Node* leftRotate(Node* x) {
        Node* y = x->right;      // The right child becomes the new root.
        Node* T2 = y->left;      // The left subtree of y is preserved.

        y->left = x;             // Update pointers to perform the rotation.
        x->right = T2;

        // Update heights of the affected nodes.
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y; // Return the new root.
    }

    // Inserts a new key into the AVL tree and rebalances it.
    Node* insert(Node* node, int key) {
        if (node == nullptr) { // Base case: empty subtree, create a new node.
            return new Node(key);
        }

        // Perform regular BST insertion.
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else { // Duplicates are not allowed in AVL trees.
            return node;
        }

        // Update height of the current node.
        node->height = 1 + max(height(node->left), height(node->right));

        // Check balance and perform rotations if necessary.
        int balance = getBalance(node);

        // Case 1: Left-Left (Single Right Rotation).
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }

        // Case 2: Right-Right (Single Left Rotation).
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }

        // Case 3: Left-Right (Left Rotation + Right Rotation).
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Case 4: Right-Left (Right Rotation + Left Rotation).
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // Return the unchanged node pointer.
    }

    // Removes a key from the AVL tree and rebalances it.
    Node* remove(Node* node, int key) {
        if (node == nullptr) { // Base case: empty subtree.
            return node;
        }

        // Perform regular BST removal.
        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            // Node with one or no child.
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor.
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }

        if (node == nullptr) { // If the tree had only one node, return.
            return node;
        }

        // Update height and rebalance.
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // Rebalancing after deletion.
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Searches for a key in the AVL tree.
    bool search(Node* node, int key) {
        if (node == nullptr) { // Base case: empty subtree.
            return false;
        }

        if (key == node->key) { // Key found.
            return true;
        } else if (key < node->key) { // Search in the left subtree.
            return search(node->left, key);
        } else { // Search in the right subtree.
            return search(node->right, key);
        }
    }

    // Finds the node with the smallest key in a subtree.
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Performs an in-order traversal of the AVL tree.
    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left); // Visit the left subtree.
            cout << node->key << ' ';    // Print the current node's key.
            inOrderTraversal(node->right); // Visit the right subtree.
        }
    }

public:
    // Wrapper function to insert a key into the AVL tree.
    void insert(int key) {
        root = insert(root, key);
    }

    // Wrapper function to remove a key from the AVL tree.
    void remove(int key) {
        root = remove(root, key);
    }

    // Wrapper function to search for a key in the AVL tree.
    bool search(int key) {
        return search(root, key);
    }

    // Wrapper function for in-order traversal.
    void inOrderTraversal() {
        inOrderTraversal(root);
    }
};

int main() {
    AVLTree avl;

    // Insert keys into the AVL tree.
    avl.insert(20);
    avl.insert(10);
    avl.insert(30);

    // Perform in-order traversal and display the tree.
    avl.inOrderTraversal();
    cout << endl;

    // Check if a key exists in the tree.
    if (avl.search(20)) {
        cout << "20 is found\n";
    } else {
        cout << "20 isn't found\n";
    }

    // Remove a key from the tree and display the updated tree.
    avl.remove(20);
    avl.inOrderTraversal();
    cout << endl;

    // Verify the removal of the key.
    if (avl.search(20)) {
        cout << "20 is found\n";
    } else {
        cout << "20 isn't found\n";
    }

    return 0;
}
