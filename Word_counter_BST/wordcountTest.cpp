//----------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   01/11/2016
// course: 502 Assignment 1 (word frequency counter)

#include "Tree.h"
#include "Word.h"
#include <fstream>

using namespace std;

template <typename T>
void print(T data) {
    cout << data;
    cout << endl;
}

int main() {
    Tree<Word> bst1;
    cin >> bst1;
    Order order1 = INORDER;
    bst1.walk(print, order1);
    return 0;    
}