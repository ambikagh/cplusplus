// ---------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   11/12/2015
// Course: 501 Assignment 3
// ---------------------------------------------------------------------------
// Implementation of Josephus problem

#include "circular.h"

// ---------------------------------------------------------------------------
// Circularlist: Constructor
Circularlist::Circularlist() {
	head = NULL;
}

// ---------------------------------------------------------------------------
// Circularlist: Destructor
Circularlist::~Circularlist() {
	if (!isEmpty()) { 
		makeEmpty();
	}
}

// ---------------------------------------------------------------------------
// isEmpty
// Returns TRUE if the circular list is empty otherwise return FALSE
bool Circularlist::isEmpty()const {
	return head == NULL ? true : false;
}

// ---------------------------------------------------------------------------
// makeEmpty
// Clear the circular linked list by deleting items in the list
void Circularlist::makeEmpty() {
	if (isEmpty()) {
		return;
	}
	Node* temp = head->next;
	// Parse the circular list until only head node is left
	while (temp != head ) {
		head->next = temp->next;
		delete temp;
		temp = head->next;
	}
    // Delete the last node in the list and mark the list as empty
	temp = head;
	head = NULL;
	delete temp;
}

// ---------------------------------------------------------------------------
// buildlist
// buildlist accepts integer parameters no_of_companions and builds a circular 
//   linked list with Nodes containin 1 to no_of_companions in data field 
//   Each node represents a companion in Josephus problem
//   Each companion is represented by data field numbered from 1.
//   For Ex: First person is represented as '1' and second as '2' & so on
void Circularlist::buildlist(int no_of_companions) {
    // return to calling function if man_count value is invalid
    // For example if man_count is -ve or if it is more than max count
	if (no_of_companions <= MIN_MAN_COUNT)
		return;
	else {// Valid value 
		Node *temp1;
		Node *temp2 = NULL;
        // Create circular linked list
		for (int i = 1; i <= no_of_companions; i++) {
			temp1 = new Node;
			temp1->item = i;
			if (head == NULL) { // Mark an entry point to the circular list
				head = temp1;
				temp2 = temp1;
			}	
			temp2->next = temp1;
			temp2 = temp1;
		}
		temp2->next = head; // Last node points to first node
	}
}

// ---------------------------------------------------------------------------
// find_josephus
// Function accepts number of me
int Circularlist::find_survivor(int order){
	if (isEmpty() || order < MIN_ORDER)
		return 0;
	if (order == MIN_ORDER) { 
		Node* tail = head;
		// Tail points to the last item in the circular list before head
		while (tail->next != head) {
			tail = tail->next;
		}
		Node* temp = head;
        // Delete one node at a time
		while (head != tail) {
			head = temp->next;
			delete temp;
			tail->next = head;
			temp = head;
		}
		return head->item; // Last item is the survivor
	}
	else { // order is not 0
		int count = 1; // variable keeping count of nodes to be skipped
		Node* current = head->next;
		Node* previous = head;
		if (current == previous) // Only one node in circular list
			return head->item;
		else{
			while (previous != current) {
                // Delete the current node if count is equal to order
				if (count == order) {
					previous->next = current->next;
					previous = previous->next;
					delete current;
					current = previous->next;
                    // Reset the count to 1
					count = 1; 
				}
				else {
                    // Number of nodes skipped is not equal to order
					count++;
					previous = current;
					current = current->next;
				}
			}
            // Return the last item(winner) in the circular list
			head = previous;
			return head->item;
		}
	}
}



