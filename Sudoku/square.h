#ifndef SQUARE_H
#define SQUARE_H
//----------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   11/18/2015
// course: 501 Assignment 5

#include "puzzle.h"

// ---------------------------------------------------------------------------
// Square class: holds all the information regarding one location in puzzle
// value   : Represents the value in that location, empty locations hold '0'
//        value is always an integer and is in the range of 0 to 9 inclusive
// status  : Represents whether the value in location is fixed or variable
//        value of 1 -> fixed, 0 -> variable
// getValue: Returns current value, returns -1 if no value is set
// setValue: Takes one integer parameter and Sets the current value to the 
//        integer parameter
//        Constraints for setting the value are enforced by Puzzle class

class square {
    friend puzzle;
protected:
    void setValue(int); // Set the value of Square object to integer parameter
    void setStatus(int); // set the status of Square 
public:
    square();
    square(int,int);
    int getValue(void)const; // Get the value of Square object  
    int getStatus(void) const; // Get the status of Square object
private:
    int value; // Holds value of each cell in puzzle
    int status; // Represents if the value is fixed or variable
};


#endif