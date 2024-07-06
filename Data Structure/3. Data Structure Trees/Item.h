// Names: Abdelrahman Mostafa Sayed - Ahmed Abdulhakeem Salah - Mohamed Sayed Shebl - Adham Salah Ezzat - Ahmed Atef Mohamed
// IDs:            20220197                   20221010                  20220290            20220051            20220024
// Sections:          S10           -          All-B          -            S7       -          S9       -          S10

#pragma once
#include <iostream>
#include <string>
using namespace std;

class Item {
    string itemName;
    string itemCategory;
    double itemPrice;

public:
    // Default constructor
    Item() : itemName("null"), itemCategory("null"), itemPrice(0.0) {}

    // Parameterized constructor
    Item(string itemName, string itemCategory, double itemPrice) {
        this->itemName = itemName;
        this->itemCategory = itemCategory;
        this->itemPrice = itemPrice;
    }

    // Getter method for item price
    double getPrice() const {
        return itemPrice;
    }

    // Less than operator overload
    bool operator<(const Item& other) const {
        return itemName < other.itemName;
    }

    // Equal to operator overload
    bool operator==(const Item& other) const {
        return itemName == other.itemName;
    }

    // Less than or equal to operator overload
    bool operator<=(const Item& other) const {
        return itemName <= other.itemName;
    }

    // Greater than operator overload
    bool operator>(const Item& other) const {
        return itemName > other.itemName;
    }

    // Method to print item details
    void print() const {
        cout << "Item Name: " << itemName << endl;
        cout << "Item Category: " << itemCategory << endl;
        cout << "Item Price: " << itemPrice << endl;
    }

    // Friend function to overload stream insertion operator
    friend ostream& operator<<(ostream& os, const Item& item) {
        os << "Item Name: " << item.itemName << endl;
        os << "Item Category: " << item.itemCategory << endl;
        os << "Item Price: " << item.itemPrice << endl;
        return os;
    }
};
