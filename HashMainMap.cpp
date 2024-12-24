#include <iostream>
#include "HashMap.h"
#include "Patient.hpp"

using namespace std;

int main() {
    HashMap<int, Patient*> patientHashMap;

    // Test case 1: Insert a patient and search for it
    Patient* patient1 = new Patient("John Doe", 12345, 30, 3, "Flu symptoms");
    patientHashMap.insertDouble(patient1->getId(), patient1);
    Patient* result = patientHashMap.searchDouble(12345);
    cout << "Test case 1: " << (result != nullptr ? "Passed" : "Failed") << endl;

    // Test case 2: Insert multiple patients and search for them
    Patient* patient2 = new Patient("Jane Doe", 54321, 45, 2, "Cough and cold");
    Patient* patient3 = new Patient("Alice Smith", 67890, 70, 4, "High fever");
    patientHashMap.insertDouble(patient2->getId(), patient2);
    patientHashMap.insertDouble(patient3->getId(), patient3);
    result = patientHashMap.searchDouble(54321);
    cout << "Test case 2a: " << (result != nullptr ? "Passed" : "Failed") << endl;
    result = patientHashMap.searchDouble(67890);
    cout << "Test case 2b: " << (result != nullptr ? "Passed" : "Failed") << endl;

    // Test case 3: Remove a patient and search for it
    patientHashMap.removeDouble(12345);
    result = patientHashMap.searchDouble(12345);
    cout << "Test case 3: " << (result == nullptr ? "Passed" : "Failed") << endl;

    // Test case 4: Insert patients, remove one, and search for all
    patientHashMap.insertDouble(patient1->getId(), patient1);
    patientHashMap.removeDouble(54321);
    result = patientHashMap.searchDouble(12345);
    cout << "Test case 4a: " << (result != nullptr ? "Passed" : "Failed") << endl;
    result = patientHashMap.searchDouble(54321);
    cout << "Test case 4b: " << (result == nullptr ? "Passed" : "Failed") << endl;
    result = patientHashMap.searchDouble(67890);
    cout << "Test case 4c: " << (result != nullptr ? "Passed" : "Failed") << endl;

    // Test case 5: Insert patients to trigger resize and search for them
    Patient* patient4 = new Patient("Bob Johnson", 11111, 10, 1, "Minor injury");
    Patient* patient5 = new Patient("Charlie Brown", 22222, 20, 2, "Headache");
    Patient* patient6 = new Patient("David Wilson", 33333, 40, 3, "Back pain");
    Patient* patient7 = new Patient("Eve Adams", 44444, 50, 4, "Chest pain");
    Patient* patient8 = new Patient("Frank Miller", 55555, 60, 5, "Severe injury");
    Patient* patient9 = new Patient("Grace Lee", 66666, 70, 1, "Fever");
    Patient* patient10 = new Patient("Hank Green", 77777, 80, 2, "Cold");

    patientHashMap.insertDouble(patient4->getId(), patient4);
    patientHashMap.insertDouble(patient5->getId(), patient5);
    patientHashMap.insertDouble(patient6->getId(), patient6);
    patientHashMap.insertDouble(patient7->getId(), patient7);
    patientHashMap.insertDouble(patient8->getId(), patient8);
    patientHashMap.insertDouble(patient9->getId(), patient9);
    patientHashMap.insertDouble(patient10->getId(), patient10);

    result = patientHashMap.searchDouble(11111);
    cout << "Test case 5a: " << (result != nullptr ? "Passed" : "Failed") << endl;
    result = patientHashMap.searchDouble(22222);
    cout << "Test case 5b: " << (result != nullptr ? "Passed" : "Failed") << endl;
    result = patientHashMap.searchDouble(33333);
    cout << "Test case 5c: " << (result != nullptr ? "Passed" : "Failed") << endl;
    result = patientHashMap.searchDouble(44444);
    cout << "Test case 5d: " << (result != nullptr ? "Passed" : "Failed") << endl;
    result = patientHashMap.searchDouble(55555);
    cout << "Test case 5e: " << (result != nullptr ? "Passed" : "Failed") << endl;
    result = patientHashMap.searchDouble(66666);
    cout << "Test case 5f: " << (result != nullptr ? "Passed" : "Failed") << endl;
    result = patientHashMap.searchDouble(77777);
    cout << "Test case 5g: " << (result != nullptr ? "Passed" : "Failed") << endl;

    // Clean up
    delete patient1;
    delete patient2;
    delete patient3;
    delete patient4;
    delete patient5;
    delete patient6;
    delete patient7;
    delete patient8;
    delete patient9;
    delete patient10;

    return 0;
}