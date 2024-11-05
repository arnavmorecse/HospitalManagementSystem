#include <iostream>
#include <string>

using namespace std;

const int MAX_PATIENTS = 15;
const int MAX_DOCTORS = 15;
const int MAX_APPOINTMENTS = 15;

// Base class Person
class Person {
protected:
    string name;

public:
    Person() : name("") {}
    Person(string n) : name(n) {}

    string getName() const { return name; }

    virtual void displayInfo() const {
        cout << "Name: " << name << "\n";
    }

    virtual ~Person() {} // destructor
};

// Patient class inheriting from Person
class Patient : public Person {
private:
    int patientID;
    int age;
    string illness;

public:
    Patient() : patientID(0), age(0), illness("") {}
    Patient(int id, string n, int a, string ill) : Person(n), patientID(id), age(a), illness(ill) {}

    int getPatientID() const { return patientID; }
    int getAge() const { return age; }
    string getIllness() const { return illness; }

    void displayInfo() const override {
        cout << "Patient ID: " << patientID << "\n";
        Person::displayInfo();
        cout << "Age: " << age << "\n";
        cout << "Illness: " << illness << "\n";
    }
};

// Doctor class inheriting from Person
class Doctor : public Person {
private:
    int doctorID;
    string specialty;

public:
    Doctor() : doctorID(0), specialty("") {}
    Doctor(int id, string n, string spec) : Person(n), doctorID(id), specialty(spec) {}

    int getDoctorID() const { return doctorID; }
    string getSpecialty() const { return specialty; }

    void displayInfo() const override {
        cout << "Doctor ID: " << doctorID << "\n";
        Person::displayInfo();
        cout << "Specialty: " << specialty << "\n";
    }
};

// Appointment class
class Appointment {
private:
    int appointmentID;
    int patientID;
    int doctorID;
    string date;
    string time;

public:
    Appointment() : appointmentID(0), patientID(0), doctorID(0), date(""), time("") {}
    Appointment(int appID, int pID, int dID, string d, string t)
        : appointmentID(appID), patientID(pID), doctorID(dID), date(d), time(t) {}

    int getAppointmentID() const { return appointmentID; }
    int getPatientID() const { return patientID; }
    int getDoctorID() const { return doctorID; }
    string getDate() const { return date; }
    string getTime() const { return time; }

    void displayAppointmentInfo() const {
        cout << "\nAppointment ID: " << appointmentID << "\n";
        cout << "Patient ID: " << patientID << "\n";
        cout << "Doctor ID: " << doctorID << "\n";
        cout << "Date: " << date << "\n";
        cout << "Time: " << time << "\n";
    }
};

// HospitalManagementSystem class
class HospitalManagementSystem {
private:
    Patient patients[MAX_PATIENTS];
    Doctor doctors[MAX_DOCTORS];
    Appointment appointments[MAX_APPOINTMENTS];
    int patientCount;
    int doctorCount;
    int appointmentCount;

public:
    HospitalManagementSystem() : patientCount(0), doctorCount(0), appointmentCount(0) {}

    void addPatient() {
        if (patientCount >= MAX_PATIENTS) {
            cout << "\nPatient limit reached. Cannot add more patients.\n";
            return;
        }
        int id, age;
        string name, illness;

        cout << "\nEnter Patient ID: ";
        cin >> id;
        cin.ignore();  // Clear newline
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();  // Clear newline
        cout << "Enter Illness or Symptom: ";
        getline(cin, illness);

        patients[patientCount++] = Patient(id, name, age, illness);
        cout << "\nPatient added successfully.\n";
    }

    void addDoctor() {
        if (doctorCount >= MAX_DOCTORS) {
            cout << "Doctor limit reached. Cannot add more doctors.\n";
            return;
        }
        int id;
        string name, specialty;

        cout << "\nEnter Doctor ID: ";
        cin >> id;
        cin.ignore();  // Clear newline
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Specialty: ";
        getline(cin, specialty);

        doctors[doctorCount++] = Doctor(id, name, specialty);
        cout << "\nDoctor added successfully.\n";
    }

    void scheduleAppointment() {
        if (appointmentCount >= MAX_APPOINTMENTS) {
            cout << "\nAppointment limit reached. Cannot schedule more appointments.\n";
            return;
        }
        int pID, appID;
        string date, time, symptom;

        cout << "\nEnter Appointment ID: ";
        cin >> appID;
        cout << "Enter Patient ID: ";
        cin >> pID;
        cin.ignore();  // Clear newline
        cout << "Enter Patient Symptom: ";
        getline(cin, symptom);

        string specialty = findSpecialty(symptom);
        int doctorID = findDoctorBySpecialty(specialty);

        if (doctorID == -1) {
            cout << "\nNo available doctor with specialty in " << specialty << ".\n";
            return;
        }

        cout << "Enter Date (DD-MM-YYYY): ";
        getline(cin, date);
        cout << "Enter Time (HH:MM): ";
        getline(cin, time);

        appointments[appointmentCount++] = Appointment(appID, pID, doctorID, date, time);
        cout << "\nAppointment scheduled successfully with Doctor ID " << doctorID << ".\n";
    }

    string findSpecialty(const string& symptom) {
        if (symptom.find("cough") != string::npos || symptom.find("fever") != string::npos) {
            return "General Medicine";
        } else if (symptom.find("heart") != string::npos || symptom.find("chest pain") != string::npos) {
            return "Cardiology";
        } else if (symptom.find("skin") != string::npos || symptom.find("rash") != string::npos) {
            return "Dermatology";
        } else if (symptom.find("mental") != string::npos || symptom.find("depression") != string::npos) {
            return "Psychiatry";
        } else if (symptom.find("teeth") != string::npos || symptom.find("gums") != string::npos) {
            return "Dental";
        } else {
            return "General Medicine";
        }
    }

    int findDoctorBySpecialty(const string& specialty) {
        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i].getSpecialty() == specialty) {
                return doctors[i].getDoctorID();
            }
        }
        return -1;
    }

    void displayPatients() const {
        if (patientCount == 0) {
            cout << "\nNo patients available.\n";
        } else {
            for (int i = 0; i < patientCount; i++) {
                cout << "\nPatient " << (i + 1) << ":\n";
                patients[i].displayInfo();
            }
        }
    }

    void displayDoctors() const {
        if (doctorCount == 0) {
            cout << "\nNo doctors available.\n";
        } else {
            for (int i = 0; i < doctorCount; i++) {
                cout << "\nDoctor " << (i + 1) << ":\n";
                doctors[i].displayInfo();
            }
        }
    }

    void displayAppointments() const {
        if (appointmentCount == 0) {
            cout << "\nNo appointments available.\n";
        } else {
            for (int i = 0; i < appointmentCount; i++) {
                cout << "\nAppointment " << (i + 1) << ":\n";
                appointments[i].displayAppointmentInfo();
            }
        }
    }
};

// Main function with menu
int main() {
    HospitalManagementSystem hms;
    int choice;

    do {
        cout << "\nHospital Management System - Menu:\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Schedule Appointment\n";
        cout << "4. Display Patients\n";
        cout << "5. Display Doctors\n";
        cout << "6. Display Appointments\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                hms.addPatient();
                break;
            case 2:
                hms.addDoctor();
                break;
            case 3:
                hms.scheduleAppointment();
                break;
            case 4:
                hms.displayPatients();
                break;
            case 5:
                hms.displayDoctors();
                break;
            case 6:
                hms.displayAppointments();
                break;
            case 0:
                cout << "\nExiting the system. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
