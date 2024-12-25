# pragma once
#include <iostream>
#include <ctime>
#include <string>
#include "Fibonacci_Heap.h"
#include "Patient.hpp"
#include <unordered_map>

using namespace std;

class TaskManager {
private:
    FibonacciHeap<Patient> patientHeap; // Fibonacci heap for managing patients
    HashMap<int, Patient*> patientMap; // Maps patient ID to their node in the heap
    bool patientExists(int id) const;

public:
    void addPatient(const string& name, int id, int age, int urgencyScore, const string& description);
    void processNextPatient();
    void viewTopPatient();
    void listAllPatients();
    void findPatient(int id) const;
    void deletePatient(int id);
    void increaseUrgency(int id, int newUrgencyScore);
};
