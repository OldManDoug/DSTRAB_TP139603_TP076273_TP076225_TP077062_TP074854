#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <cstdio>

using namespace std; // no need put std in front of everything

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

void stayC(){
    string file = "StayLengthC.csv";
    ifstream f(file);
    if(!f.is_open()){
        cerr << "File unfounded "<<endl;
    }
    NumbersLinkedList numList;
    string token;

    // Read word by word (whitespace-delimited)
    while (f >> token) {
        int  val;
        // Extract numbers and ignore text characters
        if (tryParseDouble2(token, val)) {
            numList.insertion(val);
        }   
    }
    f.close();
    numList.calculateStat();

}

// =====================================================================
// SORTING PART (linked list) - PatientList: insertion sort + merge sort
// Same fields / table layout as array.hpp so the two can be compared fairly.
// =====================================================================
// Sorting records stay in linked-list nodes; summaries use fixed-size arrays.
// Singly linked list of Patient nodes + insertion sort + merge sort, using the same
// sort fields / table layout as array.hpp so the two structures can be compared fairly.
// Names are prefixed (List...) so this header can be included together with array.hpp.


#include <stdexcept>

// Fields a list can be sorted by (same numbers as the menu: 1 / 2 / 3)
const int LIST_SORT_BY_AGE = 1;
const int LIST_SORT_BY_DURATION = 2;   // visit duration = LengthOfStay (hours)
const int LIST_SORT_BY_CARE = 4;
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

// ListGroupStats - totals for one age group
struct ListGroupStats {
    int patientCount;
    double totalCost;
    double totalStay;       // sum of lengthOfStay = visit duration (hours)
    double totalVisits;     // sum of daysVisitsPerYear
    ListGroupStats() : patientCount(0), totalCost(0), totalStay(0), totalVisits(0) {}
};


// ListCareTally - two parallel arrays (care type names and counts) plus the cost per care type
struct ListCareTally {
    string names[20];
    int counts[20];
    double costs[20];
    int used;               // how many care types have been seen so far

    ListCareTally() : used(0) {
        for (int i = 0; i < 20; i++) {
            counts[i] = 0;
            costs[i] = 0;
        }
    }

    // Add - accumulate each care-type run in O(1); find existing rows when combining datasets.
    // Counts represent patient records (one care request per record).
    void add(const string& name, double cost) {   // O(c), c = number of care types
        if (used > 0 && names[used - 1] == name) {
            counts[used - 1]++;
            costs[used - 1] += cost;
            return;
        }
        for (int i = 0; i < used; i++) {
            if (names[i] == name) {
                counts[i]++;
                costs[i] += cost;
                return;
            }
        }
        if (used == 20) {
            throw runtime_error("Too many different care types (limit is 20)");
        }
        names[used] = name;
        counts[used] = 1;
        costs[used] = cost;
        used++;
    }

    // Insertion sort of aggregate rows; names, counts and costs move together.
    ListCareTally ranked(bool byCost) const {
        ListCareTally sorted(*this);
        for (int i = 1; i < sorted.used; i++) {
            string name = sorted.names[i];
            int patients = sorted.counts[i];
            double cost = sorted.costs[i];
            int j = i - 1;
            while (j >= 0 && (byCost ? sorted.costs[j] < cost : sorted.counts[j] < patients)) {
                sorted.names[j + 1] = sorted.names[j];
                sorted.counts[j + 1] = sorted.counts[j];
                sorted.costs[j + 1] = sorted.costs[j];
                j--;
            }
            sorted.names[j + 1] = name;
            sorted.counts[j + 1] = patients;
            sorted.costs[j + 1] = cost;
        }
        return sorted;
    }

    // MostRequested - care type(s) with the highest count; ties are joined with " / "
    string mostRequested() const {   // O(c^2): insertion sort of the care totals
        if (used == 0) {
            return "none";
        }
        ListCareTally sorted = ranked(false);
        int highest = sorted.counts[0];
        string result = "";
        for (int i = 0; i < used && sorted.counts[i] == highest; i++) {
            if (result != "") result += " / ";
            result += sorted.names[i];
        }
        return result;
    }

    // HighestCount - the biggest patient count of any care type (0 when the tally is empty)
    int highestCount() const {
        return used == 0 ? 0 : ranked(false).counts[0];
    }

};

