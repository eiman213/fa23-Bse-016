#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Patient {
    string fullName;
    string emergency;
    int level;
    int order;

    Patient(string name, string condition, int prio, int arrival)
        : fullName(name), emergency(condition), level(prio), order(arrival) {}
};

struct PriorityCompare {
    bool operator()(const Patient& a, const Patient& b) {
        if (a.level == b.level)
            return a.order > b.order;
        return a.level > b.level;
    }
};
int determinePriority(const string& condition) {
    if (condition == "Heart Attack" || condition == "Stroke")
        return 1;
    else if (condition == "Broken Leg" || condition == "Severe Burn" || condition == "Fractured Arm")
        return 2;
    else if (condition == "Fever" || condition == "Food Poisoning" || condition == "Migraine")
        return 3;
    else
        return 4;
}

int main() {
    priority_queue<Patient, vector<Patient>, PriorityCompare> waitingList;
    int patientCounter = 1;
    int option;

    do {
        cout << "\n=== Emergency Room Menu ===\n";
        cout << "1. Register New Patient\n";
        cout << "2. View Treatment Sequence\n";
        cout << "3. Exit Program\n";
        cout << "Select an option: ";
        cin >> option;
        cin.ignore();

        if (option == 1) {
            string name, condition;
            cout << "Enter Patient's Name: ";
            getline(cin, name);
            cout << "Enter Emergency Condition: ";
            getline(cin, condition);

            int prio = determinePriority(condition);
            waitingList.push(Patient(name, condition, prio, patientCounter++));
            cout << "✔ Patient registered successfully.\n";
        }
        else if (option == 2) {
            if (waitingList.empty()) {
                cout << "⚠ No patients are currently waiting.\n";
            } else {
                cout << "\n--- Treatment Queue ---\n";
                auto copyQueue = waitingList;
                while (!copyQueue.empty()) {
                    Patient p = copyQueue.top();
                    copyQueue.pop();
                    cout << "Name: " << p.fullName
                         << " | Condition: " << p.emergency
                         << " | Priority: " << p.level << "\n";
                }
            }
        }
        else if (option == 3) {
            cout << "Exiting system...\n";
        }
        else {
            cout << "Invalid option! Please try again.\n";
        }
    } while (option != 3);

    return 0;
}
