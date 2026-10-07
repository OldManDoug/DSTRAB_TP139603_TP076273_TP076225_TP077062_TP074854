#ifndef SEARCH_COMPARE_HPP
#define SEARCH_COMPARE_HPP

// Include after arraySort.hpp and LinkedListSearch.hpp

// Array linear search
inline int arrayLinearSearch(const Patient* records, int n, const ListSearchQuery& q, int& comparisons) {
    int found = 0;
    comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        const Patient& p = records[i];
        if (q.type == LIST_SEARCH_AGE_GROUP) {
            found += (p.age >= q.minAge && p.age <= q.maxAge);
        } else if (q.type == LIST_SEARCH_CARE_TYPE) {
            found += (p.careType == q.careType);
        } else {
            found += (p.lengthOfStay > q.hours);
        }
    }
    return found;
}

// Array binary search: first index whose key is above the limit
inline int arrayFirstAbove(const Patient* records, int n, bool byAge, int limit, int& comparisons) {
    int low = 0;
    int high = n;
    while (low < high) {
        int mid = (low + high) / 2;
        comparisons++;
        int key = byAge ? records[mid].age : records[mid].lengthOfStay;
        if (key > limit) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

inline int arrayBinarySearch(const Patient* records, int n, const ListSearchQuery& q, int& comparisons) {
    comparisons = 0;
    if (q.type == LIST_SEARCH_AGE_GROUP) {
        int first = arrayFirstAbove(records, n, true, q.minAge - 1, comparisons);
        int last = arrayFirstAbove(records, n, true, q.maxAge, comparisons);
        return last - first;
    }
    return n - arrayFirstAbove(records, n, false, q.hours, comparisons);
}

// Average array search time
inline double averageArraySearchNanoseconds(const Patient* records, int n, const ListSearchQuery& q, bool binary,
                                            int repeats, int& found, int& comparisons) {
    found = binary ? arrayBinarySearch(records, n, q, comparisons) : arrayLinearSearch(records, n, q, comparisons);
    volatile int sink = 0;
    int ignored = 0;
    double best = -1;
    int runs = repeats;
    for (int round = 0; round < LIST_SEARCH_ROUNDS; round++) {
        double elapsed = 0;
        for (;;) {
            chrono::steady_clock::time_point start = chrono::steady_clock::now();
            for (int r = 0; r < runs; r++) {
                sink = binary ? arrayBinarySearch(records, n, q, ignored) : arrayLinearSearch(records, n, q, ignored);
            }
            chrono::steady_clock::time_point stop = chrono::steady_clock::now();
            elapsed = (double)chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
            // A round must last at least 20 ms, otherwise a coarse clock reads 0: repeat more and measure again
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

// Comparison table
inline void displaySearchComparison(const ArraySort& arrayData, const PatientList& listData,
                                    const string& datasetName, const ListSearchQuery& q) {
    const int repeats = LIST_SEARCH_REPEATS;
    const int ruleWidth = 109;
    int n = arrayData.getCount();
    bool byLOS = (q.type == LIST_SEARCH_LOS);

    ArraySort sortedArray(arrayData);
    sortedArray.mergeSort(byLOS ? SORT_BY_DURATION : SORT_BY_AGE, true);
    PatientList sortedList(listData);
    sortedList.mergeSort(byLOS ? LIST_SORT_BY_DURATION : LIST_SORT_BY_AGE, true);

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
        bool binary = sorted && q.type != LIST_SEARCH_CARE_TYPE;
        string linearName = sorted ? "Linear (sorted)" : "Linear (unsorted)";
        int found = 0;
        int comparisons = 0;

        // Array
        const ArraySort& arraySource = sorted ? sortedArray : arrayData;
        const Patient* records = (n > 0) ? &arraySource.getAt(0) : nullptr;
        double arrayNs = averageArraySearchNanoseconds(records, n, q, binary, repeats, found, comparisons);
        cout << "| " << setw(17) << (binary ? "Binary (sorted)" : linearName)
             << " | " << setw(18) << "Array"
             << " | " << setw(15) << (binary ? "O(log n)" : "O(n)")
             << " | " << setw(13) << numberText(arrayNs, 0)
             << " | " << setw(11) << comparisons
             << " | " << setw(16) << (arrayData.dataBytes() + (binary ? 5 : 3) * sizeof(int)) << " |\n";

        // Singly linked list
        const PatientList& listSource = sorted ? sortedList : listData;
        double listNs = averageListSearchNanoseconds(listSource.getHead(), q, sorted, true, repeats, found, comparisons);
        cout << "| " << setw(17) << linearName
             << " | " << setw(18) << "Singly Linked List"
             << " | " << setw(15) << "O(n)"
             << " | " << setw(13) << numberText(listNs, 0)
             << " | " << setw(11) << comparisons
             << " | " << setw(16) << (listData.nodeBytes() + sizeof(PatientNode*) + 2 * sizeof(int)) << " |\n";
    }
    cout << string(ruleWidth, '-') << "\n";
}

#endif
