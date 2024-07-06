// Names: Abdelrahman Mostafa Sayed - Ahmed Abdulhakeem Salah - Mohamed Sayed Shebl - Adham Salah Ezzat - Ahmed Atef Mohamed
// IDs:            20220197         -         20221010        -         20220290    -       20220051    -       20220024
// Sections:          S10           -          All-B          -            S7       -          S9       -          S10

// Importing necessary libraries and headers
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Item.h" // Header file for Item class
#include "Tree.h" // Header file for Tree class
#include "BinarySearchTree.h" // Header file for BinarySearchTree class
#include "Heap.h" // Header file for Heap class
#include "AVL.h" // Header file for AVLTree class

using namespace std;

// Function to read items from a file
void readFromFile(istream& input, vector<Item>& items) {
    int count;
    input >> count; // Read the number of items

    string name, category;
    double price;

    for (int i = 0; i < count; ++i) {
        input.ignore(); // Ignore newline character
        getline(input, name); // Read item name
        getline(input, category); // Read item category
        input >> price; // Read item price

        // Convert name and category to lowercase
        for (char& c : name) c = tolower(c);
        for (char& c : category) c = tolower(c);

        // Add item to the vector
        items.push_back(Item(name, category, price));
    }
}

int main() {
    vector<Item> items; // Vector to store items
    ifstream file("items.txt"); // Open file
    if (file.is_open()) {
        readFromFile(file, items); // Read items from file
        file.close(); // Close file
    }
    else {
        cout << "Unable to open file" << endl;
        return 1;
    }

    char chooseNonLinearDS; // Variable to store user's choice of data structure

    Tree<Item>* tree = nullptr; // Pointer to the chosen tree
    bool validInput = false; // Flag for valid input
    while (!validInput) {
        // Display menu for choosing data structure
        cout << "Please choose the Non-Linear Structure you want to use: \n";
        cout << "(1) Binary Search Tree (BST)\n";
        cout << "(2) Heaps\n";
        cout << "(3) AVL Trees\n";  // Note: AVL Trees are not implemented
        cout << "(q) If you want to quit the program\n";

        cin >> chooseNonLinearDS;

        if (chooseNonLinearDS == '1') {
            tree = new BinarySearchTree<Item>(); // Create a new Binary Search Tree
            for (const Item& item : items) {
                tree->insert(item); // Insert items into the tree
            }
            validInput = true;
        }
        else if (chooseNonLinearDS == '2') {
            tree = new Heap<Item>(); // Create a new Heap
            for (const Item& item : items) {
                tree->insert(item); // Insert items into the heap
            }
            validInput = true;
        }
        else if (chooseNonLinearDS == '3') {
            tree = new AVLTree<Item>(); // Create a new AVL Tree
            for (const Item& item : items) {
                tree->insert(item); // Insert items into the AVL tree
            }
            validInput = true;
        }
        else if (chooseNonLinearDS == 'Q' || chooseNonLinearDS == 'q') {
            cout << "Thank You for your time\n";
            return 0; // Quit the program
        }
        else {
            cout << "Please choose one of the available options\n";
        }
    }

    char chooseOperation; // Variable to store user's choice of operation
    bool quitOperationMenu = false; // Flag for quitting the operation menu
    while (!quitOperationMenu) {
        // Display menu for choosing an operation
        cout << "Please Enter the operation you want to make: \n";
        cout << "1. Add item data\n";
        cout << "2. Remove item data\n";
        cout << "3. Display the item data normally\n";
        cout << "4. Display all the items sorted by their name ascending\n";
        cout << "5. Display all the items sorted by their name descending\n";
        cout << "6. Display all the items sorted by their prices ascending\n";
        cout << "7. Display all the items sorted by their prices descending\n";
        cout << "q. If you want to quit the program\n";

        cin >> chooseOperation;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        string itemName, itemCategory;
        double itemPrice;

        if (chooseOperation == '1') {
            // Add item data
            cout << "Please enter item name: ";
            getline(cin, itemName);
            cout << "Please enter item category: ";
            getline(cin, itemCategory);
            cout << "Please enter item price: ";
            cin >> itemPrice;

            // Convert name and category to lowercase
            for (char& c : itemName) c = tolower(c);
            for (char& c : itemCategory) c = tolower(c);

            // Insert item into the tree
            tree->insert(Item(itemName, itemCategory, itemPrice));
        }
        else if (chooseOperation == '2') {
            // Remove item data
            cout << "Please enter item name: ";
            getline(cin, itemName);
            cout << "Please enter item category: ";
            getline(cin, itemCategory);
            cout << "Please enter item price: ";
            cin >> itemPrice;

            // Convert name and category to lowercase
            for (char& c : itemName) c = tolower(c);
            for (char& c : itemCategory) c = tolower(c);

            // Remove item from the tree
            tree->remove(Item(itemName, itemCategory, itemPrice));
        }
        else if (chooseOperation == '3') {
            // Display All items normally
            tree->inOrder();
        }
        else if (chooseOperation == '4') {
            // Display all items sorted by their name ascending
            tree->inOrder();
        }
        else if (chooseOperation == '5') {
            // Display all items sorted by their name descending
            tree->rightInOrder();
        }
        else if (chooseOperation == '6') {
            // Display all items sorted by their prices ascending
            tree->displayByPriceAscending();
        }
        else if (chooseOperation == '7') {
            // Display all items sorted by their prices descending
            tree->displayByPriceDescending();
        }
        else if (chooseOperation == 'Q' || chooseOperation == 'q') {
            // Quit the program
            cout << "Thank You for your time\n";
            quitOperationMenu = true;
        }
        else {
            cout << "Please choose an available operation: \n";
        }
    }

    delete tree; // Free allocated memory
    return 0;
}
