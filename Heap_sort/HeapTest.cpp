// ---------------------------------------------------------------------------
// Author: Mukambika Hegde  
// Date: 2/2/2016
// Course: 502, Heap and Heapsort

// Reads words (one word per line) from standard input and emits the sorted 
// words to standard output. Does not remove duplicates or count occurrences. 

#include <iostream>
#include "Heap.h"
#include "Word.h"
using namespace std;

int main() {
    Heap<Word> newHeap(Heap<Word>::comparedata);
    cin >> newHeap;
    newHeap.sort();
    cout << newHeap;    
    return 0;
}
