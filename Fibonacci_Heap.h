#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <iostream>
#include <unordered_map>
#include <cmath>
// Conventions: NIL = nullptr
//              Node* left and right pointers are used to form a circular doubly linked list
//              Node* child pointer is used to point to the leftmost child

template <typename ValueType>
class FibonacciHeap {
public:
    struct Node {
        public:  // Node must tbe private , because the user should not be able to create a node without the heap
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

    void insert(ValueType value); // mohamed tarek
    void merge(FibonacciHeap& other); // mohamed tarek
    bool isEmpty() const; // john, farrag
    Node* extractMin(); // nasri, farrag
    void decreaseKey(Node* node, ValueType newValue); // hady
    void deleteNode(Node* node); // hady
    Node* getMin() const; //john

private:
    Node* minNode;
    int nodeCount;

    //Used by decrease key to clean up the heap to be in the fib sequence
    void consolidate(); // nasri
    //Used by the consolidate function to make a node in the root list become a child
    void link(Node* y, Node* x); // mohamed tarek
    //Used by decrease key to remove a child and append it to the root list
    void cut(Node* x, Node* y); //hady NOTE: check if this is the last child of y, if so, set y->child to nullptr
    //Used by decrease key to propagate the cut upwards through the tree, recursively until a non-marked node is found or the root is reached.
    void cascadingCut(Node* y); // hady
    void deleteAll(Node* node); // farrag
    void swap(Node*& x, Node*& y);
};

#endif // FIBONACCI_HEAP_H