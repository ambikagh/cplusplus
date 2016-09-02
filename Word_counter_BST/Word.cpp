//----------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   01/11/2016
// course: 502 Assignment 1 (word frequency counter)

#include "Word.h"

using namespace std;

// ---------------------------------------------------------------------------
// setdata: Read from standard input and set the data
void Word::setdata(istream& infile) {
    infile >> word;
}

bool Word::operator<(const Word &right)const {
    
    return word < right.word ? true : false;
}

bool Word::operator>(const Word &right)const {

    return word > right.word ? true : false;
}

bool Word::operator==(const Word &right)const {

    return word == right.word ? true : false;
}

