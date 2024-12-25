#include <iostream>
#include "Patient.hpp"
#include "Patient.cpp"
using namespace std;

const int TableSize = 30;

// template <typename KeyType, typename ValueType>
template <typename KeyType, typename ValueType>
class HashMap {
    private:
        struct Node {
            int key;
            KeyType ID;
            ValueType value;
            Node(int k = -1, KeyType ID = KeyType(), ValueType val = ValueType()) : key(k), ID(ID), value(val) {};
        };

        Node* table;
        int numberOfElements;
        int capacity;

        int hash(int ID) const {
            return ID % capacity;
        }

        int hash2(int ID) const {
            int prime = 7;  // A small prime number for step size
            return prime - (ID % prime);  // This ensures a non-zero step size
        }

        void resize() {
            int oldCapacity = capacity;
            capacity = 2 * capacity;
            Node* oldTable = table;
            table = new Node[capacity];
            numberOfElements = 0;

            for (int i = 0; i < oldCapacity; i++) {
                if (oldTable[i].key != -1 && oldTable[i].key != -2) {
                    HashMap<KeyType, ValueType>::insertDouble(oldTable[i].ID, oldTable[i].value);
                }
            }
            delete[] oldTable;
        };

       

    public:
        HashMap(int capacity = TableSize);
        ~HashMap();
        void insertDouble(KeyType ID, ValueType value);
        void removeDouble(KeyType patientID);
        ValueType searchDouble(KeyType patientID) const;
};

 
template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap(int capacity): capacity(capacity), numberOfElements(0) {
    table = new Node[capacity];
    if (table == NULL) {
        cout << "Error while initializing the map";
        exit(0);
    }
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::~HashMap() {
    delete[] table;
}
template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::insertDouble(KeyType patientID, ValueType value) {
    if (numberOfElements >= 0.75 * capacity) {
        HashMap<KeyType, ValueType>::resize();
    }
    int index = hash(patientID);
    int stepSize = hash2(patientID);
    while (true) {
        if (table[index].ID == patientID) {
            cout << "Patient with ID: " << patientID << " already exists." << endl;
            return;
        }
        if (table[index].key == -1 || table[index].key == -2) {
            table[index] = Node(index, patientID, value);
            numberOfElements++;
            return;
        }
        index = (index + stepSize) % capacity;
    }

}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::removeDouble(KeyType patientID) {
    int index = hash(patientID);
    int stepSize = hash2(patientID);
    while (true) {
        if (table[index].key == -1) {
            cout << "Patient with ID: " << patientID << " does NOT exist." << endl;
            return;
        }
        if (table[index].ID == patientID) {
            table[index].key = -2;
            table[index].ID = KeyType();
            table[index].value = ValueType();
            numberOfElements--;
            return;
        }
        index = (index + stepSize) % capacity;
    }
}

template <typename KeyType, typename ValueType>
ValueType HashMap<KeyType, ValueType>::searchDouble(KeyType patientID) const {
    int index = hash(patientID);
    int stepSize = hash2(patientID);
    while (true) {
        if (table[index].key == -1) {
            cout << "Patient with ID: " << patientID << " does NOT exist." << endl;
            return ValueType(); // Return default constructed ValueType
        }
        if (table[index].ID == patientID) {
            return table[index].value;
        }
        index = (index + stepSize) % capacity;
    }
    return ValueType(); // Key not found, return default constructed ValueType
}