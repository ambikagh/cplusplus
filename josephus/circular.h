// ---------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   11/12/2015
// Course: 501 Assignment 3
// ---------------------------------------------------------------------------
#ifndef CIRCULAR_H
#define CIRCULAR_H

// Circular linked list
#include <iostream>
using namespace std;

#define MIN_ORDER 0
#define MIN_MAN_COUNT 0

// ------------------------------clas Circularlist----------------------------
// ADT Circularlist: Finite, collection of zero or more items in circular 
//                   fashion, last node points to first node
// Implementations and assumptions:
//    -- Implemented as circular linked list
//    -- head Node provides the entry point to circular list
//    -- buildlist: accepts an integer parameter(call it 'n') and builds a  
//           circular linked list with items 1 to n, item respresents persons
//    -- find_josephus: accepts parameter k such that k>=0
// Assumptions:
//    -- Input parameters 'n' and 'k' are always integers
//    -- Input is always within the range of integer type
// Note: This definition is not a complete class and does not include 
//       any overloaded operators
// ---------------------------------------------------------------------------

class Circularlist {
public:
	Circularlist();
	~Circularlist();
	void buildlist(int); // Build circular linked list with items 1 to n in it
	bool isEmpty()const; // Check if list is empty
	void makeEmpty(); // Clear the list
	int find_survivor(int); // Find the survivor in Josephus problem
private:
	struct Node {
		int item;
		Node* next;
	};
	Node *head;
};

#endif
