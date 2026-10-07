#ifndef SEARCH_COMPARE_HPP
#define SEARCH_COMPARE_HPP

// Include after arraySort.hpp, arraySearch.hpp, lists.hpp and LinkedListSearch.hpp.
// The array rows come from the array search in arraySearch.hpp and the list rows from LinkedListSearch.hpp,
// so every number here comes from the same search code as the two search experiments.

// ToArrayQuery - turn a linked list search query into the equivalent array search query
inline ArraySearchQuery toArrayQuery(const ListSearchQuery& q) {
    ArraySearchQuery arrayQuery;
    arrayQuery.type = q.type;           // both use 1 = age group, 2 = care type, 3 = visit duration
    arrayQuery.minAge = q.minAge;
    arrayQuery.maxAge = q.maxAge;
    arrayQuery.careType = q.careType;
    arrayQuery.hours = q.hours;
    return arrayQuery;
}

// DisplaySearchComparison - run the same search on the array and on the singly linked list, unsorted and sorted,
// and print time complexity, time, comparisons and memory side by side
inline void displaySearchComparison(const ArraySort& arrayData, const PatientList& listData,
                                    const string& datasetName, const ListSearchQuery& q) {
    const int ruleWidth = 109;
    bool byLOS = (q.type == LIST_SEARCH_LOS);
    ArraySearchQuery arrayQuery = toArrayQuery(q);

    // Sorted copies (age for the age group search, visit duration for the duration search)
    ArraySort sortedArray(arrayData);
    sortedArray.mergeSort(byLOS ? SORT_BY_DURATION : SORT_BY_AGE, true);
    PatientList sortedList(listData);
    sortedList.mergeSort(byLOS ? LIST_SORT_BY_DURATION : LIST_SORT_BY_AGE, true);

    // Working memory of one search: a pointer and two ints (same formula as the two search experiments)
    size_t arrayWorking = sizeof(const Patient*) + 2 * sizeof(int);
    size_t listWorking = sizeof(const PatientNode*) + 2 * sizeof(int);

    cout << "\n=== " << datasetName << " - Array vs Singly Linked List (" << listSearchCriteriaText(q) << ") ===" << endl;
    cout << string(ruleWidth, '-') << "\n";
    cout << left << "| " << setw(17) << "Algorithm"
         << " | " << setw(18) << "Structure"
         << " | " << setw(15) << "Time Complexity"
         << " | " << setw(13) << "Avg Time (ns)"
         << " | " << setw(11) << "Comparisons"
         << " | " << setw(16) << "Memory Usage (B)" << " |\n";
    cout << string(ruleWidth, '-') << "\n";

    for (int pass = 0; pass < 2; pass++) {
        bool sorted = (pass == 1);
        // On sorted data the array uses binary search to find where the matches start.
        // Care type is not a sort field, so that search stays linear.
        bool binary = sorted && q.type != LIST_SEARCH_CARE_TYPE;
        string arrayName = binary ? "Binary (sorted)" : (sorted ? "Linear (sorted)" : "Linear (unsorted)");
        string listName = sorted ? "Linear (sorted)" : "Linear (unsorted)";
        int found = 0;
        int comparisons = 0;

        // Array
        const ArraySort& arraySource = sorted ? sortedArray : arrayData;
        double arrayNs = averageArraySearchNanoseconds(arraySource, arrayQuery, sorted, true, ARRAY_SEARCH_REPEATS,
                                                       found, comparisons);
        cout << "| " << setw(17) << arrayName
             << " | " << setw(18) << "Array"
             << " | " << setw(15) << (binary ? "O(log n + k)" : "O(n)")
             << " | " << setw(13) << numberText(arrayNs, 0)
             << " | " << setw(11) << comparisons
             << " | " << setw(16) << (arrayData.dataBytes() + arrayWorking) << " |\n";

        // Singly linked list
        const PatientList& listSource = sorted ? sortedList : listData;
        double listNs = averageListSearchNanoseconds(listSource.getHead(), q, sorted, true, LIST_SEARCH_REPEATS,
                                                     found, comparisons);
        cout << "| " << setw(17) << listName
             << " | " << setw(18) << "Singly Linked List"
             << " | " << setw(15) << "O(n)"
             << " | " << setw(13) << numberText(listNs, 0)
             << " | " << setw(11) << comparisons
             << " | " << setw(16) << (listData.nodeBytes() + listWorking) << " |\n";
    }
    cout << string(ruleWidth, '-') << "\n";
}

#endif
