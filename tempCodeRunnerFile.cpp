int main() {
    // Test case 1: Valid patient
    Patient patient1("John Doe", 12345, 30, 3, "Flu symptoms");
    cout << "Patient 1:" << endl;
    cout << patient1 << endl;
    cout << "Priority: " << patient1.getPriority() << endl;

    // Test case 2: Valid patient
    Patient patient2("Jane Doe", 54321, 45, 2, "Cough and cold");
    cout << "Patient 2:" << endl;
    cout << patient2 << endl;
    cout << "Priority: " << patient2.getPriority() << endl;

    // Test case 3: Valid patient
    Patient patient3("Alice Smith", 67890, 70, 4, "High fever");
    cout << "Patient 3:" << endl;
    cout << patient3 << endl;
    cout << "Priority: " << patient3.getPriority() << endl;

    // Test case 4: Valid patient
    Patient patient4("Bob Johnson", 98765, 10, 1, "Minor injury");
    cout << "Patient 4:" << endl;
    cout << patient4 << endl;
    cout << "Priority: " << patient4.getPriority() << endl;

    // Test case 5: Update urgency score
    Patient patient5("Alice Smith", 54321, 25, 2, "Headache");
    cout << "Patient 5 before update:" << endl;
    cout << patient5 << endl;
    patient5.updateUrgencyScore(4);
    cout << "Patient 5 after update:" << endl;
    cout << patient5 << endl;
    patient5.setPriority(1);
    cout << "Priority: " << patient5.getPriority() << endl;

    return 0;
}