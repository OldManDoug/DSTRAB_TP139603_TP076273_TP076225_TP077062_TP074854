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

// NumberText - format a number with a fixed number of decimals
inline string numberText(double value, int decimals) {
    ostringstream out;
    out << fixed << setprecision(decimals) << value;
    return out.str();
}

// GroupStats - totals for one age group
struct GroupStats {
    int patientCount;
    double totalCost;
    double totalStay;       // sum of lengthOfStay = visit duration (hours)
    double totalVisits;     // sum of daysVisitsPerYear
    GroupStats() : patientCount(0), totalCost(0), totalStay(0), totalVisits(0) {}
};

// Fields a dataset can be sorted by
const int SORT_BY_AGE = 1;
const int SORT_BY_DURATION = 2;     // visit duration = LengthOfStay (hours)
const int SORT_BY_COST = 3;         // total medical cost

// SortStats - what one sort run did (moves = shifts for insertion sort, writes for merge sort)
struct SortStats {
    long long comparisons;
    long long moves;
    SortStats() : comparisons(0), moves(0) {}
};

// CareTally - two parallel arrays (care type names and counts) plus the cost per care type
struct CareTally {
    string names[20];
    int counts[20];
    double costs[20];
    int used;               // how many care types have been seen so far

    CareTally() : used(0) {
        for (int i = 0; i < 20; i++) {
            counts[i] = 0;
            costs[i] = 0;
        }
    }

