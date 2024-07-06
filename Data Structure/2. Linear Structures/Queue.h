template<typename T>
class Queue {
private:
    T* elements;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

public:
    Queue(int capacity) : capacity(capacity), frontIndex(0), rearIndex(-1), count(0) {
        elements = new T[capacity];
    }

    ~Queue() {
        delete[] elements;
    }

    void enqueue(T element) {
        if (count == capacity) {
            resize();
        }
        rearIndex = (rearIndex + 1) % capacity;
        elements[rearIndex] = element;
        count++;
    }


    T dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
        }else{
            T frontElement = elements[frontIndex];
            frontIndex = (frontIndex + 1) % capacity;
            count--;
            return frontElement;
        }
    }

    T first() {
        if (isEmpty()) {
            cout << "Queue is empty. Cannot retrieve first element." << endl;
        }else return elements[frontIndex];
    }

    bool isEmpty() {
        return count == 0;
    }

    int queueSize() {
        return count;
    }

    void clear() {
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    void print() {
        int i = frontIndex;
        int elementsPrinted = 0;
        while (elementsPrinted < count) {
            cout << elements[i] << " ";
            i = (i + 1) % capacity;
            elementsPrinted++;
        }
        cout << endl;
    }

    void resize() {
        int newCapacity = capacity * 2; // Double the capacity
        T* newElements = new T[newCapacity];

        // Copy elements to the new array
        int j = 0;
        for (int i = frontIndex; i != (rearIndex + 1) % capacity; i = (i + 1) % capacity) {
            newElements[j++] = elements[i];
        }

        delete[] elements;
        elements = newElements;
        frontIndex = 0;
        rearIndex = count - 1;
        capacity = newCapacity;
    }
};