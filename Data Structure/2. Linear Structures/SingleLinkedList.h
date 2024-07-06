// Name: Adham Salah Ezzat
// ID: 20220051

#ifndef DATASTUCTUREASS_SINGLELINKEDLIST_H
#define DATASTUCTUREASS_SINGLELINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
struct SingleNode {
    T data;  // Data of the SingleNode
    SingleNode<T>* next;  // Pointer to the next SingleNode

    // Add a constructor
    SingleNode(const T& data = T(), SingleNode<T>* next = NULL) : data(data), next(next) {}
};

template <typename T>
class LinkedList {
private:
    SingleNode<T>* head; //pointer to the head of the list
    int size;

public:
    LinkedList() : head(nullptr), size(0) {} //initialize empty linkedlist

    // Method to insert element at the head
    void insertAtHead(const T& element) {
        SingleNode<T>* newSingleNode = new SingleNode<T>(element);
        // Set the next pointer of the new SingleNode to the current head
        newSingleNode->next = head;
        head = newSingleNode;
        size++;
    }

    // Method to insert element at the tail
    void insertAtTail(const T& element) {
        if (head == nullptr) {
            insertAtHead(element);
            return;
        }

        SingleNode<T>* newSingleNode = new SingleNode<T>(element);
        SingleNode<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newSingleNode;
        size++;
    }

    // Method to insert element at a specific index
    void insertAt(const T& element, int index) {
        if (index < 0 || index > size) {
            cout << "Index out of bounds" << endl;
            return;
        }
        if (index == 0) {
            insertAtHead(element);
            return;
        }
        if (index == size) {
            insertAtTail(element);
            return;
        }

        SingleNode<T>* newSingleNode = new SingleNode<T>(element);
        SingleNode<T>* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newSingleNode->next = temp->next;
        temp->next = newSingleNode;
        size++;
    }

    // Method to remove element from the head
    void removeAtHead() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        SingleNode<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    // Method to remove element from the tail
    void removeAtTail() {
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        if (head->next == nullptr) {
            removeAtHead();
            return;
        }
        SingleNode<T>* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
        size--;
    }

    // Method to remove element at a specific index
    void removeAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds" << endl;
            return;
        }
        if (index == 0) {
            removeAtHead();
            return;
        }
        if (index == size - 1) {
            removeAtTail();
            return;
        }
        SingleNode<T>* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        SingleNode<T>* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        size--;
    }

    // Method to retrieve element at a specific index
    T retrieveAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds" <<endl;
            return T();
        }
        SingleNode<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    // Method to replace element at a specific index
    void replaceAt(const T& newElement, int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds" << endl;
            return;
        }
        SingleNode<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        temp->data = newElement;
    }

    // Method to check if an element exists in the list
    bool isExist(const T& element) {
        SingleNode<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == element) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Method to check if an element is at a specific index
    bool isItemAtEqual(const T& element, int index) {
        if (index < 0 || index >= size) {
            cout << "Index out of bounds" << endl;
            return false;
        }
        return retrieveAt(index) == element;
    }

    // Method to swap two elements without swapping data
    void swap(int firstItemIdx, int secondItemIdx) {
        if (firstItemIdx < 0 || firstItemIdx >= size || secondItemIdx < 0 || secondItemIdx >= size) {
            cout << "Index out of bounds" << endl;
            return;
        }
        if (firstItemIdx == secondItemIdx) {
            return;
        }
        if (firstItemIdx > secondItemIdx) {
            swap(firstItemIdx, secondItemIdx);
        }

        SingleNode<T>* firstPrev = nullptr;
        SingleNode<T>* firstCurr = head;
        for (int i = 0; i < firstItemIdx; i++) {
            firstPrev = firstCurr;
            firstCurr = firstCurr->next;
        }

        SingleNode<T>* secondPrev = nullptr;
        SingleNode<T>* secondCurr = head;
        for (int i = 0; i < secondItemIdx; i++) {
            secondPrev = secondCurr;
            secondCurr = secondCurr->next;
        }

        if (firstPrev != nullptr) {
            firstPrev->next = secondCurr;
        } else {
            head = secondCurr;
        }

        if (secondPrev != nullptr) {
            secondPrev->next = firstCurr;
        } else {
            head = firstCurr;
        }

        swap(firstCurr->next, secondCurr->next);
    }

    // Method to check if the list is empty
    bool isEmpty() {
        return head == nullptr;
    }

    // Method to get the size of the list
    int linkedListSize() {
        return size;
    }

    // Method to clear the list
    void clear() {
        while (head != nullptr) {
            removeAtHead();
        }
    }

    // Method to print the list
    void print() {
        SingleNode<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

#endif //DATASTUCTUREASS_SINGLELINKEDLIST_H