    // Add - count one patient (and its cost) under a care type
    void add(const string& name, double cost) {   // O(c), c = number of care types
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

    // MostRequested - care type(s) with the highest count; ties are joined with " / "
    string mostRequested() const {   // O(c)
        if (used == 0) {
            return "none";
        }
        int highest = counts[0];
        for (int i = 1; i < used; i++) {
            if (counts[i] > highest) {
                highest = counts[i];
            }
        }
        string result = "";
        for (int i = 0; i < used; i++) {
            if (counts[i] == highest) {
                if (result != "") {
                    result += " / ";
                }
                result += names[i];
            }
        }
        return result;
    }

    // PickNext - index of the biggest row not printed yet (by cost, or by count)
    int pickNext(const bool printed[], bool byCost) const {   // O(c)
        int best = -1;
        for (int i = 0; i < used; i++) {
            if (printed[i]) {
                continue;
            }
            if (best == -1) {
                best = i;
            } else if (byCost && costs[i] > costs[best]) {
                best = i;
            } else if (!byCost && counts[i] > counts[best]) {
                best = i;
            }
        }
        return best;
    }
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

    // AnalyseAgeGroups - one pass that fills stats[5] and tallies[5] (pass in fresh, empty arrays)
    void analyseAgeGroups(GroupStats stats[], CareTally tallies[], int& outOfRange) const {   // O(n * c)
        outOfRange = 0;
        for (int i = 0; i < count; i++) {
            int group = ageGroupIndex(data[i].age);
            if (group < 0) {
                outOfRange++;
                continue;
            }
            stats[group].patientCount++;
            stats[group].totalCost += data[i].totalCost;
            stats[group].totalStay += data[i].lengthOfStay;
            stats[group].totalVisits += data[i].daysVisitsPerYear;
            tallies[group].add(data[i].careType, data[i].totalCost);
        }
    }

    // TotalBilling - sum of totalCost over every record
    double totalBilling() const {   // O(n)
        double sum = 0;
        for (int i = 0; i < count; i++) {
            sum += data[i].totalCost;
        }
        return sum;
    }

    // AverageVisitDuration - mean visit duration (LengthOfStay) in hours (0 when there are no records)
    double averageVisitDuration() const {   // O(n)
        if (count == 0) {
            return 0;
        }
        double sum = 0;
        for (int i = 0; i < count; i++) {
            sum += data[i].lengthOfStay;
        }
        return sum / count;
    }

    // AverageVisitsPerYear - mean DaysVisitsPerYear per patient (0 when there are no records)
    double averageVisitsPerYear() const {   // O(n)
        if (count == 0) {
            return 0;
        }
        double sum = 0;
        for (int i = 0; i < count; i++) {
            sum += data[i].daysVisitsPerYear;
        }
        return sum / count;
    }

    // DisplayAgeGroupAnalysis - per age group: care type table, total cost, average cost, most requested care type
    void displayAgeGroupAnalysis(const string& datasetName) const {   // O(n * c)
        GroupStats stats[5];
        CareTally tallies[5];
        int outOfRange;
        analyseAgeGroups(stats, tallies, outOfRange);

        const int ruleWidth = 88;
        cout << "\n=== " << datasetName << " - Age Group and Billing Analysis ===" << endl;
        for (int g = 0; g < 5; g++) {
            cout << "\nAge Group: " << ageGroupRange(g) << " (" << ageGroupDescription(g) << ")" << endl;
            cout << string(ruleWidth, '-') << "\n";
            cout << left << "| " << setw(18) << "Care Type"
                 << " | " << setw(15) << "Patient Count"
                 << " | " << setw(16) << "Total Cost (RM)"
                 << " | " << setw(26) << "Average Cost per Patient" << " |\n";
            cout << string(ruleWidth, '-') << "\n";

            if (stats[g].patientCount == 0) {
                cout << "| " << setw(ruleWidth - 4) << "No patients in this age group" << " |\n";
            } else {
                bool printed[20] = { false };
                for (int row = 0; row < tallies[g].used; row++) {
                    int i = tallies[g].pickNext(printed, false);
                    printed[i] = true;
                    cout << "| " << setw(18) << tallies[g].names[i]
                         << " | " << setw(15) << tallies[g].counts[i]
                         << " | " << setw(16) << numberText(tallies[g].costs[i], 2)
                         << " | " << setw(26) << numberText(tallies[g].costs[i] / tallies[g].counts[i], 2) << " |\n";
                }
            }
            cout << string(ruleWidth, '-') << "\n";

            double average = 0;
            if (stats[g].patientCount > 0) {
                average = stats[g].totalCost / stats[g].patientCount;   // guarded: never divides by 0
            }
            cout << "Total Billing for Age Group: RM " << numberText(stats[g].totalCost, 2) << endl;
            cout << "Average Cost per Patient: RM " << numberText(average, 2) << endl;
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
            cout << "| " << setw(10) << ageGroupRange(g)
                 << " | " << setw(10) << stats[g].patientCount
                 << " | " << setw(16) << numberText(stats[g].totalCost, 2)
                 << " | " << setw(20) << numberText(average, 2)
                 << " | " << setw(40) << tallies[g].mostRequested() << " |\n";
        }
        cout << string(summaryWidth, '-') << "\n";
        if (outOfRange > 0) {
            cout << "Note: " << outOfRange << " patient(s) with an age outside 0-100 are not in any group." << endl;
        }
    }

    // DisplayExpenditure - total billing for the dataset and total cost grouped by care type
    void displayExpenditure(const string& datasetName) const {   // O(n * c)
        CareTally tally;
        for (int i = 0; i < count; i++) {
            tally.add(data[i].careType, data[i].totalCost);
        }
        double total = totalBilling();

        const int ruleWidth = 54;
        cout << "\n=== " << datasetName << " - Healthcare Expenditure ===" << endl;
        cout << "Total medical billing: RM " << numberText(total, 2) << " from " << count << " patients" << endl;
        cout << "\nTotal Cost by Care Type" << endl;
        cout << string(ruleWidth, '-') << "\n";
        cout << left << "| " << setw(18) << "Care Type"
             << " | " << setw(10) << "Patients"
             << " | " << setw(16) << "Total Cost (RM)" << " |\n";
        cout << string(ruleWidth, '-') << "\n";
        bool printed[20] = { false };
        for (int row = 0; row < tally.used; row++) {
            int i = tally.pickNext(printed, true);
            printed[i] = true;
            cout << "| " << setw(18) << tally.names[i]
                 << " | " << setw(10) << tally.counts[i]
                 << " | " << setw(16) << numberText(tally.costs[i], 2) << " |\n";
        }
        cout << string(ruleWidth, '-') << "\n";
    }

    // SortFieldName - label of a sort field for the tables
    static string sortFieldName(int field) {
        if (field == SORT_BY_AGE) {
            return "Age";
        }
        if (field == SORT_BY_DURATION) {
            return "Visit Duration";
        }
        return "Total Cost";
    }

    // InsertionSort - sort this array in place (shifting version); stable
    SortStats insertionSort(int field, bool ascending) {   // O(n^2) worst case, O(n) when already sorted
        SortStats stats;
        for (int i = 1; i < count; i++) {
            Patient key = data[i];
            int j = i - 1;
            while (j >= 0) {
                stats.comparisons++;
                if (!isAfter(data[j], key, field, ascending)) {
                    break;
                }
                data[j + 1] = data[j];   // shift one place to the right
                stats.moves++;
                j--;
            }
            data[j + 1] = key;
        }
        return stats;
    }

    // MergeSort - sort this array in place using one temporary buffer of n records; stable
    SortStats mergeSort(int field, bool ascending) {   // O(n log n) time, O(n) extra space
        SortStats stats;
        if (count < 2) {
            return stats;
        }
        Patient* temp = new Patient[count];
        mergeSortRange(temp, 0, count - 1, field, ascending, stats);
        delete[] temp;
        temp = nullptr;
        return stats;
    }

    // IsSorted - true when no record must come after the record next to it
    bool isSorted(int field, bool ascending) const {   // O(n)
        for (int i = 1; i < count; i++) {
            if (isAfter(data[i - 1], data[i], field, ascending)) {
                return false;
            }
        }
        return true;
    }

    // DataBytes - memory used by the records themselves (sizeof(Patient) x n; text inside strings not counted)
    size_t dataBytes() const {
        return sizeof(Patient) * count;
    }

    // DisplayWithTotalCost - every record as the five CSV columns plus the total medical cost
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
        for (int i = 0; i < count; i++) {
            cout << "| " << setw(5)  << data[i].age
                 << " | " << setw(15) << data[i].careType
                 << " | " << setw(16) << data[i].lengthOfStay
                 << " | " << setw(11) << data[i].baseCostPerHour
                 << " | " << setw(12) << data[i].daysVisitsPerYear
                 << " | " << setw(23) << numberText(data[i].totalCost, 2) << " |\n";
        }
        cout << string(ruleWidth, '-') << "\n";
        cout << "Showing " << count << " of " << count << " records" << endl;
    }

private:
    // KeyOf - the value a record is sorted on
    static double keyOf(const Patient& p, int field) {
        if (field == SORT_BY_AGE) {
            return p.age;
        }
        if (field == SORT_BY_DURATION) {
            return p.lengthOfStay;
        }
        return p.totalCost;
    }

