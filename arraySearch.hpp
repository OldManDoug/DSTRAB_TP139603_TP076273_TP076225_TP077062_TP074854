#ifndef ARRAY_SEARCH_HPP
#define ARRAY_SEARCH_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include "arraySort.hpp"

using namespace std;

// Search configuration and constants - age groups, care types, and Length of Stay(LOS)
const int ARRAY_SEARCH_AGE_GROUP = 1;
const int ARRAY_SEARCH_CARE_TYPE = 2;
const int ARRAY_SEARCH_LOS = 3;

// Demographic Age Brackets
const int ARRAY_AGE_GROUP_COUNT = 5;
const int ARRAY_AGE_GROUP_MIN[ARRAY_AGE_GROUP_COUNT] = { 0, 18, 26, 46, 61 };
const int ARRAY_AGE_GROUP_MAX[ARRAY_AGE_GROUP_COUNT] = { 17, 25, 45, 60, 100 };
const string ARRAY_AGE_GROUP_NAME[ARRAY_AGE_GROUP_COUNT] = {
    "Pediatrics & Adolescents", "Young Adults / University Students", "Working Adults (Early Career)",
    "Working Adults (Late Career)", "Senior Citizens / Geriatric Care"
};

// Care type string categories for filetering search
const int ARRAY_CARE_TYPE_COUNT = 6;
const string ARRAY_CARE_TYPES[ARRAY_CARE_TYPE_COUNT] = {
    "Emergency", "Outpatient", "Inpatient", "Vaccination", "Rehabilitation", "Routine Checkup"
};


// Encapsulates all search criteria into a single struct passed across functions.
struct ArraySearchQuery {
    int type;           // 1 = Age Group, 2 = Care Type, 3 = Visit Duration (LOS)
    int minAge;         // Lower age bound
    int maxAge;         // Upper age bound
    string careType;    // Specific department string
    int hours;          // Minimum length of stay threshold
    ArraySearchQuery() : type(ARRAY_SEARCH_AGE_GROUP), minAge(0), maxAge(0), hours(0) {}
};

// Benchmarking Parameters
const int ARRAY_SEARCH_RULE = 101;
const int ARRAY_SEARCH_REPEATS = 200; // Base iteration of repetitions for searching
const int ARRAY_SEARCH_ROUNDS = 5;    // Execution rounds to filer out noise 

// Helper function to format active criteria into text for reports
inline string arraySearchCriteriaText(const ArraySearchQuery& q) {
    if (q.type == ARRAY_SEARCH_AGE_GROUP) {
        return "Age " + to_string(q.minAge) + "-" + to_string(q.maxAge);
    }
    if (q.type == ARRAY_SEARCH_CARE_TYPE) {
        return "Care Type = " + q.careType;
    }
    return "LOS > " + to_string(q.hours) + " hours";
}

// Console Table Formatting Helpers
inline void printArraySearchHeader(const string& title) {
    cout << "\n" << title << "\n";
    cout << string(ARRAY_SEARCH_RULE, '-') << "\n";
    cout << left << "| " << setw(5) << "Age"
         << " | " << setw(15) << "Care Type"
         << " | " << setw(16) << "Length of Stay"
         << " | " << setw(11) << "Base Cost"
         << " | " << setw(12) << "Days Visit"
         << " | " << setw(23) << "Total Medical Cost (RM)" << " |\n";
    cout << string(ARRAY_SEARCH_RULE, '-') << "\n";
}

inline void printArraySearchRow(const Patient& p) {
    cout << left << "| " << setw(5) << p.age
         << " | " << setw(15) << p.careType
         << " | " << setw(16) << p.lengthOfStay
         << " | " << setw(11) << p.baseCostPerHour
         << " | " << setw(12) << p.daysVisitsPerYear
         << " | " << setw(23) << numberText(p.totalCost, 2) << " |\n";
}


// Age group binary search on sorted arrays O(log N + K) and Linear search on unsorted O(N).
// Citation: Binary search range logic adapted from GeeksforGeeks (2023)
// GeeksforGeeks. (2023, November 10). Binary Search. https://www.geeksforgeeks.org/binary-search/

