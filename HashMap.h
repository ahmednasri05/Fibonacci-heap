#include <iostream>
#include "Patient.hpp"
#include "Patient.cpp"
using namespace std;

const int TableSize = 11;

// template <typename KeyType, typename ValueType>
template <typename KeyType, typename ValueType>
class HashMap {
    private:
        struct Node {
            int key;
            ValueType value;
            Node(int k = -1, ValueType val = nullptr) : key(k), value(val) {};
        };

        Node* table;
        int numberOfElements;
        int capacity;

        int hash(int ID) {
            return ID % capacity;
        }

        int hash2(int ID) {
            int prime = 7;  // A small prime number for step size
            return prime - (ID % prime);  // This ensures a non-zero step size
        }

        // void resize() {
        //     int oldCapacity = capacity;
        //     capacity = 2 * capacity;
        //     Node* oldTable = table;
        //     table = new Node[capacity];
        //     numberOfElements = 0;

        //     for (int i = 0; i < oldCapacity; i++) {
        //         if (oldTable[i].key != -1 && oldTable[i].key != -2) {
        //             HashMap<KeyType, ValueType>::insertDouble(oldTable[i].value);
        //         }
        //     }
        //     delete[] oldTable;
        // };

       

    public:
        HashMap();
        ~HashMap();
        void insertDouble(ValueType value);
        void removeDouble(ValueType value);
        ValueType searchDouble(ValueType value);
};

 
template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap() : numberOfElements(0), capacity(TableSize) {
        table = new Node[capacity];
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::~HashMap() {
    delete[] table;
}
template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::insertDouble(ValueType value) {
    if (numberOfElements >= 0.75 * capacity) {
        // resize();
    }
    int index = hash(value->getId());
    int stepSize = hash2(value->getId());
    while (true) {
        if (table[index].key == value->getId()) {
            cout << "Patient with ID: " << value->getId() << " already exists." << endl;
            return;
        }
        if (table[index].key == -1 || table[index].key == -2) {
            table[index] = Node(index, value);
            numberOfElements++;
            return;
        }
        index = (index + stepSize) % capacity;
    }

}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::removeDouble(ValueType value) {
    int index = hash(value->getId());
    int stepSize = hash2(value->getId());
    while (true) {
        if (table[index].key == -1) {
            cout << "Patient with ID: " << value->getId() << " does NOT exist." << endl;
            return;
        }
        if (table[index].key == value->getId()) {
            table[index].key = -2;
            table[index].value = nullptr;
            numberOfElements--;
            return;
        }
        index = (index + stepSize) % capacity;
    }
}

template <typename KeyType, typename ValueType>
ValueType HashMap<KeyType, ValueType>::searchDouble(ValueType value) {
    int index = hash(value->getId());
    int stepSize = hash2(value->getId());
    while (true) {
        if (table[index].key == -1) {
            cout << "Patient with ID: " << value->getId() << " does NOT exist." << endl;
            return nullptr;
        }
        if (table[index].key == value->getId()) {
            return table[index].value;
        }
        index = (index + stepSize) % capacity;
    }
    return nullptr; // Key not found
}