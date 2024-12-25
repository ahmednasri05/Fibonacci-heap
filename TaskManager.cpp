#include "TaskManager.hpp"

bool TaskManager::patientExists(int id) const {
    return patientMap.find(id) != patientMap.end();
}

void TaskManager::addPatient(const string& name, int id, int age, int urgencyScore, const string& description) {
    if (patientMap.find(id) != patientMap.end()) {
        cerr << "Patient with ID " << id << " already exists.\n";
        return;
    }
    Patient newPatient(name, id, age, urgencyScore, description);
    patientHeap.insert(newPatient);
    patientMap[newPatient.getId()] = newPatient; // Store the mapping of ID to heap node
    cout << "Patient added successfully!\n";
}

void TaskManager::processNextPatient() {
    if (patientHeap.isEmpty()) {
        cerr << "No patients in the queue.\n";
        return;
    }
    Patient nextPatient = patientHeap.extractMin();
    patientMap.erase(nextPatient.getId()); // Remove the patient from the map
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
    auto it = patientMap.find(id); //returns an iterator with the specifies key
    cout << "Patient found:\n" << it->second << "\n";
}

void TaskManager::deletePatient(int id) {
    if (!patientExists(id)) {
        cerr << "Patient with ID " << id << " not found.\n";
        return;
    }
    auto it = patientMap.find(id);
    patientHeap.deleteNode(it->second); // Delete the node from the heap
    patientMap.erase(it); // Remove the mapping
    cout << "Patient with ID " << id << " deleted successfully.\n";
}

void TaskManager::increaseUrgency(int id, int newUrgencyScore) {
    if (!patientExists(id)) {
        cerr << "Patient with ID " << id << " not found.\n";
        return;
    }
    auto it = patientMap.find(id);
    Patient oldPatient = it->second;
    Patient updatedPatient(oldPatient);
    // deep copy using copy constructor
    if (newUrgencyScore <= updatedPatient.getUrgencyScore()) {
        cerr << "New urgency score must be higher than the current urgency score.\n";
        return;
    }
    // Add the updated patient entry
    updatedPatient.updateUrgencyScore(newUrgencyScore); // Update the urgency score
    cout << "Urg Score " <<updatedPatient.getUrgencyScore() << endl; 
    cout << "it->sec " << oldPatient.getUrgencyScore() << endl;
    cout << "Old pri score: " << oldPatient.getPriority() << "\n";
    cout << "New pri score: " << updatedPatient.getPriority() << "\n";
    patientHeap.decreaseKey(oldPatient, updatedPatient); // Perform increaseKey on the heap
    patientMap[updatedPatient.getId()] = updatedPatient;
    cout << "Urgency score for patient ID " << id << " increased successfully.\n";
}
int main() {
    TaskManager tm;
    // Add patients
    tm.addPatient("John Doe", 10001, 90, 5, "Flu");
    tm.addPatient("Jane Smith", 10002, 25, 3, "Cold");
    tm.addPatient("Alice Johnson", 10003, 40, 4, "Broken leg");
    tm.addPatient("Bob Brown", 10004, 50, 2, "Heart attack");
    tm.addPatient("Eve Davis", 10005, 60, 1, "Stroke");
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