class PatientList;
void displayListAgeGroupReport(const PatientList& dataset, const string& datasetName);
void displayListExpenditureReport(const PatientList& dataset, const string& datasetName);

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
        if (field == LIST_SORT_BY_CARE) {
            return ascending ? left.careType > right.careType : left.careType < right.careType;
        }
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

    // AgeGroupIndex - map an age to group 0-4, or -1 if the age is outside 0-100
    static int ageGroupIndex(int age) {   // O(1)
        if (age < 0 || age > 100) {
            return -1;
        }
        if (age <= 17) {
            return 0;
        }
        if (age <= 25) {
            return 1;
        }
        if (age <= 45) {
            return 2;
        }
        if (age <= 60) {
            return 3;
        }
        return 4;
    }

    // AgeGroupRange - the age range of a group, e.g. "18-25"
    static string ageGroupRange(int group) {
        switch (group) {
            case 0: return "0-17";
            case 1: return "18-25";
            case 2: return "26-45";
            case 3: return "46-60";
            default: return "61-100";
        }
    }

    // AgeGroupDescription - the name of a group, e.g. "Young Adults / University Students"
    static string ageGroupDescription(int group) {
        switch (group) {
            case 0: return "Pediatrics & Adolescents";
            case 1: return "Young Adults / University Students";
            case 2: return "Working Adults (Early Career)";
            case 3: return "Working Adults (Late Career)";
            default: return "Senior Citizens / Geriatric Care";
        }
    }

    // Merge sort a deep copy by age; age groups are contiguous in the sorted chain.
    void analyseAgeGroups(ListGroupStats stats[], ListCareTally tallies[], int& outOfRange) const {
        PatientList sorted(*this);
        sorted.calculateTotalCosts();
        sorted.mergeSort(LIST_SORT_BY_AGE, true);
        outOfRange = 0;
        for (PatientNode* cur = sorted.head; cur != nullptr; cur = cur->next) {
            const ListPatient& patient = cur->data;
            int group = ageGroupIndex(patient.age);
            if (group < 0) { outOfRange++; continue; }
            stats[group].patientCount++;
            stats[group].totalCost += patient.totalCost;
            stats[group].totalStay += patient.lengthOfStay;
            stats[group].totalVisits += patient.daysVisitsPerYear;
            tallies[group].add(patient.careType, patient.totalCost);
        }
    }

    // Total and averages consume nodes after merge sorting a copy.
    double totalBilling() const {
        PatientList sorted(*this);
        sorted.calculateTotalCosts();
        sorted.mergeSort(LIST_SORT_BY_COST, true);
        double total = 0;
        for (PatientNode* cur = sorted.head; cur != nullptr; cur = cur->next)
            total += cur->data.totalCost;
        return total;
    }

    double averageVisitDuration() const {
        if (count == 0) return 0;
        PatientList sorted(*this);
        sorted.mergeSort(LIST_SORT_BY_DURATION, true);
        double total = 0;
        for (PatientNode* cur = sorted.head; cur != nullptr; cur = cur->next)
            total += cur->data.lengthOfStay;
        return total / count;
    }

    double averageVisitsPerYear() const {
        if (count == 0) return 0;
        PatientList sorted(*this);
        sorted.mergeSort(LIST_SORT_BY_AGE, true);
        double total = 0;
        for (PatientNode* cur = sorted.head; cur != nullptr; cur = cur->next)
            total += cur->data.daysVisitsPerYear;
        return total / count;
    }

    void tallyCareTypes(ListCareTally& tally) const {
        PatientList sorted(*this);
        sorted.calculateTotalCosts();
        sorted.mergeSort(LIST_SORT_BY_CARE, true);
        for (PatientNode* cur = sorted.head; cur != nullptr; cur = cur->next)
            tally.add(cur->data.careType, cur->data.totalCost);
    }

    void displayAgeGroupAnalysis(const string& datasetName) const {
        displayListAgeGroupReport(*this, datasetName);
    }

    void displayExpenditure(const string& datasetName) const {
        displayListExpenditureReport(*this, datasetName);
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

// Section 4(a-c): sorted age groups, care preference, total and average billing.
inline void displayListAgeGroupReport(const PatientList& dataset, const string& datasetName) {
    ListGroupStats stats[5];
    ListCareTally tallies[5];
    int outOfRange;
    dataset.analyseAgeGroups(stats, tallies, outOfRange);

    const int ruleWidth = 88;
    cout << "\n=== " << datasetName << " - Age Group and Billing Analysis ===" << endl;
    cout << "Sorting: merge sort by age; insertion sort by care request count." << endl;
    cout << "Cost = Length of Stay x Base Cost Per Hour x Days Visits Per Year" << endl;
    for (int g = 0; g < 5; g++) {
        cout << "\nAge Group: " << PatientList::ageGroupRange(g) << " (" << PatientList::ageGroupDescription(g) << ")" << endl;
        cout << string(ruleWidth, '-') << "\n";
        cout << left << "| " << setw(18) << "Care Type"
             << " | " << setw(15) << "Patient Count"
             << " | " << setw(16) << "Total Cost (RM)"
             << " | " << setw(26) << "Average Cost per Patient" << " |\n";
        cout << string(ruleWidth, '-') << "\n";

        if (stats[g].patientCount == 0) {
            cout << "| " << setw(ruleWidth - 4) << "No patients in this age group" << " |\n";
        } else {
            ListCareTally ranked = tallies[g].ranked(false);
            for (int row = 0; row < tallies[g].used; row++) {
                int i = row;
                cout << "| " << setw(18) << ranked.names[i]
                     << " | " << setw(15) << ranked.counts[i]
                     << " | " << setw(16) << listNumberText(ranked.costs[i], 2)
                     << " | " << setw(26) << listNumberText(ranked.costs[i] / ranked.counts[i], 2) << " |\n";
            }
        }
        cout << string(ruleWidth, '-') << "\n";

        double average = 0;
        if (stats[g].patientCount > 0) {
            average = stats[g].totalCost / stats[g].patientCount;   // guarded: never divides by 0
        }
        cout << "Total Billing for Age Group: RM " << listNumberText(stats[g].totalCost, 2) << endl;
        cout << "Average Cost per Patient: RM " << listNumberText(average, 2) << endl;
        cout << "Most Requested Care Type: " << tallies[g].mostRequested() << endl;
    }

    // Summary table, one row per age group
    const int summaryWidth = 112;
    cout << "\nSummary - " << datasetName << endl;
    cout << string(summaryWidth, '-') << "\n";
    cout << left << "| " << setw(10) << "Age Group"
         << " | " << setw(10) << "Patients"
         << " | " << setw(16) << "Total Cost (RM)"
         << " | " << setw(20) << "Avg Cost per Patient"
         << " | " << setw(40) << "Most Requested Care Type" << " |\n";
    cout << string(summaryWidth, '-') << "\n";
    for (int g = 0; g < 5; g++) {
        double average = 0;
        if (stats[g].patientCount > 0) {
            average = stats[g].totalCost / stats[g].patientCount;
        }
        cout << "| " << setw(10) << PatientList::ageGroupRange(g)
             << " | " << setw(10) << stats[g].patientCount
             << " | " << setw(16) << listNumberText(stats[g].totalCost, 2)
             << " | " << setw(20) << listNumberText(average, 2)
             << " | " << setw(40) << tallies[g].mostRequested() << " |\n";
    }
    cout << string(summaryWidth, '-') << "\n";
    if (outOfRange > 0) {
        cout << "Note: " << outOfRange << " patient(s) with an age outside 0-100 are not in any group." << endl;
    }
}

// Section 5(a,b,d): sorted billing totals and console table by care type.
inline void displayListExpenditureReport(const PatientList& dataset, const string& datasetName) {
    ListCareTally tally;
    dataset.tallyCareTypes(tally);
    double total = dataset.totalBilling();

    const int ruleWidth = 54;
    cout << "\n=== " << datasetName << " - Healthcare Expenditure ===" << endl;
    cout << "Sorting: merge sort by care type and total cost; insertion sort by care billing." << endl;
    cout << "Total medical billing: RM " << listNumberText(total, 2) << " from " << dataset.getCount() << " patients" << endl;
    cout << "\nTotal Cost by Care Type" << endl;
    cout << string(ruleWidth, '-') << "\n";
    cout << left << "| " << setw(18) << "Care Type"
         << " | " << setw(10) << "Patients"
         << " | " << setw(16) << "Total Cost (RM)" << " |\n";
    cout << string(ruleWidth, '-') << "\n";
    ListCareTally ranked = tally.ranked(true);
    for (int row = 0; row < tally.used; row++) {
        int i = row;
        cout << "| " << setw(18) << ranked.names[i]
             << " | " << setw(10) << ranked.counts[i]
             << " | " << setw(16) << listNumberText(ranked.costs[i], 2) << " |\n";
    }
    cout << string(ruleWidth, '-') << "\n";
}

// Section 5(c,d): compare expenditure and visit durations in console tables.
inline void displayListDatasetComparison(const PatientList& a, const PatientList& b, const PatientList& c) {
    const PatientList* sets[3] = { &a, &b, &c };
    const string labels[3] = { "Dataset A", "Dataset B", "Dataset C" };
    ListGroupStats stats[3][5];
    ListCareTally tallies[3][5];
    int outOfRange;
    for (int d = 0; d < 3; d++) {
        sets[d]->analyseAgeGroups(stats[d], tallies[d], outOfRange);
    }

    const int overallWidth = 118;
    cout << "\n=== Comparison Across Datasets ===" << endl;
    cout << string(overallWidth, '-') << "\n";
    cout << left << "| " << setw(10) << "Dataset"
         << " | " << setw(8) << "Patients"
         << " | " << setw(18) << "Total Billing (RM)"
         << " | " << setw(20) << "Avg Cost per Patient"
         << " | " << setw(24) << "Avg Visit Duration (hrs)"
         << " | " << setw(19) << "Avg Visits per Year" << " |\n";
    cout << string(overallWidth, '-') << "\n";
    for (int d = 0; d < 3; d++) {
        int patients = sets[d]->getCount();
        double total = sets[d]->totalBilling();
        double average = 0;
        if (patients > 0) {
            average = total / patients;
        }
        cout << "| " << setw(10) << labels[d]
             << " | " << setw(8) << patients
             << " | " << setw(18) << listNumberText(total, 2)
             << " | " << setw(20) << listNumberText(average, 2)
             << " | " << setw(24) << listNumberText(sets[d]->averageVisitDuration(), 2)
             << " | " << setw(19) << listNumberText(sets[d]->averageVisitsPerYear(), 2) << " |\n";
    }
    cout << string(overallWidth, '-') << "\n";

    const int groupWidth = 71;
    for (int pass = 0; pass < 3; pass++) {
        string title = "Total Cost by Age Group (RM)";
        if (pass == 1) {
            title = "Average Visit Duration by Age Group (hours)";
        } else if (pass == 2) {
            title = "Average Visits per Year by Age Group";
        }
        cout << "\n" << title << endl;
        cout << string(groupWidth, '-') << "\n";
        cout << left << "| " << setw(10) << "Age Group";
        for (int d = 0; d < 3; d++) {
            cout << " | " << setw(16) << labels[d];
        }
        cout << " |\n";
        cout << string(groupWidth, '-') << "\n";
        for (int g = 0; g < 5; g++) {
            cout << "| " << setw(10) << PatientList::ageGroupRange(g);
            for (int d = 0; d < 3; d++) {
                string cell = "-";   // "-" means the dataset has no patients in this age group
                if (stats[d][g].patientCount > 0) {
                    if (pass == 0) {
                        cell = listNumberText(stats[d][g].totalCost, 2);
                    } else if (pass == 1) {
                        cell = listNumberText(stats[d][g].totalStay / stats[d][g].patientCount, 2);
                    } else {
                        cell = listNumberText(stats[d][g].totalVisits / stats[d][g].patientCount, 2);
                    }
                }
                cout << " | " << setw(16) << cell;
            }
            cout << " |\n";
        }
        cout << string(groupWidth, '-') << "\n";
    }
}

// HighestBillingGroups - the age group(s) with the highest total cost; groups without patients are ignored
inline string highestListBillingGroups(const ListGroupStats groups[], double& highestCost) {
    int order[5] = {0, 1, 2, 3, 4};
    // Insertion sort of group totals descending; empty groups rank last.
    for (int i = 1; i < 5; i++) {
        int key = order[i], j = i - 1;
        double value = groups[key].patientCount ? groups[key].totalCost : -1;
        while (j >= 0 && (groups[order[j]].patientCount ? groups[order[j]].totalCost : -1) < value) {
            order[j + 1] = order[j];
            j--;
        }
        order[j + 1] = key;
    }
    highestCost = groups[order[0]].patientCount ? groups[order[0]].totalCost : -1;
    string result = "";
    for (int g = 0; g < 5; g++) {
        if (groups[g].patientCount > 0 && groups[g].totalCost == highestCost) {
            if (result != "") {
                result += " / ";
            }
            result += PatientList::ageGroupRange(g);
        }
    }
    if (result == "") {
        highestCost = 0;
        return "none";
    }
    return result;
}

// DisplayClinicalInsights - compare treatment costs and service preferences across datasets and age groups,
// then identify the highest-billing age group and the highest-traffic care type
inline void displayListClinicalInsights(const PatientList& a, const PatientList& b, const PatientList& c) {
    const PatientList* sets[3] = { &a, &b, &c };
    const string labels[3] = { "Dataset A", "Dataset B", "Dataset C" };
    ListGroupStats stats[3][5];
    ListCareTally groupTallies[3][5];
    ListCareTally careTally[3];
    ListCareTally allCare;          // care types of all three datasets together
    int outOfRange;
    for (int d = 0; d < 3; d++) {
        sets[d]->analyseAgeGroups(stats[d], groupTallies[d], outOfRange);
        sets[d]->tallyCareTypes(careTally[d]);
        sets[d]->tallyCareTypes(allCare);
    }

    cout << "\n=== Clinical Insights ===" << endl;
    cout << "Sorting: merge sort by age/care type; insertion sort by group billing and care traffic." << endl;

    // Table 1 - treatment cost: total cost of each age group in each dataset
    const int averageWidth = 71;
    cout << "\nTotal Cost by Age Group (RM)" << endl;
    cout << string(averageWidth, '-') << "\n";
    cout << left << "| " << setw(10) << "Age Group";
    for (int d = 0; d < 3; d++) {
        cout << " | " << setw(16) << labels[d];
    }
    cout << " |\n";
    cout << string(averageWidth, '-') << "\n";
    for (int g = 0; g < 5; g++) {
        cout << "| " << setw(10) << PatientList::ageGroupRange(g);
        for (int d = 0; d < 3; d++) {
            string cell = "-";
            if (stats[d][g].patientCount > 0) {
                cell = listNumberText(stats[d][g].totalCost, 2);
            }
            cout << " | " << setw(16) << cell;
        }
        cout << " |\n";
    }
    cout << string(averageWidth, '-') << "\n";

    // Table 2 - service preference: most requested care type in each age group and dataset
    const int preferenceWidth = 89;
    cout << "\nPreferred (Most Requested) Care Type by Age Group" << endl;
    cout << string(preferenceWidth, '-') << "\n";
    cout << left << "| " << setw(10) << "Age Group";
    for (int d = 0; d < 3; d++) {
        cout << " | " << setw(22) << labels[d];
    }
    cout << " |\n";
    cout << string(preferenceWidth, '-') << "\n";
    for (int g = 0; g < 5; g++) {
        cout << "| " << setw(10) << PatientList::ageGroupRange(g);
        for (int d = 0; d < 3; d++) {
            string cell = "-";
            if (stats[d][g].patientCount > 0) {
                cell = groupTallies[d][g].mostRequested();
            }
            cout << " | " << setw(22) << cell;
        }
        cout << " |\n";
    }
    cout << string(preferenceWidth, '-') << "\n";

    // Table 3 - findings: highest-billing age group and highest-traffic care type
    ListGroupStats allGroups[5];    // age groups of all three datasets together
    for (int g = 0; g < 5; g++) {
        for (int d = 0; d < 3; d++) {
            allGroups[g].patientCount += stats[d][g].patientCount;
            allGroups[g].totalCost += stats[d][g].totalCost;
        }
    }
    const int findingWidth = 97;
    cout << "\nHighest Billing and Highest Patient Traffic" << endl;
    cout << string(findingWidth, '-') << "\n";
    cout << left << "| " << setw(13) << "Dataset"
         << " | " << setw(25) << "Highest-Billing Age Group"
         << " | " << setw(12) << "Billing (RM)"
         << " | " << setw(25) << "Highest-Traffic Care Type"
         << " | " << setw(8) << "Patients" << " |\n";
    cout << string(findingWidth, '-') << "\n";
    for (int row = 0; row < 4; row++) {
        const ListGroupStats* groups = (row < 3) ? stats[row] : allGroups;
        const ListCareTally& tally = (row < 3) ? careTally[row] : allCare;
        double highestCost;
        string groupNames = highestListBillingGroups(groups, highestCost);
        cout << "| " << setw(13) << (row < 3 ? labels[row] : string("All datasets"))
             << " | " << setw(25) << groupNames
             << " | " << setw(12) << listNumberText(highestCost, 2)
             << " | " << setw(25) << tally.mostRequested()
             << " | " << setw(8) << tally.highestCount() << " |\n";
    }
    cout << string(findingWidth, '-') << "\n";
}

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
                 << " | " << setw(16) << (original.nodeBytes() + extraBytes) << " |\n";   // nodes + temporary storage
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