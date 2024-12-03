#include "Fibonacci_Heap.cpp"
#include <string>
#include <iostream>
using namespace std;

int main() {
    FibonacciHeap<int> fibHeap;

    // Test Case 1: Insert nodes into the root list
    cout << "Test Case 1: Insert Nodes into Root List\n";
    fibHeap.insert(10);
    fibHeap.insert(5);
    fibHeap.insert(20);
    fibHeap.insert(3);
    fibHeap.insert(15);

    cout << "Tree structure after inserting nodes into the root list:\n";
    fibHeap.print();
    cout << "-----------------------------------\n";

    // Test Case 2: Manually construct a tree
    cout << "Test Case 2: Manually Construct a Tree\n";

    FibonacciHeap<int>::Node* node10 = nullptr;
    FibonacciHeap<int>::Node* node5 = nullptr;
    FibonacciHeap<int>::Node* node20 = nullptr;
    FibonacciHeap<int>::Node* node3 = nullptr;
    FibonacciHeap<int>::Node* node15 = nullptr;

    FibonacciHeap<int>::Node* current = fibHeap.getMin();
    do {
        if (current->value == 10) node10 = current;
        if (current->value == 5) node5 = current;
        if (current->value == 20) node20 = current;
        if (current->value == 3) node3 = current;
        if (current->value == 15) node15 = current;
        current = current->right;
    } while (current != fibHeap.getMin());
    FibonacciHeap<int>::Node* child2;
    // Add children manually
    if (node10) {
        node10->child = new FibonacciHeap<int>::Node(20);
        node10->child->parent = node10;
        node10->child->right = node10->child->left = node10->child;

        child2 = new FibonacciHeap<int>::Node(25);
        child2->parent = node10;
        child2->right = node10->child;
        child2->left = node10->child;
        node10->child->right = child2;
        node10->child->left = child2;

        node10->degree = 2;
    }

    if (node5) {
        node5->child = new FibonacciHeap<int>::Node(2);
        node5->child->parent = node5;
        node5->child->right = node5->child->left = node5->child;

        node5->degree = 1;
    }

    if (node20) {
        node20->child = new FibonacciHeap<int>::Node(25);
        node20->child->parent = node20;
        node20->child->right = node20->child->left = node20->child;

        node20->degree = 1;
    }

    cout << "Tree structure after manually constructing a tree:\n";
    fibHeap.print();
    cout << "-----------------------------------\n";

    // Test Case 3: Decrease Key on Another Node
    std::cout << "Test Case 3: Decrease Key on Another Node\n";
    // Find a specific node (e.g., with value 15) for demonstration
    
    fibHeap.decreaseKey(child2, 2); // Decrease key of node with value 15 to 2
    // FibonacciHeap<int>::Node* x = fibHeap.getMin();
    // FibonacciHeap<int>::Node* newNode = new FibonacciHeap<int>::Node(6);
    // newNode->right = x->left;
    // x->left->left = newNode;
    // x->right = newNode;
    // newNode->left = x;
    std::cout << "Tree structure after decreasing key of node with value 15 to 2:\n";
    fibHeap.print();
    std::cout << "-----------------------------------\n";

    return 0;
}