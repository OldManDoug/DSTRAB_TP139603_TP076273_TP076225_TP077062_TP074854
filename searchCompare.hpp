#ifndef SEARCH_COMPARE_HPP
#define SEARCH_COMPARE_HPP

// Converts list search query to matchi array search query struct
inline ArraySearchQuery toArrayQuery(const ListSearchQuery& q) {
    ArraySearchQuery arrayQuery;
    arrayQuery.type = q.type;
    arrayQuery.minAge = q.minAge;
    arrayQuery.maxAge = q.maxAge;
    arrayQuery.careType = q.careType;
    arrayQuery.hours = q.hours;
    return arrayQuery;
}

// Side by side performance table for Array and Singly Linked List comparison
inline void displaySearchComparison(const ArraySort& arrayData, const PatientList& listData,
                                    const string& datasetName, const ListSearchQuery& q) {
    const int ruleWidth = 109;
    bool byLOS = (q.type == LIST_SEARCH_LOS);
    ArraySearchQuery arrayQuery = toArrayQuery(q);

    // Sorted copies for comparison
    ArraySort sortedArray(arrayData);
    sortedArray.mergeSort(byLOS ? SORT_BY_DURATION : SORT_BY_AGE, true);

    PatientList sortedList(listData);
    sortedList.mergeSort(byLOS ? LIST_SORT_BY_DURATION : LIST_SORT_BY_AGE, true);

    // Local stack memory footprint per search
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
        // Binary search only used on sorted arrays for numeric fields (Age / LOS)
        bool binary = sorted && q.type != LIST_SEARCH_CARE_TYPE;
        
        string arrayName = binary ? "Binary (sorted)" : (sorted ? "Linear (sorted)" : "Linear (unsorted)");
        string listName = sorted ? "Linear (sorted)" : "Linear (unsorted)";

        int found = 0, comparisons = 0;

        // ArraySearch execution
        const ArraySort& arraySource = sorted ? sortedArray : arrayData;
        double arrayNs = averageArraySearchNanoseconds(arraySource, arrayQuery, sorted, true, ARRAY_SEARCH_REPEATS,
                                                       found, comparisons);
        cout << "| " << setw(17) << arrayName
             << " | " << setw(18) << "Array"
             << " | " << setw(15) << (binary ? "O(log n + k)" : "O(n)")
             << " | " << setw(13) << numberText(arrayNs, 0)
             << " | " << setw(11) << comparisons
             << " | " << setw(16) << (arrayData.dataBytes() + arrayWorking) << " |\n";

        // Singly linked list search execution
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

#endif // SEARCH_COMPARE_HPP