#include <iostream>
#include <string>
#include <limits> 
#include <cctype>
#include <regex>

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

// Helper function to validate integer input
int getValidatedIntegerInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid integer.\n";
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Helper function to validate string input
string getValidatedStringInput(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);

        bool isValid = true;
        for (char c : input) {
            if (!isalpha(c) && !isspace(c)) {
                isValid = false;
                break;
            }
        }

        if (isValid && !input.empty()) {
            return input;
        } else {
            cout << "Invalid input. Please enter alphabetic characters only.\n";
        }
    }
}

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
        int id = getValidatedIntegerInput("\nEnter Patient ID: ");
        string name = getValidatedStringInput("Enter Name: ");
        int age = getValidatedIntegerInput("Enter Age: ");
        string illness = getValidatedStringInput("Enter Illness or Symptom: ");

        patients[patientCount++] = Patient(id, name, age, illness);
        cout << "\nPatient added successfully.\n";
    }

    void addDoctor() {
        if (doctorCount >= MAX_DOCTORS) {
            cout << "Doctor limit reached. Cannot add more doctors.\n";
            return;
        }
        int id = getValidatedIntegerInput("\nEnter Doctor ID: ");
        string name = getValidatedStringInput("Enter Name: ");
        string specialty = getValidatedStringInput("Enter Specialty: ");

        doctors[doctorCount++] = Doctor(id, name, specialty);
        cout << "\nDoctor added successfully.\n";
    }

    bool isValidDateFormat(const string& date) {
        regex datePattern(R"(^\d{2}-\d{2}-\d{4}$)");
        return regex_match(date, datePattern);
    }
    
    bool isValidTimeFormat(const string& time) {
        regex timePattern(R"(^([01]\d|2[0-3]):([0-5]\d)$)");
        return regex_match(time, timePattern);
    }

    void scheduleAppointment() {
        if (appointmentCount >= MAX_APPOINTMENTS) {
            cout << "\nAppointment limit reached. Cannot schedule more appointments.\n";
            return;
        }
        int appID = getValidatedIntegerInput("\nEnter Appointment ID: ");
        int pID = getValidatedIntegerInput("Enter Patient ID: ");
        string symptom = getValidatedStringInput("Enter Patient Symptom: ");

        string specialty = findSpecialty(symptom);
        int doctorID = findDoctorBySpecialty(specialty);

        if (doctorID == -1) {
            cout << "\nNo available doctor with specialty in " << specialty << ".\n";
            return;
        }

        string date;
        while (true) {
            cout<<"Enter Date (DD-MM-YYYY): ";
            cin>>date;
            if (isValidDateFormat(date)) {
                break;
            } else {
                cout << "Invalid date format. Please enter the date in DD-MM-YYYY format.\n";
            }
        }

        string time;
        while (true) {
            cout<<"Enter Time (HH:MM): ";
            cin>>time;
            if (isValidTimeFormat(time)) {
                break;
            } else {
                cout << "Invalid time format. Please enter the time in HH:MM format.\n";
            }
        }

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

    void deletePatient() {
        int id = getValidatedIntegerInput("\nEnter Patient ID to delete: ");
        int index = -1;
        for (int i = 0; i < patientCount; i++) {
            if (patients[i].getPatientID() == id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "\nPatient with ID " << id << " not found.\n";
            return;
        }

        for (int i = index; i < patientCount - 1; i++) {
            patients[i] = patients[i + 1];
        }

        patientCount--;
        cout << "\nPatient with ID " << id << " deleted successfully.\n";
    }

    void deleteDoctor() {
        int id = getValidatedIntegerInput("\nEnter Doctor ID to delete: ");
        int index = -1;
        for (int i = 0; i < doctorCount; i++) {
            if (doctors[i].getDoctorID() == id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "\nDoctor with ID " << id << " not found.\n";
            return;
        }

        for (int i = index; i < doctorCount - 1; i++) {
            doctors[i] = doctors[i + 1];
        }

        doctorCount--;
        cout << "\nDoctor with ID " << id << " deleted successfully.\n";
    }

    void cancelAppointment() {
        int id = getValidatedIntegerInput("\nEnter Appointment ID to cancel: ");
        int index = -1;
        for (int i = 0; i < appointmentCount; i++) {
            if (appointments[i].getAppointmentID() == id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "\nAppointment with ID " << id << " not found.\n";
            return;
        }

        for (int i = index; i < appointmentCount - 1; i++) {
            appointments[i] = appointments[i + 1];
        }

        appointmentCount--;
        cout << "\nAppointment with ID " << id << " canceled successfully.\n";
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
        cout << "7. Delete Patient\n";
        cout << "8. Delete Doctor\n";
        cout << "9. Cancel Appointment\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidatedIntegerInput("");

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
            case 7:
                hms.deletePatient();
                break;
            case 8:
                hms.deleteDoctor();
                break;
            case 9:
                hms.cancelAppointment();
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
