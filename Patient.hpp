#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include <ctime>

using namespace std;

class Patient {
private:
    string name;
    int priority;
    int id;
    int age;
    int UrgencyScore;
    tm checkInDate;
    string description;
   
public:
    Patient();
    Patient(const string& name, int id, int age, int UrgencyScore = 0 , string description = "");
    Patient(const Patient& other); // copy constructor
    const string& getName() const;
    int getId() const;
    int getAge() const;
    void setPriority(int newPriority);
    int getPriority() const ;
    int getUrgencyScore() const;
    const string getCheckInDate() const;
    void updateUrgencyScore(int newUrgencyScore);
    const string& getDescription() const;
    void setDescription(const string& newDescription);
     int calculatePriority() const;
    friend ostream& operator<<(ostream& os, const Patient& patient);
    bool operator>(const Patient& other) const;
    bool operator<(const Patient& other) const;


};

#endif // PATIENT_HPP
