#ifndef HUFFTREE_H
#define HUFFTREE_H
#include <iostream>
#include "huffnode.h"
#include "char_encode.h"
#include <climits>

#define DEBUG_HUFF

template <typename Y>
class Hufftree {
    typedef unsigned char uchar_t;
public:
    typedef void(*walkpfn)(Huffnode<Y>*);
private:
    friend std::ostream& operator<<(std::ostream& out, Hufftree &htree) {
        if (htree) {
            htree->walk(print);
        }
        return out;
    }
    Huffnode<Y> *root;
    void print(Huffnode<Y> *);
    void inorder(Huffnode<Y> *, walkpfn) const;
    void destroy_tree(Huffnode<Y>*);
    void build_symbol_code(Huffnode<Y> *, uint64_t , unsigned int , int , Char_encode &) const;
    void validate(Huffnode<Y> *)const;
    
#ifdef DEBUG_HUFF
    void dumptree(Huffnode<Y>*,int)const;
#endif
public:    
    Hufftree() : root(nullptr) {};
    Hufftree(Huffnode<Y> *r) : root(r) {};  
    ~Hufftree();
    void walk(walkpfn)const ; 
    Char_encode build_symb_table()const;
    void build_hufftree(Char_encode &);
    void validate_hufftree()const;
    Huffnode<Y>* get_root();
#ifdef DEBUG_HUFF
    void dump()const;
    void display(Huffnode<Y>*)const;
#endif
};

#include "hufftree.cpp"
#endif

