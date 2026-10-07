#ifndef LINKED_LIST_SEARCH_HPP
#define LINKED_LIST_SEARCH_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
using namespace std;

// Search criteria (also used by searchCompare.hpp)
const int LIST_SEARCH_AGE_GROUP = 1;
const int LIST_SEARCH_CARE_TYPE = 2;
const int LIST_SEARCH_LOS = 3;
const int LIST_SEARCH_REPEATS = 200;
const int LIST_SEARCH_ROUNDS = 5;

const int GROUP_COUNT = 5;
const int GROUP_MIN[GROUP_COUNT] = { 0, 18, 26, 46, 61 };
const int GROUP_MAX[GROUP_COUNT] = { 17, 25, 45, 60, 100 };
const string GROUP_NAME[GROUP_COUNT] = { "Pediatrics & Adolescents", "Young Adults / University Students",
    "Working Adults (Early Career)", "Working Adults (Late Career)", "Senior Citizens / Geriatric Care" };

const int CARE_COUNT = 6;
const string CARE_TYPES[CARE_COUNT] = { "Emergency", "Outpatient", "Inpatient", "Vaccination", "Rehabilitation",
    "Routine Checkup" };

const int SEARCH_WIDTH = 101;

struct ListSearchQuery {
    int type;
    int minAge;
    int maxAge;
    string careType;
    int hours;
};

string listSearchCriteriaText(const ListSearchQuery& q) {
    if (q.type == LIST_SEARCH_AGE_GROUP) {
        return "Age " + to_string(q.minAge) + "-" + to_string(q.maxAge);
    }
    if (q.type == LIST_SEARCH_CARE_TYPE) {
        return "Care Type = " + q.careType;
    }
    return "LOS > " + to_string(q.hours) + " hours";
}

// Record table
void printHeader(const string& title) {
    cout << "\n" << title << "\n" << string(SEARCH_WIDTH, '-') << "\n";
    cout << left << "| " << setw(5) << "Age" << " | " << setw(15) << "Care Type" << " | " << setw(16)
         << "Length of Stay" << " | " << setw(11) << "Base Cost" << " | " << setw(12) << "Days Visit" << " | "
         << setw(23) << "Total Medical Cost (RM)" << " |\n";
    cout << string(SEARCH_WIDTH, '-') << "\n";
}

