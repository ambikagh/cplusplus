#include "puzzle.h"
#include "square.h"

//----------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   11/18/2015
// course: 501 Assignment 5

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


// ---------------------------------------------------------------------------
// operator>>: Takes 81 ASCII characters as input and stores it in row major 
//    order in Puzzle.That is first 9 characters are placed in first row 
//    containing 9 Square objects, then second row and so on.Any number or 
//    character other than 0 - 9 is ignored.
// Note : Should be able to read the input even without spaces
istream& operator>>(istream& input, puzzle& sudoku1) {
    char temp; // Temporary variable to hold the input stream 
    bool errFlag = false;
    for (int i = 0; i < SUDOKU_SIZE && !errFlag; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            input >> temp;
            if (input.fail()) {
                cout << "Error reading file, check file" << endl;
                errFlag = true;
                break;
            }
            else if (temp != EOF) {
                // Ignore non integer characters
                if (!isdigit(temp) && j) {
                    j--;
                    continue;
                }
                // Set input values to the squares
                sudoku1.set(i, j, (temp - '0'));
                if ((temp - '0') > MIN && (temp - '0') <= MAX) {
                    sudoku1.setState(i, j, FIXED);
                }                
            }
        }
    }
    return input;
}

// ---------------------------------------------------------------------------
// operator<<: 
//  Outputs the puzzle as a sequence of 81 characters with spaces in between.
ostream& operator<<(ostream& output, puzzle& sudoku1) {
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            square s = sudoku1.get(i, j);
            output << s.getValue();
            output << " ";
        }
    }
    return output;
}

// ---------------------------------------------------------------------------
// Puzzle: Constructor
//         Builds a N x N puzzle 
puzzle::puzzle() {
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        cells[i] = new square[SUDOKU_SIZE];
        if (cells[i] == NULL) {
            cout << "Failed memory allocation " << endl;
        }
    }
}

// ---------------------------------------------------------------------------
// Puzzle destructor:
// Frees the memory allocated for Puzzle object
puzzle::~puzzle() {
    for (int i = 0; i < SUDOKU_SIZE; i++)
        delete[] cells[i];
}

// ---------------------------------------------------------------------------
// outOfBounds: Checks whether a integer is out of bounds 
// Paramenters: Integer 
// Returns: true if the number is outside the defined range
//          false if number is within range
bool outOfBounds(int num) {
    if (num < MIN_SIZE || num >= SUDOKU_SIZE)
        return true;
    else return false;
}

// ---------------------------------------------------------------------------
// get: 
// Parameters: location of square given by row and column of puzzle
// Return : Returns a const reference to square object
const square& puzzle::get(int row, int col) {
    return cells[row][col];
}

// ---------------------------------------------------------------------------
// set: Set the value of Square object at (row,col) location to 'val'
// Parameters: location of square object given by row and column, and value to
//      be set at that location.
// Return: Returns 'true' if value is successfully set at the location 
//      otherwise returns 'false'
bool puzzle::set(int row, int col, int val) {
    // Check if row and column exceed the allowed size
    if (outOfBounds(row) || outOfBounds(col)) {
        return false;
    }
    // If the value at the location given by (row,col) is fixed return false
    if (cells[row][col].status) {
        return false;
    }

    // tempArray keeps track of all the numbers in row, column and block
    // For ex: if row contains numbers 1,4,6 index of array at 1,4,6 
    //     is set to true
    bool tempArray[SUDOKU_SIZE + 1];
    // Initialize temporary array
    for (int i = 0; i < SUDOKU_SIZE + 1; i++) {
        tempArray[i] = false;
    }
    // Update status of presence of numbers in same row and column
    int cellValue; 
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        if (row >= SUDOKU_SIZE || col >= SUDOKU_SIZE) {
            break;
        }
        // fetch the value from every cell in the row
        cellValue = cells[row][i].getValue();
        if (cellValue) { // valid value > 0
            tempArray[cellValue] = true;
        }
        // fetch the value from every cell in the column
        cellValue = cells[i][col].getValue();
        if (cellValue) {
            tempArray[cellValue] = true;
        }
    }

    // Fetch the values in the block
    int newRow = (int)(row / BLOCK_SIZE) * BLOCK_SIZE;
    int newCol = (int)(col / BLOCK_SIZE) * BLOCK_SIZE;

    for (int i = newRow; i < (newRow + BLOCK_SIZE); i++) {
        for (int j = newCol; j < (newCol + BLOCK_SIZE); j++) {
            cellValue = cells[i][j].getValue();
            if (cellValue) {
                tempArray[cellValue] = true;
            }
        }
    }
    // Set the integer value "val" to the cell specified by "row" and "col"
    //   if "val" is not present in same "row", "col" or "block"
    if (val >= MIN && val <= MAX) {
        if (!tempArray[val]){
            cells[row][col].setValue(val);
            return true;
        }        
    }
    return false;
}

