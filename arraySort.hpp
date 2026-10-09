#ifndef ARRAY_SORT_HPP
#define ARRAY_SORT_HPP

#include <chrono>
#include "arrayDataSet.hpp"

// fixed number of decimals
inline string numberText(double value, int decimals) {
    ostringstream out;
    out << fixed << setprecision(decimals) << value;
    return out.str();
}

// totals for one age group
struct GroupStats {
    int patientCount;
    double totalCost;
    double totalStay;       // lengthOfStay = visit duration (hours)
    double totalVisits;

    GroupStats() {
        patientCount = 0;
        totalCost = 0;
        totalStay = 0;
        totalVisits = 0;
    }
};

// sort criteria
const int SORT_BY_AGE = 1;
const int SORT_BY_DURATION = 2;
const int SORT_BY_COST = 3;

// use to record comparison steps
struct SortStats {
    long long comparisons;
    long long moves;

    SortStats() {
        comparisons = 0;
        moves = 0;
    }
};

// care type names and counts and the cost per care type
struct CareTally {
    string names[20];
    int counts[20];
    double costs[20];
    int used;               // how many care types have been seen so far

    CareTally() {
        used = 0;
        for (int i = 0; i < 20; i++) {
            counts[i] = 0;
            costs[i] = 0;
        }
    }

    // count patient, cost under a care type
    void add(const string& name, double cost) { 
        for (int i = 0; i < used; i++) {

            if (names[i] == name) {
                counts[i]++;
                costs[i] += cost;
                return;
            }
        }

        if (used==20) {
            throw runtime_error("Too many different care types (limit is 20)");
        }

        names[used] = name;
        counts[used] = 1;
        costs[used] = cost;
        used++;
    }

