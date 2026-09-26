#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

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
    Age* head1 = nullptr; //use from node/structure above
 //   head1 ->age = val; 
int age; //to print out age, daysvisit, length stay
ifstream f("dataset3facility_c.csv", ios::out); //for reading, we not input data into the set

if(f.is_open()){
     cerr << "Error: Could not open dataset3_facility_c.csv" << endl;
        return;
}else{
while(f >> age){
//to do so, need t define age 
cout << "Ages in facility C" << age << endl;
}
//https://www.tutorialspoint.com/article/read-integers-from-a-text-file-with-cplusplus-ifstream
}

//https://www.geeksforgeeks.org/cpp/file-handling-c-classes/ to measure times. 
const size_t BUFFER_SIZE = 8192;
    char buffer[BUFFER_SIZE];

    size_t totalBytes = 0;
    size_t totalLines = 0;

    auto start = chrono::steady_clock::now();

    while (f.read(buffer, BUFFER_SIZE) || f.gcount() > 0) {
        size_t bytesRead = static_cast<size_t>(f.gcount());

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
f.close();
}
// deletion of the patient id then save back into datasets
//write back new data to file? 

void readDays(DaysVisit* d){ 
    int daysvisit;
    ifstream f("Book1.csv",ios::out);

    if(f.is_open()){  //error handling
        cout <<"File cannot opened"<<endl;
    }
DaysVisit* temp = d;
while(f >> daysvisit){
    cout << "Days visited" << daysvisit << endl;
}
/*
while(d){
    cout << "DaysVisited" << d->daysvisit<< endl;
}
//cause infinity loop*/
f.close(); //remember close file
    //clear memory
}