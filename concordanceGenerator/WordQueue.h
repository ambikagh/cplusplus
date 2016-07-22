// ---------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   12/4/2015
// Course: 501 Assignment 6
// ---------------------------------------------------------------------------

#include <iostream>
#define MAX_SIZE 5
using namespace std;

//--------------------------  class WordQueue  -------------------------------
// ADT WordQueue: finite, ordered collection of zero or more items.
//           The order is first in first out
//          
// Assumptions:  
//   -- Insertions is always done at the end and deletion at the beginning  
//   -- There is no dummy head node, head points to first node.  
//      If the list is empty, head is NULL.
//   -- The insert allocates memory for a Node, data is passed in as argument
//      Allocating memory and setting data is the responsibility of the caller
//   -- deleteBegin removes the Node at the beginning, returns data
//   -- insertEnd inserts the node at the end   
//   -- 
//----------------------------------------------------------------------------



class WordQueue {    
    struct Node {
        string data; 
        Node *next;
    };
    // Head points to the first node of the queue
    // Tail points to the last node of the queue
    Node *head, *tail;
    int count;
    void makeEmpty(); // Empty the queue
    
public:
    WordQueue();
    ~WordQueue();
    //WordQueue& operator=(const WordQueue&);
    void insertEnd(string); // Insert a node at the end of the queue
    string deleteBegin(void); // Delete the first node 
    bool isEmpty()const; // Check if queue is empty
    int getCount(void)const; // Get the number of items in queue
    // copy words from queue to array
    friend void copyWordsToArray(WordQueue&, string *); 
};

