#ifndef PUFF_H
#define PUFF_H
#include <iostream>
#include <fstream>
#include "data.h"
#include "hufftree.h"
#include "char_encode.h"
#include <climits>
// Puff class: responsible for decodind the compressed .huff file
class Puff {
    typedef unsigned char uchar_t;
    template <typename Y>
    friend class Hufftree;
    Char_encode decoded_symbtable;
    Hufftree<Data> *pt;
    // holds total character count obtained by decoding .huff file
    uint32_t total_char_count; 
    // Read .huff file and decode it , output is written to .puff file
    void read_huff_file(std::fstream&,std::ofstream&);
public:
    Puff();
    ~Puff();
    void decoder(std::fstream&,std::ofstream&);
    // reconstructs symbol table from .huff file
    void reconstruct_symb_table(std::fstream& );
    // reconstructs huff tree using symbol table 
    void reconstruct_hufftree();    
};

#include "puff.cpp"
#endif
