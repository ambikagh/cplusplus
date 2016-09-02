#ifndef WRITE_H
#define WRITE_H
#include <iostream>
#include <ios>
#include <fstream>
#include "char_encode.h"



class Writestream {
    typedef unsigned char uchar_t;
    unsigned char buffer;
    char nbits;
public:
    Writestream();
    void write_byte(std::ifstream&, std::fstream&, Char_encode&);
    void flush();
};

void Writestream::flush() {
    buffer = 0;
    nbits = 0;
}

Writestream::Writestream() {
    nbits = 0;
    buffer = 0;
}

void Writestream::write_byte(std::ifstream& input_text_file, std::fstream& huffile, Char_encode& symb_tab) {
    // Start reading the file from beginning
    input_text_file.clear();
    input_text_file.seekg(std::ios_base::beg);
    uchar_t data;
    uchar_t bit_count;
    uint64_t code;
    uchar_t *ch_arrp = nullptr;
    ch_arrp = reinterpret_cast<uchar_t*>(&code);
    while (!input_text_file.eof()) {
        data = input_text_file.get();
        symb_tab.get_members(data, bit_count, code);
        while (bit_count > 0) {
            if (ch_arrp[7] & 128) {
                buffer = buffer | (1 << (8 - nbits - 1));
            }
            nbits++;
            code = code << 1;
            bit_count--;
            if (nbits == 8) {
                huffile << buffer;
                flush();
            }
        }
    }
    huffile << buffer;
}


#endif
