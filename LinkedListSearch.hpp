#ifndef LINKED_LIST_SEARCH_HPP
#define LINKED_LIST_SEARCH_HPP

// Include after lists.hpp
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
using namespace std;

// Search criteria
const int LIST_SEARCH_AGE_GROUP = 1;
const int LIST_SEARCH_CARE_TYPE = 2;
const int LIST_SEARCH_LOS = 3;

// Age groups
const int LIST_AGE_GROUP_COUNT = 5;
const int LIST_AGE_GROUP_MIN[LIST_AGE_GROUP_COUNT] = { 0, 18, 26, 46, 61 };
const int LIST_AGE_GROUP_MAX[LIST_AGE_GROUP_COUNT] = { 17, 25, 45, 60, 100 };
const string LIST_AGE_GROUP_NAME[LIST_AGE_GROUP_COUNT] = {
    "Pediatrics & Adolescents", "Young Adults / University Students", "Working Adults (Early Career)",
    "Working Adults (Late Career)", "Senior Citizens / Geriatric Care"
};

// Care types
const int LIST_CARE_TYPE_COUNT = 6;
const string LIST_CARE_TYPES[LIST_CARE_TYPE_COUNT] = {
    "Emergency", "Outpatient", "Inpatient", "Vaccination", "Rehabilitation", "Routine Checkup"
};

// Search query
struct ListSearchQuery {
    int type;
    int minAge;
    int maxAge;
    string careType;
    int hours;
    ListSearchQuery() : type(LIST_SEARCH_AGE_GROUP), minAge(0), maxAge(0), hours(0) {}
};

// Settings
const int LIST_SEARCH_RULE = 108;
const int LIST_SEARCH_REPEATS = 200;
const int LIST_SEARCH_ROUNDS = 5;

// Criteria text
inline string listSearchCriteriaText(const ListSearchQuery& q) {
    if (q.type == LIST_SEARCH_AGE_GROUP) {
        return "Age " + to_string(q.minAge) + "-" + to_string(q.maxAge);
    }
    if (q.type == LIST_SEARCH_CARE_TYPE) {
        return "Care Type = " + q.careType;
    }
    return "LOS > " + to_string(q.hours) + " hours";
}

// Record table
inline void printListSearchHeader(const string& title) {
    cout << "\n" << title << "\n";
    cout << string(LIST_SEARCH_RULE, '-') << "\n";
    cout << left << "| " << setw(4) << "ID"
         << " | " << setw(5) << "Age"
         << " | " << setw(15) << "Care Type"
         << " | " << setw(16) << "Length of Stay"
         << " | " << setw(11) << "Base Cost"
         << " | " << setw(12) << "Days Visit"
         << " | " << setw(23) << "Total Medical Cost (RM)" << " |\n";
    cout << string(LIST_SEARCH_RULE, '-') << "\n";
}

inline void printListSearchRow(const ListPatient& p) {
    cout << left << "| " << setw(4) << p.patientID
         << " | " << setw(5) << p.age
         << " | " << setw(15) << p.careType
         << " | " << setw(16) << p.lengthOfStay
         << " | " << setw(11) << p.baseCostPerHour
         << " | " << setw(12) << p.daysVisitsPerYear
         << " | " << setw(23) << listNumberText(p.totalCost, 2) << " |\n";
}

// Search by age group
inline int listSearchAgeGroup(const PatientNode* head, int minAge, int maxAge, bool isSorted, bool ascending,
                              int& comparisons, bool show) {
    int found = 0;
    comparisons = 0;
    const PatientNode* current = head;
    while (current != nullptr) {
        comparisons++;
        int age = current->data.age;
        if (age >= minAge && age <= maxAge) {
            found++;
            if (show) {
                printListSearchRow(current->data);
            }
        } else if (isSorted && (ascending ? age > maxAge : age < minAge)) {
            break;
        }
        current = current->next;
    }
    return found;
}

// Search by care type
inline int listSearchCareType(const PatientNode* head, const string& careType, int& comparisons, bool show) {
    int found = 0;
    comparisons = 0;
    const PatientNode* current = head;
    while (current != nullptr) {
        comparisons++;
        if (current->data.careType == careType) {
            found++;
            if (show) {
                printListSearchRow(current->data);
            }
        }
        current = current->next;
    }
    return found;
}

