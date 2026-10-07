#ifndef ARRAY_DATASET_HPP
#define ARRAY_DATASET_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdexcept>
using namespace std;

// Patient record
struct Patient {
    int patientID;
    int age;
    string careType;
    int lengthOfStay;
    double baseCostPerHour;
    int daysVisitsPerYear;
    double totalCost;       // lengthOfStay * baseCostPerHour * daysVisitsPerYear
};


class ArrayData {
protected:
    Patient* data;
    int count;
    int capacity;

private:
    // use to add records
    void grow() {
        int newCapacity = capacity * 2;
        Patient* newData = new Patient[newCapacity];
        for (int i = 0; i < count; i++) {

            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    // remove spaces
    static string trim(const string& text) {
        const string whitespace = " \t\r\n";
        size_t first = text.find_first_not_of(whitespace);
        if (first == string::npos) {
            return "";
        }
        size_t last = text.find_last_not_of(whitespace);
        return text.substr(first, last - first + 1);
    }

    // true only if contain integer
    static bool parseInt(const string& text, int& value) {
        istringstream ss(text);
        char extra;
        if (!(ss >> value)) {
            return false;
        }
        return !(ss >> extra);
    }

    // true only if contain double
    static bool parseDouble(const string& text, double& value) {
        istringstream ss(text);
        char extra;
        if (!(ss >> value)) {
            return false;
        }
        return !(ss >> extra);
    }

    // handles error for each record line
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
    ArrayData() {
        data = new Patient[16];
        count = 0;
        capacity = 16;
    }

    ArrayData(const ArrayData& other) {
        data = new Patient[other.capacity];
        count = other.count;
        capacity = other.capacity;
        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }

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

    ~ArrayData() {
        delete[] data;
        data = nullptr;
    }

    // add a record at the END
    void insertEnd(const Patient& p) {   
        if (count == capacity) {
            grow();
        }
        data[count] = p;
        count++;
    }

    // calculate total cost for every record
    void calculateTotalCosts() {
        for (int i = 0; i < count; i++) {
            data[i].totalCost = data[i].lengthOfStay*data[i].baseCostPerHour*data[i].daysVisitsPerYear;
        }
    }

    // read a CSV file
    bool loadFromFile(const string& filename) {
        clear();
        ifstream file(filename.c_str());

        if (!file.is_open()) {
            cerr << "Error: Cannot open file " << filename <<endl;
            return false;
        }

        string line;
        int lineNumber = 0;
        int skipped = 0;
        bool firstRecordLine = true;

        while (getline(file, line)) {
            lineNumber++;
            line = trim(line);
            if (line.empty()) {
                continue;
            }

            // ignore header row
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

    // number of records stored
    int getCount() const {
        return count;
    }

    const Patient& getAt(int index) const {
        if (index < 0 || index >= count) {
            ostringstream message;
            message << "Index out of range: getAt(" << index << ") with count " << count;
            throw runtime_error(message.str());
        }
        return data[index];
    }

    void clear() {  
        count = 0;
    }

    // print records as a table
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
        for (int i = 0; i < shown; i++) {
            cout << "| " << setw(5)  << data[i].age
                 << " | " << setw(15) << data[i].careType
                 << " | " << setw(16) << data[i].lengthOfStay
                 << " | " << setw(11) << data[i].baseCostPerHour
                 << " | " << setw(12) << data[i].daysVisitsPerYear << " |\n";
        }
        cout << string(75, '-') << "\n";
        cout << "Showing " << shown << " of " << count << " records" <<endl;
    }
};

// TylerMSFT. (2024, January 22). Inline Functions (C++). Learn.Microsoft.Com. https://learn.microsoft.com/en-us/cpp/cpp/inline-functions-cpp?view=msvc-170
// load a dataset
inline bool loadIfEmpty(ArrayData& dataset, const string& filename) {
    if (dataset.getCount() > 0) {
        return true;
    }
    return dataset.loadFromFile(filename);
}

// load one CSV print its table
inline void showDataset(ArrayData& dataset, const string& title, const string& filename) {
    cout << "\n" << title << endl;
    if (loadIfEmpty(dataset, filename)) {
        dataset.display(); 
    }
}

// make sure all three datasets are in memory
inline bool ensureAllLoaded(ArrayData& datasetA, ArrayData& datasetB, ArrayData& datasetC) {
    bool loadedA = loadIfEmpty(datasetA, "dataset1facility_a.csv");
    bool loadedB = loadIfEmpty(datasetB, "dataset2facility_b.csv");
    bool loadedC = loadIfEmpty(datasetC, "dataset3facility_c.csv");

    return loadedA && loadedB && loadedC;
}

#endif
