
#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Request {
public:
    int id;
    string name;
    string location;
    string service;
    string description;
    int priority;
    string status;
    Request* next;

    Request(int i, string n, string loc, string s,
            string desc, int p) {
        id = i;
        name = n;
        location = loc;
        service = s;
        description = desc;
        priority = p;
        status = "Pending";
        next = nullptr;
    }
};

class EmergencySystem {
private:
    Request* head;
    int nextID;

    Request* findRequest(int id) {
        Request* temp = head;

        while (temp != nullptr) {
            if (temp->id == id)
                return temp;

            temp = temp->next;
        }

        return nullptr;
    }

    int getPriority() {
        int priority;

        cout << "\nSelect Priority Level:\n";
        cout << "1. Critical\n";
        cout << "2. High\n";
        cout << "3. Medium\n";
        cout << "4. Low\n";
        cout << "Enter priority: ";

        if (!(cin >> priority) ||
            priority < 1 || priority > 4) {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            return -1;
        }

        return priority;
    }

    string priorityName(int priority) {
        switch (priority) {
            case 1: return "Critical";
            case 2: return "High";
            case 3: return "Medium";
            case 4: return "Low";
            default: return "Unknown";
        }
    }

public:
    EmergencySystem() {
        head = nullptr;
        nextID = 1001;
    }

    // 1. Register emergency request
    void registerRequest() {
        string name, location, service, description;
        int choice;

        cout << "\nEnter Caller Name: ";
        getline(cin >> ws, name);

        cout << "Enter Emergency Location: ";
        getline(cin >> ws, location);

        cout << "\nSelect Emergency Service:\n";
        cout << "1. Ambulance\n";
        cout << "2. Fire Brigade\n";
        cout << "3. Police\n";
        cout << "4. Disaster Response\n";
        cout << "Enter choice: ";

        if (!(cin >> choice) ||
            choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            cout << "Invalid service selection!\n";
            return;
        }

        switch (choice) {
            case 1: service = "Ambulance"; break;
            case 2: service = "Fire Brigade"; break;
            case 3: service = "Police"; break;
            case 4: service = "Disaster Response"; break;
        }

        cout << "Describe the Emergency: ";
        getline(cin >> ws, description);

        int priority = getPriority();

        if (priority == -1) {
            cout << "Invalid priority!\n";
            return;
        }

        Request* newRequest = new Request(
            nextID, name, location, service,
            description, priority
        );

        // Insert at end to preserve registration order
        if (head == nullptr) {
            head = newRequest;
        } else {
            Request* temp = head;

            while (temp->next != nullptr)
                temp = temp->next;

            temp->next = newRequest;
        }

        cout << "\nEmergency request registered!\n";
        cout << "Request ID: " << nextID << '\n';
        cout << "Service: " << service << '\n';
        cout << "Priority: " << priorityName(priority) << '\n';

        nextID++;
    }

    // 2. Display all requests
    void displayRequests() {
        if (head == nullptr) {
            cout << "\nNo emergency requests found.\n";
            return;
        }

        Request* temp = head;

        cout << "\n========== EMERGENCY REQUESTS ==========\n";

        while (temp != nullptr) {
            cout << "\nRequest ID  : " << temp->id;
            cout << "\nCaller      : " << temp->name;
            cout << "\nLocation    : " << temp->location;
            cout << "\nService     : " << temp->service;
            cout << "\nDescription : " << temp->description;
            cout << "\nPriority    : "
                 << priorityName(temp->priority);
            cout << "\nStatus      : " << temp->status;
            cout << "\n----------------------------------------\n";

            temp = temp->next;
        }
    }

    // 3. Search request
    void searchRequest() {
        int id;

        cout << "\nEnter Request ID: ";
        cin >> id;

        Request* r = findRequest(id);

        if (r == nullptr) {
            cout << "Request not found!\n";
            return;
        }

        cout << "\nRequest Found!\n";
        cout << "ID          : " << r->id << '\n';
        cout << "Caller      : " << r->name << '\n';
        cout << "Location    : " << r->location << '\n';
        cout << "Service     : " << r->service << '\n';
        cout << "Description : " << r->description << '\n';
        cout << "Priority    : "
             << priorityName(r->priority) << '\n';
        cout << "Status      : " << r->status << '\n';
    }

