//----------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   01/11/2016
// course: 502 Assignment 1 (word frequency counter)

#ifndef WORD_H
#define WORD_H

#include <string>
#include <iostream>
#include <fstream>

// ---------------------------------------------------------------------------
// Word class: represents a word 
//             Each object holds a word
// Setdata: sets data from file
// operator <,>, ==: compare two Word objects, returns true if calling object
//                   is greater than, less than, equal to parameterized object
//                   respectively

class Word {
    friend std::ostream&  operator<<(std::ostream& output, const Word& right) {
        output << right.word;
        return output;
    }
public:
    Word() { word = ""; }
    ~Word() { }
    Word(std::string key) { word = key; }
    void setdata(std::istream&);
    bool operator<(const Word&)const;
    bool operator>(const Word&)const;
    bool operator==(const Word&)const;
private:
    std::string word;
};
#endif
