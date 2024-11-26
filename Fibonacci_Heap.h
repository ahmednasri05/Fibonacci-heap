#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <iostream>
#include <unordered_map>
#include <cmath>

template <typename ValueType>
class FibonacciHeap {
public:
    struct Node {
        ValueType value;
        int degree;
        bool marked;
        Node* parent;
        Node* child;
        Node* left;
        Node* right;

        Node(ValueType v)
            : value(v), degree(0), marked(false), parent(nullptr), child(nullptr), left(this), right(this) {}
    };

    FibonacciHeap();
    ~FibonacciHeap();

    void insert(ValueType value);
    void merge(FibonacciHeap& other);
    bool isEmpty() const;
    Node* extractMin() const;
    void deleteMin();
    void decreaseKey(Node* node, ValueType newValue);
    void deleteNode(Node* node);
    Node* getMin() const;

private:
    Node* minNode;
    int nodeCount;

    //Used by decrease key to clean up the heap to be in the fib sequence
    void consolidate();
    //Used by the consolidate function to make a node in the root list become a child
    void link(Node* y, Node* x);
    //Used by decrease key to remove a child and append it to the root list
    void cut(Node* x, Node* y);
    //Used by decrease key to propagate the cut upwards through the tree, recursively until a non-marked node is found or the root is reached.
    void cascadingCut(Node* y);
    void deleteAll(Node* node);
};

#endif // FIBONACCI_HEAP_H