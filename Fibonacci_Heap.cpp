/*
#include "Fibonacci_Heap.h";
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

template <typename ValueType>
FibonacciHeap<ValueType>::FibonacciHeap() {
    minNode = nullptr;
    nodeCount = 0;
}

template <typename ValueType>
FibonacciHeap<ValueType>::~FibonacciHeap() {
    deleteAll(minNode);
}

template <typename ValueType>
void FibonacciHeap<ValueType>::insert(ValueType value) {
    Node* x = new Node(value);
    if (minNode == nullptr) {
        x->right = x;
        x->left = x;
        minNode = x;
    } else {
        x->right = minNode;
        x->left = minNode->left;
        minNode->left->right = x;
        minNode->left = x;

        if (x->value < minNode->value) {
            minNode = x;
        }
    }
    nodeCount++;
}

template <typename ValueType>
FibonacciHeap<ValueType>::NodePointer FibonacciHeap<ValueType>::extractMin() {
    // Empty implementation
}
template <typename ValueType>
typename FibonacciHeap<ValueType>::Node* FibonacciHeap<ValueType>::getMin() const {
    return minNode;
}

template <typename ValueType>
void FibonacciHeap<ValueType>::merge(FibonacciHeap& other) {
    // Empty implementation
}

template <typename ValueType>
bool FibonacciHeap<ValueType>::isEmpty() const{
    // Empty implementation
}

template <typename ValueType>
void FibonacciHeap<ValueType>::decreaseKey(Node* node, ValueType newValue) {
    if (newValue > node->value) {
        cout << "New Value is greater than current" << endl;
        exit(0);
    }
    //Update the desired node with the decreased value
    node->value = newValue;
    //Get Parent
    Node* parent = node->parent;
    //If new value is smaller than parent cut and mark parent
    if (parent != nullptr && parent->value > node->value) {
        cout << "hell" << endl;
        cut(node, parent);
        cascadingCut(parent);
    }
    //Update min
    if (node->value < minNode->value) {
        minNode = node;
    }

}

template <typename ValueType>
void FibonacciHeap<ValueType>::cut(Node* x, Node* y) {
    //If x is the only child, set y's child to nullptr.
    if (x->right == x) {
        y->child = nullptr;
    } else {
        //Remove x from its sibilings
        x->right->left = x->left;
        x->left->right = x->right;
        //Connect y child to any of the siblings
        if (y->child == x) {
            y->child = x->right;
        }
    }
    y->degree--;
    //Add the node in the root list
    x->right = minNode;
    x->left = minNode->left;
    minNode->left->right = x;
    minNode->left = x;
    //Remove its parent and unmark it
    x->parent = nullptr;
    x->marked = false;
}
template <typename ValueType>
void FibonacciHeap<ValueType>::cascadingCut(Node* y) {
    Node* z = y->parent;
    //Only enters if y has parent because if y doesn't have a parent it is already in the root list
    if (z != nullptr) {
        //Mark true if unmarked because this function is always called after cutting
        if (!y->marked) {
            y->marked = true;
        } else {
            //If marked cut and recurse using the parent until until a non-marked node is found or the root is reached
            cut(y, z);
            cascadingCut(z);
        }
    }
}

template <typename ValueType>
void FibonacciHeap<ValueType>::deleteNode(Node* x) {
    // Empty implementation
}

template <typename ValueType>
void FibonacciHeap<ValueType>::consolidate() {
    // array size is log(n) base 1.618, which is the golden ration aka fibonacci ratio
     int arraySize = static_cast<int>(log(nodeCount) / log(1.618)) + 1;
    Node** degreeTable = new Node*[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        degreeTable[i] = nullptr;
    }
    vector<Node*> rootNodes;
    Node* current = minNode;
    if (current != nullptr) {
        do {
            rootNodes.push_back(current);
            current = current->right;
        } while (current != minNode);
    }

    for (Node* w : rootNodes) {
        Node* x = w;
        int d = x->degree;
        while (degreeTable[d] != nullptr) {
            Node* y = degreeTable[d];
            if (x->value > y->value) {
                swap(x, y);
            }
            link(y, x);
            degreeTable[d] = nullptr;
            d++;
        }
        degreeTable[d] = x;
    }

    minNode = nullptr;
for (int i = 0; i < arraySize; i++) {
    if (degreeTable[i] != nullptr) {
        if (minNode == nullptr) {
            minNode = degreeTable[i];
            minNode->left = minNode;
            minNode->right = minNode;
        } else {
            degreeTable[i]->left = minNode;
            degreeTable[i]->right = minNode->right;
            minNode->right->left = degreeTable[i];
            minNode->right = degreeTable[i];
            if (degreeTable[i]->value < minNode->value) {
                minNode = degreeTable[i];
            }
        }
    }
}
    delete[] degreeTable;
}

template <typename ValueType>
void FibonacciHeap<ValueType>::swap(Node*& x, Node*& y) {
    Node* temp = x; 
    x = y;
    y = temp;
}

template <typename ValueType>
void FibonacciHeap<ValueType>::link(Node* y, Node* x) {
    // Empty implementation
}
template <typename ValueType>
void FibonacciHeap<ValueType>::deleteAll(Node* node) {
    // Empty implementation
}
template <typename ValueType>
void FibonacciHeap<ValueType>::printTree(Node* node, int level) {
    if (!node) return;

    Node* start = node;
    do {
        // Indent according to the level
        for (int i = 0; i < level; ++i) {
            cout << "   ";
        }
        // Print the node value
        cout << node->value;
        if (node->child) {
            cout << " -> {" << endl;
            printTree(node->child, level + 1);
            for (int i = 0; i < level; ++i) {
                cout << "   ";
            }
            cout << "}";
        }
        cout << endl;

        node = node->right;
    } while (node != start);
}

template <typename ValueType>
void FibonacciHeap<ValueType>::print() {
    if (!minNode) {
        cout << "The Fibonacci Heap is empty." << endl;
        return;
    }

    cout << "Fibonacci Heap:" << endl;
    printTree(minNode, 0);
}  */