// Search by visit duration
inline int listSearchLOS(const PatientNode* head, int hours, bool isSorted, bool ascending, int& comparisons,
                         bool show) {
    int found = 0;
    comparisons = 0;
    const PatientNode* current = head;
    while (current != nullptr) {
        comparisons++;
        if (current->data.lengthOfStay > hours) {
            found++;
            if (show) {
                printListSearchRow(current->data);
            }
        } else if (isSorted && !ascending) {
            break;
        }
        current = current->next;
    }
    return found;
}

// Run selected search
inline int runListSearch(const PatientNode* head, const ListSearchQuery& q, bool isSorted, bool ascending,
                         int& comparisons, bool show) {
    if (q.type == LIST_SEARCH_AGE_GROUP) {
        return listSearchAgeGroup(head, q.minAge, q.maxAge, isSorted, ascending, comparisons, show);
    }
    if (q.type == LIST_SEARCH_CARE_TYPE) {
        return listSearchCareType(head, q.careType, comparisons, show);
    }
    return listSearchLOS(head, q.hours, isSorted, ascending, comparisons, show);
}

// Average search time
inline double averageListSearchNanoseconds(const PatientNode* head, const ListSearchQuery& q, bool isSorted,
                                           bool ascending, int repeats, int& found, int& comparisons) {
    found = runListSearch(head, q, isSorted, ascending, comparisons, false);
    volatile int sink = 0;
    int ignored = 0;
    double best = -1;
    for (int round = 0; round < LIST_SEARCH_ROUNDS; round++) {
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        for (int r = 0; r < repeats; r++) {
            sink = runListSearch(head, q, isSorted, ascending, ignored, false);
        }
        chrono::steady_clock::time_point stop = chrono::steady_clock::now();
        double average = (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count() / repeats;
        if (best < 0 || average < best) {
            best = average;
        }
    }
    (void)sink;
    return best;
}

// Search experiment
inline void displayListSearchExperiment(const PatientList& original, const string& datasetName,
                                        const ListSearchQuery& q) {
    const int ruleWidth = 79;
    string criteria = listSearchCriteriaText(q);

    // Sorted copies
    int sortField = (q.type == LIST_SEARCH_LOS) ? LIST_SORT_BY_DURATION : LIST_SORT_BY_AGE;
    string fieldLabel = (q.type == LIST_SEARCH_LOS) ? "LOS" : "Age";
    PatientList sortedAsc(original);
    sortedAsc.mergeSort(sortField, true);
    PatientList sortedDesc(original);
    sortedDesc.mergeSort(sortField, false);

    // Matching records
    int comparisons = 0;
    printListSearchHeader("=== " + datasetName + " - Search: " + criteria + " ===");
    int shown = runListSearch(sortedAsc.getHead(), q, true, true, comparisons, true);
    if (shown == 0) {
        cout << left << "| " << setw(LIST_SEARCH_RULE - 4) << "(no matching records)" << " |\n";
    }
    cout << string(LIST_SEARCH_RULE, '-') << "\n";
    cout << "Showing " << shown << " matching records (ordered by " << PatientList::sortFieldName(sortField) << ")"
         << endl;

    // Performance table
    const PatientList* lists[3] = { &original, &sortedAsc, &sortedDesc };
    const string labels[3] = { "Unsorted", "Sorted (" + fieldLabel + " asc)", "Sorted (" + fieldLabel + " desc)" };
    int rowCount = (q.type == LIST_SEARCH_CARE_TYPE) ? 2 : 3;
    size_t searchBytes = sizeof(const PatientNode*) + 2 * sizeof(int);

    cout << "\n--- " << datasetName << " - Search Performance: " << criteria << " ---" << endl;
    cout << string(ruleWidth, '-') << "\n";
    cout << left << "| " << setw(17) << "List"
         << " | " << setw(6) << "Found"
         << " | " << setw(11) << "Comparisons"
         << " | " << setw(13) << "Avg Time (ns)"
         << " | " << setw(16) << "Extra Memory (B)" << " |\n";
    cout << string(ruleWidth, '-') << "\n";
    bool sameResult = true;
    for (int i = 0; i < rowCount; i++) {
        bool isSorted = (i > 0);
        bool ascending = (i != 2);
        int found = 0;
        double nanoseconds = averageListSearchNanoseconds(lists[i]->getHead(), q, isSorted, ascending, LIST_SEARCH_REPEATS,
                                                          found, comparisons);
        if (found != shown) {
            sameResult = false;
        }
        cout << "| " << setw(17) << labels[i]
             << " | " << setw(6) << found
             << " | " << setw(11) << comparisons
             << " | " << setw(13) << listNumberText(nanoseconds, 0)
             << " | " << setw(16) << searchBytes << " |\n";
    }
    cout << string(ruleWidth, '-') << "\n";
    if (!sameResult) {
        cout << "WARNING: the lists returned different counts - check the sort order" << endl;
    }
    cout << "List memory: " << original.getCount() << " nodes x " << sizeof(PatientNode) << " B = "
         << original.nodeBytes() << " B (next pointers alone: " << original.getCount() << " x "
         << sizeof(PatientNode*) << " B = " << original.getCount() * sizeof(PatientNode*) << " B)" << endl;
    cout << "Avg Time = mean of " << LIST_SEARCH_REPEATS << " runs, best of " << LIST_SEARCH_ROUNDS
         << " rounds; sort time not included (see sorting experiments)" << endl;
    if (q.type == LIST_SEARCH_CARE_TYPE) {
        cout << "Care Type is not a sort field, so the Age-sorted list cannot stop early" << endl;
    }
}

// Menu input
inline int readListSearchChoice() {
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    cin.ignore(10000, '\n');
    return choice;
}

// Search criteria menu
inline int chooseListSearchQuery(ListSearchQuery& query, const string& title) {
    cout << "\n===== " << title << " =====" << endl;
    cout << "1. Age group" << endl;
    cout << "2. Care type" << endl;
    cout << "3. Visit duration (LOS > hours)" << endl;
    cout << "0. Back" << endl;
    cout << "Criterion: ";
    int criterion = readListSearchChoice();

    if (criterion == 0) {
        return 0;
    }
    query.type = criterion;
    if (criterion == LIST_SEARCH_AGE_GROUP) {
        cout << "\n===== AGE GROUP =====" << endl;
        for (int g = 0; g < LIST_AGE_GROUP_COUNT; g++) {
            string range = to_string(LIST_AGE_GROUP_MIN[g]) + "-" + to_string(LIST_AGE_GROUP_MAX[g]);
            cout << g + 1 << ". " << left << setw(8) << range << LIST_AGE_GROUP_NAME[g] << endl;
        }
        cout << "Group: ";
        int group = readListSearchChoice();
        if (group < 1 || group > LIST_AGE_GROUP_COUNT) {
            cout << "Invalid group, try again." << endl;
            return -1;
        }
        query.minAge = LIST_AGE_GROUP_MIN[group - 1];
        query.maxAge = LIST_AGE_GROUP_MAX[group - 1];
    } else if (criterion == LIST_SEARCH_CARE_TYPE) {
        cout << "\n===== CARE TYPE =====" << endl;
        for (int t = 0; t < LIST_CARE_TYPE_COUNT; t++) {
            cout << t + 1 << ". " << LIST_CARE_TYPES[t] << endl;
        }
        cout << "Care type: ";
        int type = readListSearchChoice();
        if (type < 1 || type > LIST_CARE_TYPE_COUNT) {
            cout << "Invalid care type, try again." << endl;
            return -1;
        }
        query.careType = LIST_CARE_TYPES[type - 1];
    } else if (criterion == LIST_SEARCH_LOS) {
        cout << "Show patients who stayed MORE than how many hours? ";
        int hours = readListSearchChoice();
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

// Load lists
inline bool loadSearchLists(PatientList& listA, PatientList& listB, PatientList& listC) {
    bool loadedA = listA.getCount() > 0 || listA.loadFromFile("dataset1facility_a.csv");
    bool loadedB = listB.getCount() > 0 || listB.loadFromFile("dataset2facility_b.csv");
    bool loadedC = listC.getCount() > 0 || listC.loadFromFile("dataset3facility_c.csv");
    return loadedA && loadedB && loadedC;
}

// Search menu
inline void runListSearchMenu(PatientList& listA, PatientList& listB, PatientList& listC) {
    int status;
    do {
        ListSearchQuery query;
        status = chooseListSearchQuery(query, "SEARCH BY");
        if (status == 1) {
            if (!loadSearchLists(listA, listB, listC)) {
                return;
            }
            displayListSearchExperiment(listA, "Dataset A", query);
            displayListSearchExperiment(listB, "Dataset B", query);
            displayListSearchExperiment(listC, "Dataset C", query);
        }
    } while (status != 0);
}

#endif
