// Names: Abdelrahman Mostafa Sayed - Mohamed Sayed Shebl - Ahmed Abdelhakim Salah -
//                Adham Salah Ezzat - Ahmed Atef Mohamed
// IDs: 20220197 - 20220290 - 20221010 - 20220051 - 20220024
// Sections: S10 - S7 - All-B - S9 - S10

#include <iostream>
#include "SingleLinkedList.h"
#include "DoubleLinkedList.h"
#include "CircularLinkedList.h"
#include "Stack.h"
#include "Queue.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "Single Linked-List Testing\n"; // Single Linked-List Testing

    LinkedList<int> myList;
    myList.insertAtHead(1);
    myList.insertAtHead(2);
    myList.insertAtHead(3);
    myList.insertAtTail(4);
    myList.print(); // Output: 3 2 1 4

    myList.removeAt(1);
    myList.print(); // Output: 3 1 4

    cout << "Element at index 1: " << myList.retrieveAt(1) << endl; // Output: 1

    myList.replaceAt(5, 1);
    myList.print(); // Output: 3 5 4

    cout << "Is 5 in the list? " << (myList.isExist(5) ? "Yes" : "No") <<endl; // Output: Yes

    cout << "List size: " << myList.linkedListSize() << endl; // Output: 3

    myList.clear();
    cout << "List cleared." <<endl;
    cout << "Is list empty? " << (myList.isEmpty() ? "Yes" : "No") << endl; // Output: Yes

    cout << endl << endl << endl;

    ////////////////////////////////////////////////////////////////////////////////////////////

    cout << "Double Linked-List Testing\n"; // Double Linked-List Testing

    DoubleLinkedList<int> dll;
    dll.insertAtHead(1);
    dll.insertAtHead(2);
    dll.insertAtHead(3);
    dll.insertAtTail(4);
    dll.insertAtTail(5);
    dll.print(); // Output: 3 2 1 4 5
    dll.removeAtHead();
    dll.removeAtTail();
    dll.print(); // Output: 2 1 4
    dll.insertAt(3, 2);
    dll.print(); // Output: 2 1 3 4
    cout << dll.retrieveAt(2) << endl; // Output: 3
    dll.replaceAt(7, 2);
    dll.print(); // Output: 2 1 7 4
    cout << boolalpha << dll.isExist(7) << endl; // Output: true
    cout << boolalpha << dll.isItemAtEqual(7, 2) << endl; // Output: true
    dll.swap(1, 2);
    dll.print(); // Output: 2 7 1 4
    cout << boolalpha << dll.isEmpty() << endl; // Output: false
    cout << dll.linkedListSize() << endl; // Output: 4

    cout << endl << endl << endl;

    ////////////////////////////////////////////////////////////////////////////////////////////

    cout << "Circular Linked-List Testing\n"; // Circular Linked-List Testing
    CircularLinkedList<int> l;

    // Test: Insert at head
    l.insertAtHead(5);
    l.insertAtHead(6);
    l.insertAtHead(7);
    cout << "After inserting 7, 6, 5 at head, list is: ";
    l.print();

    // Test: Insert at specific index
    l.insertAt(8, 1);
    cout << "After inserting 8 at index 1, list is: ";
    l.print();

    // Test: Remove at head
    l.removeAtHead();
    cout << "After removing at head, list is: ";
    l.print();

    // Test: Remove at tail
    l.removeAtTail();
    cout << "After removing at tail, list is: ";
    l.print();

    // Test: Remove at specific index
    l.removeAt(1);
    cout << "After removing at index 1, list is: ";
    l.print();

    // Test: Retrieve at index
    cout << "Element at index 0: " << l.retrieveAt(0) << endl;

    // Test: Replace at index
    l.replaceAt(8, 0);
    cout << "After replacing at index 0 with 8, list is: ";
    l.print();

    // Test: Check existence of elements
    cout << "Does 5 exist? " << (l.isExist(5) ? "Yes" : "No") << endl;
    cout << "Does 8 exist? " << (l.isExist(8) ? "Yes" : "No") << endl;

    // Test: Check if element at index is equal to value
    cout << "Is item at index 0 equal to 5? " << (l.isItemAtEqual(5, 0) ? "Yes" : "No") << endl;
    cout << "Is item at index 0 equal to 8? " << (l.isItemAtEqual(8, 0) ? "Yes" : "No") << endl;

    // Test: Insert at head and swap
    l.insertAtHead(5);
    cout << "After inserting 5 at head, list is: ";
    l.print();
    l.swap(0, 1);
    cout << "After swapping elements at index 0 and 1, list is: ";
    l.print();

    // Test: Check if list is empty
    cout << "Is list empty? " << (l.isEmpty() ? "Yes" : "No") << endl;

    // Test: Clear list
    l.clear();
    cout << "After clearing list, is list empty? " << (l.isEmpty() ? "Yes" : "No") << endl;

    cout << endl << endl << endl;

    ////////////////////////////////////////////////////////////////////////////////////////////

    cout << "Stack Testing\n"; // Stack Testing

    Stack<int> stack;

    // Test push
    stack.push(1);
    cout << "After pushing 1: ";
    stack.print();

    // Test push
    stack.push(2);
    cout << "After pushing 2: ";
    stack.print();

    // Test top
    cout << "Top of stack: " << stack.top() << endl;

    // Test pop
    stack.pop();
    cout << "After popping: ";
    stack.print();

    // Test isEmpty
    cout << "Is stack empty? " << (stack.isEmpty() ? "Yes" : "No") << endl;

    // Test stackSize
    cout << "Size of stack: " << stack.stackSize() << endl;

    cout << endl << endl << endl;

    ////////////////////////////////////////////////////////////////////////////////////////////

    cout << "Queue Testing\n"; // Queue Testing

    // Create a Queue of integers
    Queue<int> q(10);

    // Test enqueue
    for (int i = 0; i < 10; i++) {
        q.enqueue(i);
    }

    // Test print
    q.print();

    // Test dequeue
    for (int i = 0; i < 5; i++) {
        cout << "Dequeued: " << q.dequeue() << endl;
    }

    // Test print after dequeue
    q.print();

    return 0;
}