void printRow(const ListPatient& p) {
    cout << left << "| " << setw(5) << p.age << " | " << setw(15) << p.careType << " | " << setw(16)
         << p.lengthOfStay << " | " << setw(11) << p.baseCostPerHour << " | " << setw(12) << p.daysVisitsPerYear
         << " | " << setw(23) << listNumberText(p.totalCost, 2) << " |\n";
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

int searchCareType(const PatientNode* head, const string& careType, int& comparisons, bool show) {
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

int runSearch(const PatientNode* head, const ListSearchQuery& q, bool sorted, bool ascending, int& comparisons,
              bool show) {
    if (q.type == LIST_SEARCH_AGE_GROUP) {
        return searchAgeGroup(head, q.minAge, q.maxAge, sorted, ascending, comparisons, show);
    }
    if (q.type == LIST_SEARCH_CARE_TYPE) {
        return searchCareType(head, q.careType, comparisons, show);
    }
    return searchLOS(head, q.hours, sorted, ascending, comparisons, show);
}

// Timing (same method as arraySearch.hpp): best of 5 rounds, each round runs for at least 20 ms
double averageListSearchNanoseconds(const PatientNode* head, const ListSearchQuery& q, bool sorted, bool ascending,
                                    int repeats, int& found, int& comparisons) {
    found = runSearch(head, q, sorted, ascending, comparisons, false);
    volatile int sink = 0;
    int ignored = 0;
    double best = -1;
    int runs = repeats;
    for (int round = 0; round < LIST_SEARCH_ROUNDS; round++) {
        double elapsed = 0;
        while (true) {
            chrono::steady_clock::time_point start = chrono::steady_clock::now();
            for (int r = 0; r < runs; r++) {
                sink = runSearch(head, q, sorted, ascending, ignored, false);
            }
            chrono::steady_clock::time_point stop = chrono::steady_clock::now();
            elapsed = (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
            if (elapsed >= 20000000.0 || runs >= 100000000) {
                break;
            }
            runs *= 2;
        }
        double average = elapsed / runs;
        if (best < 0 || average < best) {
            best = average;
        }
    }
    (void)sink;
    return best;
}

// One dataset: matching records + unsorted vs sorted performance
void searchDataset(const PatientList& list, const string& name, const ListSearchQuery& q) {
    int sortField = LIST_SORT_BY_AGE;
    string field = "Age";
    if (q.type == LIST_SEARCH_LOS) {
        sortField = LIST_SORT_BY_DURATION;
        field = "LOS";
    }
    string criteria = listSearchCriteriaText(q);
    PatientList asc(list);
    asc.mergeSort(sortField, true);
    PatientList desc(list);
    desc.mergeSort(sortField, false);
    int comparisons = 0;
    printHeader("=== " + name + " - Search: " + criteria + " ===");
    int shown = runSearch(asc.getHead(), q, true, true, comparisons, true);
    if (shown == 0) {
        cout << left << "| " << setw(SEARCH_WIDTH - 4) << "(no matching records)" << " |\n";
    }
    cout << string(SEARCH_WIDTH, '-') << "\n";
    cout << "Showing " << shown << " matching records (ordered by " << PatientList::sortFieldName(sortField) << ")"
         << endl;

    const PatientList* lists[3] = { &list, &asc, &desc };
    string labels[3] = { "Unsorted", "Sorted (" + field + " asc)", "Sorted (" + field + " desc)" };
    int rows = 3;
    if (q.type == LIST_SEARCH_CARE_TYPE) {
        rows = 2;
    }
    size_t memory = list.nodeBytes() + sizeof(const PatientNode*) + 2 * sizeof(int);
    bool sameResult = true;
    cout << "\n--- " << name << " - Search Performance: " << criteria << " ---\n" << string(79, '-') << "\n";
    cout << left << "| " << setw(17) << "List" << " | " << setw(6) << "Found" << " | " << setw(11) << "Comparisons"
         << " | " << setw(13) << "Avg Time (ns)" << " | " << setw(16) << "Memory Usage (B)" << " |\n";
    cout << string(79, '-') << "\n";
    for (int i = 0; i < rows; i++) {
        int found = 0;
        double ns = averageListSearchNanoseconds(lists[i]->getHead(), q, i > 0, i != 2, LIST_SEARCH_REPEATS, found,
                                                 comparisons);
        if (found != shown) {
            sameResult = false;
        }
        cout << "| " << setw(17) << labels[i] << " | " << setw(6) << found << " | " << setw(11) << comparisons
             << " | " << setw(13) << listNumberText(ns, 0) << " | " << setw(16) << memory << " |\n";
    }
    cout << string(79, '-') << "\n";
    if (!sameResult) {
        cout << "WARNING: the lists returned different counts - check the sort order" << endl;
    }
    cout << "List memory: " << list.getCount() << " nodes x " << sizeof(PatientNode) << " B = " << list.nodeBytes()
         << " B (next pointers alone: " << list.getCount() << " x " << sizeof(PatientNode*) << " B = "
         << list.getCount() * sizeof(PatientNode*) << " B)" << endl;
    cout << "Avg Time = mean of one search, best of " << LIST_SEARCH_ROUNDS
         << " rounds, each repeated for 20+ ms; sort time not included" << endl;
    if (q.type == LIST_SEARCH_CARE_TYPE) {
        cout << "Care Type is not a sort field, so the Age-sorted list cannot stop early" << endl;
    }
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

int chooseListSearchQuery(ListSearchQuery& query, const string& title) {
    query.minAge = 0;
    query.maxAge = 0;
    query.careType = "";
    query.hours = 0;
    cout << "\n===== " << title << " =====" << endl;
    cout << "1. Age group" << endl;
    cout << "2. Care type" << endl;
    cout << "3. Visit duration (LOS > hours)" << endl;
    cout << "0. Back" << endl;
    cout << "Criterion: ";
    query.type = readNumber();
    if (query.type == 0) {
        return 0;
    }
    if (query.type == LIST_SEARCH_AGE_GROUP) {
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
        query.minAge = GROUP_MIN[choice - 1];
        query.maxAge = GROUP_MAX[choice - 1];
    } else if (query.type == LIST_SEARCH_CARE_TYPE) {
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
        query.careType = CARE_TYPES[choice - 1];
    } else if (query.type == LIST_SEARCH_LOS) {
        cout << "Show patients who stayed MORE than how many hours? ";
        query.hours = readNumber();
        if (query.hours < 0) {
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
        ListSearchQuery query;
        status = chooseListSearchQuery(query, "SEARCH BY");
        if (status == 1 && loadLists(listA, listB, listC)) {
            searchDataset(listA, "Dataset A", query);
            searchDataset(listB, "Dataset B", query);
            searchDataset(listC, "Dataset C", query);
        }
    } while (status != 0);
}

#endif
