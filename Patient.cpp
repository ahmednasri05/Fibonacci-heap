#include "Patient.hpp"
using namespace std;
#include <iostream>
// Constructor
Patient::Patient() : name(""), id(0), age(0), UrgencyScore(0), description("") {
    time_t now = time(0);
    checkInDate = *localtime(&now);
}
Patient::Patient(const string& name, int id, int age, int UrgencyScore, string description) {
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) { // name sgould contain only characters and whitespaces
            cerr << "Name must contain only characters and whitespaces." << endl;
            exit(EXIT_FAILURE);
        }
    }
    this->name = name;
    if (to_string(id).length() != 5) {
        cerr << "ID must be the last 5 digits of your National ID." << endl;
        exit(EXIT_FAILURE);
    }
    this->id = id;
    if (age < 0 || age > 100) {
        cerr << "Age must be between 0 and 120." << endl;
        exit(EXIT_FAILURE);
    }
    this->age = age;
    if (UrgencyScore < 0 || UrgencyScore > 5) { // Urgency score should be between 0 and 5
        cerr << "Urgency Score must be between 0 and 5." << endl;
        exit(EXIT_FAILURE);
    }
    this->UrgencyScore = UrgencyScore;
    this->description = description;
    this->priority = calculatePriority() *-1;

    time_t now = time(0);
    checkInDate = *localtime(&now);
}
// Copy Constructor
Patient::Patient(const Patient& other) {
    name = other.name;
    id = other.id;
    age = other.age;
    UrgencyScore = other.UrgencyScore;
    description = other.description;
    checkInDate = other.checkInDate;
}
int Patient::calculatePriority() const {
    // Weights 
    //Urgency score has highest weight, followed by age, and then check-in time
    const double w1 = 5, w2 = 3, w3 = 2;
    // Max possible score: MaxPossibleScore= (5⋅5)+(3⋅10)+(2⋅10)=75
    const double maxPossibleScore = 75.0; // Derived from weights and max factors
        // Urgency Factor
    double urgencyFactor = UrgencyScore; // Already between 0 and 5
        // Age Factor: higher for children and elderly
    double ageFactor = (age >= 0 && age <= 10) || (age >= 60 && age <= 100) ? 10 : 5;

        // Check-In Time Factor
    double CheckInHours = checkInDate.tm_hour + (checkInDate.tm_min / 60.0);
    double maxHours = 23.59; // Maximum wait time for normalization
    // if the time is small aka the patient came early, the factor will be higher
    double checkInTimeFactor = max( 0.0 , (maxHours - CheckInHours) / maxHours * 10);

        // Calculate raw priority
    double rawPriority = (w1 * urgencyFactor) + (w2 * ageFactor) + (w3 * checkInTimeFactor);

        // Normalize to 0-10
    return (rawPriority / maxPossibleScore) * 10;
}
const string& Patient::getName() const {
    return name;
}

int Patient::getId() const {
    return id;
}

int Patient::getAge() const {
    return age;
}

int Patient::getUrgencyScore() const {
    return UrgencyScore;
}
void Patient::setPriority(int newPriority) {
    if (newPriority < -11 || newPriority > 1) {
        cerr << "Priority must be between -11 and 1." << endl;
        return;
    }
    priority = newPriority;
}

const string Patient::getCheckInDate() const {
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &checkInDate);
    return string(buffer);
}

int Patient::getPriority() const {
    return this->priority; // Placeholder
}

void Patient::updateUrgencyScore(int newUrgencyScore) {
    UrgencyScore = newUrgencyScore;
    calculatePriority();
}

const string& Patient::getDescription() const {
    return description;
}

void Patient::setDescription(const string& newDescription) {
    description = newDescription;
}

ostream& operator<<(ostream& os, const Patient& patient) {
    os << "Name: " << patient.name << "\n"
       << "ID: " << patient.id << "\n"
       << "Age: " << patient.age << "\n"
       << "Priority: " << patient.getPriority() << "\n"
       << "Urgency Score: " << patient.UrgencyScore << "\n"
       << "Check-In Date: " << patient.getCheckInDate() << "\n"
       << "Description: " << patient.description << "\n";
    return os;
}
bool Patient::operator>(const Patient& other) const {
    return this->priority > other.priority;
}
bool Patient::operator<(const Patient& other) const {
    return this->priority < other.priority;
}

// int main() {
//     // Test case 1: Valid patient
//     Patient patient1("John Doe", 12345, 30, 3, "Flu symptoms");
//     cout << "Patient 1:" << endl;
//     cout << patient1 << endl;
//     cout << "Priority: " << patient1.getPriority() << endl;

//     // Test case 2: Valid patient
//     Patient patient2("Jane Doe", 54321, 45, 2, "Cough and cold");
//     cout << "Patient 2:" << endl;
//     cout << patient2 << endl;
//     cout << "Priority: " << patient2.getPriority() << endl;

//     // Test case 3: Valid patient
//     Patient patient3("Alice Smith", 67890, 70, 4, "High fever");
//     cout << "Patient 3:" << endl;
//     cout << patient3 << endl;
//     cout << "Priority: " << patient3.getPriority() << endl;

//     // Test case 4: Valid patient
//     Patient patient4("Bob Johnson", 98765, 10, 1, "Minor injury");
//     cout << "Patient 4:" << endl;
//     cout << patient4 << endl;
//     cout << "Priority: " << patient4.getPriority() << endl;

//     // Test case 5: Update urgency score
//     Patient patient5("Alice Smith", 54321, 25, 2, "Headache");
//     cout << "Patient 5 before update:" << endl;
//     cout << patient5 << endl;
//     patient5.updateUrgencyScore(4);
//     cout << "Patient 5 after update:" << endl;
//     cout << patient5 << endl;
//     patient5.setPriority(1);
//     cout << "Priority: " << patient5.getPriority() << endl;

//     return 0;
// }
