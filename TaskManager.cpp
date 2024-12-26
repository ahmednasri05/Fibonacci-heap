#include "TaskManager.hpp"
#include "HashMap.h"
#include "Patient.cpp"

bool TaskManager::patientExists(int id) const {
    Patient* result = patientMap.searchDouble(id);
    return result != nullptr; // Check if the pointer is valid
}

void TaskManager::addPatient(const string& name, int id, int age, int urgencyScore, const string& description) {
    if (patientExists(id)) {
        cerr << "Patient with ID " << id << " already exists.\n";
        return;
    }
    Patient* newPatient = new Patient(name, id, age, urgencyScore, description);
    patientHeap.insert(*newPatient); // Insert by value into the heap
    patientMap.insertDouble(newPatient->getId(), newPatient); // Store the pointer in the map
    cout << "Patient added successfully!\n";
}

void TaskManager::processNextPatient() {
    if (patientHeap.isEmpty()) {
        cerr << "No patients in the queue.\n";
        return;
    }
    Patient nextPatient = patientHeap.extractMin(); // Extract by value
    patientMap.removeDouble(nextPatient.getId());   // Remove from map
    cout << "Processing next patient:\n" << nextPatient << "\n";
}

void TaskManager::viewTopPatient() {
    if (patientHeap.isEmpty()) {
        cerr << "No patients in the queue.\n";
        return;
    }
    cout << "Next patient to be treated:\n" << patientHeap.getMin() << "\n";
}

void TaskManager::listAllPatients() {
    if (patientHeap.isEmpty()) {
        cerr << "No patients in the queue.\n";
        return;
    }
    cout << "All patients in the queue:\n";
    patientHeap.print();
}

void TaskManager::findPatient(int id) const {
    if (!patientExists(id)) {
        cerr << "Patient with ID " << id << " not found.\n";
        return;
    }
    Patient* patient = patientMap.searchDouble(id); // Access the pointer from the map
    cout << "Patient found:\n" << *patient << "\n";
}

void TaskManager::deletePatient(int id) {
    if (!patientExists(id)) {
        cerr << "Patient with ID " << id << " not found.\n";
        return;
    }
    Patient* patient = patientMap.searchDouble(id);
    patientMap.removeDouble(patient->getId()); // Remove from the map
    delete patient; // Free the memory
    cout << "Patient with ID " << id << " deleted successfully.\n";
}

void TaskManager::increaseUrgency(int id, int newUrgencyScore) {
    if (!patientExists(id)) {
        cerr << "Patient with ID " << id << " not found.\n";
        return;
    }
    Patient* patient = patientMap.searchDouble(id);
    Patient updatedPatient(*patient); // Create a copy for updating
    if (newUrgencyScore <= updatedPatient.getUrgencyScore()) {
        cerr << "New urgency score must be higher than the current urgency score.\n";
        return;
    }
    updatedPatient.updateUrgencyScore(newUrgencyScore); // Update urgency score
    patientHeap.decreaseKey(*patient, updatedPatient);  // Update in heap
    cout << "Urgency score for patient ID " << id << " increased successfully.\n";
}
int main() {
    TaskManager tm;
    // Add patients
    tm.addPatient("John Doe", 10001, 90, 5, "Flu");
    tm.addPatient("Jane Smith", 10002, 25, 2, "Cold");
    tm.addPatient("Alice Johnson", 10003, 40, 4, "Broken leg");
    tm.addPatient("Bob Brown", 10004, 50, 2, "Heart attack");
    tm.addPatient("Eve Davis", 10005, 60, 4, "Stroke");
    // List all patients
    cout << "Listing all patients:\n";
    tm.listAllPatients();

    // cout << "\nViewing top patient:\n";
    // tm.viewTopPatient();

    // cout << "\nProcessing next patient:\n";
    // tm.processNextPatient();

    // cout << "\nListing all patients after processing one:\n";
    // tm.listAllPatients();

    // cout << "\nFinding a specific patient with ID 10001:\n";
    // tm.findPatient(10002);

    cout << "\nIncreasing urgency score of patient with ID 10002:\n";
    tm.increaseUrgency(10002, 5);

    // cout << "\nViewing top patient after increasing urgency score:\n";
    // tm.viewTopPatient();

    // cout << "\nDeleting patient with ID 10003:\n";
    // tm.deletePatient(10003);

    cout << "\nListing all patients after deletion:\n";
    tm.listAllPatients();

    return 0;
}