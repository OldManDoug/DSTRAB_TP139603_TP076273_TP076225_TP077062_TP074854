#include<io.h>
#include<iostream> //libraries
#include "lists.hpp" //include header file, which is where your main code is. GeeksforGeeks. (2020, July 23). Header Files in C++. GeeksforGeeks. https://www.geeksforgeeks.org/cpp/header-files-in-c-c-with-examples/
#include <string>
#include "arrayDataSet.hpp"
#include "arraySort.hpp"
#include "arraySearch.hpp"
#include "sortCompare.hpp"
#include "LinkedListSearch.hpp"
#include "searchCompare.hpp"
#include <ctime>
using namespace std; // to avoid repeating std:: before every standard library function

// ---------------- MENU HELPERS ----------------

// ReadChoice - read one menu number; returns -1 if the input is not a number
int readChoice() {
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    cin.ignore(10000, '\n');
    return choice;
}

// ---------------- ARRAY PART ----------------

// loading and displaying a dataset is in arrayDataSet.hpp
// analysis and sorting are in arraySort.hpp

// runSortingExperiment - sort menu: pick a field and order, time insertion sort and merge sort on all datasets,
void runSortingExperiment(ArraySort& datasetA, ArraySort& datasetB, ArraySort& datasetC) {
    int field;
    do {
        cout << "\n===== SORT BY =====" << endl;
        cout << "1. Age" << endl;
        cout << "2. Visit Duration (Length of Stay)" << endl;
        cout << "3. Total Medical Cost" << endl;
        cout << "0. Back" << endl;
        cout << "Field: ";
        field = readChoice();

        if (field == 0) {
            break;
        }
        if (field < 1 || field > 3) {
            cout << "Invalid field, try again." << endl;
            continue;
        }

        cout << "\n===== ORDER =====" << endl;
        cout << "1. Ascending" << endl;
        cout << "2. Descending" << endl;
        cout << "Order: ";
        int order = readChoice();
        if (order != 1 && order != 2) {
            cout << "Invalid order, try again." << endl;
            continue;
        }
        if (!ensureAllLoaded(datasetA, datasetB, datasetC)) {
            return;
        }

        bool ascending = (order == 1);
        displaySortExperiment(datasetA, "Dataset A", field, field, ascending);
        displaySortExperiment(datasetB, "Dataset B", field, field, ascending);
        displaySortExperiment(datasetC, "Dataset C", field, field, ascending);
    } while (field != 0);
}

