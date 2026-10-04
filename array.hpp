#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <chrono>
using namespace std;

// Patient record - one row of a facility CSV file
struct Patient {
    int patientID;          // assigned in load order (CSV has no ID column)
    int age;
    string careType;        // may contain spaces, e.g. "Routine Checkup"
    int lengthOfStay;
    double baseCostPerHour;
    int daysVisitsPerYear;
    double totalCost;       // lengthOfStay * baseCostPerHour * daysVisitsPerYear
};

// Class definition - dynamic array of Patient that doubles when full
class ArrayData {
private:
    // Data members
    Patient* data;
    int count;
    int capacity;

    // Grow - double the capacity and copy the records across
    void grow() {   // O(n), but happens rarely so insertEnd is O(1) amortised
        int newCapacity = capacity * 2;
        Patient* newData = new Patient[newCapacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    // Trim - remove spaces, tabs and line endings (\r) from both ends
    static string trim(const string& text) {
        const string whitespace = " \t\r\n";
        size_t first = text.find_first_not_of(whitespace);
        if (first == string::npos) {
            return "";
        }
        size_t last = text.find_last_not_of(whitespace);
        return text.substr(first, last - first + 1);
    }

    // ParseInt - true only if the WHOLE text is one integer
    static bool parseInt(const string& text, int& value) {
        istringstream ss(text);
        char extra;
        if (!(ss >> value)) {
            return false;
        }
        return !(ss >> extra);
    }

    // ParseDouble - true only if the WHOLE text is one number
    static bool parseDouble(const string& text, double& value) {
        istringstream ss(text);
        char extra;
        if (!(ss >> value)) {
            return false;
        }
        return !(ss >> extra);
    }

    // ParseRecord - split one CSV line into a Patient, or explain why not
    static bool parseRecord(const string& line, Patient& p, string& reason) {
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

public:
    // Constructor - start with room for 16 records
    ArrayData() : data(new Patient[16]), count(0), capacity(16) {}

    // Copy constructor - deep copy so a sort on the copy leaves the original alone
    ArrayData(const ArrayData& other)
        : data(new Patient[other.capacity]), count(other.count), capacity(other.capacity) {
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }

    // Assignment - deep copy (safe against self-assignment)
    ArrayData& operator=(const ArrayData& other) {
        if (this != &other) {
            Patient* newData = new Patient[other.capacity];
            for (int i = 0; i < other.count; i++) {
                newData[i] = other.data[i];
            }
            delete[] data;
            data = newData;
            count = other.count;
            capacity = other.capacity;
        }
        return *this;
    }

    // Destructor - clean memory
    ~ArrayData() {
        delete[] data;
        data = nullptr;
    }

    // InsertEnd - add a record at the END
    void insertEnd(const Patient& p) {   // O(1) amortised
        if (count == capacity) {
            grow();
        }
        data[count] = p;
        count++;
    }

    // CalculateTotalCosts - fill totalCost for every record
    void calculateTotalCosts() {   // O(n)
        for (int i = 0; i < count; i++) {
            data[i].totalCost = data[i].lengthOfStay * data[i].baseCostPerHour * data[i].daysVisitsPerYear;
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
        int skipped = 0;
        bool firstRecordLine = true;
        while (getline(file, line)) {
            lineNumber++;
            // Remove the UTF-8 BOM some editors put at the start of a file
            if (lineNumber == 1 && line.size() >= 3 &&
                (unsigned char)line[0] == 0xEF && (unsigned char)line[1] == 0xBB && (unsigned char)line[2] == 0xBF) {
                line.erase(0, 3);
            }
            line = trim(line);
            if (line.empty()) {
                continue;
            }

            // If the first field of the first line is not a number it is a header row
            if (firstRecordLine) {
                firstRecordLine = false;
                int firstValue;
                if (!parseInt(trim(line.substr(0, line.find(','))), firstValue)) {
                    continue;
                }
            }

            Patient p;
            string reason;
            if (!parseRecord(line, p, reason)) {
                cerr << "Warning: line " << lineNumber << " skipped (" << reason << ")" << endl;
                skipped++;
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

    // GetCount - number of records stored
    int getCount() const {
        return count;
    }

    // GetAt - read-only access to one record by index
    const Patient& getAt(int index) const {   // O(1)
        if (index < 0 || index >= count) {
            ostringstream message;
            message << "Index out of range: getAt(" << index << ") with count " << count;
            throw runtime_error(message.str());
        }
        return data[index];
    }

    // Clear - forget all records (the memory is kept for reuse)
    void clear() {   // O(1)
        count = 0;
    }

    // Display - print records as a table; limit < 0 means print all
    void display(int limit = -1) const {
        if (count == 0) {
            cout << "(no records)" << endl;
            return;
        }
        int shown = (limit < 0 || limit > count) ? count : limit;

        // Same column layout as the linked-list tables
        cout << left
             << "| " << setw(5)  << "Age"
             << " | " << setw(15) << "Care Type"
             << " | " << setw(16) << "Length of Stay"
             << " | " << setw(11) << "Base Cost"
             << " | " << setw(12) << "Days Visit" << " |\n";
        cout << string(75, '-') << "\n";
        for (int i = 0; i < shown; i++) {
            cout << "| " << setw(5)  << data[i].age
                 << " | " << setw(15) << data[i].careType
                 << " | " << setw(16) << data[i].lengthOfStay
                 << " | " << setw(11) << data[i].baseCostPerHour
                 << " | " << setw(12) << data[i].daysVisitsPerYear << " |\n";
        }
        cout << string(75, '-') << "\n";
        cout << "Showing " << shown << " of " << count << " records" << endl;
    }
};

