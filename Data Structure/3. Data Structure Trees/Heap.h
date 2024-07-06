// Adham Salah Ezzat - 20220051 - S9
// Abdelrahman Mostafa Sayed - 20220197 - S10

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "Tree.h" // Base Tree class header file

using namespace std;

template <typename T> // Template for generic type T
class Heap : public Tree<T> { // Inherits from Tree class
private:
    vector<T> items; // Vector to store heap items

public:
    Heap() {} // Constructor

    // Inserts an item into the heap
    void insert(T item) override {
        items.push_back(item); // Add item to heap
        push_heap(items.begin(), items.end()); // Reorder heap
    }

    // Removes an item from the heap
    void remove(T item) override {
        auto it = find(items.begin(), items.end(), item); // Find item
        if (it != items.end()) { // If item found
            swap(*it, items.back()); // Swap with last element
            items.pop_back(); // Remove last element
            make_heap(items.begin(), items.end()); // Rebuild heap
        }
    }

    // Searches for an item in the heap
    bool search(const T& item) override {
        return find(items.begin(), items.end(), item) != items.end(); // Return true if found
    }

    // Prints an item
    void print(const T& item) const override {
        cout << item << endl; // Output item
    }

    // Displays items in ascending order
    void inOrder() override {
        vector<T> sortedItems = items; // Copy items
        sort(sortedItems.begin(), sortedItems.end()); // Sort
        for (const auto& item : sortedItems) { // Output sorted items
            cout << item << endl;
        }
    }

    // Displays items in descending order
    void rightInOrder() override {
        vector<T> sortedItems = items; // Copy items
        sort(sortedItems.rbegin(), sortedItems.rend()); // Sort in reverse
        for (const auto& item : sortedItems) { // Output sorted items
            cout << item << endl;
        }
    }

    // Displays items sorted by price in ascending order
    void displayByPriceAscending() override {
        vector<T> sortedItems = items; // Copy items
        sort(sortedItems.begin(), sortedItems.end(), [](const T& a, const T& b) { // Sort using custom comparison function
            return a.getPrice() < b.getPrice(); // Compare by price
            });
        for (const auto& item : sortedItems) { // Output sorted items
            cout << item << endl;
        }
    }

    // Displays items sorted by price in descending order
    void displayByPriceDescending() override {
        vector<T> sortedItems = items; // Copy items
        sort(sortedItems.begin(), sortedItems.end(), [](const T& a, const T& b) { // Sort using custom comparison function
            return a.getPrice() > b.getPrice(); // Compare by price
            });
        for (const auto& item : sortedItems) { // Output sorted items
            cout << item << endl;
        }
    }

    // Displays items sorted by name in ascending order
    void displayByNameAscending() {
        vector<T> sortedItems = items; // Copy items
        sort(sortedItems.begin(), sortedItems.end(), [](const T& a, const T& b) { // Sort using custom comparison function
            return a < b; // Compare by name
            });
        for (const auto& item : sortedItems) { // Output sorted items
            cout << item << endl;
        }
    }

    // Displays items sorted by name in descending order
    void displayByNameDescending() {
        vector<T> sortedItems = items; // Copy items
        sort(sortedItems.begin(), sortedItems.end(), [](const T& a, const T& b) { // Sort using custom comparison function
            return a > b; // Compare by name
            });
        for (const auto& item : sortedItems) { // Output sorted items
            cout << item << endl;
        }
    }

    ~Heap() {} // Destructor
};
