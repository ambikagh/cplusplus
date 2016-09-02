//----------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   01/11/2016
// course: 502 Assignment 1 (word frequency counter)

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "Word.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

// Enumeration to specify the order in which data is to be displayed
enum Order { INORDER, PREORDER, POSTORDER };

// ---------------------------------------------------------------------------
// Tree class: Represents binary search tree 
//             Each node in tree holds a data and number of times the data
//             repeats in input.
// Tree class has two public methods
// add(): Inserts the data into tree or increases the count if the data  
//        already exists in tree
// walk(): Visits every node in correct order and displays the count and data

// Assumptions and constraints:
//  -- Input file is preporcessed with one word per line with no 
//     extraneous punctuation.

template <typename T>
class Tree {
    // Reads the data list from standard input and builds the binary search 
    //    tree as and when the data is read.
    friend std::istream& operator>>(std::istream& infile, Tree& bst){
        T *tnode;
        while (!infile.eof()) { 
            tnode = new T; 
            tnode->setdata(infile); 
            if (!bst.add(tnode)) {
                delete tnode;
            }
        }
        return infile;
    }

public:
    Tree();
    ~Tree();
    bool add(T *); 
    void walk(void (*function)(T ), enum Order)const;
private:
    struct Node {
        T *key; 
        int count;
        Node *left;
        Node *right;
        // constructor
        Node(T *keydata) : key(keydata), count(1), left(NULL), right(NULL){}
    };
    Node *root;
    void makeEmpty(Node *);
    void inorder(Node *, void(*function)(T ))const;
    void preorder(Node *, void(*function)(T))const;
    void postorder(Node *, void(*function)(T))const;    
};

#include "Tree.h"

// ---------------------------------------------------------------------------
// Tree: Constructor
template <typename T>
Tree<T>::Tree() {
    root = NULL;
}

// ---------------------------------------------------------------------------
// ~Tree: Destructor
template <typename T>
Tree<T>::~Tree() {
    makeEmpty(root);    // Empty the tree
}

// ---------------------------------------------------------------------------
// makeEmpty:
// Deletes the tree nodes, one at a time from leaf to root
// Parameters: pointer to tree node
template <typename T>
void Tree<T>::makeEmpty(Node *treeNode) {
    if (treeNode != NULL) {        
        makeEmpty(treeNode->left);
        makeEmpty(treeNode->right);
        delete treeNode->key;
        treeNode->key = NULL;
        delete treeNode;
        treeNode = NULL;
        return;
    }
}

// ---------------------------------------------------------------------------
// add:
// Inserts an item into tree, operator <, > and == of T class is 
//     resonsible for the sorting criteria
// Paratmeters: Pointer to an object of T class
// Return: True-> if new node is created and insertion is successful
//         False -> If the item is already present or node could not 
//                  created
template <typename T>
bool Tree<T>::add(T *dataptr) {
    // Tree is empty
    if (root == NULL) {
        Node *temp = new Node(dataptr);
        if (temp == NULL) {
            return false; // out of memory
        }
        // First item is the root
        root = temp;
        return true;
    }
    else { // Tree is not empty
        Node *previous, *current;
        previous = root;
        current = root;
        // Find appropriate place in tree to add the new item
        while (current != NULL) {
            // Item to be added is smaller, move to left sub tree
            if (*dataptr < *current->key) {
                previous = current;
                current = current->left;
            }
            // Item to be added is bigger, move to right sub tree
            else if (*dataptr > *current->key) {
                previous = current;
                current = current->right;
            }
            else { // Item already exists, increment the frequency counter
                current->count++;
                return false;
            }
        }
        Node *temp = new Node(dataptr);
        if (temp == NULL) {
            return false; // Out of memory
        }
        // Previous points to the leaf node at which new item is to be added
        if (*temp->key < *previous->key) {
            previous->left = temp;
        }
        else {
            previous->right = temp;
        }       
        return true;
    }
    
}

// ---------------------------------------------------------------------------
// walk: visits every node in the specified order and prints out the data
// Parameters: function pointer(function is responsible for processing data
//             enum order -> specifies the order in which data is processed
// Return: Void
template <typename T>
void Tree<T>::walk(void (*function)(T data), enum Order printorder)const{
    switch (printorder) {
        case INORDER: inorder(root, function);
            break;
        case PREORDER: preorder(root, function);
            break;
        case POSTORDER: postorder(root, function);
            break;
        default: inorder(root, function);
            break;
    }
}


// ---------------------------------------------------------------------------
// Inorder: Traverses the tree in 'inorder' fashion recursively
// Parameters: function pointer(function is responsible for action on data)
//             Pointer to tree node
template <typename T>
void Tree<T>::inorder(Node *treeNode, void (*function)(T data))const {
    if (treeNode == NULL) {
        return;
    }
    inorder(treeNode->left, function);
    std::cout.width(3);
    std::cout << std::right;
    std::cout << treeNode->count << std::setw(1) << " ";
    (*function)(*treeNode->key);
    inorder(treeNode->right, function);
}

// ---------------------------------------------------------------------------
// preoder: Traverses the tree in 'preorder' fashion recursively
// Parameters: function pointer(function is responsible for action on data)
//             Pointer to tree node
template <typename T>
void Tree<T>::preorder(Node *treeNode, void (*function)(T data))const {
    if (treeNode == NULL) {
        return;
    }
    std::cout.width(3);
    std::cout << std::right << treeNode->count << std::setw(1) << " ";
    (*function)(*treeNode->key);
    preorder(treeNode->left, function);
    preorder(treeNode->right, function);
}

// ---------------------------------------------------------------------------
// postorder: Traverses the tree in 'postorder' fashion recursively
// Parameters: function pointer(function is responsible for action on data)
//             Pointer to tree node
template <typename T>
void Tree<T>::postorder(Node *treeNode, void(*function)(T data))const {
    if (treeNode == NULL) {
        return;
    }
    postorder(treeNode->left, function);
    postorder(treeNode->right, function);
    std::cout.width(3);
    std::cout << std::right << treeNode->count << std::setw(1) << " ";
    (*function)(*treeNode->key);
}

#endif
