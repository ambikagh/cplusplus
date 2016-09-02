#ifndef HUFFNODE_H
#define HUFFNODE_H
#include <iostream>
#include "data.h"

template <typename Y>
class Hufftree;

// Huffnode class
// Each node consists of --> key pointer of type Y
//                       --> left and right pointer
template <typename Y>
class Huffnode {
    friend class Puff;
    template <typename Z>
    friend class Hufftree;
    friend inline std::ostream& operator<<(std::ostream& out, Huffnode& h) {
        out << *h.key;
        return out;
    }
    Y* key; 
    Huffnode *left;
    Huffnode *right;
    bool isleaf; // set to 1 if node is a leaf otherwise set to 0
public:
    Huffnode() :key(nullptr), left(nullptr), right(nullptr), isleaf(true) {};
    Huffnode(Y *k) : key(k), left(nullptr), right(nullptr), isleaf(true) {};
    Huffnode(Y *k, Huffnode *l, Huffnode *r, bool leafflag) : 
        key(k), left(l), right(r), isleaf(leafflag) {};
    ~Huffnode();
    bool operator<(const Huffnode&) const;
    bool operator>(const Huffnode&) const;
    // Merges contents of two nodes to form a new node
    Huffnode<Y>* merge(Huffnode *) ; 
    void print()const;
};

template <typename Y>
Huffnode<Y>::~Huffnode() {
    delete key;
    key = nullptr;
    left = right = nullptr;
}

// Compares two keys, '<' function defined by 'Y' class is responsible for
//    the comparison of keys
template <typename Y>
bool Huffnode<Y>::operator<(const Huffnode& r) const {
    return *key < *r.key ? true : false;
}

template <typename Y>
bool Huffnode<Y>::operator>(const Huffnode& r) const {
    return *key > *r.key ? true : false;
}

// Merges two nodes to form a new node 
// key of the resulting node is sum of keys of two nodes
template <typename Y>
Huffnode<Y>* Huffnode<Y>::merge(Huffnode *rnode) {
    Y *temp_key;
    if (rnode) {
        temp_key = *key + *rnode->key;
    }
    else {
        return this; // if there is no rnode, return this
    }
    // create a new node with the 'temp_key'
    Huffnode<Y> *tempnode = new Huffnode<Y>(temp_key, this, rnode,false);
    return tempnode;
}

// display the contents of key
template <typename Y>
void Huffnode<Y>::print()const {
    std::cout << *this->key;
}

#endif
