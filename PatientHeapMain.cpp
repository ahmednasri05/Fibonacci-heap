#include <iostream>
#include <ctime>
#include <string>
#include "Fibonacci_Heap.h"
#include "Patient.hpp"
#include "Patient.cpp"

using namespace std;

int main() {
    // Create a Fibonacci Heap for Patient objects
    FibonacciHeap<Patient> patientHeap;

    // Helper function to get the current time
    // Create some Patient objects
    Patient patient1("Alice", 1, 25, 3, "Fractured arm");
    Patient patient2("Bob", 2, 70, 5, "Heart issue");
    Patient patient3("Charlie", 3, 5, 4, "High fever");
    Patient patient4("Diana", 4, 50, 2, "Minor injury");
    Patient patient5("Eve", 5, 90, 4, "Difficulty breathing");
    // Test the insert function
    cout << "Inserting patients into the Fibonacci Heap...\n";
    patientHeap.insert(patient1); //insert(ValueType value)
    patientHeap.insert(patient2);
    patientHeap.insert(patient3);
    patientHeap.insert(patient4);
    patientHeap.insert(patient5);

    // Test the print function to display the heap structure
    cout << "Heap after inserting patients:\n";
    patientHeap.print();

    // Test the getMin function
    cout << "\nPatient with the highest priority (min in heap):\n";
    cout << patientHeap.getMin() << "\n";

    // Test the extractMin function
    cout << "\nExtracting the patient with the highest priority...\n";
    patientHeap.extractMin();
    // Test the print function after extraction
    cout << "\nHeap after extracting the highest priority patient:\n";
    patientHeap.print();

    // Test the decreaseKey function (updating urgency score of a patient)
    cout << "\nDecreasing the urgency score of patient Diana...\n"; // el paramters beta3eut el decrease key hatet8ayar
    auto node = patientHeap.findNode(patient4); // Find Diana's node
    if (node) {
        patientHeap.decreaseKey(node, Patient("Diana", 4, 50, 1, "Minor injury")); // Lower urgency score
        cout << "Updated heap after decreasing key:\n";
        patientHeap.print();
    } else {
        cout << "Patient Diana not found in the heap.\n";
    }

    // Test the deleteNode function
    cout << "\nDeleting patient Eve from the heap...\n";
    patientHeap.deleteNode(patient5); // Delete Eve
    cout << "Heap after deleting patient Eve:\n";
    patientHeap.print();

    // Test the merge function
    cout << "\nCreating a second heap and merging...\n";
    FibonacciHeap<Patient> secondHeap;
    Patient patient6("Frank", 6, 30, 4, "Burns");
    Patient patient7("Grace", 7, 80, 5, "Stroke");


    secondHeap.insert(patient6);
    secondHeap.insert(patient7);

    cout << "Second heap:\n";
    secondHeap.print();

    cout << "Merging the second heap into the main heap...\n";
    patientHeap.merge(secondHeap);

    cout << "Heap after merging:\n";
    patientHeap.print();

    // Final cleanup
    cout << "\nClearing all patients from the heap...\n";
    while (!patientHeap.isEmpty()) {
        cout << "Extracted: " << patientHeap.extractMin() << "\n";
    }
    cout << "Heap is now empty.\n";

    return 0;
}
