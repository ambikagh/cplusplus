#ifndef CHAR_ENCODER_H
#define CHAR_ENCODER_H
#include <iostream>
#include <climits>

// char encode class 
// Used for building symbol table
class Char_encode {
    typedef unsigned char uchar_t;
    struct encode {
        char bitcount; // number of bits used to represent a symbol
        uint64_t encoded_char; // encoded character
        encode() :bitcount(0), encoded_char(0) {};
    };
    encode enchar[UCHAR_MAX + 1];
public:
    void operator=(const Char_encode &);
    void set_members(unsigned char, uchar_t, uint64_t);
    void get_members(unsigned char, uchar_t&, uint64_t&)const;
};

// overloaded assignment operator
void Char_encode::operator=(const Char_encode &rencoded) {
    if (this !=  &rencoded) {
        for (int i = 0; i <= UCHAR_MAX; i++) {
            enchar[i].bitcount = rencoded.enchar[i].bitcount;
            enchar[i].encoded_char = rencoded.enchar[i].encoded_char;
        }
    }
}

// setter function for the class
void Char_encode::set_members(unsigned char index, uchar_t count, uint64_t code) {
    enchar[index].bitcount = count;
    enchar[index].encoded_char = code;
}

// getter function for the class
void Char_encode::get_members(unsigned char index, uchar_t& bitcountp, uint64_t& codep) const {
    bitcountp = enchar[index].bitcount;
    codep = enchar[index].encoded_char;
}
#endif


