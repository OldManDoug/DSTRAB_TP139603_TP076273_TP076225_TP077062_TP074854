#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// ------------------------------------
// 1. Singly Linked List Implementation
// ------------------------------------
struct Node {
    string data;
    Node* next;
    Node(string val) : data(val), next(nullptr) {}
};

void insertEnd(Node*& head, const string& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void implements() {
    Node* head = nullptr;
    // Escaped backslashes or forward slashes for Windows paths
    ifstream infile("dataset1facility_a.csv"); 

    if (!infile.is_open()) {
        cerr << "Error: Could not open dataset3_facility_c.csv" << endl;
        return;
    }

    string line;
    int age;
    while (getline(infile, line)) {
        insertEnd(head, line);
    }
    infile.close();

    // Display linked list
    Node* temp = head;
    while (temp) {
        cout << temp->data << endl;
        temp = temp->next;
    }
}

/*/ ------------------------------------
// 2. Singly Linked List Implementation
// ------------------------------------*/
struct RecordB {
    string data;
    RecordB* next;
    RecordB(string val) : data(val), next(nullptr) {}
};

// FIX: Added '*' so 'heade' is a reference to a RecordB pointer
void insertatEnd(RecordB*& heade, const string& value1) { 
    RecordB* newNod = new RecordB(value1);
    if (!heade) {
        heade = newNod;
        return;
    }
    RecordB* temp = heade;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNod;
}

void creater() {
    RecordB* heade = nullptr;
    
    ifstream infile("dataset2facility_b.csv",ios::out); 

    if (!infile.is_open()) {
        cerr << "Error: Could not open dataset2facility_b.csv" << endl;
        return;
    }

    string line;

    while (getline(infile, line)) {
        insertatEnd(heade, line); // Now matches the RecordB*& signature
    }
    infile.close();

    // Display linked list
    RecordB* temp = heade;
    while (temp) {
        cout << temp->data << endl;
        temp = temp->next;
    }
}
// Doubly or Circular for Daatset 3
struct Age{
    // one structure for each data, age 
    int age;
    Age* proc;
    Age*prev;
};
struct DaysVisit{
    int daysvisit;
DaysVisit* next1;

};
struct baseCost{
    double basecost;
    baseCost* proc1;
    baseCost* prev;
};


class DoubleLinkLIST{
public:
    Age* head1;
    Age* tail;

    DoubleLinkLIST(){
        head1 = tail = nullptr;
    }


void traverse(){
    Age* current = head1;
    while(current != nullptr){
        cout << current->age << "";
        current  = current ->proc;
    }
}
void insertionH(int val){
  Age* newN = new Age();
  newN ->age = val;
  newN ->proc =head1;
  newN ->prev = nullptr;
  if(head1 != nullptr){
    head1 ->prev = newN;
    head1 = newN;
  }
}

};

void readAge(){
    Age* head1 = nullptr;
ifstream f("dataset3_facility_c.csv", ios::out); //for reading, we not input data into the set
if(f.is_open()){
     cerr << "Error: Could not open dataset3_facility_c.csv" << endl;
        return;
}
int ager; //To read numerics from a file use stringstream as all files read with string


}