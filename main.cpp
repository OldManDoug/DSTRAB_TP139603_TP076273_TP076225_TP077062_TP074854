#include<io.h>
#include<iostream> //libraries
#include "lists.hpp" //include header file, which is where your main code is. GeeksforGeeks. (2020, July 23). Header Files in C++. GeeksforGeeks. https://www.geeksforgeeks.org/cpp/header-files-in-c-c-with-examples/
#include <string>
#include "listdatasetab.hpp"
#include "array.hpp"
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

// LoadAndShow - load one CSV into a dataset, then print its table
void loadAndShow(ArrayData& dataset, const string& title, const string& filename) {
    cout << "\n" << title << endl;
    if (dataset.loadFromFile(filename)) {
        dataset.display();
    }
}

// LoadIfEmpty - load a dataset quietly (no table) when it has no records yet; false if the file cannot be read
bool loadIfEmpty(ArrayData& dataset, const string& filename) {
    if (dataset.getCount() > 0) {
        return true;
    }
    return dataset.loadFromFile(filename);
}

// EnsureAllLoaded - make sure all three datasets are in memory, so any menu option can be chosen first
bool ensureAllLoaded(ArrayData& datasetA, ArrayData& datasetB, ArrayData& datasetC) {
    bool loadedA = loadIfEmpty(datasetA, "dataset1facility_a.csv");
    bool loadedB = loadIfEmpty(datasetB, "dataset2facility_b.csv");
    bool loadedC = loadIfEmpty(datasetC, "dataset3facility_c.csv");
    return loadedA && loadedB && loadedC;
}

// RunSortingExperiment - sort menu: pick a field and order, time insertion sort and merge sort on all datasets,
// then show the menu again until the user chooses Back
void runSortingExperiment(ArrayData& datasetA, ArrayData& datasetB, ArrayData& datasetC) {
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

void runArrayMenu(ArrayData& datasetA, ArrayData& datasetB, ArrayData& datasetC) {
    int choice;
    do {
        cout << "\n===== ARRAY MENU =====" << endl;
        cout << "1. Display all datasets (A, B, C)" << endl;
        cout << "2. Age group and billing analysis" << endl;
        cout << "3. Healthcare expenditure analysis" << endl;
        cout << "4. Sorting experiments (insertion sort vs merge sort)" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        choice = readChoice();

        switch (choice) {
            case 1:
                loadAndShow(datasetA, "Dataset A details", "dataset1facility_a.csv");
                loadAndShow(datasetB, "Dataset B details", "dataset2facility_b.csv");
                loadAndShow(datasetC, "Dataset C details", "dataset3facility_c.csv");
                break;
            case 2:
                if (ensureAllLoaded(datasetA, datasetB, datasetC)) {
                    datasetA.displayAgeGroupAnalysis("Dataset A");
                    datasetB.displayAgeGroupAnalysis("Dataset B");
                    datasetC.displayAgeGroupAnalysis("Dataset C");
                }
                break;
            case 3:
                if (ensureAllLoaded(datasetA, datasetB, datasetC)) {
                    datasetA.displayExpenditure("Dataset A");
                    datasetB.displayExpenditure("Dataset B");
                    datasetC.displayExpenditure("Dataset C");
                    displayDatasetComparison(datasetA, datasetB, datasetC);
                }
                break;
            case 4:
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

// ---------------- MAIN MENU ----------------

int main() {
    ArrayData datasetA, datasetB, datasetC;

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
            case 2: runLinkedListDemo(); break;
            case 0: cout << "Goodbye." << endl; break;
            default: cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
//skeleton [prpgram]