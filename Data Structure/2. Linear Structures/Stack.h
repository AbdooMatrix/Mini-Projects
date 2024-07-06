// Name: Abdelrahman Mostafa Sayed
// ID: 20220197

// Include necessary libraries
#include <iostream>
using namespace std;

// Ensure the header file is only included once
#ifndef DATASTUCTUREASS_STACK_H
#define DATASTUCTUREASS_STACK_H

template <typename T>
struct StackNode {
    T data;  // Data of the StackNode
    StackNode<T>* next;  // Pointer to the next StackNode

    // Add a constructor
    StackNode(const T& data = T(), StackNode<T>* next = NULL) : data(data), next(next) {}
};

// Stack class definition
template <typename T>
class Stack {
private:
    StackNode<T> *topStackNode;  // Pointer to the top StackNode
    int size;  // Size of the stack

public:
    // Default constructor
    Stack() : topStackNode(NULL), size(0) {}

    // Destructor to clean up memory
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Copy constructor
    Stack(const Stack &other) : topStackNode(NULL), size(0) {
        Stack<T> tempStack;
        StackNode<T>* temp = other.topStackNode;
        while (temp != NULL) {
            tempStack.push(temp->data);
            temp = temp->next;
        }
        temp = tempStack.topStackNode;
        while (temp != NULL) {
            push(temp->data);
            temp = temp->next;
        }
    }

    // Assignment operator
    Stack<T>& operator=(const Stack<T>& other) {
        if (this != &other) {
            this->clear();
            Stack<T> tempStack;
            StackNode<T>* temp = other.topStackNode;
            while (temp != NULL) {
                tempStack.push(temp->data);
                temp = temp->next;
            }
            temp = tempStack.topStackNode;
            while (temp != NULL) {
                push(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return topStackNode == NULL;
    }

    // Push an element onto the stack
    void push(const T& element) {
        StackNode<T>* newStackNode = new StackNode<T>;
        newStackNode->data = element;
        newStackNode->next = topStackNode;
        topStackNode = newStackNode;
        size++;
    }

    // Pop an element from the stack
    T pop() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty. Cannot pop.");
        }
        T topData = topStackNode->data;
        StackNode<T>* temp = topStackNode;
        topStackNode = topStackNode->next;
        delete temp;
        size--;
        return topData;
    }

    // Get the top element of the stack
    T& top() const {
        if (isEmpty()) {
            throw out_of_range("Stack is empty. No top element.");
        }
        return topStackNode->data;
    }

    // Get the size of the stack
    int stackSize() const {
        return size;
    }

    // Clear the stack
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Print the stack
    void print() {
        StackNode<T>* temp = topStackNode;
        while (temp != NULL) {
            cout << temp->data << ' ';
            temp = temp->next;
        }
        cout << endl;
    }

};

#endif //DATASTUCTUREASS_STACK_H
