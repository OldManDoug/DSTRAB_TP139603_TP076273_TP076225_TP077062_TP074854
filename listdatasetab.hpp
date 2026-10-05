#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <cstdio>

using namespace std; // no need put std in front of everything

// ------------------------------------
// 1. Singly Linked List Implementation
// ------------------------------------

// RecordA structure for linked list
struct RecordA {
    string *fields; // dynamic array of fields
    int fieldCount;
    RecordA *next;
};

// Linked list class for CSV rows
class SinglyB {
private:
    RecordA *head;

public:
    SinglyB() : head(nullptr) {}

    ~SinglyB() {
        clear(); //clean memory
    }

    // Add a row to the linked list
    void appendRow(string *fields, int count) {
        RecordA *newNode = new RecordA;
        newNode->fields = fields;
        newNode->fieldCount = count;
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
        } else {
            RecordA *temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    // Display all rows
    void display() const {
    RecordA *temp = head;

    // 1. Fix width outside the looping
    cout << left 
         << "| " << setw(5)  << "Age"
         << " | " << setw(15) << "Care Type"
         << " | " << setw(16) << "Length of Stay"
         << " | " << setw(11) << "Base Cost"
         << " | " << setw(12) << "Days Visit" << " |\n";

    // Header separator line
    cout << string(75, '-') << "\n";

    // 2. Loop through nodes and print rows horizontally
    while (temp) {
        cout << "| ";
        
        for (int i = 0; i < temp->fieldCount; ++i) {
            // Match column widths with header
            int width = 10;
            if (i == 0) width = 5;       // Age
            else if (i == 1) width = 15; // Care Type
            else if (i == 2) width = 16; // Length of Stay
            else if (i == 3) width = 11; // Base Cost
            else if (i == 4) width = 12; // Days Visit

            cout << left << setw(width) << temp->fields[i] << " | ";
        }
// single line separateion
        cout << "\n";
        temp = temp->next; //to allow for A
    }
    // Closing separator line
    cout << string(75, '-') << "\n";
}
    // Clear all rows
    void clear() {
        RecordA *temp = head;
        while (temp) {
            RecordA *nextNode = temp->next;
            delete[] temp->fields;
            delete temp;
            temp = nextNode;
        }
        head = nullptr;
    }
};

// Function to parse a CSV line into fields
string* parseCSVLine1(const string &line, int &count) {
stringstream ss(line);
   string field;
    count = 0;

    // First pass: count fields
    stringstream ssCount(line);
    while (getline(ssCount, field, ',')) count++;

    // Allocate array for fields
    string *fields = new string[count];

    // Second pass: store fields
    int idx = 0;
    while (getline(ss, field, ',')) {
        fields[idx++] = field;
    }

    return fields;
}

void implementing() {
    SinglyB csvList;
    string filename = "dataset1facility_a.csv";

    // Read CSV file
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << "\n";
    }

string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // skip empty lines
        int fieldCount = 0;
        string *fields = parseCSVLine1(line, fieldCount);
        csvList.appendRow(fields, fieldCount);
    }
    file.close();

    // Display CSV contents
    cout << "\nDataset 1 Details:\n";
    csvList.display();
    
}
// ------------------------------------
// 1. Singly Linked List Implementation
// ------------------------------------

// Node structure for linked list
struct RecordB {
    string *fields; // dynamic array of fields
    int fieldCount;
    RecordB *next;
};

// Linked list class for CSV rows
class SinglyA {
private:
    RecordB *head;

public:
    SinglyA() : head(nullptr) {}

    ~SinglyA() {
        clear(); //clean memory
    }

