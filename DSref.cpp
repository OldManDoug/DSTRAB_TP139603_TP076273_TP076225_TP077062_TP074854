#include<iostream>
#include <stdexcept>
using namespace std;
class Node{
private:
    int element;
    Node *next_node,*previous_node;
public:
    Node(int e=0,Node *n=nullptr,Node*p=nullptr):element(e),next_node(n),previous_node(p){}
    //Getters
    int retrieve() const{
        return element;
    }
    Node* next() const {
        return next_node;
    }
    Node* previous() const{
        return previous_node;
    }
    //Setters
    void setnext(Node* n){
        next_node=n;
    }
    void setprevious(Node* n){
        previous_node=n;
    }
    void setelement(int e){
        element= e;
    }
    friend class DoublyList;
};
class DoublyList{
private:
    Node *list_head;
public:
    DoublyList() {
        list_head = nullptr;
    }
    bool emptyList(){
        return list_head==nullptr;
    }
    int listSize(){
        int size=0;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            size++;
        }
        return size;
    }
    int frontElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        return list_head->retrieve();
    }
    int lastElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        Node *p1=nullptr;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            p1=ptr;
        }
        return p1->retrieve();
    }
    int countElement(int n)const{
        if (list_head==nullptr){
            throw "underflow";
        }
        int countE=0;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            if(ptr->retrieve()==n){
                countE++;
            }
        }
        return countE;
    }
    Node *head(){
        return list_head;
    }
    void pushAtFront(int e){
        Node*p=new Node(e,list_head,nullptr);
        if(list_head!=nullptr){
            list_head->setprevious(p);
        }
        list_head=p;
    }
    void pushAtEnd(int e){
        //For an Empty List
        if (list_head == nullptr) {
            pushAtFront(e);
            return;
        }
        Node* last=nullptr;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        Node*newnode= new Node(e,nullptr,last);
        last->setnext(newnode);
    }
    int popAtEnd(){
        int e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node* last=nullptr;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        e=last->retrieve();
        last->previous()->setnext(nullptr);
        delete last;
        return e;
    }
    int popAtFront(){
        int e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node* temp= list_head;
        e=list_head->retrieve();
        list_head=list_head->next();
        list_head->setprevious(nullptr);
        delete temp;
        return e;
    }
    void eraseElement(int e){
        // empty list
        if (list_head == nullptr) {
            throw "underflow";
        }
        bool found=false;
        for(Node *ptr=list_head;ptr!=nullptr;){
                if(ptr->retrieve()==e){
                    found = true;
                    Node* erasePtr=ptr;
                    ptr=ptr->next();
                    if(erasePtr==list_head){
                        popAtFront();
                    }
                    else if (erasePtr->next()==nullptr){
                        popAtEnd();
                    }
                    else{
                        erasePtr->previous()->setnext(erasePtr->next());
                        erasePtr->next()->setprevious(erasePtr->previous());
                        delete erasePtr;
                        erasePtr = nullptr;
                        }
                }
                else {
                    ptr= ptr->next();
                }
        }
        if(found=false){
            cout<<"Element not found"<<endl;
        }
    }
    void display() {
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout << ptr->retrieve() << " ";
        }
        cout << endl;
    }
};
int main(){
    DoublyList dl;

    cout << "Testing Doubly Linked List Functions\n" << endl;

    cout << "Inserting elements at end: 10, 20, 30, 40" << endl;
    dl.pushAtEnd(10);
    dl.pushAtEnd(20);
    dl.pushAtEnd(30);
    dl.pushAtEnd(40);
    dl.display();

    cout << "\nInserting elements at front: 5, 0" << endl;
    dl.pushAtFront(5);
    dl.pushAtFront(0);
    dl.display();

    cout << "\nCurrent list size: " << dl.listSize() << endl;
    cout << "Front element: " << dl.frontElement() << endl;
    cout << "Last element: " << dl.lastElement() << endl;

    cout << "\nInserting duplicates: 20, 30" << endl;
    dl.pushAtEnd(20);
    dl.pushAtEnd(30);
    dl.display();

    cout << "\nCount occurrences of 20: " << dl.countElement(20) << endl;

    cout << "\nRemoving from front and end" << endl;
    cout << "Popped from front: " << dl.popAtFront() << endl;
    cout << "Popped from end: " << dl.popAtEnd() << endl;
    dl.display();

    cout << "\nErasing all occurrences of 20" << endl;
    dl.eraseElement(20);
    dl.display();

    cout << "\nFinal size: " << dl.listSize() << endl;
    cout << "\nAll functions tested successfully." << endl;

    return 0;
}
//https://github.com/SaifDevAI/DoublyLinkedList-CPP
