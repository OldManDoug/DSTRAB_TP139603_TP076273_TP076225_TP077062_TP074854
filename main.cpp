#include<io.h>
#include<iostream> //libraries
#include "lists.hpp" //include header file, which is where your main code is. GeeksforGeeks. (2020, July 23). Header Files in C++. GeeksforGeeks. https://www.geeksforgeeks.org/cpp/header-files-in-c-c-with-examples/
#include <string>
#include "listdatasetab.hpp"
#include <ctime>
using namespace std; // to avoid repeating std:: before every standard library function

int main() {

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

    return 0;

}
//skeleton [prpgram]