    // Add a row to the linked list
    void appendRow(string *fields, int count) {
        RecordB *newNode = new RecordB;
        newNode->fields = fields;
        newNode->fieldCount = count;
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
        } else {
            RecordB *temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    // Display all rows
    void display() const {
    RecordB *temp = head;

    // 1. Fix width outside the looping
    cout << left 
         << "| " << setw(5)  << "Age"
         << " | " << setw(15) << "Care Type"
         << " | " << setw(16) << "Length of Stay"
         << " | " << setw(11) << "Base Cost"
         << " | " << setw(12) << "Days Visit" << " |\n";

    // Header separator line
    cout << string(75, '-') << "\n";

    // 2. Loop through nodes and print rows horizontally
    while (temp) {
        cout << "| ";
        
        for (int i = 0; i < temp->fieldCount; ++i) {
            // Match column widths with header
            int width = 10;
            if (i == 0) width = 5;       // Age
            else if (i == 1) width = 15; // Care Type
            else if (i == 2) width = 16; // Length of Stay
            else if (i == 3) width = 11; // Base Cost
            else if (i == 4) width = 12; // Days Visit

            cout << left << setw(width) << temp->fields[i] << " | ";
        }
// single line separateion
        cout << "\n";
        temp = temp->next; //to allow for A
    }
    // Closing separator line
    cout << string(75, '-') << "\n";
}
    // Clear all rows
    void clear() {
        RecordB *temp = head;
        while (temp) {
            RecordB *nextNode = temp->next;
            delete[] temp->fields;
            delete temp;
            temp = nextNode;
        }
        head = nullptr;
    }
};

// Function to parse a CSV line into fields
string* parseCSVLines(const string &line, int &count) {
stringstream ss(line);
   string field;
    count = 0;

    // First pass: count fields
    stringstream ssCount(line);
    while (getline(ssCount, field, ',')) count++;

    // Allocate array for fields
    string *fields = new string[count];

    // Second pass: store fields
    int idx = 0;
    while (getline(ss, field, ',')) {
        fields[idx++] = field;
    }

    return fields;
}

void clears() {
    SinglyA csvList;
    string filename = "dataset2facility_b.csv";

    // Read CSV file
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << "\n";
    }

string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // skip empty lines
        int fieldCount = 0;
        string *fields = parseCSVLines(line, fieldCount);
        csvList.appendRow(fields, fieldCount);
    }
    file.close();

    // Display CSV contents
    cout << "\nDataset 2 Details:\n";
    csvList.display();
    
}// Node structure for linked list
struct Node {
    string *fields; // dynamic array of fields
    int fieldCount;
    Node *next;
};

// Linked list class for CSV rows
class Singly {
private:
    Node *head;

public:
    Singly() : head(nullptr) {}

    ~Singly() {
        clear(); //clean memory
    }

    // Add a row to the linked list
    void appendRow(string *fields, int count) {
        Node *newNode = new Node;
        newNode->fields = fields;
        newNode->fieldCount = count;
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
        } else {
            Node *temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    // Display all rows
    void display() const {
    Node *temp = head;

    // 1. Fix width outside the looping
    cout << left 
         << "| " << setw(5)  << "Age"
         << " | " << setw(15) << "Care Type"
         << " | " << setw(16) << "Length of Stay"
         << " | " << setw(11) << "Base Cost"
         << " | " << setw(12) << "Days Visit" << " |\n";

    // Header separator line
    cout << string(75, '-') << "\n";

    // 2. Loop through nodes and print rows horizontally
    while (temp) {
        cout << "| ";
        
        for (int i = 0; i < temp->fieldCount; ++i) {
            // Match column widths with header
            int width = 10;
            if (i == 0) width = 5;       // Age
            else if (i == 1) width = 15; // Care Type
            else if (i == 2) width = 16; // Length of Stay
            else if (i == 3) width = 11; // Base Cost
            else if (i == 4) width = 12; // Days Visit

            cout << left << setw(width) << temp->fields[i] << " | ";
        }
// single line separateion
        cout << "\n";
        temp = temp->next; //to allow for A
    }
    // Closing separator line
    cout << string(75, '-') << "\n";
}
    // Clear all rows
    void clear() {
        Node *temp = head;
        while (temp) {
            Node *nextNode = temp->next;
            delete[] temp->fields;
            delete temp;
            temp = nextNode;
        }
        head = nullptr;
    }
};

// Function to parse a CSV line into fields
string* parseCSVLine(const string &line, int &count) {
stringstream ss(line);
   string field;
    count = 0;

    // First pass: count fields
    stringstream ssCount(line);
    while (getline(ssCount, field, ',')) count++;

    // Allocate array for fields
    string *fields = new string[count];

    // Second pass: store fields
    int idx = 0;
    while (getline(ss, field, ',')) {
        fields[idx++] = field;
    }

    return fields;
}

void implements() {
    Singly csvList;
    string filename = "dataset3facility_c.csv";

    // Read CSV file
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Cannot open file " << filename << "\n";
    }

string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // skip empty lines
        int fieldCount = 0;
        string *fields = parseCSVLine(line, fieldCount);
        csvList.appendRow(fields, fieldCount);
    }
    file.close();

    // Display CSV contents
    cout << "\nDataset 3 Details:\n";
    csvList.display();
    
}
