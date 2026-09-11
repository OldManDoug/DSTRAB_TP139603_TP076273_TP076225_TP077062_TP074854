#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;
//GeeksforGeeks. (2018, June 6). File Handling through C++ Classes. GeeksforGeeks. https://www.geeksforgeeks.org/cpp/file-handling-c-classes/
void processFile(const string& filename)
{
    ifstream file(filename, ios::binary);

    if (!file) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    const size_t BUFFER_SIZE = 8192;
    char buffer[BUFFER_SIZE];

    size_t totalBytes = 0;
    size_t totalLines = 0;

    auto start = chrono::steady_clock::now();

    while (file.read(buffer, BUFFER_SIZE) || file.gcount() > 0) {
        size_t bytesRead = static_cast<size_t>(file.gcount());

        totalBytes += bytesRead;

        // Pointer points to the beginning of the buffer
        char* ptr = buffer;

        // Process the buffer using the pointer
        for (size_t i = 0; i < bytesRead; i++) {
            if (*(ptr + i) == '\n') {
                totalLines++;
            }
        }
    }

    auto end = chrono::steady_clock::now();

    chrono::duration<double> elapsed = end - start;

    file.close();

    cout << "Total Bytes: " << totalBytes << endl;
    cout << "Total Lines: " << totalLines << endl;
    cout << "Time Taken: " << elapsed.count() << " seconds" << endl;
    // Check for eof
    if (file.eof())
        cout << "Reached end of file." << endl;
    else
        cerr << "Error: File reading failed!" << endl;

    file.close();


}

void ProcesFile()
{
    processFile("dataset1facility_a.csv");

}
void ProcessFile1(){
    processFile("dataset2facilityb.csv");
} //IMPLEMENT AS A LIST - fat slides learn dei. 
// Definition of a Node in a singly linked list - from GeeksforGeeks
void ProcessFile2(){
    processFile("dataset3_facility_c.csv");
}

// singly linked list node structure
class Node {
public:
    int data;
    Node* next;

    // constructor to initialize a new node with data
    Node(int new_data) {
        this->data = new_data;
        this->next = nullptr;
    }
};

int main() {
    // reference:
    // Create the first node (head of the list)
    Node* head = new Node(10);

    // Link the second node
    head->next = new Node(20);

    // Link the third node
    head->next->next = new Node(30);

    // Link the fourth node
    head->next->next->next = new Node(40);

    // printing linked list
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
}
/* Search and Sort will be implemented here 
low = 0
high = n - 1
while low <= high
    mid = (low + high) // 2
    if A[mid] == target
        return mid
    else if A[mid] < target
        low = mid + 1
    else:
        high = mid - 1
return -1   // not found
*/
// Suitability based on the types of Sort and Search, CAN COMBINE many sortings to be one new sort.  
// Many more to learn...