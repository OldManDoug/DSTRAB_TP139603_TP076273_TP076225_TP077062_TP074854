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

// Node structure for linked list
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


/*/ ------------------------------------
// 2. Singly Linked List Implementation
// ------------------------------------
struct RecordB {
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

// ------------------------------------
// Length of stay - total and average (teammate's part, merged)
// ------------------------------------

// Node structure for the length-of-stay linked list
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
        cout << "Average length of stay: " << average << "days"<< endl;
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

// =====================================================================
// SORTING PART (linked list) - PatientList: insertion sort + merge sort
// Same fields / table layout as array.hpp so the two can be compared fairly.
// =====================================================================
// listsort.hpp - PURE linked list version of the patient datasets (no arrays, no STL containers)
// Singly linked list of Patient nodes + insertion sort + merge sort, using the same
// sort fields / table layout as array.hpp so the two structures can be compared fairly.
// Names are prefixed (List...) so this header can be included together with array.hpp.


// Fields a list can be sorted by (same numbers as the menu: 1 / 2 / 3)
const int LIST_SORT_BY_AGE = 1;
const int LIST_SORT_BY_DURATION = 2;   // visit duration = LengthOfStay (hours)
const int LIST_SORT_BY_COST = 3;       // total medical cost

// ListPatient - one row of a facility CSV file
struct ListPatient {
    int patientID;
    int age;
    string careType;
    int lengthOfStay;
    double baseCostPerHour;
    int daysVisitsPerYear;
    double totalCost;      // lengthOfStay * baseCostPerHour * daysVisitsPerYear
};

// PatientNode - one node: the record + pointer to the next node
struct PatientNode {
    ListPatient data;
    PatientNode* next;
    PatientNode() : next(nullptr) {}
    PatientNode(const ListPatient& p) : data(p), next(nullptr) {}
};

// ListSortStats - what one sort run did
struct ListSortStats {
    long long comparisons;
    int maxDepth;          // deepest recursion level reached (merge sort only)
    ListSortStats() : comparisons(0), maxDepth(0) {}
};

// ListNumberText - format a number with a fixed number of decimals
inline string listNumberText(double value, int decimals) {
    ostringstream out;
    out << fixed << setprecision(decimals) << value;
    return out.str();
}

class PatientList {
private:
    PatientNode* head;
    PatientNode* tail;     // kept so appending is O(1) instead of walking the whole list
    int count;

    // ---- CSV helpers (same rules as the array loader) ----
    static string trim(const string& text) {
        const string whitespace = " \t\r\n";
        size_t first = text.find_first_not_of(whitespace);
        if (first == string::npos) {
            return "";
        }
        size_t last = text.find_last_not_of(whitespace);
        return text.substr(first, last - first + 1);
    }

    static bool parseInt(const string& text, int& value) {
        istringstream ss(text);
        char extra;
        if (!(ss >> value)) {
            return false;
        }
        return !(ss >> extra);
    }

    static bool parseDouble(const string& text, double& value) {
        istringstream ss(text);
        char extra;
        if (!(ss >> value)) {
            return false;
        }
        return !(ss >> extra);
    }

    static bool parseRecord(const string& line, ListPatient& p, string& reason) {
        string fields[5];
        int fieldCount = 0;
        string field;
        stringstream ss(line);
        while (getline(ss, field, ',')) {
            if (fieldCount < 5) {
                fields[fieldCount] = trim(field);
            }
            fieldCount++;
        }
        if (fieldCount != 5) {
            ostringstream message;
            message << "expected 5 fields, found " << fieldCount;
            reason = message.str();
            return false;
        }
        if (!parseInt(fields[0], p.age) || p.age < 0) {
            reason = "invalid Age '" + fields[0] + "'";
            return false;
        }
        if (fields[1].empty()) {
            reason = "empty CareType";
            return false;
        }
        p.careType = fields[1];
        if (!parseInt(fields[2], p.lengthOfStay) || p.lengthOfStay < 0) {
            reason = "invalid LengthOfStay '" + fields[2] + "'";
            return false;
        }
        if (!parseDouble(fields[3], p.baseCostPerHour) || p.baseCostPerHour < 0) {
            reason = "invalid BaseCostPerHour '" + fields[3] + "'";
            return false;
        }
        if (!parseInt(fields[4], p.daysVisitsPerYear) || p.daysVisitsPerYear < 0) {
            reason = "invalid DaysVisitsPerYear '" + fields[4] + "'";
            return false;
        }
        return true;
    }

    // ---- sorting helpers ----
    // KeyOf - the value a record is sorted on
    static double keyOf(const ListPatient& p, int field) {
        if (field == LIST_SORT_BY_AGE) {
            return p.age;
        }
        if (field == LIST_SORT_BY_DURATION) {
            return p.lengthOfStay;
        }
        return p.totalCost;
    }

    // IsAfter - true when 'left' must be placed after 'right' (equal keys are NOT "after", so sorts are stable)
    static bool isAfter(const ListPatient& left, const ListPatient& right, int field, bool ascending) {
        double a = keyOf(left, field);
        double b = keyOf(right, field);
        if (ascending) {
            return a > b;
        }
        return a < b;
    }

    // FixTail - walk to the last node (needed after a sort re-links the nodes)
    void fixTail() {
        tail = head;
        while (tail != nullptr && tail->next != nullptr) {
            tail = tail->next;
        }
    }

    // MergeTwo - merge two sorted chains into one by re-linking nodes (no new nodes, no copying)
    static PatientNode* mergeTwo(PatientNode* a, PatientNode* b, int field, bool ascending, ListSortStats& stats) {
        PatientNode* result = nullptr;
        PatientNode** link = &result;      // address of the pointer we must fill next
        while (a != nullptr && b != nullptr) {
            stats.comparisons++;
            if (isAfter(a->data, b->data, field, ascending)) {
                *link = b;
                b = b->next;
            } else {
                *link = a;                 // left one wins ties, which keeps the sort stable
                a = a->next;
            }
            link = &((*link)->next);
        }
        *link = (a != nullptr) ? a : b;    // append whatever is left
        return result;
    }

    // MergeSortNodes - split the chain in half (slow/fast pointers), sort both halves, merge them
    static PatientNode* mergeSortNodes(PatientNode* first, int field, bool ascending, ListSortStats& stats, int depth) {
        if (depth > stats.maxDepth) {
            stats.maxDepth = depth;
        }
        if (first == nullptr || first->next == nullptr) {
            return first;
        }
        PatientNode* slow = first;
        PatientNode* fast = first->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        PatientNode* second = slow->next;  // start of the right half
        slow->next = nullptr;              // cut the chain in two

        PatientNode* left = mergeSortNodes(first, field, ascending, stats, depth + 1);
        PatientNode* right = mergeSortNodes(second, field, ascending, stats, depth + 1);
        return mergeTwo(left, right, field, ascending, stats);
    }

public:
    PatientList() : head(nullptr), tail(nullptr), count(0) {}

    // Copy constructor - deep copy so a sort on the copy leaves the original alone
    PatientList(const PatientList& other) : head(nullptr), tail(nullptr), count(0) {
        for (PatientNode* cur = other.head; cur != nullptr; cur = cur->next) {
            insertEnd(cur->data);
        }
    }

    PatientList& operator=(const PatientList& other) {
        if (this != &other) {
            clear();
            for (PatientNode* cur = other.head; cur != nullptr; cur = cur->next) {
                insertEnd(cur->data);
            }
        }
        return *this;
    }

    ~PatientList() {
        clear();
    }

    // InsertEnd - add a record at the END using the tail pointer
    void insertEnd(const ListPatient& p) {   // O(1)
        PatientNode* node = new PatientNode(p);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        count++;
    }

    // Clear - delete every node
    void clear() {   // O(n)
        PatientNode* cur = head;
        while (cur != nullptr) {
            PatientNode* nextNode = cur->next;
            delete cur;
            cur = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    int getCount() const {
        return count;
    }

    // CalculateTotalCosts - fill totalCost for every record
    void calculateTotalCosts() {   // O(n)
        for (PatientNode* cur = head; cur != nullptr; cur = cur->next) {
            cur->data.totalCost = cur->data.lengthOfStay * cur->data.baseCostPerHour * cur->data.daysVisitsPerYear;
        }
    }

    // LoadFromFile - read a CSV file (header optional); returns false if it cannot be opened
    bool loadFromFile(const string& filename) {   // O(n)
        clear();
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            cerr << "Error: Cannot open file " << filename << endl;
            return false;
        }
        string line;
        int lineNumber = 0;
        bool firstRecordLine = true;
        while (getline(file, line)) {
            lineNumber++;
            if (lineNumber == 1 && line.size() >= 3 &&
                (unsigned char)line[0] == 0xEF && (unsigned char)line[1] == 0xBB && (unsigned char)line[2] == 0xBF) {
                line.erase(0, 3);   // remove UTF-8 BOM
            }
            line = trim(line);
            if (line.empty()) {
                continue;
            }
            if (firstRecordLine) {
                firstRecordLine = false;
                int firstValue;
                if (!parseInt(trim(line.substr(0, line.find(','))), firstValue)) {
                    continue;       // header row
                }
            }
            ListPatient p;
            string reason;
            if (!parseRecord(line, p, reason)) {
                cerr << "Warning: line " << lineNumber << " skipped (" << reason << ")" << endl;
                continue;
            }
            p.patientID = count + 1;
            p.totalCost = 0;
            insertEnd(p);
        }
        file.close();
        calculateTotalCosts();
        return true;
    }

    // Display - same table as the array version; limit < 0 means print all
    void display(int limit = -1) const {
        if (count == 0) {
            cout << "(no records)" << endl;
            return;
        }
        int shown = (limit < 0 || limit > count) ? count : limit;
        cout << left
             << "| " << setw(5)  << "Age"
             << " | " << setw(15) << "Care Type"
             << " | " << setw(16) << "Length of Stay"
             << " | " << setw(11) << "Base Cost"
             << " | " << setw(12) << "Days Visit" << " |\n";
        cout << string(75, '-') << "\n";
        PatientNode* cur = head;
        for (int i = 0; i < shown; i++) {
            cout << "| " << setw(5)  << cur->data.age
                 << " | " << setw(15) << cur->data.careType
                 << " | " << setw(16) << cur->data.lengthOfStay
                 << " | " << setw(11) << cur->data.baseCostPerHour
                 << " | " << setw(12) << cur->data.daysVisitsPerYear << " |\n";
            cur = cur->next;
        }
        cout << string(75, '-') << "\n";
        cout << "Showing " << shown << " of " << count << " records" << endl;
    }

    // DisplayWithTotalCost - every record plus the total medical cost
    void displayWithTotalCost() const {   // O(n)
        const int ruleWidth = 101;
        cout << left
             << "| " << setw(5)  << "Age"
             << " | " << setw(15) << "Care Type"
             << " | " << setw(16) << "Length of Stay"
             << " | " << setw(11) << "Base Cost"
             << " | " << setw(12) << "Days Visit"
             << " | " << setw(23) << "Total Medical Cost (RM)" << " |\n";
        cout << string(ruleWidth, '-') << "\n";
        for (PatientNode* cur = head; cur != nullptr; cur = cur->next) {
            cout << "| " << setw(5)  << cur->data.age
                 << " | " << setw(15) << cur->data.careType
                 << " | " << setw(16) << cur->data.lengthOfStay
                 << " | " << setw(11) << cur->data.baseCostPerHour
                 << " | " << setw(12) << cur->data.daysVisitsPerYear
                 << " | " << setw(23) << listNumberText(cur->data.totalCost, 2) << " |\n";
        }
        cout << string(ruleWidth, '-') << "\n";
        cout << "Showing " << count << " of " << count << " records" << endl;
    }

    static string sortFieldName(int field) {
        if (field == LIST_SORT_BY_AGE) {
            return "Age";
        }
        if (field == LIST_SORT_BY_DURATION) {
            return "Visit Duration";
        }
        return "Total Cost";
    }

    // InsertionSort - build a new sorted chain by taking nodes one at a time from the old chain
    // and re-linking each into the right place; stable. O(n^2) average/worst case.
    // Best case O(n) is when the input is in the OPPOSITE order (each node goes to the front after 1 comparison),
    // because the search for the insert position starts from the head (a singly list cannot walk backwards).
    ListSortStats insertionSort(int field, bool ascending) {
        ListSortStats stats;
        PatientNode* sorted = nullptr;
        PatientNode* cur = head;
        while (cur != nullptr) {
            PatientNode* nextNode = cur->next;     // remember, because cur->next is about to change
            if (sorted == nullptr) {
                cur->next = nullptr;
                sorted = cur;
            } else {
                stats.comparisons++;
                if (isAfter(sorted->data, cur->data, field, ascending)) {
                    cur->next = sorted;            // goes in front of everything
                    sorted = cur;
                } else {
                    PatientNode* walker = sorted;
                    while (walker->next != nullptr) {
                        stats.comparisons++;
                        if (isAfter(walker->next->data, cur->data, field, ascending)) {
                            break;
                        }
                        walker = walker->next;
                    }
                    cur->next = walker->next;      // splice cur in after walker
                    walker->next = cur;
                }
            }
            cur = nextNode;
        }
        head = sorted;
        fixTail();
        return stats;
    }

    // MergeSort - split / sort halves / merge by re-linking nodes; stable.
    // O(n log n) time, O(log n) extra space (recursion only - no temporary buffer like the array needs)
    ListSortStats mergeSort(int field, bool ascending) {
        ListSortStats stats;
        head = mergeSortNodes(head, field, ascending, stats, 1);
        fixTail();
        return stats;
    }

    // IsSorted - true when no record must come after the record next to it
    bool isSorted(int field, bool ascending) const {   // O(n)
        for (PatientNode* cur = head; cur != nullptr && cur->next != nullptr; cur = cur->next) {
            if (isAfter(cur->data, cur->next->data, field, ascending)) {
                return false;
            }
        }
        return true;
    }

    // NodeBytes - memory of the whole list (sizeof(PatientNode) x n; includes the next pointer of every node)
    size_t nodeBytes() const {
        return sizeof(PatientNode) * count;
    }
};

// AverageListSortNanoseconds - run one sort many times, each on a fresh copy, return the mean time
inline double averageListSortNanoseconds(const PatientList& original, bool useMerge, int field, bool ascending,
                                         int repeats, ListSortStats& statsOut) {
    long long totalNs = 0;
    for (int r = 0; r < repeats; r++) {
        PatientList copy(original);     // copying is NOT timed
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        if (useMerge) {
            statsOut = copy.mergeSort(field, ascending);
        } else {
            statsOut = copy.insertionSort(field, ascending);
        }
        chrono::steady_clock::time_point stop = chrono::steady_clock::now();
        totalNs += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    }
    return (double)totalNs / repeats;
}

// DisplayListSortExperiment - time both sorts for fields firstField..lastField, then print the sorted list
inline void displayListSortExperiment(const PatientList& original, const string& datasetName,
                                      int firstField, int lastField, bool ascending) {
    const int repeats = 200;
    const int ruleWidth = 102;
    int n = original.getCount();
    cout << "\n=== " << datasetName << " - Sorting Experiment ===" << endl;
    cout << string(ruleWidth, '-') << "\n";
    cout << left << "| " << setw(14) << "Sort Field"
         << " | " << setw(14) << "Algorithm"
         << " | " << setw(15) << "Time Complexity"
         << " | " << setw(13) << "Avg Time (ns)"
         << " | " << setw(11) << "Comparisons"
         << " | " << setw(16) << "Memory Usage (B)" << " |\n";
    cout << string(ruleWidth, '-') << "\n";
    for (int field = firstField; field <= lastField; field++) {
        for (int algorithm = 0; algorithm < 2; algorithm++) {
            bool useMerge = (algorithm == 1);
            ListSortStats stats;
            double nanoseconds = averageListSortNanoseconds(original, useMerge, field, ascending, repeats, stats);

            // Extra memory beyond the list itself: insertion = a few pointers;
            // merge = about 6 pointer-sized values per recursion level (estimate)
            size_t extraBytes = useMerge ? (size_t)stats.maxDepth * 6 * sizeof(void*) : 3 * sizeof(void*);
            cout << "| " << setw(14) << PatientList::sortFieldName(field)
                 << " | " << setw(14) << (useMerge ? "Merge Sort" : "Insertion Sort")
                 << " | " << setw(15) << (useMerge ? "O(n log n)" : "O(n^2)")
                 << " | " << setw(13) << listNumberText(nanoseconds, 0)
                 << " | " << setw(11) << stats.comparisons
                 << " | " << setw(16) << extraBytes << " |\n";
        }
    }
    cout << string(ruleWidth, '-') << "\n";

    for (int field = firstField; field <= lastField; field++) {
        PatientList sorted(original);
        sorted.mergeSort(field, ascending);
        cout << "\n All " << n << " records sorted by " << PatientList::sortFieldName(field) << endl;
        sorted.displayWithTotalCost();
    }
}