    // IsAfter - true when 'left' must be placed after 'right' (equal keys keep their order, so sorts are stable)
    static bool isAfter(const Patient& left, const Patient& right, int field, bool ascending) {
        double a = keyOf(left, field);
        double b = keyOf(right, field);
        if (ascending) {
            return a > b;
        }
        return a < b;
    }

    // MergeSortRange - sort data[left..right] by sorting both halves and then merging them
    void mergeSortRange(Patient* temp, int left, int right, int field, bool ascending, SortStats& stats) {
        if (left >= right) {
            return;
        }
        int mid = left + (right - left) / 2;
        mergeSortRange(temp, left, mid, field, ascending, stats);
        mergeSortRange(temp, mid + 1, right, field, ascending, stats);
        mergeRanges(temp, left, mid, right, field, ascending, stats);
    }

    // MergeRanges - merge the sorted halves data[left..mid] and data[mid+1..right]
    void mergeRanges(Patient* temp, int left, int mid, int right, int field, bool ascending, SortStats& stats) {
        for (int k = left; k <= right; k++) {
            temp[k] = data[k];
        }
        int i = left;
        int j = mid + 1;
        int k = left;
        while (i <= mid && j <= right) {
            stats.comparisons++;
            if (isAfter(temp[i], temp[j], field, ascending)) {
                data[k++] = temp[j++];
            } else {
                data[k++] = temp[i++];   // left one wins ties, which keeps the sort stable
            }
            stats.moves++;
        }
        while (i <= mid) {
            data[k++] = temp[i++];
            stats.moves++;
        }
        while (j <= right) {
            data[k++] = temp[j++];
            stats.moves++;
        }
    }
};

