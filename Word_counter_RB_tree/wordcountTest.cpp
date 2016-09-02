//----------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   01/21/2016
// course: 502 Assignment 1 (word frequency counter)

// This program finds the frequency of each word in some text.
// Program reads the words from standard input and emits to the standard o/p
// Program is implemented using Red Black Binary search tree, which keeps 
//   the tree balanced even when we encounter pathological cases such as 
//   already sorted inputs. 
// In a normal binary search tree when we encounter sorted inputs or 
//    reverse sorted inputs, complexity of 

#include "RB_Tree.h"
#include "Word.h"
#include <fstream>

using namespace std;

int main() {
    RB_Tree<Word> bst1; 
    cin >> bst1; // Read from standard input
    Order order1 = INORDER;
    // Walk the Red Black tree in "inorder" fashion
    bst1.walk(&RB_Tree<Word>::print, order1);
#ifdef DEBUG_RBTREE
    bst1.dumptree();
#endif
    return 0;    
}