#include <iostream>
#include <ctime>
#include <string>
#include "Fibonacci_Heap.h"
#include "Patient.hpp"

using namespace std;

template <typename ValueType>
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

int main() {
    Patient patient1("Alice", 12345, 25, 3, "Fractured arm");
    cout << "Patient 1: " << patient1 << endl;
    cout << "Node value: " << patient1.calculatePriority() << endl;
    //Node<Patient> node1(patient1);
    return 0;
}