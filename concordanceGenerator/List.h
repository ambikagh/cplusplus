// ---------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   12/4/2015
// Course: 501 Assignment 6
// ---------------------------------------------------------------------------

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <iomanip>

#define MAX_SIZE 5
using namespace std;

//--------------------------  class List  ------------------------------------
// ADT List: finite, ordered collection of zero or more items.
//           The ordering is determined by first in first out policy
//          
// Assumptions:    
//   -- There is no dummy head node, head points to first node.  
//      when the list is empty head points to NULL.
//   -- Every node in the list has two string pointers which point to 
//      array of strings appearing before and after a keyword in text
//   -- The insertEnd allocates memory for a Node, and inserts the node at end
//   -- Delete function is not necessary for this ADT.
//      De allocating the memory of data pointer has to be handled by the 
//      calling function
// Constraints:
//   -- This is not complete ADT. implements only insertion at the end of the
//      list, no other operation on list such as delete or retrieve or 
//      inserting the node at the beginning are implemented
//----------------------------------------------------------------------------

struct Node {
    
    string *before; // Pointer to array of strings appearing before
    string *after; // Pointer to array of strings appearing after
    Node *next;

    // Constructor
    Node() {
        before = after = NULL;
        next = NULL;
    }
    
    // Destructor
    ~Node(){
        if(before){
            delete[] before;
        }
        if(after){
            delete[] after;
        }
    }
};

class List {  
    Node *head;              // pointer to first node in list
public:
    List();
    ~List();
    bool insertEnd(string*,string*);   // insert item at the end of list  
    bool isEmpty() const;              // is list empty?    
    void makeEmpty(void); // Clear the list    
    void display(string)const; // Output the words on screen
    string *getBefore(void)const; // Fetch the before pointer
    void setBefore(string*); // Set the before pointer
    string *getAfter(void)const; // get the after pointer
    void setAfter(string*); // set the after pointer
 };



#endif

