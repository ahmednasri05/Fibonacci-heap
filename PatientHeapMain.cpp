#include <iostream>
#include <ctime>
#include <string>
#include <thread>
#include "Fibonacci_Heap.h"
#include "Patient.hpp"

using namespace std;

int main()
{
    // Create a Fibonacci Heap for Patient objects
    FibonacciHeap<Patient> patientHeap;

    // Create some Patient objects
    Patient patient1("Alice", 12345, 25, 3, "Fractured arm");
    Patient patient2("Bob", 23456, 70, 0, "Heart issue");
    Patient patient3("Charlie", 34567, 5, 3, "High fever");
    Patient patient4("Diana", 45678, 50, 0, "Minor injury");
    Patient patient5("Eve", 59101, 90, 5, "Difficulty breathing");
    Patient patient6("Frank", 67890, 40, 3, "Back pain");
    Patient patient7("Grace", 78901, 60, 2, "Headache");
    Patient patient8("Hank", 89012, 30, 1, "Sprained ankle");
    Patient patient9("Ivy", 90123, 20, 4, "Stomach ache");
    Patient patient10("Jack", 12346, 10, 2, "Flu");
    Patient patient11("Karen", 23457, 80, 1, "Broken leg");
    Patient patient12("Leo", 34568, 15, 3, "Ear infection");
    Patient patient13("Mona", 45679, 55, 0, "Migraine");
    Patient patient14("Nina", 56780, 65, 2, "Allergic reaction");
    Patient patient15("Oscar", 67891, 35, 4, "Burns");

    // Test the insert function
    cout << "Inserting patients into the Fibonacci Heap...\n";
    patientHeap.insert(patient1);
    patientHeap.insert(patient2);
    patientHeap.insert(patient3);
    patientHeap.insert(patient4);
    patientHeap.insert(patient5);
    patientHeap.insert(patient6);
    patientHeap.insert(patient7);
    patientHeap.insert(patient8);
    patientHeap.insert(patient9);
    patientHeap.insert(patient10);
    patientHeap.insert(patient11);
    patientHeap.insert(patient12);
    patientHeap.insert(patient13);
    patientHeap.insert(patient14);
    patientHeap.insert(patient15);
    // patientHeap.print();
    //  Print priorities after insertion
    //  cout << "Priorities after insertion:\n";
    //  // Test the getMin function
    //  cout << "\nPatient with the highest priority (min in heap):\n";
    //  cout << patientHeap.getMin() << "\n";
    patientHeap.print();
    // Test the extractMin function
    cout << "\nExtracting the patient with the highest priority...\n";
    patientHeap.extractMin();
    // Sleep for 15 seconds
    // Print priorities after extraction
    // cout << "Priorities after extracting the highest priority patient:\n";
    // cout<< patientHeap.getMin();

    // // Test the decreaseKey function
    // cout << "\nDecreasing the urgency score of Patient 4...\n";
    // patientHeap.decreaseKey(patient4, Patient("Diana", 45678, 50, 5, "Minor injury"));
    // // Test the deleteNode function
    // cout << "\nDeleting Patient 3...\n";
    // patientHeap.deleteNode(patient3);
    // // Print priorities after deletion
    // cout << "Priorities after deleting Patient 3:\n";
    // patientHeap.print();

    // // Test the merge function
    // cout << "\nMerging with another Fibonacci Heap...\n";
    // FibonacciHeap<Patient> anotherHeap;
    // Patient patient6("Frank", 67890, 40, 3, "Back pain");
    // Patient patient7("Grace", 78901, 60, 2, "Headache");
    //     anotherHeap.insert(patient6);
    // anotherHeap.insert(patient7);
    // patientHeap.merge(anotherHeap);

    // // Print priorities after merging
    // cout << "Priorities after merging with another heap:\n";
    patientHeap.print();

    return 0;
}