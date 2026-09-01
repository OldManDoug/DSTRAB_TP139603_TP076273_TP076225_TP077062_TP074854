// https://github.com/Varadmuley33/Generalized-Data-Structure-Library/blob/main/Generalized_Data_Structure_Library.cpp
////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project Name   :   Generic Data Structure Library  
//
//  Description    :   This project implements a generalized, menu-driven data structure
//                     library using C++ and object-oriented programming concepts.
//                     It provides complete implementations of four linked list types:
//                     1) Singly Linear Linked List
//                     2) Singly Circular Linked List     
//                     3) Doubly Linear Linked List
//                     4) Doubly Circular Linked List
//
//                     Each linked list supports standard operations such as insertion,
//                     deletion, display, and counting of nodes. The project is designed
//                     using dynamic memory allocation, templates, and modular switch-case
//                     driven menus to demonstrate reusability and scalability.
//
//  Author Name    :   Varad Nitin Muley
//
//  Date           :   07/01/2026
//
////////////////////////////////////////////////////////////////////////////////////////////////
     
                                
/* 
------------------------------------------------------------------------------------
Type                 Name of class for node          Name of class For Functionality
------------------------------------------------------------------------------------

Singly Linear        SinglyLLLnode                   SinglyLLL
Singly Circular      SinglyCLLnode                   SinglyCLL
Doubly Linear        DoublyLLLnode                   DoublyLLL
Doubly Circular      DoublyCLLnode                   DoublyCLL
------------------------------------------------------------------------------------
*/


#include<iostream>
using namespace std;


/*---------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////// 
//               Singly Linear Linked List using generic approach
/////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------------------------------------*/


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Class Name     :    SinglyLLLnode
//  Data Members   :    data, next
//  Description    :    Represents a node of singly linear linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)
template <class T>
class SinglyLLLnode
{
    public:
        T data;
        SinglyLLLnode<T> *next;

