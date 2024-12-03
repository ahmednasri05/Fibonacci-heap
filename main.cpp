#include "Fibonacci_Heap.h"
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    // Create a Fibonacci Heap
    FibonacciHeap<int> fibHeap;

    // Insert elements into the heap
    cout << "Inserting elements into the Fibonacci Heap..." << endl;
    fibHeap.insert(10);
    fibHeap.insert(3);
    fibHeap.insert(7);
    fibHeap.insert(15);
    fibHeap.insert(8);

    // Display the heap
    cout << "\nInitial Fibonacci Heap:" << endl;
    fibHeap.print();

    // Extract the minimum element
    cout << "\nExtracting the minimum element from the heap..." << endl;
    FibonacciHeap<int>::Node* minNode = fibHeap.extractMin();
    if (minNode) {
        cout << "Extracted minimum: " << minNode->value << endl;
        delete minNode; // Clean up the extracted node
    }

    // Display the heap after extraction
    cout << "\nFibonacci Heap after extractMin:" << endl;
    fibHeap.print();

    // Decrease a key
    cout << "\nDecreasing a key in the heap..." << endl;
    // Decrease the key of a specific node (for demonstration, use node with value 15)
    // NOTE: Find the node with value 15 manually for testing
    FibonacciHeap<int>::Node* targetNode = nullptr;
    for (FibonacciHeap<int>::Node* cur = fibHeap.getMin(); cur != nullptr; cur = cur->right) {
        if (cur->value == 15) {
            targetNode = cur;
            break;
        }
        if (cur->right == fibHeap.getMin()) break; // Stop circular iteration
    }

    if (targetNode) {
        fibHeap.decreaseKey(targetNode, 2); // Decrease the value to 2
        cout << "Decreased value of node 15 to 2." << endl;
    } else {
        cout << "Node with value 15 not found!" << endl;
    }

    // Display the heap after decreasing key
    cout << "\nFibonacci Heap after decreaseKey:" << endl;
    fibHeap.print();

    // Extract the minimum element again
    cout << "\nExtracting the minimum element again from the heap..." << endl;
    minNode = fibHeap.extractMin();
    if (minNode) {
        cout << "Extracted minimum: " << minNode->value << endl;
        delete minNode; // Clean up the extracted node
    }

    // Display the heap after the second extraction
    cout << "\nFibonacci Heap after the second extractMin:" << endl;
    fibHeap.print();

    return 0;
}
