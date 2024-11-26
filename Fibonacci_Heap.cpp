#include "Fibonacci_Heap.h";
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
template <typename ValueType>
FibonacciHeap< ValueType>::FibonacciHeap() { //constructor
    minNode = nullptr;
    nodeCount = 0;
}

template <typename ValueType>
void FibonacciHeap<ValueType>::insert(ValueType value) {
    Node* x = new Node(value);

    x->degree = 0;
    x->parent = nullptr;
    x->child = nullptr;
    x->marked = false;
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
typename FibonacciHeap<ValueType>::Node* FibonacciHeap<ValueType>::getMin() const {
    // Implementation here
    return this->minNode;
}

template <typename ValueType>
typename FibonacciHeap<ValueType>::Node* FibonacciHeap<ValueType>::extractMin() {
     Node* z = minNode;
     if(!empty()){
        while(z->child != nullptr)
        //add x to the roo tlist of H
           cut(z->child, z); // x.p = nullprt   z.degree--  x.marked = false insertNode(z-> child) nodeCount++
        // remove z from the root list
        z->left->right = z->right;
        z->right->left = z->left;  
        if(z == z->right)
            minNode = nullptr;
        else{
            minNode = z->right;
            consolidate();
            nodeCount--;
        }   
        return z; 
     }
    cerr<<"The heap is empty"<<endl;
    return nullptr;
}

template <typename ValueType>
void FibonacciHeap<ValueType>::decreaseKey(Node* x, ValueType k) {
    // Empty implementation
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
void FibonacciHeap<ValueType>::cut(Node* x, Node* y) {
    // Empty implementation
}

template <typename ValueType>
void FibonacciHeap<ValueType>::cascadingCut(Node* y) {
    // Empty implementation
}
template <typename ValueType>
void FibonacciHeap<ValueType>::link(Node* y, Node* x) {
    // Empty implementation
}
template <typename ValueType>
void FibonacciHeap<ValueType>::swap(Node*& x, Node*& y) {
    Node* temp = x; 
    x = y;
    y = temp;
}