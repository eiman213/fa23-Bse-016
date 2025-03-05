#include <iostream>
#include <string>
using namespace std;

struct Task {
    int id;
    string description;
    int priority;
    Task* next;
};

class TaskManager {
private:
    Task* head;
public:
    TaskManager() : head(nullptr) {}

    void addTask(int id, const string& desc, int priority) {
        Task* newTask = new Task{id, desc, priority, nullptr};
        if (!head || head->priority < priority) {
            newTask->next = head;
            head = newTask;
            return;
        }
        Task* current = head;
        while (current->next && current->next->priority >= priority) {
            current = current->next;
        }
        newTask->next = current->next;
        current->next = newTask;
    }

    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        Task* temp = head;
        head = head->next;
        delete temp;
        cout << "Removed highest priority task.\n";
    }

    void removeTaskById(int id) {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }
        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Task ID " << id << " removed.\n";
            return;
        }
        Task* current = head;
        while (current->next && current->next->id != id) {
            current = current->next;
        }
        if (!current->next) {
            cout << "Task ID " << id << " not found.\n";
            return;
        }
        Task* temp = current->next;
        current->next = temp->next;
        delete temp;
        cout << "Task ID " << id << " removed.\n";
    }

    void displayTasks() const {
        if (!head) {
            cout << "No tasks available.\n";
            return;
        }
        Task* temp = head;
        while (temp) {
            cout << "[ID: " << temp->id << ", Priority: " << temp->priority << "] " << temp->description << "\n";
            temp = temp->next;
        }
    }

    ~TaskManager() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TaskManager manager;
    int choice, id, priority;
    string desc;

    do {
        cout << "\nTask Manager\n";
        cout << "1. Add Task\n2. View Tasks\n3. Remove Highest Priority Task\n4. Remove Task by ID\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Task ID: ";
                cin >> id;
                cin.ignore();
                cout << "Description: ";
                getline(cin, desc);
                cout << "Priority: ";
                cin >> priority;
                manager.addTask(id, desc, priority);
                break;
            case 2:
                manager.displayTasks();
                break;
            case 3:
                manager.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter ID to remove: ";
                cin >> id;
                manager.removeTaskById(id);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
