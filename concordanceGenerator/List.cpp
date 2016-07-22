// ---------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   12/4/2015
// Course: 501 Assignment 6
// ---------------------------------------------------------------------------

#include "List.h"
#include <string>

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
// Constructor 
List::List() {
    head = NULL;
}

// ---------------------------------------------------------------------------
// Destructor
List::~List() {
    makeEmpty();
}

// ---------------------------------------------------------------------------
// getBefore: 
// Returns the pointer to the array of words occurring before the keyWord
string* List::getBefore(void)const {
    return head->before;
}

// ---------------------------------------------------------------------------
// getAfter:
// Return the pointer to array of words appearing after the key word
string* List::getAfter(void)const {
    return head->after;
}


// ---------------------------------------------------------------------------
// setBefore:
// Set the pointer to array of words appearing before
void List::setBefore(string *newstring) {
    head->before = newstring;
}


// ---------------------------------------------------------------------------
// setAfter: 
// Set the pointer to array of words appearing after
void List::setAfter(string *newstring) {
    head->after = newstring;
}

//----------------------------------------------------------------------------
// isEmpty 
// check to see if List is empty as defined by a NULL head
// Return true if head is NULL, return false otherwise
bool List::isEmpty() const {
    return head == NULL;
}

//----------------------------------------------------------------------------
// insert 
// insert a node at the end of the list
bool List::insertEnd(string *wordsBef, string *wordsAft) {

    Node *tempNode = new Node;
    if (tempNode == NULL) return false;                // out of memory, bail

    tempNode->before = wordsBef;  // link the before pointer to array of words
    tempNode->after = wordsAft;   // link the after pointer to array of words
    tempNode->next = NULL;

    // if the list is empty or if the node should be inserted before 
    // the first node of the list
    if (isEmpty()) {
        head = tempNode;
        return true;
    }
    // Insert the new item at the end 
    Node *current = head;
    // Traverse the list
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = tempNode; // Insert the new node at the end of this list
    return true;
}

// ---------------------------------------------------------------------------
// makeEmpty
// Empty the list by deleting one node at a time starting for head

void List::makeEmpty(void) {
    if (isEmpty()) // If list is already empty, return
        return;
    Node *current = head;
    head = NULL; // Mark the head NULL to indicate list is empty
    while (current != NULL) {
        Node *tempCurrent = current->next;
        delete current; // Free the node        
        current = tempCurrent;
    };

}

// ---------------------------------------------------------------------------
// display:
// Displays the cointext information in a readable format
void List::display(string key)const {
    Node *temp = head;
    string printLeft; // place holder for 5 words before the key word
    string printRight; // place holder for 5 words appearing after

    while (temp != NULL) {
        printLeft = "";
        // Collect all the words appearing before in printLeft
        for (int i = 0; i < MAX_SIZE; i++) {
            printLeft.append(temp->before[i]);
            printLeft.append(" ");
        }
        cout.width(50);
        cout << printLeft;
        cout << right; // Right justify the output
        cout.width(20);
        cout << key << " ";
        printRight = "";
        // Collect all the words appearing after in printRight
        for (int i = 0; i < MAX_SIZE; i++) {
            printRight.append(temp->after[i]);
            printRight.append(" ");
        }
        cout << printRight;
        cout << endl;
        temp = temp->next;
    }
}
