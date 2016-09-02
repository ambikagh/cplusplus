#ifndef DATA_H
#define DATA_H
#include <iostream>

// Data class
// symbol -> represents character in an input file
// symbol_freq -> number of times the 'symbol/character' occurs in file
//                This is the key responsible for deciding output of 
//                comparison functions(character value is not the key)
//                For exambple character a symb_freq = 5
//                             character b symb_freq = 3
//                             a > b returns true even
// overloaded operators >, <, are responsible for the the comparison 
class Data{
public:
    Data() :symbol(0), symb_freq(0) {};
    Data(unsigned char s, uint32_t key) :symbol(s), symb_freq(key) {};
    ~Data();
    bool operator<(const Data&)const; 
    bool operator>(const Data&)const;
    bool operator==(const Data&)const;
    bool operator!=(const Data&)const;
    Data* operator+(Data &);
    Data& operator=(Data&);
    unsigned char get_symbol();
    void set_symbol(unsigned char);
private:
    friend std::ostream& operator<<(std::ostream& out, Data &d){
        std::cout << d.symbol <<":" << d.symb_freq ;
        return out;
    }
    unsigned char symbol;  
    uint32_t symb_freq; // symbol frequency  
};

Data::~Data() {

}

// Returns true if the calling object symb_freq is less than rdata symbol freq
bool Data::operator<(const Data& rdata)const{
    return symb_freq < rdata.symb_freq ? true : false;
}

// Returns true if the calling object symb_freq is greater than rdata symb_freq
bool Data::operator>(const Data& rdata)const{
    return symb_freq > rdata.symb_freq ? true : false;
}

// Returns true if symb freq of both the objects are equal
bool Data::operator==(const Data& rdata)const{
    return (symb_freq == rdata.symb_freq && symbol == rdata.symbol)? true : false;
}

// Returns true if symbo freq of calling object and parameter object is different
bool Data::operator!=(const Data& rdata)const{
    return !(*this == rdata);
}

Data* Data::operator+(Data &rhs) {
    Data *temp = new Data;
    temp->symb_freq = symb_freq + rhs.symb_freq;
    return temp;
}

Data& Data::operator=(Data& rhs) {
    if (*this != rhs) {
        symbol = rhs.symbol;
        symb_freq = rhs.symb_freq;
    }
    return *this;
}

unsigned char Data::get_symbol() {
    return symbol;
}

void Data::set_symbol(unsigned char ch) {
    symbol = ch;
}
#endif

