// Name: Ahmed Abdelhakeem Salah
// ID: 20221010

#ifndef DATASTUCTUREASS_CIRCULARLINKEDLIST_H
#define DATASTUCTUREASS_CIRCULARLINKEDLIST_H

#include <iostream>

using namespace std;

// Template for node in a circular linked list
template<typename T>
struct CircularNode {
    T data;  // Data stored in the node
    CircularNode *link;  // Link to the next node
};

// Template for a circular linked list
template<typename T>
class CircularLinkedList {
protected:
    int size;  // Size of the list
    CircularNode<T> *head;  // Head of the list
    CircularNode<T> *tail;  // Tail of the list
public:
    // Constructor
    CircularLinkedList() {
        size = 0;
        head = NULL;
        tail = NULL;
    }

    // Destructor
    ~CircularLinkedList() {
        CircularNode<T> *current = head;
        while (current != NULL) {
            CircularNode<T> *link = current->link;
            delete current;
            current = link;
        }
        head = NULL;
        tail = NULL;
    }

    // Insert an item at the head of the list
    void insertAtHead(T item) {
        CircularNode<T> *newCircularNode = new CircularNode<T>();
        newCircularNode->data = item;
        if (head == NULL) {
            head = newCircularNode;
            tail = newCircularNode;
            newCircularNode->link = head;
        } else {
            newCircularNode->link = head;
            head = newCircularNode;
            tail->link = head;
        }
        size++;
    }

    // Insert an item at the tail of the list
    void insertAtTail(T item) {
        if (head == NULL) {
            insertAtHead(item);
        } else {
            CircularNode<T> *newCircularNode = new CircularNode<T>();
            newCircularNode->data = item;
            newCircularNode->link = head;
            tail->link = newCircularNode;
            tail = newCircularNode;
            size++;
        }
    }

    // Remove the item at the head of the list
    void removeAtHead() {
        if (head == NULL) {
            return;
        } else {
            CircularNode<T> *temp = head;
            head = head->link;
            tail->link = head;
            delete temp;
            size--;
            if (size == 0) {
                head = NULL;
                tail = NULL;
            }
        }
    }

    // Remove the item at the tail of the list
    void removeAtTail() {
        if (head == NULL) {
            return;
        } else {
            CircularNode<T> *temp = head;
            while (temp->link != tail) {
                temp = temp->link;
            }
            temp->link = head;
            delete tail;
            tail = temp;
            size--;
            if (size == 0) {
                head = NULL;
                tail = NULL;
            }
        }
    }

    // Print the list
    void print() {
        if (head == NULL) {
            return;
        } else {
            CircularNode<T> *temp = head;
            do {
                cout << temp->data << " ";
                temp = temp->link;
            } while (temp != head);
            cout << endl;
        }
    }

    // Insert an element at a specific index
    void insertAt(T element, int index) {
        if (index > size || index < 0) {
            cout << "you can't insert out of index 0 to index " << size << endl;
            return;
        }
        if (index == 0) insertAtHead(element);
        else if (index == size - 1) insertAtTail(element);
        else {
            ++size;
            CircularNode<T> *newCircularNode = new CircularNode<T>, *p;
            p = tail;

            for (int i = 0; i < index; ++i) {
                p = p->link;
            }
            newCircularNode->data = element;
            newCircularNode->link = p->link;

            p->link = newCircularNode;
        }
    }

    // Remove an element at a specific index
    void removeAt(int index) {
        if (head == NULL || index >= size) return;

        if (index == 0) { removeAtHead(); }
        else if (index == size - 1) { removeAtTail(); }

        else {
            --size;
            CircularNode<T> *current = head;
            CircularNode<T> *next = nullptr;
            for (int i = 0; i < index - 1; ++i) {
                current = current->link;
            }
            next = current->link;
            current->link = current->link->link;
            if (next == tail) {
                tail = current;
            }
            delete next;
            if (size == 0) {
                head = NULL;
                tail = NULL;
            }
        }
    }