    // highest care type
    string mostRequested() const {
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

    // find next care type to print
    int pickNext(const bool printed[], bool byCost) const {   // O(c)
        int best = -1;
        for (int i = 0; i < used; i++) {
            if (printed[i]) {
                continue;
            }
            if (best == -1) {
                best = i;
            } 
            else if (byCost && costs[i] > costs[best]) {
                best = i;
            } 
            else if (!byCost && counts[i] > counts[best]) {
                best = i;
            }
        }
        return best;
    }

    // biggest patient count of any care type (0 when the tally is empty)
    int highestCount() const {
        int highest = 0;
        for (int i = 0; i < used; i++) {
            if (counts[i] > highest) {
                highest = counts[i];
            }
        }
        return highest;
    }
};

class ArraySort : public ArrayData {
public:
    // map an age to group
    static int ageGroupIndex(int age) {
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

    // age range of a group
    static string ageGroupRange(int group) {
        switch (group) {
            case 0: return "0-17";
            case 1: return "18-25";
            case 2: return "26-45";
            case 3: return "46-60";
            default: return "61-100";
        }
    }

    // name of age group
    static string ageGroupDescription(int group) {
        switch (group) {
            case 0: return "Pediatrics & Adolescents";
            case 1: return "Young Adults / University Students";
            case 2: return "Working Adults (Early Career)";
            case 3: return "Working Adults (Late Career)";
            default: return "Senior Citizens / Geriatric Care";
        }
    }

    void analyseAgeGroups(GroupStats stats[], CareTally tallies[], int& outOfRange) const {
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

    // sum of totalCost over every record
    double totalBilling() const {
        double sum = 0;

        for (int i = 0; i < count; i++) {
            sum += data[i].totalCost;
        }
        return sum;
    }

    double averageVisitDuration() const {
        if (count == 0) {
            return 0;
        }

        double sum = 0;
        for (int i = 0; i < count; i++) {

            sum += data[i].lengthOfStay;
        }
        return sum / count;
    }

    double averageVisitsPerYear() const {
        if (count == 0) {
            return 0;
        }

        double sum = 0;
        for (int i = 0; i < count; i++) {

            sum += data[i].daysVisitsPerYear;
        }
        return sum / count;
    }

    // patients and cost per care type
    void tallyCareTypes(CareTally& tally) const {
        for (int i = 0; i < count; i++) {
            tally.add(data[i].careType, data[i].totalCost);
        }
    }

    // care type table, total cost, average cost, most requested care type per age grp
    void displayAgeGroupAnalysis(const string& datasetName) const {
        GroupStats stats[5];
        CareTally tallies[5];
        int outOfRange;
        analyseAgeGroups(stats, tallies, outOfRange);

        const int ruleWidth = 88;
        cout << "\n=== " << datasetName << " - Age Group and Billing Analysis ===" << endl;

        for (int g = 0; g < 5; g++) {
            string range = ageGroupRange(g);
            string description = ageGroupDescription(g);
            cout << "\nAge Group: " << range << " (" << description << ")" << endl;
            cout << string(ruleWidth, '-') << "\n";
            cout << left << "| " << setw(18) << "Care Type"
                 << " | " << setw(15) << "Patient Count"
                 << " | " << setw(16) << "Total Cost (RM)"
                 << " | " << setw(26) << "Average Cost per Patient" << " |\n";
            cout << string(ruleWidth, '-') << "\n";

            if (stats[g].patientCount == 0) {
                cout << "| " << setw(ruleWidth - 4) << "No patients in this age group" << " |\n";
            } 
            else {
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

        // summary table, one row per age group
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
            string range = ageGroupRange(g);
            cout << "| " << setw(10) << range
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

    // total billing for the dataset and total cost grouped by care type
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

    static string sortFieldName(int field) {
        if (field == SORT_BY_AGE) {
            return "Age";
        }
        if (field == SORT_BY_DURATION) {
            return "Visit Duration";
        }
        return "Total Cost";
    }

    // Insertion Sort  https://www.programiz.com/dsa/insertion-sort
    SortStats insertionSort(int field, bool ascending) {  
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
//https://www.programiz.com/dsa/merge-sort
    // Merge Sort
    SortStats mergeSort(int field, bool ascending) {
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

    bool isSorted(int field, bool ascending) const {
        for (int i = 1; i < count; i++) {
            if (isAfter(data[i - 1], data[i], field, ascending)) {
                return false;
            }
        }
        return true;
    }

    // memory used by the records themselves
    size_t dataBytes() const {
        return sizeof(Patient) * count;
    }

    // every record in CSV columns and the total medical cost
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
    // sort criteria
    static double keyOf(const Patient& p, int field) {
        if (field == SORT_BY_AGE) {
            return p.age;
        }
        if (field == SORT_BY_DURATION) {
            return p.lengthOfStay;
        }
        return p.totalCost;
    }

    static bool isAfter(const Patient& left, const Patient& right, int field, bool ascending) {
        double a = keyOf(left, field);
        double b = keyOf(right, field);
        if (ascending) {
            return a > b;
        }
        return a < b;
    }

    void mergeSortRange(Patient* temp, int left, int right, int field, bool ascending, SortStats& stats) {
        if (left >= right) {
            return;
        }

        int mid = left + (right - left) / 2;
        mergeSortRange(temp, left, mid, field, ascending, stats);
        mergeSortRange(temp, mid + 1, right, field, ascending, stats);
        mergeRanges(temp, left, mid, right, field, ascending, stats);
    }

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

// run one sort many times, each time on a fresh copy, and return the mean time
inline double averageSortNanoseconds(const ArraySort& original, bool useMerge, int field, bool ascending,                                      int repeats, SortStats& statsOut) {
    long long totalNs = 0;
    int runs = 0;

    while (runs < repeats || (totalNs < 20000000 && runs < 100000)) {
        ArraySort copy(original);   // the original stays unsorted
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        if (useMerge) {
            statsOut = copy.mergeSort(field, ascending);
        } else {
            statsOut = copy.insertionSort(field, ascending);
        }
        chrono::steady_clock::time_point stop = chrono::steady_clock::now();
        totalNs += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
        runs++;
    }
    return (double)totalNs / runs;
}

inline void displaySortExperiment(const ArraySort& original, const string& datasetName, int firstField, int lastField, bool ascending) {
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
            cout << "| " << setw(14) << ArraySort::sortFieldName(field)
                 << " | " << setw(14) << (useMerge ? "Merge Sort" : "Insertion Sort")
                 << " | " << setw(15) << (useMerge ? "O(n log n)" : "O(n^2)")
                 << " | " << setw(13) << numberText(nanoseconds, 0)
                 << " | " << setw(11) << stats.comparisons
                 << " | " << setw(16) << (original.dataBytes() + extraBytes) << " |\n";   // records + temporary storage
        }
    }
    cout << string(ruleWidth, '-') << "\n";

    for (int field = firstField; field <= lastField; field++) {
        ArraySort sorted(original);
        sorted.mergeSort(field, ascending);
        cout << "\n All " << n << " records sorted by " << ArraySort::sortFieldName(field) << endl;
        sorted.displayWithTotalCost();
    }
}

// expenditure and visit duration across the three datasets and the age groups
inline void displayDatasetComparison(const ArraySort& a, const ArraySort& b, const ArraySort& c) {
    const ArraySort* sets[3] = { &a, &b, &c };
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
        } 
        else if (pass == 2) {
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
            string range = ArraySort::ageGroupRange(g);
            cout << "| " << setw(10) << range;
            for (int d = 0; d < 3; d++) {
                string cell = "-";   // no patients in this age group
                if (stats[d][g].patientCount > 0) {
                    if (pass == 0) {
                        cell = numberText(stats[d][g].totalCost, 2);
                    } 
                    else if (pass == 1) {
                        cell = numberText(stats[d][g].totalStay / stats[d][g].patientCount, 2);
                    } 
                    else {
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

inline string highestBillingGroups(const GroupStats groups[], double& highestCost) {
    highestCost = -1;
    for (int g = 0; g < 5; g++) {
        if (groups[g].patientCount > 0 && groups[g].totalCost > highestCost) {
            highestCost = groups[g].totalCost;
        }
    }
    string result = "";
    
    for (int g = 0; g < 5; g++) {
        if (groups[g].patientCount > 0 && groups[g].totalCost == highestCost) {
            if (result != "") {
                result += " / ";
            }
            string range = ArraySort::ageGroupRange(g);
            result += range;
        }
    }
    if (result == "") {
        highestCost = 0;
        return "none";
    }
    return result;
}

// compare treatment costs and service preferences across datasets and age groups,
// then identify the highest-billing age group and the highest-traffic care type
inline void displayClinicalInsights(const ArraySort& a, const ArraySort& b, const ArraySort& c) {
    const ArraySort* sets[3] = { &a, &b, &c };
    const string labels[3] = { "Dataset A", "Dataset B", "Dataset C" };
    GroupStats stats[3][5];
    CareTally groupTallies[3][5];
    CareTally careTally[3];
    CareTally allCare;          // care types of all three datasets together
    int outOfRange;

    for (int d = 0; d < 3; d++) {
        sets[d]->analyseAgeGroups(stats[d], groupTallies[d], outOfRange);
        sets[d]->tallyCareTypes(careTally[d]);
        sets[d]->tallyCareTypes(allCare);
    }

    cout << "\n=== Clinical Insights ===" << endl;

    // Table of total cost of each age group in each dataset
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
        string range = ArraySort::ageGroupRange(g);
        cout << "| " << setw(10) << range;
        for (int d = 0; d < 3; d++) {
            string cell = "-";
            if (stats[d][g].patientCount > 0) {
                cell = numberText(stats[d][g].totalCost, 2);
            }
            cout << " | " << setw(16) << cell;
        }
        cout << " |\n";
    }
    cout << string(averageWidth, '-') << "\n";

    // Table of most requested care type in each age group and dataset
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
        string range = ArraySort::ageGroupRange(g);
        cout << "| " << setw(10) << range;
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

    // Table of highest-billing age group and highest-traffic care type
    GroupStats allGroups[5];    // age groups of all three datasets together
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
        const GroupStats* groups = (row < 3) ? stats[row] : allGroups;
        const CareTally& tally = (row < 3) ? careTally[row] : allCare;
        double highestCost;
        string groupNames = highestBillingGroups(groups, highestCost);
        cout << "| " << setw(13) << (row < 3 ? labels[row] : string("All datasets"))
             << " | " << setw(25) << groupNames
             << " | " << setw(12) << numberText(highestCost, 2)
             << " | " << setw(25) << tally.mostRequested()
             << " | " << setw(8) << tally.highestCount() << " |\n";
    }
    cout << string(findingWidth, '-') << "\n";
}

#endif
