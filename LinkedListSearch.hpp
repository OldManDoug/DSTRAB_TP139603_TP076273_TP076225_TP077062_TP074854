#ifndef LINKED_LIST_SEARCH_HPP
#define LINKED_LIST_SEARCH_HPP

// Include after lists.hpp
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
using namespace std;

// Search criteria
const int SEARCH_AGE = 1;
const int SEARCH_CARE = 2;
const int SEARCH_LOS = 3;

const int GROUP_COUNT = 5;
const int GROUP_MIN[GROUP_COUNT] = { 0, 18, 26, 46, 61 };
const int GROUP_MAX[GROUP_COUNT] = { 17, 25, 45, 60, 100 };
const string GROUP_NAME[GROUP_COUNT] = { "Pediatrics & Adolescents", "Young Adults / University Students",
    "Working Adults (Early Career)", "Working Adults (Late Career)", "Senior Citizens / Geriatric Care" };

const int CARE_COUNT = 6;
const string CARE_TYPES[CARE_COUNT] = { "Emergency", "Outpatient", "Inpatient", "Vaccination", "Rehabilitation",
    "Routine Checkup" };

const int SEARCH_REPEATS = 1000;
const int SEARCH_WIDTH = 108;

struct SearchQuery {
    int type;
    int minAge;
    int maxAge;
    string careType;
    int hours;
};

string queryText(SearchQuery& q) {
    if (q.type == SEARCH_AGE) {
        return "Age " + to_string(q.minAge) + "-" + to_string(q.maxAge);
    }
    if (q.type == SEARCH_CARE) {
        return "Care Type = " + q.careType;
    }
    return "LOS > " + to_string(q.hours) + " hours";
}

// Record table
void printHeader(string title) {
    cout << "\n" << title << "\n" << string(SEARCH_WIDTH, '-') << "\n";
    cout << left << "| " << setw(4) << "ID" << " | " << setw(5) << "Age" << " | " << setw(15) << "Care Type"
         << " | " << setw(16) << "Length of Stay" << " | " << setw(11) << "Base Cost" << " | " << setw(12)
         << "Days Visit" << " | " << setw(23) << "Total Medical Cost (RM)" << " |\n";
    cout << string(SEARCH_WIDTH, '-') << "\n";
}

void printRow(const ListPatient& p) {
    cout << left << "| " << setw(4) << p.patientID << " | " << setw(5) << p.age << " | " << setw(15) << p.careType
         << " | " << setw(16) << p.lengthOfStay << " | " << setw(11) << p.baseCostPerHour << " | " << setw(12)
         << p.daysVisitsPerYear << " | " << setw(23) << listNumberText(p.totalCost, 2) << " |\n";
}

// Searches
int searchAgeGroup(const PatientNode* head, int minAge, int maxAge, bool sorted, bool ascending, int& comparisons,
                   bool show) {
    int found = 0;
    comparisons = 0;
    const PatientNode* current = head;
    while (current != NULL) {
        comparisons++;
        int age = current->data.age;
        if (age >= minAge && age <= maxAge) {
            found++;
            if (show) printRow(current->data);
        } else if (sorted && ascending && age > maxAge) {
            break;
        } else if (sorted && !ascending && age < minAge) {
            break;
        }
        current = current->next;
    }
    return found;
}

int searchCareType(const PatientNode* head, string& careType, int& comparisons, bool show) {
    int found = 0;
    comparisons = 0;
    const PatientNode* current = head;
    while (current != NULL) {
        comparisons++;
        if (current->data.careType == careType) {
            found++;
            if (show) printRow(current->data);
        }
        current = current->next;
    }
    return found;
}

int searchLOS(const PatientNode* head, int hours, bool sorted, bool ascending, int& comparisons, bool show) {
    int found = 0;
    comparisons = 0;
    const PatientNode* current = head;
    while (current != NULL) {
        comparisons++;
        if (current->data.lengthOfStay > hours) {
            found++;
            if (show) printRow(current->data);
        } else if (sorted && !ascending) {
            break;
        }
        current = current->next;
    }
    return found;
}

int runSearch(const PatientNode* head, SearchQuery& q, bool sorted, bool ascending, int& comparisons, bool show) {
    if (q.type == SEARCH_AGE) {
        return searchAgeGroup(head, q.minAge, q.maxAge, sorted, ascending, comparisons, show);
    }
    if (q.type == SEARCH_CARE) {
        return searchCareType(head, q.careType, comparisons, show);
    }
    return searchLOS(head, q.hours, sorted, ascending, comparisons, show);
}