void runArrayMenu(ArraySort& datasetA, ArraySort& datasetB, ArraySort& datasetC) {
    int choice;
    do {
        cout << "\n===== ARRAY MENU =====" << endl;
        cout << "1. Display Dataset A" << endl;
        cout << "2. Display Dataset B" << endl;
        cout << "3. Display Dataset C" << endl;
        cout << "4. Age group and billing analysis" << endl;
        cout << "5. Healthcare expenditure analysis" << endl;
        cout << "6. Sorting experiments (insertion sort vs merge sort)" << endl;
        cout << "7. Searching experiments (unsorted vs sorted)" << endl;
        cout << "8. Clinical insights" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        choice = readChoice();

        switch (choice) {
            case 1:
                showDataset(datasetA, "Dataset A details", "dataset1facility_a.csv");
                break;
            case 2:
                showDataset(datasetB, "Dataset B details", "dataset2facility_b.csv");
                break;
            case 3:
                showDataset(datasetC, "Dataset C details", "dataset3facility_c.csv");
                break;
            case 4:
                if (ensureAllLoaded(datasetA, datasetB, datasetC)) {
                    datasetA.displayAgeGroupAnalysis("Dataset A");
                    datasetB.displayAgeGroupAnalysis("Dataset B");
                    datasetC.displayAgeGroupAnalysis("Dataset C");
                }
                break;
            case 5:
                if (ensureAllLoaded(datasetA, datasetB, datasetC)) {
                    datasetA.displayExpenditure("Dataset A");
                    datasetB.displayExpenditure("Dataset B");
                    datasetC.displayExpenditure("Dataset C");
                    displayDatasetComparison(datasetA, datasetB, datasetC);
                }
                break;
            case 6:
                runSortingExperiment(datasetA, datasetB, datasetC);
                break;
            case 7:
                runArraySearchMenu(datasetA, datasetB, datasetC);
                break;
            case 8:
                if (ensureAllLoaded(datasetA, datasetB, datasetC)) {
                    displayClinicalInsights(datasetA, datasetB, datasetC);
                }
                break;
            case 0: break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

// ---------------- LINKED LIST SORT PART ----------------

bool loadListIfEmpty(PatientList& list, const string& filename) {
    if (list.getCount() > 0) {
        return true;
    }
    return list.loadFromFile(filename);
}

bool ensureAllListsLoaded(PatientList& listA, PatientList& listB, PatientList& listC) {
    bool loadedA = loadListIfEmpty(listA, "dataset1facility_a.csv");
    bool loadedB = loadListIfEmpty(listB, "dataset2facility_b.csv");
    bool loadedC = loadListIfEmpty(listC, "dataset3facility_c.csv");
    return loadedA && loadedB && loadedC;
}

void runListSortingExperiment(PatientList& listA, PatientList& listB, PatientList& listC) {
    int field;
    do {
        cout << "\n===== SORT BY =====" << endl;
        cout << "1. Age" << endl;
        cout << "2. Visit Duration (Length of Stay)" << endl;
        cout << "3. Total Medical Cost" << endl;
        cout << "0. Back" << endl;
        cout << "Field: ";
        field = readChoice();

        if (field == 0) {
            break;
        }
        if (field < 1 || field > 3) {
            cout << "Invalid field, try again." << endl;
            continue;
        }

        cout << "\n===== ORDER =====" << endl;
        cout << "1. Ascending" << endl;
        cout << "2. Descending" << endl;
        cout << "Order: ";
        int order = readChoice();
        if (order != 1 && order != 2) {
            cout << "Invalid order, try again." << endl;
            continue;
        }
        if (!ensureAllListsLoaded(listA, listB, listC)) {
            return;
        }

        bool ascending = (order == 1);
        displayListSortExperiment(listA, "Dataset A", field, field, ascending);
        displayListSortExperiment(listB, "Dataset B", field, field, ascending);
        displayListSortExperiment(listC, "Dataset C", field, field, ascending);
    } while (field != 0);
}

void runLinkedListMenu(PatientList& listA, PatientList& listB, PatientList& listC) {
    int choice;
    do {
        cout << "\n===== LINKED LIST MENU =====" << endl;
        cout << "1. Display Dataset A" << endl;
        cout << "2. Display Dataset B" << endl;
        cout << "3. Display Dataset C" << endl;
        cout << "4. Age group and billing analysis" << endl;
        cout << "5. Healthcare expenditure analysis" << endl;
        cout << "6. Sorting experiments (insertion sort vs merge sort)" << endl;
        cout << "7. Searching experiments (unsorted vs sorted)" << endl;
        cout << "8. Clinical insights" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        choice = readChoice();

        switch (choice) {
            case 1:
                if (loadListIfEmpty(listA, "dataset1facility_a.csv")) listA.display();
                break;
            case 2:
                if (loadListIfEmpty(listB, "dataset2facility_b.csv")) listB.display();
                break;
            case 3:
                if (loadListIfEmpty(listC, "dataset3facility_c.csv")) listC.display();
                break;
            case 4:
                if (ensureAllListsLoaded(listA, listB, listC)) {
                    listA.displayAgeGroupAnalysis("Dataset A");
                    listB.displayAgeGroupAnalysis("Dataset B");
                    listC.displayAgeGroupAnalysis("Dataset C");
                }
                break;
            case 5:
                if (ensureAllListsLoaded(listA, listB, listC)) {
                    listA.displayExpenditure("Dataset A");
                    listB.displayExpenditure("Dataset B");
                    listC.displayExpenditure("Dataset C");
                    displayListDatasetComparison(listA, listB, listC);
                }
                break;
            case 6: runListSortingExperiment(listA, listB, listC); break;
            case 7: runListSearchMenu(listA, listB, listC); break;
            case 8:
                if (ensureAllListsLoaded(listA, listB, listC)) {
                    displayListClinicalInsights(listA, listB, listC);
                }
                break;
            case 0: break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

// ---------------- ARRAY VS LINKED LIST COMPARISON ----------------

// RunStructureComparison - sort menu: pick a field, then compare the array and the singly linked list
// side by side on every dataset; shows the menu again until the user chooses Back
void runStructureComparison(ArraySort& datasetA, ArraySort& datasetB, ArraySort& datasetC,
                            PatientList& listA, PatientList& listB, PatientList& listC) {
    int field;
    do {
        cout << "\n===== COMPARE BY =====" << endl;
        cout << "1. Age" << endl;
        cout << "2. Visit Duration" << endl;
        cout << "3. Total Cost" << endl;
        cout << "0. Back" << endl;
        cout << "Field: ";
        field = readChoice();

        if (field == 0) {
            break;
        }
        if (field < 1 || field > 3) {
            cout << "Invalid field, try again." << endl;
            continue;
        }

        if (!ensureAllLoaded(datasetA, datasetB, datasetC) || !ensureAllListsLoaded(listA, listB, listC)) {
            return;
        }

        // The comparison always sorts in ascending order, so no order menu is needed
        displaySortComparison(datasetA, listA, "Dataset A", field, true);
        displaySortComparison(datasetB, listB, "Dataset B", field, true);
        displaySortComparison(datasetC, listC, "Dataset C", field, true);
    } while (field != 0);
}

// RunSearchComparison - search menu
void runSearchComparison(ArraySort& datasetA, ArraySort& datasetB, ArraySort& datasetC,
                         PatientList& listA, PatientList& listB, PatientList& listC) {
    int status;
    do {
        ListSearchQuery query;
        status = chooseListSearchQuery(query, "COMPARE BY");
        if (status != 1) {
            continue;
        }
        if (!ensureAllLoaded(datasetA, datasetB, datasetC) || !ensureAllListsLoaded(listA, listB, listC)) {
            return;
        }
        displaySearchComparison(datasetA, listA, "Dataset A", query);
        displaySearchComparison(datasetB, listB, "Dataset B", query);
        displaySearchComparison(datasetC, listC, "Dataset C", query);
    } while (status != 0);
}

// ---------------- MAIN MENU ----------------

int main() {
    ArraySort datasetA, datasetB, datasetC;
    PatientList listA, listB, listC;

    int choice;
    do {
        cout << "\n===== DSTR ASSIGNMENT =====" << endl;
        cout << "1. Array" << endl;
        cout << "2. Linked List" << endl;
        cout << "3. Compare Array vs Linked List (sorting)" << endl;
        cout << "4. Compare Array vs Linked List (searching)" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        choice = readChoice();

        switch (choice) {
            case 1: runArrayMenu(datasetA, datasetB, datasetC); break;
            case 2: runLinkedListMenu(listA, listB, listC); break;
            case 3: runStructureComparison(datasetA, datasetB, datasetC, listA, listB, listC); break;
            case 4: runSearchComparison(datasetA, datasetB, datasetC, listA, listB, listC); break;
            case 0: cout << "Goodbye." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
//skeleton [prpgram]