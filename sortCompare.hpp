#ifndef SORT_COMPARE_HPP
#define SORT_COMPARE_HPP

// run insertion sort and merge sort on the array and on the singly linked list
// for one dataset, and print them side by side (time complexity, time, comparisons and memory)
inline void displaySortComparison(const ArraySort& arrayData, const PatientList& listData,                                   const string& datasetName, int field, bool ascending) {
    const int repeats = 200;
    const int ruleWidth = 102;
    int n = arrayData.getCount();

    cout << "\n=== " << datasetName << " - Array vs Singly Linked List ===" << endl;
    cout << string(ruleWidth, '-') << "\n";
    cout << left << "| " << setw(14) << "Algorithm"
         << " | " << setw(18) << "Structure"
         << " | " << setw(15) << "Time Complexity"
         << " | " << setw(13) << "Avg Time (ns)"
         << " | " << setw(11) << "Comparisons"
         << " | " << setw(16) << "Memory Usage (B)" << " |\n";
    cout << string(ruleWidth, '-') << "\n";

    for (int algorithm = 0; algorithm < 2; algorithm++) {
        bool useMerge = (algorithm == 1);
        string algorithmName = useMerge ? "Merge Sort" : "Insertion Sort";
        string complexity = useMerge ? "O(n log n)" : "O(n^2)";

        // Array
        SortStats arrayStats;
        double arrayNs = averageSortNanoseconds(arrayData, useMerge, field, ascending, repeats, arrayStats);
        size_t arrayExtra = useMerge ? sizeof(Patient) * n : sizeof(Patient);   // buffer of n records, or one key
        cout << "| " << setw(14) << algorithmName
             << " | " << setw(18) << "Array"
             << " | " << setw(15) << complexity
             << " | " << setw(13) << numberText(arrayNs, 0)
             << " | " << setw(11) << arrayStats.comparisons
             << " | " << setw(16) << (arrayData.dataBytes() + arrayExtra) << " |\n";

        // Singly linked list
        ListSortStats listStats;
        double listNs = averageListSortNanoseconds(listData, useMerge, field, ascending, repeats, listStats);
        size_t listExtra = useMerge ? (size_t)listStats.maxDepth * 6 * sizeof(void*) : 3 * sizeof(void*);
        cout << "| " << setw(14) << algorithmName
             << " | " << setw(18) << "Singly Linked List"
             << " | " << setw(15) << complexity
             << " | " << setw(13) << numberText(listNs, 0)
             << " | " << setw(11) << listStats.comparisons
             << " | " << setw(16) << (listData.nodeBytes() + listExtra) << " |\n";
    }
    cout << string(ruleWidth, '-') << "\n";
}

#endif