    // 4. Process highest-priority pending request
    void processNextRequest() {
        Request* temp = head;
        Request* best = nullptr;

        while (temp != nullptr) {
            if (temp->status == "Pending") {
                if (best == nullptr ||
                    temp->priority < best->priority) {
                    best = temp;
                }
            }

            temp = temp->next;
        }

        if (best == nullptr) {
            cout << "No pending requests available.\n";
            return;
        }

        best->status = "In Progress";

        cout << "\nHighest-priority request assigned!\n";
        cout << "Request ID : " << best->id << '\n';
        cout << "Service    : " << best->service << '\n';
        cout << "Location   : " << best->location << '\n';
        cout << "Priority   : "
             << priorityName(best->priority) << '\n';
        cout << "Status     : In Progress\n";
    }

    // 5. Complete request
    void completeRequest() {
        int id;

        cout << "\nEnter Request ID to complete: ";
        cin >> id;

        Request* r = findRequest(id);

        if (r == nullptr) {
            cout << "Request not found!\n";
            return;
        }

        if (r->status != "In Progress") {
            cout << "Only in-progress requests can be completed.\n";
            return;
        }

        r->status = "Completed";
        cout << "Request marked as completed.\n";
    }

    // 6. Cancel request
    void cancelRequest() {
        int id;

        cout << "\nEnter Request ID to cancel: ";
        cin >> id;

        Request* r = findRequest(id);

        if (r == nullptr) {
            cout << "Request not found!\n";
            return;
        }

        if (r->status != "Pending") {
            cout << "Only pending requests can be cancelled.\n";
            return;
        }

        r->status = "Cancelled";
        cout << "Request cancelled successfully.\n";
    }

    // 7. Display pending requests
    void displayPending() {
        Request* temp = head;
        bool found = false;

        cout << "\n========== PENDING REQUESTS ==========\n";

        while (temp != nullptr) {
            if (temp->status == "Pending") {
                cout << "ID: " << temp->id
                     << " | Service: " << temp->service
                     << " | Priority: "
                     << priorityName(temp->priority)
                     << " | Location: " << temp->location
                     << '\n';

                found = true;
            }

            temp = temp->next;
        }

        if (!found)
            cout << "No pending requests.\n";
    }

    // 8. Request statistics
    void showStatistics() {
        int total = 0, pending = 0;
        int progress = 0, completed = 0, cancelled = 0;

        Request* temp = head;

        while (temp != nullptr) {
            total++;

            if (temp->status == "Pending")
                pending++;
            else if (temp->status == "In Progress")
                progress++;
            else if (temp->status == "Completed")
                completed++;
            else if (temp->status == "Cancelled")
                cancelled++;

            temp = temp->next;
        }

        cout << "\n========== STATISTICS ==========\n";
        cout << "Total Requests      : " << total << '\n';
        cout << "Pending             : " << pending << '\n';
        cout << "In Progress         : " << progress << '\n';
        cout << "Completed           : " << completed << '\n';
        cout << "Cancelled           : " << cancelled << '\n';
    }

    // Free memory
    ~EmergencySystem() {
        while (head != nullptr) {
            Request* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    EmergencySystem system;
    int choice;

    do {
        cout << "\n\n======================================";
        cout << "\n   EMERGENCY SERVICE MANAGEMENT";
        cout << "\n======================================";
        cout << "\n1. Register Emergency";
        cout << "\n2. Display All Requests";
        cout << "\n3. Search Request";
        cout << "\n4. Process Next Request";
        cout << "\n5. Complete Request";
        cout << "\n6. Cancel Request";
        cout << "\n7. Display Pending Requests";
        cout << "\n8. Show Statistics";
        cout << "\n0. Exit";
        cout << "\nEnter Your Choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            continue;
        }

        switch (choice) {
            case 1:
                system.registerRequest();
                break;
            case 2:
                system.displayRequests();
                break;
            case 3:
                system.searchRequest();
                break;
            case 4:
                system.processNextRequest();
                break;
            case 5:
                system.completeRequest();
                break;
            case 6:
                system.cancelRequest();
                break;
            case 7:
                system.displayPending();
                break;
            case 8:
                system.showStatistics();
                break;
            case 0:
                cout << "Exiting Emergency Management System.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
