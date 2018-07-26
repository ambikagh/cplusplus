// ---------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   11/12/2015
// Course: 501 Assignment 3
// ---------------------------------------------------------------------------
// Main function to test Josephus problem

#include "circular.h"

// ---------------------------------------------------------------------------
// In main, values for 'n'(number_of_companions) and 'k'(order)
//    are read multiple times and winner is output for every 'n' and 'k'
// When n and k both are entered value of '0', exit the loop

int main() {
    Circularlist mylist, mylist2; 
    int number_of_companions; // number of companions
    int order; // Order in which people have to be executed. 
    int survivor = 0; // contains survivor number at the end of each loop
    cout << "Enter number of men, and the order" << endl;
    cin >> number_of_companions >> order;
    if (cin.fail()) { // Number is too big for integer
        cout << "Number too long" << endl;
        return 0; // Exit from program
    }
    do {
        // Exit the loop if both n and k are '0'
        if (number_of_companions == MIN_MAN_COUNT && order == MIN_ORDER)
            break;
        // Build a circular linked list of n items
        mylist.buildlist(number_of_companions);
        // inputs are valid, find survivor
        if (!mylist.isEmpty() && order >= MIN_ORDER) {
            survivor = mylist.find_survivor(order);
            cout << "survivor is: " << survivor << endl;
        }
        else { // inputs are invalid, accept inputs again
            cout << "Invalid inputs, enter number of companions>0";
            cout << "and order >= 0" << endl;
        }
        // Empty the circular list before accepting next set of inputs
        mylist.makeEmpty();
        cout << "Enter number of men, and the order" << endl;
        cin >> number_of_companions >> order;
        if (cin.fail()) { // Number is too big for integer
            cout << "Number too long" << endl;
            break; 
        }
    } while (number_of_companions || order); // exit condition not satisfied

	return 0;
}