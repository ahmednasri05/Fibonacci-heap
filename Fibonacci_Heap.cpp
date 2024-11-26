#include "Fibonacci_Heap.h";

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