// Timing: warm up first, then average of SEARCH_REPEATS runs
double averageTime(const PatientNode* head, SearchQuery& q, bool sorted, bool ascending, int& found,
                   int& comparisons) {
    int ignore = 0;
    for (int r = 0; r < SEARCH_REPEATS; r++) {
        found = runSearch(head, q, sorted, ascending, comparisons, false);
    }
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    for (int r = 0; r < SEARCH_REPEATS; r++) {
        runSearch(head, q, sorted, ascending, ignore, false);
    }
    chrono::steady_clock::time_point stop = chrono::steady_clock::now();
    return (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count() / SEARCH_REPEATS;
}

// One dataset: matching records + unsorted vs sorted performance
void searchDataset(PatientList& list, string name, SearchQuery& q) {
    int sortField = LIST_SORT_BY_AGE;
    string field = "Age";
    if (q.type == SEARCH_LOS) {
        sortField = LIST_SORT_BY_DURATION;
        field = "LOS";
    }
    PatientList asc(list);
    asc.mergeSort(sortField, true);
    PatientList desc(list);
    desc.mergeSort(sortField, false);
    int comparisons = 0;
    printHeader("=== " + name + " - Search: " + queryText(q) + " ===");
    int found = runSearch(asc.getHead(), q, true, true, comparisons, true);
    if (found == 0) {
        cout << left << "| " << setw(SEARCH_WIDTH - 4) << "(no matching records)" << " |\n";
    }
    cout << string(SEARCH_WIDTH, '-') << "\n";
    cout << "Showing " << found << " matching records (ordered by " << PatientList::sortFieldName(sortField) << ")"
         << endl;

    PatientList* lists[3] = { &list, &asc, &desc };
    string labels[3] = { "Unsorted", "Sorted (" + field + " asc)", "Sorted (" + field + " desc)" };
    int rows = 3;
    if (q.type == SEARCH_CARE) {
        rows = 2;
    }
    cout << "\n--- " << name << " - Search Performance: " << queryText(q) << " ---\n" << string(79, '-') << "\n";
    cout << left << "| " << setw(17) << "List" << " | " << setw(6) << "Found" << " | " << setw(11) << "Comparisons"
         << " | " << setw(13) << "Avg Time (ns)" << " | " << setw(16) << "Extra Memory (B)" << " |\n";
    cout << string(79, '-') << "\n";
    for (int i = 0; i < rows; i++) {
        double ns = averageTime(lists[i]->getHead(), q, i > 0, i != 2, found, comparisons);
        cout << "| " << setw(17) << labels[i] << " | " << setw(6) << found << " | " << setw(11) << comparisons
             << " | " << setw(13) << listNumberText(ns, 0) << " | " << setw(16)
             << sizeof(PatientNode*) + 2 * sizeof(int) << " |\n";
    }
    cout << string(79, '-') << "\n";
    cout << "List memory: " << list.getCount() << " nodes x " << sizeof(PatientNode) << " B = " << list.nodeBytes()
         << " B (next pointers alone: " << list.getCount() * sizeof(PatientNode*) << " B)" << endl;
}

// Menu
int readNumber() {
    int number;
    if (!(cin >> number)) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    cin.ignore(10000, '\n');
    return number;
}

int askQuery(SearchQuery& q) {
    q.minAge = 0;
    q.maxAge = 0;
    q.careType = "";
    q.hours = 0;
    cout << "\n===== SEARCH BY =====" << endl;
    cout << "1. Age group" << endl;
    cout << "2. Care type" << endl;
    cout << "3. Visit duration (LOS > hours)" << endl;
    cout << "0. Back" << endl;
    cout << "Criterion: ";
    q.type = readNumber();
    if (q.type == 0) {
        return 0;
    }
    if (q.type == SEARCH_AGE) {
        cout << "\n===== AGE GROUP =====" << endl;
        for (int g = 0; g < GROUP_COUNT; g++) {
            string range = to_string(GROUP_MIN[g]) + "-" + to_string(GROUP_MAX[g]);
            cout << g + 1 << ". " << left << setw(8) << range << GROUP_NAME[g] << endl;
        }
        cout << "Group: ";
        int choice = readNumber();
        if (choice < 1 || choice > GROUP_COUNT) {
            cout << "Invalid group, try again." << endl;
            return -1;
        }
        q.minAge = GROUP_MIN[choice - 1];
        q.maxAge = GROUP_MAX[choice - 1];
    } else if (q.type == SEARCH_CARE) {
        cout << "\n===== CARE TYPE =====" << endl;
        for (int t = 0; t < CARE_COUNT; t++) {
            cout << t + 1 << ". " << CARE_TYPES[t] << endl;
        }
        cout << "Care type: ";
        int choice = readNumber();
        if (choice < 1 || choice > CARE_COUNT) {
            cout << "Invalid care type, try again." << endl;
            return -1;
        }
        q.careType = CARE_TYPES[choice - 1];
    } else if (q.type == SEARCH_LOS) {
        cout << "Show patients who stayed MORE than how many hours? ";
        q.hours = readNumber();
        if (q.hours < 0) {
            cout << "Invalid hours, try again." << endl;
            return -1;
        }
    } else {
        cout << "Invalid criterion, try again." << endl;
        return -1;
    }
    return 1;
}

bool loadLists(PatientList& listA, PatientList& listB, PatientList& listC) {
    if (listA.getCount() == 0 && !listA.loadFromFile("dataset1facility_a.csv")) return false;
    if (listB.getCount() == 0 && !listB.loadFromFile("dataset2facility_b.csv")) return false;
    if (listC.getCount() == 0 && !listC.loadFromFile("dataset3facility_c.csv")) return false;
    return true;
}

void runListSearchMenu(PatientList& listA, PatientList& listB, PatientList& listC) {
    int status;
    do {
        SearchQuery q;
        status = askQuery(q);
        if (status == 1 && loadLists(listA, listB, listC)) {
            searchDataset(listA, "Dataset A", q);
            searchDataset(listB, "Dataset B", q);
            searchDataset(listC, "Dataset C", q);
        }
    } while (status != 0);
}

#endif