inline int arraySearchAgeGroup(const ArrayData& dataset, int minAge, int maxAge, bool isSorted, bool ascending, int& comparisons, bool show) {
    int found = 0;
    comparisons = 0;
    int count = dataset.getCount();

    if (isSorted && count > 0) {  // Binary search to find lower bound index in O(log N) comparisons
        if (ascending) {
            int low = 0, high = count - 1;
            int startIndex = count;
            while (low <= high) {
                comparisons++;
                int mid = low + (high - low) / 2;
                if (dataset.getAt(mid).age >= minAge) {
                    startIndex = mid;
                    high = mid - 1; // to narrow down to find first occurrence
                } else {
                    low = mid + 1;
                }
            }
            //Sequential forward scan that terminates early when age > maxAge
            for (int i = startIndex; i < count; i++) {
                comparisons++;
                if (dataset.getAt(i).age > maxAge) break; 
                
                found++;
                if (show) printArraySearchRow(dataset.getAt(i));
            }
        } else {
            // Binary search for descending sorted arrays
            int low = 0, high = count - 1;
            int startIndex = count;
            while (low <= high) {
                comparisons++;
                int mid = low + (high - low) / 2;
                if (dataset.getAt(mid).age <= maxAge) {
                    startIndex = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            for (int i = startIndex; i < count; i++) {
                comparisons++;
                if (dataset.getAt(i).age < minAge) break;
                
                found++;
                if (show) printArraySearchRow(dataset.getAt(i));
            }
        }
    } else {
        // Unsorted array fallback: Full linear scan through all N elements O(N)
        for (int i = 0; i < count; i++) {
            comparisons++;
            if (dataset.getAt(i).age >= minAge && dataset.getAt(i).age <= maxAge) {
                found++;
                if (show) printArraySearchRow(dataset.getAt(i));
            }
        }
    }
    return found;
}

// Care type search via sequential linear search O(N) because Care Type string is non-numeric and unsorted.
inline int arraySearchCareType(const ArrayData& dataset, const string& careType, int& comparisons, bool show) {
    int found = 0;
    comparisons = 0;
    int count = dataset.getCount();
    
    for (int i = 0; i < count; i++) {
        comparisons++;
        if (dataset.getAt(i).careType == careType) {
            found++;
            if (show) printArraySearchRow(dataset.getAt(i));
        }
    }
    return found;
}


// Length of stay searchLOS via stay length > threshold using Binary Search on duration-sorted data.

inline int arraySearchLOS(const ArrayData& dataset, int hours, bool isSorted, bool ascending, int& comparisons, bool show) {
    int found = 0;
    comparisons = 0;
    int count = dataset.getCount();

    if (isSorted && count > 0) {
        if (ascending) {
            // Binary Search lower bound for LengthOfStay > hours
            int low = 0, high = count - 1;
            int startIndex = count;
            while (low <= high) {
                comparisons++;
                int mid = low + (high - low) / 2;
                if (dataset.getAt(mid).lengthOfStay > hours) {
                    startIndex = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            for (int i = startIndex; i < count; i++) {
                found++;
                if (show) printArraySearchRow(dataset.getAt(i));
            }
        } else {
            for (int i = 0; i < count; i++) {
                comparisons++;
                if (dataset.getAt(i).lengthOfStay > hours) {
                    found++;
                    if (show) printArraySearchRow(dataset.getAt(i));
                } else {
                    break;
                }
            }
        }
    } else {
        // Unsorted array linear search O(N)
        for (int i = 0; i < count; i++) {
            comparisons++;
            if (dataset.getAt(i).lengthOfStay > hours) {
                found++;
                if (show) printArraySearchRow(dataset.getAt(i));
            }
        }
    }
    return found;
}


// SEARCH ROUTER / DISPATCHER
// Central hub that delegates execution based on the chosen ArraySearchQuery type.

inline int runArraySearch(const ArrayData& dataset, const ArraySearchQuery& q, bool isSorted, bool ascending, int& comparisons, bool show) {
    if (q.type == ARRAY_SEARCH_AGE_GROUP) {
        return arraySearchAgeGroup(dataset, q.minAge, q.maxAge, isSorted, ascending, comparisons, show);
    }
    if (q.type == ARRAY_SEARCH_CARE_TYPE) {
        return arraySearchCareType(dataset, q.careType, comparisons, show);
    }
    return arraySearchLOS(dataset, q.hours, isSorted, ascending, comparisons, show);
}


// Timing benchmark using chrono::steady_clock to filter out OS background context-switching noise and return clean nanoseconds.
// Citation: High-resolution clock timing adapted from Cplusplus.com
// Cplusplus.com. (2021). chrono::steady_clock. https://cplusplus.com/reference/chrono/steady_clock/

inline double averageArraySearchNanoseconds(const ArrayData& dataset, const ArraySearchQuery& q, bool isSorted, bool ascending, int repeats, int& found, int& comparisons) {
    found = runArraySearch(dataset, q, isSorted, ascending, comparisons, false);
    volatile int sink = 0;
    int ignored = 0;
    double best = -1;
    int runs = repeats;
    
    for (int round = 0; round < ARRAY_SEARCH_ROUNDS; round++) {
        double elapsed = 0;
        for (;;) {
            chrono::steady_clock::time_point start = chrono::steady_clock::now();
            for (int r = 0; r < runs; r++) {
                sink = runArraySearch(dataset, q, isSorted, ascending, ignored, false);
            }
            chrono::steady_clock::time_point stop = chrono::steady_clock::now();
            elapsed = (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
            
            if (elapsed >= 20000000.0 || runs >= 100000000) { // 20ms noise threshold
                break;
            }
            runs *= 2; // Dynamically scale repetitions
        }
        double average = elapsed / runs;
        if (best < 0 || average < best) {
            best = average;
        }
    }
    (void)sink;
    return best;
}

// Runs array search benchmark and displays performance comparison table
inline void displayArraySearchExperiment(const ArraySort& original, const string& datasetName, const ArraySearchQuery& q) {
    const int ruleWidth = 79;
    string criteria = arraySearchCriteriaText(q);

    int sortField = (q.type == ARRAY_SEARCH_LOS) ? SORT_BY_DURATION : SORT_BY_AGE;
    string fieldLabel = (q.type == ARRAY_SEARCH_LOS) ? "LOS" : "Age";
    
    // Creates sorted array copies for testing
    ArraySort sortedAsc(original);
    sortedAsc.mergeSort(sortField, true);
    ArraySort sortedDesc(original);
    sortedDesc.mergeSort(sortField, false);

    int comparisons = 0;
    printArraySearchHeader("=== " + datasetName + " - Search: " + criteria + " ===");
    int shown = runArraySearch(sortedAsc, q, true, true, comparisons, true);
    if (shown == 0) {
        cout << left << "| " << setw(ARRAY_SEARCH_RULE - 4) << "(no matching records)" << " |\n";
    }
    cout << string(ARRAY_SEARCH_RULE, '-') << "\n";
    cout << "Showing " << shown << " matching records (ordered by " << ArraySort::sortFieldName(sortField) << ")" << endl;

    const ArraySort* datasets[3] = { &original, &sortedAsc, &sortedDesc };
    const string labels[3] = { "Unsorted", "Sorted (" + fieldLabel + " asc)", "Sorted (" + fieldLabel + " desc)" };
    int rowCount = (q.type == ARRAY_SEARCH_CARE_TYPE) ? 2 : 3;
    size_t searchBytes = sizeof(const Patient*) + 2 * sizeof(int);

    cout << "\n--- " << datasetName << " - Search Performance: " << criteria << " ---" << endl;
    cout << string(ruleWidth, '-') << "\n";
    cout << left << "| " << setw(17) << "Array"
         << " | " << setw(6) << "Found"
         << " | " << setw(11) << "Comparisons"
         << " | " << setw(13) << "Avg Time (ns)"
         << " | " << setw(16) << "Memory Usage (B)" << " |\n";
    cout << string(ruleWidth, '-') << "\n";

    bool sameResult = true;
    for (int i = 0; i < rowCount; i++) {
        bool isSorted = (i > 0);
        bool ascending = (i != 2);
        int found = 0;
        double nanoseconds = averageArraySearchNanoseconds(*datasets[i], q, isSorted, ascending, ARRAY_SEARCH_REPEATS, found, comparisons);
        if (found != shown) {
            sameResult = false;
        }
        cout << "| " << setw(17) << labels[i]
             << " | " << setw(6) << found
             << " | " << setw(11) << comparisons
             << " | " << setw(13) << numberText(nanoseconds, 0)
             << " | " << setw(16) << (original.dataBytes() + searchBytes) << " |\n";
    }
    cout << string(ruleWidth, '-') << "\n";
    if (!sameResult) {
        cout << "WARNING: the arrays returned different counts - check the sort order" << endl;
    }
    cout << "Array memory: " << original.getCount() << " elements x " << sizeof(Patient) << " B = "
         << original.dataBytes() << " B" << endl;
    cout << "Avg Time = mean of one search, best of " << ARRAY_SEARCH_ROUNDS
         << " rounds, each repeated for 20+ ms; sort time not included" << endl;
    if (q.type == ARRAY_SEARCH_CARE_TYPE) {
        cout << "Care Type is not a sort field, so the Age-sorted array cannot stop early" << endl;
    }
}

// User menu input reader
inline int readArraySearchChoice() {
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    cin.ignore(10000, '\n');
    return choice;
}

// Interactive search criteria menu
inline int chooseArraySearchQuery(ArraySearchQuery& query, const string& title) {
    cout << "\n===== " << title << " =====" << endl;
    cout << "1. Age group" << endl;
    cout << "2. Care type" << endl;
    cout << "3. Visit duration (LOS > hours)" << endl;
    cout << "0. Back" << endl;
    cout << "Criterion: ";
    int criterion = readArraySearchChoice();

    if (criterion == 0) return 0;

    query.type = criterion;
    if (criterion == ARRAY_SEARCH_AGE_GROUP) {
        cout << "\n===== AGE GROUP =====" << endl;
        for (int g = 0; g < ARRAY_AGE_GROUP_COUNT; g++) {
            string range = to_string(ARRAY_AGE_GROUP_MIN[g]) + "-" + to_string(ARRAY_AGE_GROUP_MAX[g]);
            cout << g + 1 << ". " << left << setw(8) << range << ARRAY_AGE_GROUP_NAME[g] << endl;
        }
        cout << "Group: ";
        int group = readArraySearchChoice();
        if (group < 1 || group > ARRAY_AGE_GROUP_COUNT) {
            cout << "Invalid group, try again." << endl;
            return -1;
        }
        query.minAge = ARRAY_AGE_GROUP_MIN[group - 1];
        query.maxAge = ARRAY_AGE_GROUP_MAX[group - 1];
    } else if (criterion == ARRAY_SEARCH_CARE_TYPE) {
        cout << "\n===== CARE TYPE =====" << endl;
        for (int t = 0; t < ARRAY_CARE_TYPE_COUNT; t++) {
            cout << t + 1 << ". " << ARRAY_CARE_TYPES[t] << endl;
        }
        cout << "Care type: ";
        int type = readArraySearchChoice();
        if (type < 1 || type > ARRAY_CARE_TYPE_COUNT) {
            cout << "Invalid care type, try again." << endl;
            return -1;
        }
        query.careType = ARRAY_CARE_TYPES[type - 1];
    } else if (criterion == ARRAY_SEARCH_LOS) {
        cout << "Show patients who stayed MORE than how many hours? ";
        int hours = readArraySearchChoice();
        if (hours < 0) {
            cout << "Invalid hours, try again." << endl;
            return -1;
        }
        query.hours = hours;
    } else {
        cout << "Invalid criterion, try again." << endl;
        return -1;
    }
    return 1;
}

// Triggers search experiments for all datasets
inline void runArraySearchMenu(ArraySort& datasetA, ArraySort& datasetB, ArraySort& datasetC) {
    int status;
    do {
        ArraySearchQuery query;
        status = chooseArraySearchQuery(query, "SEARCH BY");
        if (status == 1) {
            if (!ensureAllLoaded(datasetA, datasetB, datasetC)) return;

            displayArraySearchExperiment(datasetA, "Dataset A", query);
            displayArraySearchExperiment(datasetB, "Dataset B", query);
            displayArraySearchExperiment(datasetC, "Dataset C", query);
        }
    } while (status != 0);
}

#endif // ARRAY_SEARCH_HPP