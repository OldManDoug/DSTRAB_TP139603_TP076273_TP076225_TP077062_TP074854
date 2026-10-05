#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <cstdio>

using namespace std; // no need put std in front of everything


/*/ ------------------------------------
// 2. Singly Linked List Implementation
// ------------------------------------
struct LengthStay {
    int age;
    string *caretype;
    int lengthofstay;
    float basecost;
    int daysVisit;
    RecordB* next;
}; // Structure of a dataset

// Linked List class
class LinkedList {
private:
    RecordB* head;

public:
    LinkedList() : head(nullptr) {}

    // Destructor to clean up memory
    ~LinkedList() {
        RecordB* current = head;
        while (current != nullptr) {
            RecordB* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Append a new node at the end of the list
    void append(string caretype,
    int lengthofstay,
    float basecost,
    int daysVisit) {
        RecordB *newNode = new RecordB;
        newNode->caretype = caretype;
        newNode->lengthofstay = lengthofstay;
        newNode->basecost = basecost;
        newNode->daysVisit = daysVisit;
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
};

void creater() {
    LinkedList list;
    
    // Open the file
    ifstream file("dataset2facility_b.csv");

    // Check if the file opened successfully
    if (!file.is_open()) {
        cerr << "Error: Could not open the file.\n";
    }

string line;
    while (getline(file, line)) {
        if (line.empty()) continue; // skip empty lines
        int fieldCount = 0;
        string *fields = parseCSVLine(line, fieldCount);
        list.append(fields, fieldCount);
    }
    file.close();

    // Display CSV contents
    cout << "\nDataset 2 Details:\n";
   
    list.display();
};*/

// Node structure for the linked list
struct BaseCost {
    double data;
    BaseCost* next;

    BaseCost(double val) : data(val), next(nullptr) {}
};

// Linked List class
class NumberedLinkedList {
private:
    BaseCost* head;
    int count;

public:
    NumberedLinkedList() : head(nullptr), count(0) {}

