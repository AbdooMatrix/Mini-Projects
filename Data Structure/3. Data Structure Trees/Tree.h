// Names: Abdelrahman Mostafa Sayed - Ahmed Abdulhakeem Salah - Mohamed Sayed Shebl - Adham Salah Ezzat - Ahmed Atef Mohamed
// IDs:            20220197                   20221010                  20220290            20220051            20220024
// Sections:          S10           -          All-B          -            S7       -          S9       -          S10

#pragma once

// Define a template struct for a Node in the binary search tree
template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;
    Node() : left(nullptr), right(nullptr) {}
};

// Define a template class for a Tree interface
template <typename T>
class Tree {
public:
    // Virtual methods to be implemented by derived classes
    virtual void insert(T item) = 0;
    virtual void remove(T item) = 0;
    virtual bool search(const T& item) = 0;
    virtual void print(const T& item) const = 0;
    virtual void inOrder() = 0;
    virtual void rightInOrder() = 0;
    virtual void displayByPriceAscending() = 0;
    virtual void displayByPriceDescending() = 0;
    virtual ~Tree() {} // Virtual destructor
};
