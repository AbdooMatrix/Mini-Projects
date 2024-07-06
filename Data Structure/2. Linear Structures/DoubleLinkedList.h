// Name: Ahmed Atef Mohamed
// ID: 20220024

#ifndef DATASTUCTUREASS_DOUBLELINKEDLIST_H
#define DATASTUCTUREASS_DOUBLELINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
struct DoubleNode {
    T data;
    DoubleNode* prev;
    DoubleNode* next;

    DoubleNode(const T& data) : data(data), prev(nullptr), next(nullptr) {}
};

template <typename T>
class DoubleLinkedList {
private:
    DoubleNode<T>* head = nullptr;
    DoubleNode<T>* tail = nullptr;
    int size = 0;

public:
    void insertAtHead(const T& element) {
        DoubleNode<T>* newDoubleNode = new DoubleNode<T>(element);
        if (!isEmpty()) {
            newDoubleNode->next = head;
            head->prev = newDoubleNode;
        } else {
            tail = newDoubleNode;
        }
        head = newDoubleNode;
        size++;
    }

    void insertAtTail(const T& element) {
        DoubleNode<T>* newDoubleNode = new DoubleNode<T>(element);
        if (!isEmpty()) {
            tail->next = newDoubleNode;
            newDoubleNode->prev = tail;
        } else {
            head = newDoubleNode;
        }
        tail = newDoubleNode;
        size++;
    }

    void insertAt(const T& element, int index) {
        if (index < 0 || index > size) return;
        if (index == 0) return insertAtHead(element);
        if (index == size) return insertAtTail(element);
        DoubleNode<T>* newDoubleNode = new DoubleNode<T>(element);
        DoubleNode<T>* current = head;
        for (int i = 0; i < index - 1; i++) current = current->next;
        newDoubleNode->next = current->next;
        newDoubleNode->prev = current;
        current->next->prev = newDoubleNode;
        current->next = newDoubleNode;
        size++;
    }

    void removeAtHead() {
        if (isEmpty()) return;
        DoubleNode<T>* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        size--;
    }

    void removeAtTail() {
        if (isEmpty()) return;
        DoubleNode<T>* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        size--;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) return;
        if (index == 0) return removeAtHead();
        if (index == size - 1) return removeAtTail();
        DoubleNode<T>* current = head;
        for (int i = 0; i < index; i++) current = current->next;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
    }

    T retrieveAt(int index) {
        if (index < 0 || index >= size) throw out_of_range("Index out of range");
        DoubleNode<T>* current = head;
        for (int i = 0; i < index; i++) current = current->next;
        return current->data;
    }

    void replaceAt(const T& newElement, int index) {
        if (index < 0 || index >= size) return;
        DoubleNode<T>* current = head;
        for (int i = 0; i < index; i++) current = current->next;
        current->data = newElement;
    }

    bool isExist(const T& element) const {
        DoubleNode<T>* current = head;
        while (current) {
            if (current->data == element) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool isItemAtEqual(const T& element, int index) const {
        if (index < 0 || index >= size) return false;
        DoubleNode<T>* current = head;
        for (int i = 0; i < index; i++) current = current->next;
        return current->data == element;
    }

    void swap(int firstItemIdx, int secondItemIdx) {
        if (firstItemIdx < 0 || firstItemIdx >= size || secondItemIdx < 0 || secondItemIdx >= size) return;
        if (firstItemIdx == secondItemIdx) return;
        DoubleNode<T>* firstDoubleNode = head;
        DoubleNode<T>* secondDoubleNode = head;
        for (int i = 0; i < firstItemIdx; i++) firstDoubleNode = firstDoubleNode->next;
        for (int i = 0; i < secondItemIdx; i++) secondDoubleNode = secondDoubleNode->next;
        T temp = firstDoubleNode->data;
        firstDoubleNode->data = secondDoubleNode->data;
        secondDoubleNode->data = temp;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int linkedListSize() const {
        return size;
    }

    void clear() {
        while (!isEmpty()) removeAtTail();
    }

    void print() const {
        DoubleNode<T>* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~DoubleLinkedList() {
        clear();
    }
};

#endif //DATASTUCTUREASS_DOUBLELINKEDLIST_H
