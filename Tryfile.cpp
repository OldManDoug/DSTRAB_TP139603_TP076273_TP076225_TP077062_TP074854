#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Node structure for the linked list
struct BaseCost {
    double data;
    BaseCost* next;

    BaseCost(double val) : data(val), next(nullptr) {}
};

// Linked List class
class NumberedLinkedList {
private:
    BaseCost* head;
    int count;

public:
    NumberedLinkedList() : head(nullptr), count(0) {}

    // Destructor to clean up dynamically allocated memory
    ~NumberedLinkedList() {
        BaseCost* current = head;
        while (current != nullptr) {
            BaseCost* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Insert a new number at the end of the linked list
    void insert(double val) {
        BaseCost* newNode = new BaseCost(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            BaseCost* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        count++;
    }

    // Calculate total and average
    void calculateStats() const {
        if (head == nullptr) {
            cout << "No numbers found in the file." << endl;
            return;
        }

        double total = 0.0;
        BaseCost* temp = head;

        while (temp != nullptr) {
            total += temp->data;
            temp = temp->next;
        }

        double average = total / count;

        cout << "Total Numbers Found: " << count << endl;
        cout << "Total Sum: " << total << endl;
        cout << "Average: " << average << endl;
    }
};

// Helper function to check if a token string is a valid number
bool tryParseDouble(const string& str, double& value) {
    stringstream ss(str);
    ss >> value;
    // Check if entire token was consumed as a number
    return !ss.fail() && ss.eof();
}

int main() {
    string fileName = "Book1.csv";
    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return 1;
    }

    NumberedLinkedList numList;
    string token;

    // Read word by word (whitespace-delimited)
    while (inFile >> token) {
        double val;
        // Extract numbers and ignore text characters
        if (tryParseDouble(token, val)) {
            numList.insert(val);
        }
    }

    inFile.close();

    // Compute total and average from linked list
    numList.calculateStats();

    return 0;
}
/*WHAT IS YOUR CONTRIBUTION**TO THE FUTURE pls answer - dont see slide, talk about it UNDERSTAND HOW it WORKS
however long is wanted to speak and he chooses start speaking abput it 
No presentation ⟶ do part 2 continue now, dont come 🙂  join online teams*/