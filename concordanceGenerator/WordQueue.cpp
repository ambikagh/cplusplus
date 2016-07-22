// ---------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   12/4/2015
// Course: 501 Assignment 6
// ---------------------------------------------------------------------------

#include "WordQueue.h"

//----------------------------------------------------------------------------
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


// ---------------------------------------------------------------------------
// Constructor:
WordQueue::WordQueue() {
    head = NULL;
    tail = NULL;
    count = 0;
}

// ---------------------------------------------------------------------------
// Destructor:
WordQueue::~WordQueue() {
    makeEmpty(); // Empty the queue
}

// ---------------------------------------------------------------------------
// insertEnd:
// Insert the node with data "word" at the end of queue
void WordQueue::insertEnd(string word) {
    Node *tempNode = new Node;
    tempNode->data = word; // Set the data of new node with argument "word"
    tempNode->next = NULL;
    if (isEmpty()) { // Queue is empty
        head = tempNode; // Mark the first node as head
        tail = tempNode; // Mark the only node as tail
        count++; // Increment number of items in queue
        return;
    }
    tail->next = tempNode; // insert the node at the end
    tail = tempNode;
    count++;
}

// ---------------------------------------------------------------------------
// deleteBegin:
// Delete the first node in queue and return the data in deleted node
string WordQueue::deleteBegin() {
    string word;
    if (isEmpty()) {
        return ""; // Queue is empty, return empty string
    }
    // If there is only one node, head and tail both point to the same node
    if (head == tail) {
        tail = tail->next; // Make sure tail always points to a valid node
    }
    Node *tempNode = head; // Fetch the first node
    head = head->next;
    word = tempNode->data; // Fetch the data in first node
    delete tempNode;
    count--;
    return word;
}

// ---------------------------------------------------------------------------
// getCount:
// Returns the number of items in queue
int WordQueue::getCount(void)const {
    return count; // Return the number of items in queue
}

// ---------------------------------------------------------------------------
// isEmpty:
// Return true if the queue is empty return false otherwise
bool WordQueue::isEmpty()const {
    if (head == NULL && tail == NULL) {
        return true;
    }
    else {
        return false;
    }
}

// ---------------------------------------------------------------------------
// makeEmpty:
// Destroy the queue
void WordQueue::makeEmpty() {
    if (isEmpty()) {
        return;
    }
    Node *current = head;
    head = NULL; // Mark head as NULL to indicate queue is empty
    tail = NULL; // Mark tail as NULL to indicate queue is empty
    while (current != NULL) {
        Node *temp = current->next;
        delete current;
        current = temp;
    }

}

// ---------------------------------------------------------------------------
// copyWordsToArray:
// Copy words from "wordList" queue to array "wordArray"
void copyWordsToArray(WordQueue& wordList, string *wordArray) {
    WordQueue::Node *temp = wordList.head;
    int i = 0;
    while (temp != NULL) {
        wordArray[i++] = temp->data;
        temp = temp->next;
    }
}