    SinglyLLLnode(T no)
    {
        this->data = no;
        this->next = NULL;
    }
};


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Class Name     :    SinglyLLL
//  Data Members   :    first, iCount
//  Description    :    Implements singly linear linked list operations.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class SinglyLLL
{
private:
    SinglyLLLnode<T> *first;
    int iCount;

public:
    SinglyLLL();
    void InsertFirst(T );            
    void InsertLast(T );
    void DeleteFirst();
    void DeleteLast(); 
    void Display();
    int Count();
    void InsertAtPos(T ,int);
    void DeleteAtPos(int);
};

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  :    SinglyLLL
//  Description    :    Initializes an empty singly linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
SinglyLLL<T> :: SinglyLLL()
{
    cout << "Object of SinglyLL gets Created.\n";
    this->first = NULL;
    this->iCount = 0;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertFirst
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at first position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////


template <class T>
void SinglyLLL<T> ::  InsertFirst(T no)            
{
    SinglyLLLnode<T> *newn = NULL;
    newn = new SinglyLLLnode<T>(no);

    newn -> next = this->first;
    this->first = newn;
    
    this->iCount++;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertLast
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at Last position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void SinglyLLL<T> :: InsertLast(T no)
{
    SinglyLLLnode<T> * newn = NULL;
    SinglyLLLnode<T> * temp = NULL;
    newn = new SinglyLLLnode<T>(no);

    if(this->iCount == 0)          
    {
        this->first = newn;
    }
    else
    {
        temp = this->first;

        while(temp -> next != NULL)
        {
            temp = temp -> next;
        }

        temp -> next = newn;
    }
    this->iCount++;
}



//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteFirst
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to delete node at first position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void SinglyLLL<T> :: DeleteFirst()
{
    SinglyLLLnode<T> * temp = NULL;

    if(this->first == NULL)
    {
        return;
    }
    else if(this->first->next == NULL)  //(this->iCount == 1)
    {
        delete this->first;
        this->first = NULL;
    }
    else
    {
        temp = this->first;

        this->first = this->first->next;
        delete temp;

    }
    this->iCount--;

}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteLast
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to Delete node at Last position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void SinglyLLL<T> :: DeleteLast()
{
    SinglyLLLnode<T> * temp = NULL;
    if(this->first == NULL)
    {
        return;
    }
    else if(this->first-> next == NULL)  //this->iCount == 1
    {
        delete this->first;
        this->first = NULL;
    }
    else
    {
        temp = this->first;

        while(temp -> next -> next != NULL)
        {
            temp = temp -> next;
        }

        delete temp -> next;
        temp -> next = NULL;
    }
    this->iCount--;
}



//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  :    Display
//  Input          :    Data stored in each node
//  Output         :    Displays node data on screen
//  Description    :    Displays all elements of the singly circular linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void SinglyLLL<T> :: Display()
{
    int iCnt = 0;

    SinglyLLLnode<T> * temp = NULL;
    temp = first;

    for(iCnt = 1 ; iCnt <= this->iCount ; iCnt++)             
    {
        cout<<"| "<<temp -> data <<" |->";
        temp = temp -> next;
    }
cout<<"NULL\n";
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  :    Count
//  Input          :    None
//  Output         :    Returns number of nodes
//  Description    :    Returns total count of nodes in the list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
int SinglyLLL<T> :: Count()
{
    return this->iCount;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertAtPos
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at Any position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void SinglyLLL<T> :: InsertAtPos(T no, int pos)
{
    int iCnt = 0;
    SinglyLLLnode<T> * temp = NULL;
    SinglyLLLnode<T> * newn = NULL;
    
    if((pos < 1) || (pos > this->iCount + 1) )
    {
        cout<<"Invalid position ";
        return;
    }

    if(pos == 1)
    {
        this->InsertFirst(no);
    }
    else if(pos == this->iCount + 1)
    {
        this->InsertLast(no);
    }
    else 
    {
        newn = new SinglyLLLnode<T>(no);

        temp = this->first;

        for(iCnt = 1 ; iCnt < pos - 1; iCnt++)
        {
            temp = temp -> next;
        }
        newn -> next = temp -> next;
        temp -> next = newn;

        this->iCount ++;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteAtPos
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to Delete node at any position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void SinglyLLL<T> :: DeleteAtPos(int pos)
{
    int iCnt = 0;
    SinglyLLLnode<T> * temp = NULL;
    SinglyLLLnode<T> * target = NULL;
    
    if((pos < 1) || (pos > this->iCount) )
    {
        cout<<"Invalid position ";
        return;
    }

    if(pos == 1)
    {
        this->DeleteFirst();
    }
    else if(pos == this->iCount + 1)
    {
        this->DeleteLast();
    }
    else 
    {
        temp = this->first;

        for(iCnt = 1 ; iCnt < pos - 1; iCnt++)
        {
            temp = temp -> next;
        }

        target = temp -> next;
        temp -> next = target->next;
        delete target;
        
        this->iCount --;
    }
}

/*---------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////// 
//               Singly Circular Linked List using generic approach
/////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------------------------------------*/

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Class Name     :    node
//  Data Members   :    data, next, last
//  Description    :    Represents a node of a singly circular linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)
template <class T>
class SinglyCLLnode
{
    public:
        T data;
        SinglyCLLnode *next;
        SinglyCLLnode *last;

    SinglyCLLnode( T no)
    {
        this->data = no;
        this->next = NULL;
        this->last = NULL;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Class Name     :    SinglyCLL
//  Data Members   :    first, last, iCount
//  Description    :    Implements singly circular linked list operations.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template < class T>
class SinglyCLL
{
    private:
        SinglyCLLnode<T> * first;
        SinglyCLLnode<T> * last;
        int iCount;

    public:    
        SinglyCLL();
        void InsertFirst(T no);
        void InsertLast(T no);
        void InsertAtPos(T no, int pos);

        void DeleteLast();
        void DeleteFirst();
        void DeleteAtPos(int pos);

        void Display();
        int Count();
};


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     SinglyCLL
//  Input          :    None
//  Output         :    Initializes data members
//  Description    :    Initializes an empty singly circular linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template < class T>
SinglyCLL<T> :: SinglyCLL()
{
    cout<<"Object of SinglyCLL gets created.\n";
    first = NULL;
    last = NULL;
    iCount = 0;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertFirst
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at first position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void SinglyCLL<T> :: InsertFirst(T no)
{
    SinglyCLLnode <T>* newn = NULL;

    newn = new SinglyCLLnode<T>(no);

    newn->data = no;
    newn->next = NULL;
    newn->last = NULL;

    if(first == NULL || last == NULL)
    {
        first = newn;
        last = newn;
    }
    else
    {
        newn-> next = first;
        first = newn;
    }
    last -> next = first;

    iCount++;

}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertLast
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at Last position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////

template < class T>
void SinglyCLL<T> :: InsertLast(T no)
{
    SinglyCLLnode<T> * newn = NULL;

    newn = new SinglyCLLnode<T>(no);

    newn->data = no;
    newn->next = NULL;
    newn->last = NULL;

    if(first == NULL && last == NULL)
    {
        first = newn;
        last = newn;
    }
    else 
    {
        last->next = newn;
        last = newn;
    }
    last -> next = first;

    iCount++;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertAtPos
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at Any position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////

template < class T>
void SinglyCLL<T> :: InsertAtPos(T no, int pos)
{
    SinglyCLLnode<T> * temp = NULL;
    SinglyCLLnode<T> * newn = NULL;

    int iCnt = 0;

    if(pos<1 || pos > iCount+1)
    {
        cout<<"Inavlid Position\n";
        return;
    }

    if(pos == 1)
    {
        InsertFirst(no);
    }
    else if(pos == iCount+1)
    {
        InsertLast(no);
    }
    else
    {
        newn = new SinglyCLLnode<T>(no);

        temp = first;
        for(iCnt = 1; iCnt <= pos-1 ; iCnt++)
        {
            temp = temp-> next ;
            iCnt++;
        }

        newn -> next = temp -> next;
        temp->next = newn;
        last->next = first;

        iCount++;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteFirst
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to delete node at first position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template < class T>
void SinglyCLL<T> :: DeleteFirst()
{
    SinglyCLLnode<T> * temp = NULL;
    if(first == NULL &&  last == NULL)
    {
        cout<<"Linked List is Empty";
        return;
    }
    else if(first == last)
    {
        free(first);
        first = NULL;
        last = NULL;
    }
    else
    {
        temp = first;
        first = first->next;
        free(temp);
        last->next = first;
    }

    iCount--;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteLast
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to Delete node at Last position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template < class T>
void SinglyCLL<T> :: DeleteLast()
{
    SinglyCLLnode<T> * temp = NULL;
    if(first == NULL &&  last == NULL)
    {
        cout<<"Linked List is Empty";
        return;
    }
    else if(first == last)
    {
        free(first);
        first = NULL;
        last = NULL;
    }
    else
    {
        temp = first;
        while(temp->next != last)
        {
            temp = temp -> next;
        }
        free(last);
        last = temp;
        last->next = first;
    }

    iCount--;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteAtPos
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to Delete node at any position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template < class T>
void SinglyCLL<T> :: DeleteAtPos(int pos)
{
    SinglyCLLnode<T> * temp = NULL;
    SinglyCLLnode<T> * target = NULL;

    int iCnt = 0;

    if(pos<1 || pos > iCount)
    {
        cout<<"Inavlid Position\n";
        return;
    }

    if(pos == 1)
    {
        DeleteFirst();
    }
    else if(pos == iCount)
    {
        DeleteLast();
    }
    else
    {
        temp = first;

        for(iCnt = 1; iCnt <= pos-1 ; iCnt++)
        {
            temp = temp-> next ;
            iCnt++;
        }
        target = temp->next;
        temp->next = target->next;
        free(target);

        iCount--;

    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  :    Display
//  Input          :    Data stored in each node
//  Output         :    Displays node data on screen
//  Description    :    Displays all elements of the singly circular linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template < class T>
void SinglyCLL<T> :: Display()
{
    do
    {
        printf("|%d|->",first -> data);
        first = first -> next;
    } while (first != last -> next);

    printf("NULL\n");
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  :    Count
//  Input          :    None
//  Output         :    Returns number of nodes
//  Description    :    Returns total count of nodes in the list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template < class T>
int SinglyCLL<T> :: Count()
{
    return iCount;
}

/*---------------------------------------------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////
//               Doubly Linear Linked List using generic approach
/////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------------------------------------*/


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Class Name     :    node
//  Data Members   :    data, next, last
//  Description    :    Represents a node of a Doubly Linear linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)
template <class T>
class DoublyLLLnode
{
    public:
        T data;
        DoublyLLLnode *next;
        DoublyLLLnode *prev;

        DoublyLLLnode(T no)
        {
            this->data = no;
            this->next = NULL;
            this->prev = NULL;
        }
    
};


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Class Name     :    DoublyLLL
//  Data Members   :    first, last, iCount
//  Description    :    Implements singly circular linked list operations.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class DoublyLLL
{
    private:
        DoublyLLLnode<T> *first;
        int iCount;

    public:
        DoublyLLL();
        void InsertFirst(T );
        void InsertLast(T);
        void InsertAtPos(T, int);

        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int);

        void Display();
        int Count();
};


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     DoublyLLL
//  Input          :    None
//  Output         :    Initializes data members
//  Description    :    Initializes an empty Doubly Linear linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
DoublyLLL<T> :: DoublyLLL()
{
    cout<<"Linked List gets created\n";
    this->first = NULL;
    this->iCount = 0;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertFirst
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at first position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyLLL<T> :: InsertFirst(T no )
{
    DoublyLLLnode<T> *newn = NULL;

    newn = new DoublyLLLnode<T>(no);

    if(this->first == NULL)
    {
        this->first = newn;
    }
    else
    {
        newn->next = this->first;
        this->first->prev = newn;
        this->first = newn;
    }
    this->iCount++;
}

template <class T>



//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertLast
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at Last position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
void DoublyLLL<T> :: InsertLast(T no)
{
    DoublyLLLnode<T> *newn = NULL;
    DoublyLLLnode<T> *temp = NULL;

    newn = new DoublyLLLnode<T>(no);

    if(this->first == NULL)
    {
        this->first = newn;
    }
    else
    {
        temp = this->first;
        while(temp -> next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newn;
        newn->prev = temp;

    }
    this->iCount++;
}




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertAtPos
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at Any position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyLLL<T> :: InsertAtPos(T no, int pos)
{
    DoublyLLLnode<T> *newn = NULL;
    DoublyLLLnode<T> *temp = NULL;
    int iCnt = 0;

    if((pos < 1) || (pos > this->iCount + 1))
    {
        cout<<"Invalid Position\n";
        return;
    }

    if(pos == 1)
    {
        this->InsertFirst(no);
    }
    else if(pos == this->iCount+1)
    {
        this->InsertLast(no);
    }
    else
    {
        newn = new DoublyLLLnode<T>(no);

        temp = this->first;

        for(iCnt = 1 ; iCnt < pos -1 ; iCnt++)
        {
            temp = temp->next;
        }

        newn->next = temp->next;
        temp->next->prev = newn;

        temp->next = newn;
        newn->prev = temp;
        this->iCount++;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteFirst
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to delete node at first position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyLLL<T> :: DeleteFirst()
{
    if(this->first == NULL)                        
    {
        return;
    }
    else if(this->first->next == NULL)             
    {
        delete this->first;
        this->first = NULL;
    }
    else                                           
    {
        this->first = this->first -> next;
        delete this->first -> prev;
        this->first -> prev = NULL;
    }
    this -> iCount--;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteLast
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to Delete node at Last position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyLLL<T> :: DeleteLast()
{
    DoublyLLLnode<T> *temp = NULL;
    if(this->first == NULL)                        
    {
        return;
    }
    else if(this->first->next == NULL)            
    {
        delete this->first;
        this->first = NULL;
    }
    else                                           
    {
        temp = this->first;
        while(temp->next->next != NULL)
        {
            temp = temp->next;
        }

        delete temp->next;
        temp->next = NULL;
    }
    this -> iCount--;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteAtPos
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to Delete node at any position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyLLL<T> :: DeleteAtPos(int pos)
{
    DoublyLLLnode<T> *temp = NULL;
    int iCnt = 0;
    if((pos < 1) || (pos > this->iCount))
    {
        cout<<"Invalid Position\n";
        return;
    }

    if(pos == 1)
    {
        this->DeleteFirst();
    }
    else if(pos == this->iCount)
    {
        this->DeleteLast();
    }
    else
    {
        temp = this->first;

        for(iCnt = 1 ; iCnt < pos -1 ; iCnt++)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        delete temp->next->prev;
        temp->next->prev = temp;

        this->iCount--;
    }
    
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  :    Display
//  Input          :    Data stored in each node
//  Output         :    Displays node data on screen
//  Description    :    Displays all elements of the Doubly Linear linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyLLL<T> :: Display()
{
    DoublyLLLnode<T> * temp = NULL;

    temp = this->first;

    cout<<"\nNULL<=>";
    while(temp != NULL)
    {
        cout<<"| "<<temp->data<<" |<=>";
        temp = temp->next;
    }
    cout<<"NULL\n";
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  :    Count
//  Input          :    None
//  Output         :    Returns number of nodes
//  Description    :    Returns total count of nodes in the list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
int DoublyLLL<T> :: Count()
{
    return this->iCount;
}


/*---------------------------------------------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////
//               Doubly Circular Linked List using generic approach
/////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------------------------------------*/

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Class Name     :    DoublyCLLnode
//  Data Members   :    data, next, prev
//  Description    :    Represents a node of doubly circular linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)
template <class T>
class  DoublyCLLnode
{
    public :
        T data;
        DoublyCLLnode *next;
        DoublyCLLnode *prev;

    DoublyCLLnode(T no)
    {
        this->data = no;
        this->next = NULL;
        this->prev = NULL;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Class Name     :    DoublyCLL
//  Data Members   :    first, last, iCount
//  Description    :    Implements doubly circular linked list operations.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class DoublyCLL
{
    private:
        DoublyCLLnode<T> * first;
        DoublyCLLnode<T> * last;
        int iCount;

    public:    
        DoublyCLL();
        void InsertFirst(T no);
        void InsertLast(T no);
        void InsertAtPos(T no, int pos);
    
        void DeleteFirst();
        void DeleteLast();
        void DeleteAtPos(int pos);
    
        void Display();
        int Count();
};

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DoublyCLL
//  Input          :    None
//  Output         :    Initializes data members
//  Description    :    Initializes an empty doubly circular linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
DoublyCLL <T>:: DoublyCLL()
{
    cout<<"Object of DOUBLYCLL gets created.\n";
    first = NULL;
    last = NULL;
    iCount = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertFirst
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at first position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyCLL<T> :: InsertFirst(T no)
{
    DoublyCLLnode<T> * newn = NULL;

    newn = new DoublyCLLnode<T>(no);

    if(first == NULL && last == NULL)
    {
        first = newn;
        last = newn;
    }
    else
    {
        newn->next = first;
        first->prev = newn;
        first = newn;
        
        last->next = first;

    }
    iCount++;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertLast
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at Last position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyCLL<T> :: InsertLast(T no)
{
    DoublyCLLnode<T> * newn = NULL;

    newn = new DoublyCLLnode<T>(no);

    if(first == NULL && last == NULL) // LL is empty
    {
        first = newn;
        last = newn;
    }
    else    // LL contains one or more
    {
        last->next = newn;
        newn->prev = last;
        last = newn;
    }

    last->next = first;
    first->prev = last;

    iCount++;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    InsertAtPos
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to insert node at Any position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyCLL<T> :: InsertAtPos(T no, int pos)
{
    DoublyCLLnode<T> * temp = NULL;
    DoublyCLLnode<T> * newn = NULL;
    int iCnt = 0;

    if(pos < 1 || pos > iCount+1)
    {
        printf("Invalid position\n");
        return;
    }

    if(pos == 1)
    {
        InsertFirst(no);
    }
    else if(pos == iCount+1)
    {
        InsertLast(no);
    }
    else
    {
        newn = new DoublyCLLnode<T>(no);


        temp = first;

        for(iCnt = 1; iCnt < pos-1; iCnt++)
        {
            temp = temp->next;
        }

        newn->next = temp->next;
        newn->next->prev = newn;

        temp->next = newn;
        newn->prev = temp;

        iCount++;
    }
}



//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteFirst
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to delete node at first position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyCLL<T> :: DeleteFirst()
{
    if(first == NULL && last == NULL) // LL is empty
    {
        return;
    }
    else if(first == last)    // LL contains 1 node
    {
        delete(first);
        first = NULL;
        last = NULL;
    }
    else
    {
        first = first ->next;
        delete(first->prev);

        last->next = first;
        first->prev = last;
    }
    iCount--;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteLast
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to Delete node at Last position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyCLL<T> :: DeleteLast()
{
    if(first == NULL && last == NULL) // LL is empty
    {
        return;
    }
    else if(first == last)    // LL contains 1 node
    {
        delete(first);
        first = NULL;
        last = NULL;
    }
    else
    {
        last = (last)->prev;
        delete(last->next);
        
        (last)->next = first;
        (first)->prev = last;
    }    
    iCount--;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :    DeleteAtPos
//  Input :            Data of Node 
//  Output :           Nothing 
//  Description :      Use to Delete node at any position 
//  Author :           Varad Nitin Muley
//  Date :             07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyCLL<T> :: DeleteAtPos(int pos)
{
    DoublyCLLnode<T> * temp = NULL;
    int iCnt = 0;

    if(pos < 1 || pos > iCount)
    {
        printf("Invalid position\n");
        return;
    }

    if(pos == 1)
    {
        DeleteFirst();
    }
    else if(pos == iCount)
    {
        DeleteLast();
    }
    else
    {
        temp = first;

        for(iCnt = 1; iCnt < pos-1; iCnt++)
        {
            temp = temp->next;
        }

        temp->next = temp->next->next;
        delete(temp->next->prev);
        temp->next->prev = temp;
        iCount--;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  :    Display
//  Input          :    Data stored in each node
//  Output         :    Displays node data on screen
//  Description    :    Displays all elements of the Doubly circular linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026  
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void DoublyCLL<T> :: Display()
{
    if(first == NULL && last == NULL)   // LL is empty
    {
        printf("Linked List is empty\n");
        return;
    }

    printf(" NULL <=> ");
    
    do
    {
        printf("| %d | <=> ",first->data);
        first = first -> next;
    }while(first != last->next);
    
    printf("NULL\n");
}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  :    Count
//  Input          :    None
//  Output         :    Returns number of nodes
//  Description    :    Returns total count of nodes in the list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
template <class T>
int DoublyCLL<T> :: Count()
{
    return iCount;
}



//////////////////////////////////////End Of Library////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name  :    main
//  Description    :    Demonstrates all operations of singly circular linked list.
//  Author         :    Varad Nitin Muley
//  Date           :    07/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    int iMainChoice = 1;

    while(iMainChoice != 0)
    {
        cout<<"\n========================================\n";
        cout<<"   GENERALISED DATA STRUCTURE LIBRARY\n";
        cout<<"========================================\n";
        cout<<"1. Singly Linear Linked List\n";
        cout<<"2. Singly Circular Linked List\n";
        cout<<"3. Doubly Linear Linked List\n";
        cout<<"4. Doubly Circular Linked List\n";
        cout<<"0. Exit\n";
        cout<<"----------------------------------------\n";
        cout<<"Enter your choice : ";
        cin>>iMainChoice;

        switch(iMainChoice)
        {
            case 1:   // Singly Linear
            {
                SinglyLLL<int> *sobj = new SinglyLLL<int>();
                int iChoice = 1, iValue = 0, iPos = 0;

                while(iChoice != 9)
                {
                    cout<<"\n--- SINGLY LINEAR LINKED LIST ---\n";
                    cout<<"1. Insert First\n";
                    cout<<"2. Insert Last\n";
                    cout<<"3. Insert At Position\n";
                    cout<<"4. Delete First\n";
                    cout<<"5. Delete Last\n";
                    cout<<"6. Delete At Position\n";
                    cout<<"7. Display\n";
                    cout<<"8. Count\n";
                    cout<<"9. Back to Main Menu\n";
                    cout<<"Enter choice : ";
                    cin>>iChoice;

                    switch(iChoice)
                    {
                        case 1: 
                            cout<<"Enter value : ";
                            cin>>iValue; 
                            sobj->InsertFirst(iValue);
                            break;

                        case 2: 
                            cout<<"Enter value : "; 
                            cin>>iValue; 
                            sobj->InsertLast(iValue); 
                            break;

                        case 3: 
                            cout<<"Enter value : "; 
                            cin>>iValue; 
                            cout<<"Enter pos : "; 
                            cin>>iPos; 
                            sobj->InsertAtPos(iValue,iPos); 
                            break;

                        case 4: 
                            sobj->DeleteFirst();
                            break;

                        case 5: 
                            sobj->DeleteLast(); 
                            break;

                        case 6: 
                            cout<<"Enter pos : "; 
                            cin>>iPos; 
                            sobj->DeleteAtPos(iPos); 
                            break;

                        case 7: 
                            sobj->Display(); 
                            break;

                        case 8: 
                            cout<<"Count : "<<sobj->Count()<<"\n"; 
                            break;

                        case 9: 
                            break;
                            default: cout<<"Invalid choice\n";
                    }
                }

                delete sobj;
                break;
            }

            case 2:   // Singly Circular
            {
                SinglyCLL<int> *scobj = new SinglyCLL<int>();
                int iChoice = 1, iValue = 0, iPos = 0;

                while(iChoice != 9)
                {
                    cout<<"\n--- SINGLY CIRCULAR LINKED LIST ---\n";
                    cout<<"1. Insert First\n";
                    cout<<"2. Insert Last\n";
                    cout<<"3. Insert At Position\n";
                    cout<<"4. Delete First\n";
                    cout<<"5. Delete Last\n";
                    cout<<"6. Delete At Position\n";
                    cout<<"7. Display\n";
                    cout<<"8. Count\n";
                    cout<<"9. Back to Main Menu\n";
                    cout<<"Enter choice : ";
                    cin>>iChoice;

                    switch(iChoice)
                    {
                        case 1:
                            cout << "Enter value : ";
                            cin >> iValue;
                            scobj->InsertFirst(iValue);
                            break;

                        case 2:
                            cout << "Enter value : ";
                            cin >> iValue;
                            scobj->InsertLast(iValue);
                            break;

                        case 3:
                            cout << "Enter value : ";
                            cin >> iValue;

                            cout << "Enter position : ";
                            cin >> iPos;

                            scobj->InsertAtPos(iValue, iPos);
                            break;

                        case 4:
                            scobj->DeleteFirst();
                            break;

                        case 5:
                            scobj->DeleteLast();
                            break;

                        case 6:
                            cout << "Enter position : ";
                            cin >> iPos;

                            scobj->DeleteAtPos(iPos);
                            break;

                        case 7:
                            scobj->Display();
                            break;

                        case 8:
                            cout << "Count : " << scobj->Count() << "\n";
                            break;

                        case 9:
                            break;

                        default:
                            cout << "Invalid choice\n";
                            break;

                    }
                }

                delete scobj;
                break;
            }

            case 3:
            {
                DoublyLLL<int> *dobj = new DoublyLLL<int>();

                int iChoice = 1;
                int iValue = 0;
                int iPos = 0;

                while(iChoice != 9)
                {
                    cout << "\n--- DOUBLY LINEAR LINKED LIST ---\n";
                    cout << "1. Insert First\n";
                    cout << "2. Insert Last\n";
                    cout << "3. Insert At Position\n";
                    cout << "4. Delete First\n";
                    cout << "5. Delete Last\n";
                    cout << "6. Delete At Position\n";
                    cout << "7. Display\n";
                    cout << "8. Count\n";
                    cout << "9. Back to Main Menu\n";
                    cout << "Enter choice : ";
                    cin >> iChoice;

                    switch(iChoice)
                    {
                        case 1:
                            cout << "Enter value : ";
                            cin >> iValue;
                            dobj->InsertFirst(iValue);
                            break;

                        case 2:
                            cout << "Enter value : ";
                            cin >> iValue;
                            dobj->InsertLast(iValue);
                            break;

                        case 3:
                            cout << "Enter value : ";
                            cin >> iValue;

                            cout << "Enter position : ";
                            cin >> iPos;

                            dobj->InsertAtPos(iValue, iPos);
                            break;

                        case 4:
                            dobj->DeleteFirst();
                            break;

                        case 5:
                            dobj->DeleteLast();
                            break;

                        case 6:
                            cout << "Enter position : ";
                            cin >> iPos;

                            dobj->DeleteAtPos(iPos);
                            break;

                        case 7:
                            dobj->Display();
                            break;

                        case 8:
                            cout << "Count : " << dobj->Count() << "\n";
                            break;

                        case 9:
                            break;

                        default:
                            cout << "Invalid choice\n";
                            break;
                    }
                }

                delete dobj;
                break;
            }

            case 4:
            {
                DoublyCLL<int> *dcobj = new DoublyCLL<int>();

                int iChoice = 1;
                int iValue = 0;
                int iPos = 0;

                while(iChoice != 9)
                {
                    cout << "\n--- DOUBLY CIRCULAR LINKED LIST ---\n";
                    cout << "1. Insert First\n";
                    cout << "2. Insert Last\n";
                    cout << "3. Insert At Position\n";
                    cout << "4. Delete First\n";
                    cout << "5. Delete Last\n";
                    cout << "6. Delete At Position\n";
                    cout << "7. Display\n";
                    cout << "8. Count\n";
                    cout << "9. Back to Main Menu\n";
                    cout << "Enter choice : ";
                    cin >> iChoice;

                    switch(iChoice)
                    {
                        case 1:
                            cout << "Enter value : ";
                            cin >> iValue;
                            dcobj->InsertFirst(iValue);
                            break;

                        case 2:
                            cout << "Enter value : ";
                            cin >> iValue;
                            dcobj->InsertLast(iValue);
                            break;

                        case 3:
                            cout << "Enter value : ";
                            cin >> iValue;

                            cout << "Enter position : ";
                            cin >> iPos;

                            dcobj->InsertAtPos(iValue, iPos);
                            break;

                        case 4:
                            dcobj->DeleteFirst();
                            break;

                        case 5:
                            dcobj->DeleteLast();
                            break;

                        case 6:
                            cout << "Enter position : ";
                            cin >> iPos;

                            dcobj->DeleteAtPos(iPos);
                            break;

                        case 7:
                            dcobj->Display();
                            break;

                        case 8:
                            cout << "Count : " << dcobj->Count() << "\n";
                            break;

                        case 9:
                            break;

                        default:
                            cout << "Invalid choice\n";
                            break;
                    }
                }

                delete dcobj;
                break;
            }

            case 0:
                cout<<"Thank you for using Generalised Data Structure Library...\n";
                break;

            default:
                cout<<"Invalid choice\n";
        }
    }
    return 0;
}