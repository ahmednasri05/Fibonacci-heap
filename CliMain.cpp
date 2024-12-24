#include <iostream>
#include <string>
#include "TaskManager.hpp"

using namespace std;

void displayMenu() {
    cout << "\n=== Hospital Task Manager ===\n";
    cout << "1. Add a new patient\n";
    cout << "2. Process the next patient\n";
    cout << "3. View the next patient\n";
    cout << "4. List all patients\n";
    cout << "5. Find a specific patient by ID\n";
    cout << "6. Decrease urgency score of a patient\n";
    cout << "7. Delete a patient\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}

void handleAddPatient(TaskManager& tm) {
    string name, description;
    int id, age, urgencyScore;

    cout << "\nEnter patient's name: ";
    cin.ignore(); // Clear input buffer
    getline(cin, name);

    cout << "Enter patient's ID: ";
    cin >> id;

    cout << "Enter patient's age: ";
    cin >> age;

    cout << "Enter patient's urgency score (1-5): ";
    cin >> urgencyScore;

    cin.ignore(); // Clear input buffer
    cout << "Enter patient's description: ";
    getline(cin, description);

    tm.addPatient(name, id, age, urgencyScore, description);
}

void handleDecreaseKey(TaskManager& tm) {
    int id, newUrgencyScore;

    cout << "\nEnter patient ID: ";
    cin >> id;

    cout << "Enter new urgency score (lower than the current): ";
    cin >> newUrgencyScore;

    tm.decreaseKey(id, newUrgencyScore);
}

void handleDeletePatient(TaskManager& tm) {
    int id;

    cout << "\nEnter patient ID to delete: ";
    cin >> id;

    tm.deletePatient(id);
}

void handleFindPatient(TaskManager& tm) {
    int id;

    cout << "\nEnter patient ID to find: ";
    cin >> id;

    tm.findPatient(id);
}

int main() {
    TaskManager tm;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                handleAddPatient(tm);
                break;
            case 2:
                tm.processNextPatient();
                break;
            case 3:
                tm.viewTopPatient();
                break;
            case 4:
                tm.listAllPatients();
                break;
            case 5:
                handleFindPatient(tm);
                break;
            case 6:
                handleDecreaseKey(tm);
                break;
            case 7:
                handleDeletePatient(tm);
                break;
            case 8:
                cout << "Exiting the application. Goodbye!\n";
                return 0;
            default:
                cerr << "Invalid choice. Please try again.\n";
        }
    }
}