// AverageSortNanoseconds - run one sort many times, each time on a fresh copy, and return the mean time
inline double averageSortNanoseconds(const ArrayData& original, bool useMerge, int field, bool ascending,
                                     int repeats, SortStats& statsOut) {
    long long totalNs = 0;
    for (int r = 0; r < repeats; r++) {
        ArrayData copy(original);   // the original stays unsorted
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

// DisplaySortExperiment - time both sorts on a copy of the dataset for fields firstField..lastField
inline void displaySortExperiment(const ArrayData& original, const string& datasetName,
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
            SortStats stats;
            double nanoseconds = averageSortNanoseconds(original, useMerge, field, ascending, repeats, stats);

            size_t extraBytes = useMerge ? sizeof(Patient) * n : sizeof(Patient);   // buffer of n records, or one key
            cout << "| " << setw(14) << ArrayData::sortFieldName(field)
                 << " | " << setw(14) << (useMerge ? "Merge Sort" : "Insertion Sort")
                 << " | " << setw(15) << (useMerge ? "O(n log n)" : "O(n^2)")
                 << " | " << setw(13) << numberText(nanoseconds, 0)
                 << " | " << setw(11) << stats.comparisons
                 << " | " << setw(16) << extraBytes << " |\n";
        }
    }
    cout << string(ruleWidth, '-') << "\n";

    for (int field = firstField; field <= lastField; field++) {
        ArrayData sorted(original);
        sorted.mergeSort(field, ascending);
        cout << "\n All " << n << " records sorted by " << ArrayData::sortFieldName(field) << endl;
        sorted.displayWithTotalCost();
    }
}

// DisplayDatasetComparison - expenditure and visit duration across the three datasets and the age groups
inline void displayDatasetComparison(const ArrayData& a, const ArrayData& b, const ArrayData& c) {
    const ArrayData* sets[3] = { &a, &b, &c };
    const string labels[3] = { "Dataset A", "Dataset B", "Dataset C" };
    GroupStats stats[3][5];
    CareTally tallies[3][5];
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
             << " | " << setw(18) << numberText(total, 2)
             << " | " << setw(20) << numberText(average, 2)
             << " | " << setw(24) << numberText(sets[d]->averageVisitDuration(), 2)
             << " | " << setw(19) << numberText(sets[d]->averageVisitsPerYear(), 2) << " |\n";
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
            cout << "| " << setw(10) << ArrayData::ageGroupRange(g);
            for (int d = 0; d < 3; d++) {
                string cell = "-";   // "-" means the dataset has no patients in this age group
                if (stats[d][g].patientCount > 0) {
                    if (pass == 0) {
                        cell = numberText(stats[d][g].totalCost, 2);
                    } else if (pass == 1) {
                        cell = numberText(stats[d][g].totalStay / stats[d][g].patientCount, 2);
                    } else {
                        cell = numberText(stats[d][g].totalVisits / stats[d][g].patientCount, 2);
                    }
                }
                cout << " | " << setw(16) << cell;
            }
            cout << " |\n";
        }
        cout << string(groupWidth, '-') << "\n";
    }
}

