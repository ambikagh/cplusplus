#ifndef PUZZLE_H
#define PUZZLE_H

//----------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   11/18/2015
// course: 501 Assignment 5

#include <iostream>
using namespace std;

#define FIXED 1
#define VARIABLE 0
#define BLOCK_SIZE 3
#define SUDOKU_SIZE 9
#define MIN_SIZE 0
#define MIN 0
#define MAX 9

// ---------------------------------------------------------------------------
// Puzzle class: Represents Sudoku puzzle. 
//        Holds square objects and enforces constraints among the squares 
//        in a row, column or block.
// Assumptions and constraints:
//  -- Puzzle size is a perfect square for ex, 4, 9 etc
//  -- Empty cells are represented by square object with a value '0'
//  -- Every square object holds a value of 0 - 9, any other value
//     is invalid
//  -- Every square object in a row, column or a block holds distinct
//     9 integer values, if there are any repeating values then 
//     sudoku cannot be solved, assumption is input is semantically 
//     valid
//  Input operator(>>): Reads a sequence of 81 integers, as ASCII text
//     operator should be able to read the input even if characters are not 
//     separated by white space
//  Output operator(<<): Writes sequence of 81 integers representing each 
//     cell in Sudoku puzzle with white spaces in between.


class square; // Make Square class visible to Puzzle class

class puzzle {
    // Reads sequence of 81 integers, as ASCII text
    friend istream& operator>>(istream&, puzzle&);
    // Outputs the 81 numbers separated by white space
    friend ostream& operator<<(ostream&, puzzle&);
    
public:
    puzzle();
    ~puzzle();
    // Returns const reference to Square object at the location given by
    //  -integer parameters in argument
    const square& get(int, int);
    // Set the value of Square object at the location specified by arguments 
    bool set(int, int, int); 
    // Set the state of Square object at the location specified by arguments
    void setState(int, int, int );
    void display()const; // Display the puzzle in human friendly format 
    int size()const; // counts number of variable entries in the puzzle
    int numEmpty()const; // Counts number of empty squares    
    bool solvePuzzle(); 
    
private:
    square *cells[9]; // Pointer to row of square objects
    bool solve(int, int); // solve the puzzle using backtracking algorithm
};

// Function to check whether number is out of bounds
bool outOfBounds(int);

#endif
