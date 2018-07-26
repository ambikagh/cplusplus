#include "square.h"

//----------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   11/18/2015
// course: 501 Assignment 5

// ---------------------------------------------------------------------------
// Square Class: holds all the information associated with each location in 
//               puzzle
// value: value at each lovation 
// status: indicates whether the value is "fixed" or "variable"

// ---------------------------------------------------------------------------
// Square: Default Constructor
// Initializes the private members
square::square() {
    value = 0;
    status = 0; // value is not fixed initially
}

// ---------------------------------------------------------------------------
// Parameterized constructor, initializes value according to the parameter
square::square(int val,int state) {
    value = val;
    status = state;
}

// ---------------------------------------------------------------------------
// getValue: fetch the value of Square object
int square::getValue(void)const {
    return value;
}

// ---------------------------------------------------------------------------
// getStatus: fetch the status of square object
int square::getStatus(void)const {
    return status;
}

// ---------------------------------------------------------------------------
// setValue: Set the "value" to "val"
void square::setValue(int val) {
    value = val;
}

// ---------------------------------------------------------------------------
// setStatus: set the "status" to "state"
void square::setStatus(int state) {
    status = state;
}