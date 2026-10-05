#include<io.h>
#include<iostream> //libraries
#include "lists.hpp" //include header file, which is where your main code is. GeeksforGeeks. (2020, July 23). Header Files in C++. GeeksforGeeks. https://www.geeksforgeeks.org/cpp/header-files-in-c-c-with-examples/
#include <string>
#include "listdatasetab.hpp"
#include "arrayDataSet.hpp"
#include "arraySort.hpp"
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

// (loading and displaying a dataset is in arrayDataSet.hpp; analysis and sorting are in arraySort.hpp)

// RunSortingExperiment - sort menu: pick a field and order, time insertion sort and merge sort on all datasets,
// then show the menu again until the user chooses Back
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
            case 0: break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
}

// ---------------- LINKED LIST PART (teammate's demo, moved here unchanged) ----------------

void runLinkedListDemo() {

//IMPLEMENT AS A LIST - frmt slides learn dei.
// Definition of a Node in a singly linked list - from GeeksforGeeks
implements();
 //creater();
 check();
 days();
 
cout << "--- Double Linked List Contents ---" << endl;
//age();
clears();
implementing();
DoublyLinkedList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);

    list.print_forward();  // Outputs: 5 <-> 10 <-> 20 <-> 30 <-> nullptr
    list.print_backward(); // Outputs: 30 <-> 20 <-> 10 <-> 5 <-> nullptr

    list.remove(20);
    list.print_forward();  // Outputs: 5 <-> 10 <-> 30 <-> nullptr

    list.pop_front();
    list.pop_back();
    list.print_forward();  // Outputs: 10 <-> nullptr

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
        cout << "1. Sorting experiments (insertion sort vs merge sort)" << endl;
        cout << "2. Linked list demo (teammates)" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        choice = readChoice();

        switch (choice) {
            case 1: runListSortingExperiment(listA, listB, listC); break;
            case 2: runLinkedListDemo(); break;
            case 0: break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);
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
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        choice = readChoice();

        switch (choice) {
            case 1: runArrayMenu(datasetA, datasetB, datasetC); break;
            case 2: runLinkedListMenu(listA, listB, listC); break;
            case 0: cout << "Goodbye." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
//skeleton [prpgram]