#include "square.h"
#include <fstream>

int main() { 
    /*
    square s; // default constructor is called
    cout << "value = " << s.getValue() << endl;
    cout << "status =" << s.getStatus() << endl;

    square s1(3, 1); // Paramterized constructor
    cout << "value = " << s1.getValue() << endl;
    cout << "status =" << s1.getStatus() << endl;

    puzzle p;
    cout << p << endl;
    // Test to evaluate "set" and "get" functions
    bool success = p.set(0, 0, 1);
    if (success) {
        p.setState(0, 0, FIXED);
    }
    else {
        cout << "could not set the value" << endl;
    }
    p.display();

    success = p.set(0, 0, 2);
    if (!success) {
        cout << "Value is already set" << endl;
    }
    cout << "value at 0,0 is " << p.get(0, 0).getValue() << endl;
    p.setState(0, 0, VARIABLE);

    success = p.set(0, 0, 2);
    if (!success) {
        cout << "Value is already set" << endl;
    }
    else {
        cout << "successfully set the value at 0,0 to 2" << endl;
    }
    p.display();

    cout << "Number of empty cells " << p.numEmpty() << endl;
    cout << "Size of the sudoku " << p.size() << endl;

    success = p.set(0, 0, 7);
    cout << "Success setting value " << success << endl;
    p.setState(0, 0, FIXED);
    cout << "Number of empty cells " << p.numEmpty() << endl;
    cout << "Size of the sudoku " << p.size() << endl;

    cout << "in Puzzle" << endl;
    p.display();
    success = p.set(0, 5, 3);
    cout << "success value " << success << endl;
    success = p.set(0, 5, -11);
    cout << "success value " << success << endl;
    success = p.set(0, 3, 10);
    cout << "success value " << success << endl;
    success = p.set(10, 5, 3);
    cout << "success value " << success << endl;
    success = p.set(5, 11, 3);
    cout << "success value " << success << endl;
    success = p.set(0, 0, 8);
    cout << "success value " << success << endl;
    success = p.set(9, 9, 1);
    cout << "success value " << success << endl;

    s = p.get(0, 4);
    cout << s.getValue() << endl;
    if (p.solvePuzzle()) {
        p.display(); // Display the puzzle if you are its solved
    }
    else {
        cout << "cannot solve puzzle " << endl;
    }
    cout << "Number of empty cells " << p.numEmpty() << endl;
    cout << "Size of the sudoku " << p.size() << endl;*/


    puzzle p1;
    cin >> p1;
    cout << "Initial input " << endl;
    p1.display();
    if (p1.solvePuzzle()) {
        cout << "successfully solved the puzzle" << endl;
        p1.display();
    }
    else {
        cout << "Puzzle cannot be solved " << endl;
    }
    return 0;
}