// --------------------------------------------------------------------------
// setState: Set the state of square at location (row,col) to "state"
void puzzle::setState(int row, int col, int state) {
    // if "row" or "col" is out of bounds
    if (outOfBounds(row) || outOfBounds(col))
        return;
    else {
        cells[row][col].setStatus(state);
    }    
}

// ---------------------------------------------------------------------------
// display: Displays the solved puzzle in a human friendly format.
//          Each row should print 19 characters. 9 digits 8 spaces and 2 '|'  
//          for non-divider lines and 17 '-' and 2'+' for divider lines
// Parameters:None
// Returns: None
void puzzle::display()const {
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            cout << cells[i][j].getValue() << " ";
            if ((j + 1) % BLOCK_SIZE == 0) {
                cout << "| ";
            }
        }
        cout << endl;
        if ((i + 1) % BLOCK_SIZE == 0) {
            for (int i = 0; i < 23; i++) {
                cout << "-";
            }
        }
        cout << endl;
    }
}

// ---------------------------------------------------------------------------
// size: Counts number of entries in the puzzle corresponding to original 
//       size before any empty squares are filled
// Parameters: None
// Returns: number of original entries in the puzzle
int puzzle::size()const {
    int count = 0;
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            if ((cells[i][j].getValue() > MIN) && 
                (cells[i][j].getStatus() == FIXED)) {
                count++;
            }
        }
    }
    return count;
}

// ---------------------------------------------------------------------------
// numEmpty: Counts number of empty cells in the puzzle
// Parameters: None
// Returns: Number of empty cells
int puzzle::numEmpty()const {
    int count = 0;
    for (int i = 0; i < SUDOKU_SIZE; i++) {
        for (int j = 0; j < SUDOKU_SIZE; j++) {
            if (cells[i][j].getValue() == MIN) {
                count++;
            }
        }
    }
    return count;
}

// ---------------------------------------------------------------------------
// solvePuzzle
// Parameters: None
// Returns: true if puzzle is solved, false otherwise
bool puzzle::solvePuzzle() {
    return solve(0, 0);
}

// ---------------------------------------------------------------------------
// solve
// Parameters: Row and column numbers
// Returns: true if puzzle is solved false otherwise
bool puzzle::solve(int row, int col) {
    // check if row and column are out of bounds
    if (outOfBounds(row) || outOfBounds(col)) {
        return false;
    }

    // row, column past end of the puzzle, return success
    if (row == SUDOKU_SIZE - 1 && col == SUDOKU_SIZE - 1) {
        return true;
    }
    
    // Move to the next square without a value
    while (row < SUDOKU_SIZE && col < SUDOKU_SIZE) {
        if (cells[row][col].getValue() == MIN) {
            break;
        }
        else {
            if (col == SUDOKU_SIZE - 1)
            {
                col = 0;
                row++;
            }
            else
            {
                col++;
            }
        }
    }

    if (row == SUDOKU_SIZE)
    {
        return true;
    }
    // Find a legal value to set to the square
    bool legalValue = false;
    for (int i = 1; i <= SUDOKU_SIZE && !legalValue; i++) {
        legalValue = set(row, col, i);
        if (!legalValue) { // value is illegal
            continue; // Try next number
        }
        if (legalValue) { // value is legal
            if (solve(row, col)) { // solve next row and column
                return true;
            }
            else {
                legalValue = false;
            }
        }
    }
    if (!legalValue) {
        // Erase the square value
        if (row < SUDOKU_SIZE && col < SUDOKU_SIZE) {
            if (!cells[row][col].getStatus()) { // status is not fixed
                cells[row][col].setValue(MIN); // erase the value
            }
        }     
        return false;
    }
}