    // Destructor to clean up dynamically allocated memory
    ~NumberedLinkedList() {
        BaseCost* current = head;
        while (current != nullptr) {
            BaseCost* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Insert a new number at the end of the linked list
    void insert(double val) {
        BaseCost* newNode = new BaseCost(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            BaseCost* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        count++;
    }

    // Calculate total and average
    void calculateStats() const {
        if (head == nullptr) {
            cout << "No numbers found in the file." << endl;
            return;
        }

        double total = 0.0;
        BaseCost* temp = head;

        while (temp != nullptr) {
            total += temp->data;
            temp = temp->next;
        }

        double average = total / count;

        cout << "Total Count of Patients: " << count << endl;
        cout << "Total Sum of Costs: RM" << total << endl;
        cout << "Average Base Cost: RM" << average << endl;
    }
};

// Helper function to check if a token string is a valid number
bool tryParseDouble(const string& str, double& value) {
    stringstream ss(str);
    ss >> value;
    // Check if entire token was consumed as a number
    return !ss.fail() && ss.eof();
}

void check() {
    string fileName = "Book1.csv";
    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
    }

    NumberedLinkedList numList;
    string token;

    // Read word by word (whitespace-delimited)
    while (inFile >> token) {
        double val;
        // Extract numbers and ignore text characters
        if (tryParseDouble(token, val)) {
            numList.insert(val);
        }
    }

    inFile.close();

    // Compute total and average from linked list
    numList.calculateStats();

}
// the above code brings forth the overall datasetX's costs. 
// for the other 2 datasets we can combine to make 600. 

//https://tutorialforgeeks.com/linked-list-operations-in-c-traversal-insertion-deletion-searching-and-reversal
template <typename T>
class DoublyLinkedList {
private:
    struct Age {
        T data;
        Age* prev;
        Age* next;

        Age(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Age* head;
    Age* tail;
    size_t listSize;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    bool empty() const {
        return head == nullptr;
    }

    size_t size() const {
        return listSize;
    }

    // --- Core Operations ---
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    void remove(const T& value);
    void print_forward() const;
    void print_backward() const;
    void clear();
};
template <typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
    Age* newNode = new Age(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    ++listSize;
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    Age* newNode = new Age(value);
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    ++listSize;
}template <typename T>
void DoublyLinkedList<T>::pop_front() {
    if (empty()) return;

    Age* temp = head;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    delete temp;
    --listSize;
}

template <typename T>
void DoublyLinkedList<T>::pop_back() {
    if (empty()) return;

    Age* temp = tail;
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete temp;
    --listSize;
}

template <typename T>
void DoublyLinkedList<T>::remove(const T& value) {
    Age* current = head;
    while (current && current->data != value) {
        current = current->next;
    }

    if (!current) return; // Value not found

    if (current == head) {
        pop_front();
    } else if (current == tail) {
        pop_back();
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        --listSize;
    }
}
template <typename T>
void DoublyLinkedList<T>::print_forward() const {
    Age* current = head;
    std::cout << "Forward:  ";
    while (current) {
        std::cout << current->data << " <-> ";
        current = current->next;
    }
    std::cout << "nullptr\n";
}

template <typename T>
void DoublyLinkedList<T>::print_backward() const {
    Age* current = tail;
    std::cout << "Backward: ";
    while (current) {
        std::cout << current->data << " <-> ";
        current = current->prev;
    }
    std::cout << "nullptr\n";
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

// RecordB structure
struct DaysVisit {
    int data;
    DaysVisit* next;
   DaysVisit(int val) : data(val), next(nullptr) {}

};

// Linked List class
class NumberLinkedList {
private:
    DaysVisit* head;
    int count;

public:
    NumberLinkedList() : head(nullptr), count(0) {}

    // Destructor to clean up dynamically allocated memory
    ~NumberLinkedList() {
        DaysVisit* current = head;
        while (current != nullptr) {
            DaysVisit* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Insert a new number at the end of the linked list
    void insertion(int val) {
        DaysVisit* newNode = new DaysVisit(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            DaysVisit* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        count++;
    }

    // Calculate total and average
    void calculateStat() const {
        if (head == nullptr) {
            cout << "No numbers found in the file." << endl;
            return;
        }

        int total = 0;
        DaysVisit* temp = head;
//somewhere here is the issue - head is null 
        while (temp != nullptr) {
            total += temp->data;
            temp = temp->next;
        }

        double average = static_cast<double>(total) / count;

        cout << "Total Count of Patients: " << count << endl;
        cout << "Total Sum of Days:" << total << endl;
        cout << "Average visit duration:" << average << "days"<< endl;
    }
};

// Helper function to check if a token string is a valid number
bool tryParseDouble1(const string& str, int& value) {
    stringstream ss(str);
    ss >> value;
    // Check if entire token was consumed as a number
    return !ss.fail() && ss.eof();
}

void days() {
    string fileName = "DaysVisitedDataset.csv";
    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
    }

    NumberLinkedList numList;
    string token;

    // Read word by word (whitespace-delimited)
    while (inFile >> token) {
        int  val;
        // Extract numbers and ignore text characters
        if (tryParseDouble1(token, val)) {
            numList.insertion(val);
        }
    }

    inFile.close();

    // Compute total and average from linked list
    numList.calculateStat();

}
struct Staylength {
    int data;
    Staylength* next;
   Staylength(int val) : data(val), next(nullptr) {}

};

// Linked List class
class NumbersLinkedList {
private:
    Staylength* header;
    int count;

public:
    NumbersLinkedList() : header(nullptr), count(0) {}

    // Destructor to clean up dynamically allocated memory
    ~NumbersLinkedList() {
        Staylength* current = header;
        while (current != nullptr) {
            Staylength* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Insert a new number at the end of the linked list
    void insertion(int val) {
        Staylength* newNode = new Staylength(val);
        if (header == nullptr) {
            header = newNode;
        } else {
            Staylength* temp = header;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        count++;
    }

    // Calculate total and average
    void calculateStat() const {
        if (header == nullptr) {
            cout << "No numbers found in the file." << endl;
            return;
        }

        int total = 0;
        Staylength* temp = header;
//somewhere here is the issue - head is null 
        while (temp != nullptr) {
            total += temp->data;
            temp = temp->next;
        }

        double average = static_cast<double>(total) / count;

        cout << "Total Count of Patients: " << count << endl;
        cout << "Total Spent Days:" << total << endl;
        cout << "Average length of stay: %.2f" << average << "days"<< endl;
    }
};

// Helper function to check if a token string is a valid number
bool tryParseDouble2(const string& str, int& value) {
    stringstream ss(str);
    ss >> value;
    // Check if entire token was consumed as a number
    return !ss.fail() && ss.eof();
}

void stayA() {
    string fileName = "StayLengthA.csv";
    string file = "StayLengthC.csv";
    ifstream inFile(fileName);
//try 2 files 
ifstream f(file);

    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
    }
    else if(!f.is_open()){
        cerr << "File unfounded "<<endl;
    }

    NumbersLinkedList numList;
    string token;

    // Read word by word (whitespace-delimited)
    while (inFile >> token) {
        int  val;
        // Extract numbers and ignore text characters
        if (tryParseDouble2(token, val)) {
            numList.insertion(val);
        }   
    }
// if then B then C if not,,,,
    inFile.close();

    // Compute total and average from linked list
    numList.calculateStat();

}

void stayB() {
    string fileName = "StayLengthB.csv";
    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
    }

    NumbersLinkedList numList;
    string token;

    // Read word by word (whitespace-delimited)
    while (inFile >> token) {
        int  val;
        // Extract numbers and ignore text characters
        if (tryParseDouble2(token, val)) {
            numList.insertion(val);
        }
    }

    inFile.close();

    // Compute total and average from linked list
    numList.calculateStat();

}
//