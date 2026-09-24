#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

// Node structure for linked list
struct Node {
    std::string *fields; // dynamic array of fields
    int fieldCount;
    Node *next;
};

// Linked list class for CSV rows
class CSVLinkedList {
private:
    Node *head;

public:
    CSVLinkedList() : head(nullptr) {}

    ~CSVLinkedList() {
        clear();
    }

    // Add a row to the linked list
    void appendRow(std::string *fields, int count) {
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
        int rowNum = 1;
        while (temp) {
            std::cout << "Row " << rowNum++ << ": ";
            for (int i = 0; i < temp->fieldCount; ++i) {
                std::cout << temp->fields[i];
                if (i < temp->fieldCount - 1) std::cout << " | ";
            }
            std::cout << "\n";
            temp = temp->next;
        }
    }

    // Delete a row by index (1-based)
    bool deleteRow(int index) {
        if (index <= 0 || !head) return false;

        Node *temp = head;
        Node *prev = nullptr;
        int currentIndex = 1;

        while (temp && currentIndex < index) {
            prev = temp;
            temp = temp->next;
            currentIndex++;
        }

        if (!temp) return false; // index out of range

        if (!prev) {
            head = temp->next;
        } else {
            prev->next = temp->next;
        }

        delete[] temp->fields;
        delete temp;
        return true;
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
std::string* parseCSVLine(const std::string &line, int &count) {
    std::stringstream ss(line);
    std::string field;
    count = 0;

    // First pass: count fields
    std::stringstream ssCount(line);
    while (std::getline(ssCount, field, ',')) count++;

    // Allocate array for fields
    std::string *fields = new std::string[count];

    // Second pass: store fields
    int idx = 0;
    while (std::getline(ss, field, ',')) {
        fields[idx++] = field;
    }

    return fields;
}

int main() {
    CSVLinkedList csvList;
    std::string filename = "dataset3_facility_c.csv";

    // Read CSV file
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << "\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue; // skip empty lines
        int fieldCount = 0;
        std::string *fields = parseCSVLine(line, fieldCount);
        csvList.appendRow(fields, fieldCount);
    }
    file.close();

    // Display CSV contents
    std::cout << "Initial CSV contents:\n";
    csvList.display();

    // Append a new row manually
    std::string *newFields = new std::string[3];
    newFields[0] = "New";
    newFields[1] = "Row";
    newFields[2] = "Data";
    csvList.appendRow(newFields, 3);

    std::cout << "\nAfter appending a new row:\n";
    csvList.display();

    // Delete a row
    if (csvList.deleteRow(2)) {
        std::cout << "\nAfter deleting row 2:\n";
        csvList.display();
    } else {
        std::cout << "\nFailed to delete row 2.\n";
    }

    return 0;
}