    // Retrieve an element at a specific index
    T retrieveAt(int index) {
        if (index > size - 1) {
            cout << "you can't retrieve out of index 0 to index " << size << endl;
            return T();
        }
        CircularNode<T> *current;
        current = head;
        for (int i = 0; i < index; ++i) {
            current = current->link;
        }
        return current->data;
    }

    // Replace an element at a specific index
    void replaceAt(T newElement, int index) {
        if (index > size - 1) {
            cout << "you can't retrieve out of index 0 to index " << size << endl;
            return;
        }
        CircularNode<T> *current;
        current = head;
        for (int i = 0; i < index; ++i) {
            current = current->link;
        }
        current->data = newElement;
    }

    // Check if an element exists in the list
    bool isExist(T element) {
        CircularNode<T> *current = head;
        if (current->data == element) return true;
        current = current->link;
        while (current != head) {
            if (current->data == element) return true;
            current = current->link;
        }
        return false;
    }

    // Check if an element is at a specific index
    bool isItemAtEqual(T element, int index) {
        if (index > size - 1) {
            cout << "element out of scope";
            return false;
        }
        CircularNode<T> *current;
        current = head;
        for (int i = 0; i < index; ++i) {
            current = current->link;
        }
        return current->data == element;
    }

    // Swap two elements in the list
    void swap(int headItemIdx, int secondItemIdx) {
        if (size < 2 || headItemIdx < 0 || headItemIdx > size || secondItemIdx < 0 || secondItemIdx > size ||
            headItemIdx == secondItemIdx)
            return;
        CircularNode<T> *c1, *c2, *n1, *n2, *p1 = head, *p2 = head;
        if (headItemIdx > secondItemIdx) {
            swap(secondItemIdx, headItemIdx);
            return;
        }
        if (secondItemIdx - headItemIdx == 1) {
            if (headItemIdx == 0) {
                p1 = tail;
                c1 = head;
                c2 = head->link;
            } else {
                for (int i = 0; i < headItemIdx - 1; ++i) {
                    p1 = p1->link;
                }
                c1 = p1->link;
                c2 = c1->link;
            }
            p1->link = c2;
            c1->link = c2->link;
            c2->link = c1;
            if (headItemIdx == 0) head = c2;
            if (secondItemIdx == size - 1) tail = c1;
        } else if (headItemIdx == 0 && secondItemIdx == size - 1) {
            for (int i = 0; i < secondItemIdx - 1; ++i) {
                p1 = p1->link;
            }
            c2 = tail;
            c1 = head;
            p1->link = c1;
            c2->link = c1->link;
            c1->link = c2;
            head = c2;
            tail = c1;

        } else {
            if (headItemIdx == 0) {
                p1 = tail;
                c1 = head;
                n1 = head->link;
            } else {
                for (int i = 0; i < headItemIdx - 1; ++i) {
                    p1 = p1->link;
                }
                c1 = p1->link;
                n1 = c1->link;
            }
            for (int i = 0; i < secondItemIdx - 1; ++i) {
                p2 = p2->link;
            }
            c2 = p2->link;
            n2 = c2->link;

            c1->link = n2;
            c2->link = n1;
            p1->link = c2;
            p2->link = c1;
            if (secondItemIdx == size - 1) tail = c1;
            if (headItemIdx == 0) head = c2;
        }
    }

    // Check if the list is empty
    bool isEmpty() {
        return (head == NULL);
    }

    // Get the size of the list
    int linkedListSize() {
        return size;
    }

    // Clear the list
    void clear() {
        if (head == NULL) return;
        CircularNode<T> *current = head, *next = nullptr;
        do {
            next = current->link;
            delete current;
            current = next;
        } while (current != head);
        head = NULL;
        tail = NULL;
        size = 0;
    }
};

#endif //DATASTUCTUREASS_CIRCULARLINKEDLIST_H
