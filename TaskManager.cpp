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

void TaskManager::decreaseKey(int id, int newUrgencyScore) {
    if (!patientExists(id)) {
        cerr << "Patient with ID " << id << " not found.\n";
        return;
    }
    auto it = patientMap.find(id);

    Patient updatedPatient = it->second; // deep copy using copy constructor
    if (newUrgencyScore >= updatedPatient.getUrgencyScore()) {
        cerr << "New urgency score must be lower than the current urgency score.\n";
        return;
    }
    // Add the updated patient entry
    updatedPatient.updateUrgencyScore(newUrgencyScore); // Update the urgency score
    //patientHeap.decreaseKey(it->second, updatedPatient); // Perform decreaseKey on the heap
    patientMap[updatedPatient.getId()] = updatedPatient;
    cout << "Urgency score for patient ID " << id << " decreased successfully.\n";
}
int main() {
    TaskManager tm;
    // Add patients
    tm.addPatient("John Doe", 10001, 30, 5, "Flu");
    tm.addPatient("Jane Smith", 10002, 25, 3, "Cold");
    tm.addPatient("Alice Johnson", 10003, 40, 4, "Broken leg");
    tm.addPatient("Bob Brown", 10004, 50, 2, "Heart attack");
    tm.addPatient("Eve Davis", 10005, 60, 1, "Stroke");
    // List all patients
    tm.listAllPatients();

    // View top patient
    tm.viewTopPatient();

    // Process next patient
    tm.processNextPatient();

    // List all patients after processing one
    tm.listAllPatients();

    // Find a specific patient
    tm.findPatient(10001);

    // Decrease urgency score of a patient
    tm.decreaseKey(10002, 1);

    // View top patient after decreasing urgency score
    tm.viewTopPatient();

    // Delete a patient
    tm.deletePatient(10003);

    // List all patients after deletion
    tm.listAllPatients();

    return 0;
}