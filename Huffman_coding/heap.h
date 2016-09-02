// ---------------------------------------------------------------------------
// Author: Mukambika Hegde  
// Date: 2/2/2016
// Course: 502, Heap and Heapsort

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum SIZE { EMPTY, ROOT }; // Root is the first index of array 

// ---------------------------------------------------------------------------
// Heap Class:
// Builds a heap structure by reading data from standard inputs, and sorts the
//    data using heapsort algorithm
// operator>> : This function is responsible for reading the data from 
//              standard input
// operator<< : This function is responsible for displaying Heap contents
//              onto standard output
// Member variables:
//        heapdata : is a vector which holds pointer to data of type 'T'
//        lastIndex : Holds index of last element in heap structure
// Member functions:
// push: Pushes data on to heap as and when it is read fron standard input
// pop: removes the first element from the heap and returns the element
// sort: Performs an in place sort of heapdata 
// destroyheap: Frees the memory allocated for heap
// is_empty : Returns true if the heap is empty false otherwise

template <typename T>
class Heap {
    // Read data from standard input and call 'push' function to build heap
    friend std::istream& operator>>(std::istream& infile, Heap<T> &neoHeap) {
        T *tnode;
        while (!infile.eof()) {
            if(infile.good()) {
                tnode = new T;
            	tnode->setdata(infile);
            	neoHeap.push(tnode);
            }
        }
        return infile;
    }
    // Display heap contents on standard output
    friend std::ostream& operator<<(std::ostream& output, Heap<T> &nHeap) {
        if (!nHeap.is_empty()) {
            for (int i = 1; i <= nHeap.lastIndex; i++) {
                output << *nHeap.heapdata[i];
                output << std::endl;
            }
        }        
        return output;
    }
public:
    typedef bool (*funcp)(const T*, const T*); 
    Heap();
    Heap(funcp); 
    ~Heap();
    void push(T *);
    T* pop(void);
    bool is_empty()const;
    void sort();
    static bool comparedata(const T*, const T*);
    void print()const;
private:
    std::vector<T*> heapdata; // Vector of T*
    int lastIndex; // Holds the last element in heap   
    funcp compare; 
    void destroyHeap(); // Clean up memory allocated for Heap
};

#include "heap.cpp"

#endif
