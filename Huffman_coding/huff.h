#ifndef HUFF_H
#define HUFF_H
#include <iostream>
#include <fstream>
#include <climits>
#include "heap.h"
#include "hufftree.h"
#include "writestream.h"

// --------------------------------------------------------------------------
// Huff class:
// Implements huffman coding algorithm to compress a text file and outputs
//   the compressed data into a .huff file 
// freq_counter: This function reads one character at a time from the 
//               input file and calculates the frequency of occurrence
//               of each character.
// build_prio_q: builds prio queue from freq count table
// build_huffman_tree: builds huffman tree from priority queue
// write_bit_streams: writes symbol table to the .huff file followed by 
//                    encoded text
class Huff {
    typedef unsigned char uchar_t;
    template <typename Y>
    friend class Hufftree;
    friend class Writestream;
    friend inline std::ostream& operator<<(std::ostream& out, Huff &h) {
        for (int i = 0; i<(UCHAR_MAX + 1); i++) {
            ;
        }
        return out;
    }    
    // Tracks the character and its frequency    
    uint32_t char_count[UCHAR_MAX + 1];
    // counts the total number of characters in input file
    uint32_t total_char_count;
    // Symbol table representing bit counts of each character and 
    //   encoded character representation 
    Char_encode coded_symbtable;
    Heap<Huffnode<Data>> pri_q;
    Hufftree<Data> *ht; // hufftree generated from prio queue
    Writestream write_to_file;
    void freq_counter(std::ifstream&);
    void build_prio_q();
    void build_huffman_tree();
    void write_bit_streams(std::ifstream&, std::fstream&);
    void dump()const;
 
public:
    Huff();
    ~Huff();
    void encoder(std::ifstream&, std::fstream&);
   };


Huff::Huff() {
    // initialize the frequency table
    for (int i = 0; i<(UCHAR_MAX + 1); i++) {
        char_count[i] = 0;
    }
    total_char_count = 0;
    ht = nullptr;
}

Huff::~Huff() {
    delete ht; // delete hufftree object
    ht = nullptr;
}

// freq_counter: counts the frequency of characters
// Number of unque characters do not exceed 256, hence 
//   each character and its counts can be represented as
//   array of unsigned integers of length 256, where index
//   indicates the character and count indicates the frequency
void Huff::freq_counter(std::ifstream& infile) {
    unsigned char data;
    while (!infile.eof()) {
        data = infile.get();
        if (data == 0xff)
            break;
        // get next character from file
        total_char_count++;
        // increment frequency
        char_count[data]++;
    }
}

// Build the priority queue from frequncy counter
// Prio queue consists Huffnode objects as key
// Huffnode objects are created from freq table
// Each node consists pointer to key which is of tye "Data" provided by 
//   "Data" class
// This function makes use of Heap class to construct the 
//   priority queue
void Huff::build_prio_q() {
    Huffnode<Data> *tempnode;
    int i = 0;
    for (i = 0; i<(UCHAR_MAX + 1); i++) {
        if (char_count[i]) {
            Data *temp;
            temp = new Data(uchar_t(i), char_count[i]);
            tempnode = new Huffnode<Data>(temp);
            pri_q.push(tempnode);
        }
    }
}

#ifdef DEBUG_HUFF
// displays bar chart of characters and its frequency
void Huff::dump()const {
    for (int i = 0; i<=UCHAR_MAX; i++) {
        int j = char_count[i];
        std::cout << uchar_t(i) << ":" << char_count[i] << "-->";
        while (j>0) {
            std::cout << "*";
            j--;
        }
        std::cout << std::endl;
    }
}
#endif

// Build huffman tree from priority queue
// Nodes are popped from priority queue, parent node is created
//   using frequency of the child nodes and pushed back
// Single node is left at the end is the rootnode of the 
//   newly formed huff tree
void Huff::build_huffman_tree() {
    while (!pri_q.is_empty()) {
        Huffnode<Data> *lnode = pri_q.pop();
        if (pri_q.is_empty()) {
            pri_q.push(lnode);
            break;
        }
        // pop the smallest two items from priority queue to form
        //  a parent node and push the node back on queue
        Huffnode<Data> *rnode = pri_q.pop();
        Huffnode<Data> *parent = lnode->merge(rnode);
        pri_q.push(parent);
    }
    // pop the last node and set it as the root of huff tree
    ht = new Hufftree<Data>(pri_q.pop());
#ifdef DEBUG_HUFF
    ht->dump();
#endif
}

// Write symbol table byte by byte to the huff file
// Function writes bit_count followed by its coded value
//   for example if 'a' bit_count = 3 and code = '110' 
//   then table is written as 00000011 11000000
//   if character does not occur in a file then bit_count = 0
//   only 1 byte is written to represent bit_count is 0 as 00000000
// Symbol table is written for 256 symbols followed by 
// total_char_count, if total count is 0xabcd then in .huff file
//   it is 11001101 10101011 00000000 00000000
// Total_char_count is followed by encoded value of the text
void Huff::write_bit_streams(std::ifstream& infile, std::fstream& outfile) {
    // Write symbol table to file
    for (int i = 0; i <= UCHAR_MAX; i++) {
        uchar_t *ch_arrp;
        uchar_t bit_count;
        uint64_t code;
        coded_symbtable.get_members(i, bit_count, code);
        outfile << bit_count;
        // calculate no of bytes to be written
        int no_of_bytes = ((bit_count + 7) & (~7)) >> 3;
        // access the coded symbol byte by byte
        ch_arrp = (uchar_t *)&code;
        for (int j = 0; j < no_of_bytes; j++) {
            outfile << ch_arrp[7 - j];
        }
    }
    // output the total character count to the file
    uchar_t *chp;
    chp = (uchar_t *)&total_char_count;
    for (unsigned int i = 0; i < sizeof(total_char_count); i++) {
        outfile << chp[i];
    }
    // Read text file and write the encoded value to .huff file
    write_to_file.write_byte(infile, outfile, coded_symbtable);
}

void Huff::encoder(std::ifstream& infile, std::fstream& huffile) {
    // count frequncy of each character in file
    freq_counter(infile);
    // Build priority queue of characters and its frequency 
    //   keeping the frequency count of characters as the key
    build_prio_q();
#ifdef DEBUG_HUFF   
    // Dump routine for the frequency counter
    dump();
    // Dump routing for the priority queue
    pri_q.print();
#endif
    // Build the huffman tree from priority queue
    build_huffman_tree();
#ifdef DEBUG_HUFF    
    // Validate if hufftree is a valid tree
    ht->validate_hufftree();
#endif    
    // build symbol table
    coded_symbtable = ht->build_symb_table();
    // Write symbtable to a file
    write_bit_streams(infile, huffile);
}

#endif






