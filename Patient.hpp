#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include <ctime>

using namespace std;

class Patient {
public:
    Patient(const string& name, int id, int age, int UrgencyScore = 0 , string description = "");
    Patient(const Patient& other); // copy constructor
    const string& getName() const;
    int getId() const;
    int getAge() const;
    int getUrgencyScore() const;
    const string getCheckInDate() const;
    int getPriority() const ;
    void updateUrgencyScore(int newUrgencyScore);
    const string& getDescription() const;
    void setDescription(const string& newDescription);
    friend ostream& operator<<(ostream& os, const Patient& patient);
    bool operator>(const Patient& other) const;
    bool operator<(const Patient& other) const;

private:
    string name;
    int id;
    int age;
    int UrgencyScore;
    tm checkInDate;
    string description;
    int calculatePriority() const;
};

#endif // PATIENT_HPP
