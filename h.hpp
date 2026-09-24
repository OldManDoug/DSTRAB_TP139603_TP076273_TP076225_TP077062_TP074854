#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// ------------------------------------
// 1. Singly Linked List Implementation
// ------------------------------------
struct Node {
    string data;
    Node* next;
    Node(string val) : data(val), next(nullptr) {}
};

void insertEnd(Node*& head, const string& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void implements() {
    Node* head = nullptr;
    // Escaped backslashes or forward slashes for Windows paths
    ifstream infile("dataset1facility_a.csv"); 

    if (!infile.is_open()) {
        cerr << "Error: Could not open dataset3_facility_c.csv" << endl;
        return;
    }

    string line;
    int age;
    while (getline(infile, line)) {
        insertEnd(head, line);
    }
    infile.close();

    // Display linked list
    Node* temp = head;
    while (temp) {
        cout << temp->data << endl;
        temp = temp->next;
    }
}

/*/ ------------------------------------
// 2. Circular Linked List Implementation
// ------------------------------------
struct RecordA {
    string careType;
    int age;
    int daysVisit;
    int baseCost;
};

struct ProcessRecordA {
    RecordA data;
    ProcessRecordA* next;
    ProcessRecordA(const RecordA& rec) : data(rec), next(nullptr) {}
};

class CircularListA {
    ProcessRecordA* head;
public:
    CircularListA() : head(nullptr) {}

    void insert(const RecordA& rec) {
        ProcessRecordA* newNode = new ProcessRecordA(rec);
        if (!head) {
            head = newNode;
            head->next = head; // Point to self (Circular)
            return;
        }
        ProcessRecordA* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }

    
};
void processFile(const string& filename) {
    ProcessRecordA* r = nullptr;
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string careTypeStr, ageStr, daysStr, costStr;

            // Parse CSV comma-separated tokens
            if (getline(ss, careTypeStr, ',') &&
                getline(ss, ageStr, ',') &&
                getline(ss, daysStr, ',') &&
                getline(ss, costStr, ',')) {

                RecordA rec;
                rec.careType = careTypeStr;
                rec.age = stoi(ageStr);
                rec.daysVisit = stoi(daysStr);
                rec.baseCost = stoi(costStr);

              //  insert(rec);
            }
        }
        file.close();
    }
*/