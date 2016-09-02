//----------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   01/20/2016
// course: 502 Assignment 1 (word frequency counter using red black tree)

#ifndef RB_TREE_H
#define RB_TREE_H

#include <iostream>
#include "Word.h"
#include <iomanip>
#include <string>
#include <fstream>

#define RED 0
#define BLACK 1

// Comment out the below line to remove all debugging assertions
//#define DEBUG_RBTREE

#ifdef DEBUG_RBTREE
int gBlack_height; // holds black height of of the Red Black tree
#endif

// Enumeration to specify the order in which data is to be displayed
enum Order { INORDER, PREORDER, POSTORDER };
enum Orientation { NONE, LEFT, RIGHT};


// ---------------------------------------------------------------------------
// RB_Tree class: Represents Red Black tree which is a balanced binary tree 
//             Each node in tree holds a data and number of times the data
//             repeats in input.
// RB_Tree class has two public methods
// add(): Inserts the data into tree or increases the count if the data  
//        already exists in tree
// walk():Visits every node in specified order and performs action 
//        on data specified by the function pointer
// print(): Outputs the data onto 'stdout' one at a time
// 
// Assumptions and constraints:
//  -- Input file is preporcessed with one word per line with no 
//     extraneous punctuation.

template <typename T>
class RB_Tree {
    // Reads the data from standard input and builds the binary search 
    //    tree as and when the data is read.
    friend std::istream& operator>>(std::istream& infile, RB_Tree& bst){
        T *tnode;
        while (!infile.eof()) { 
            tnode = new T; 
            tnode->setdata(infile); 
            // if the iterm already exist, node will not be added
            if (!bst.add(tnode)) { 
                delete tnode;
            }
        }
        return infile;
    }
private:
    // Node structure represents every node in RB tree
    struct Node {
        T *key;
        int count;
		int color; // 0 -> red, 1 -> black
        Node *left; 
        Node *right;
		Node *parent; 
        // constructor
        Node(T *keydata) : key(keydata), count(0), color(BLACK),
             left(NULL), right(NULL), parent(NULL) {};
        Node(T *keydata, Node* end) :key(keydata), count(1), color(RED),
            left(end), right(end), parent(NULL) {};
    };
public:
    typedef void(*WalkPfn)(Node *); // Function pointer type definition
    RB_Tree(); 
    ~RB_Tree();
    bool add(T *); // Insert Node containing 'T' data into RB Tree
    void walk(WalkPfn, enum Order)const; // Traverses the RB Tree
    static void print(Node *);
#ifdef DEBUG_RBTREE
    void dumptree(void);
#endif
private:
    Node *root;
    Node *nil; // Sentinel node
    void makeEmpty(Node *); // Destroy tree
    void inorder(Node *, WalkPfn) const; 
    void preorder(Node *, WalkPfn) const;
    void postorder(Node *, WalkPfn) const;
    bool insert(T *, Node *); // insert Node with T data into tree
    void verify(Node *)const; // Verify RB Tree properties
    void right_rotate(Node *);
    void left_rotate(Node *);
    void rb_insert_fix(Node *, int); // Fix the violations in RB tree if any
#ifdef DEBUG_RBTREE
    void dump(Node *, int count);
#endif    
};


// ---------------------------------------------------------------------------
// RB_Tree: Constructor
template <typename T>
RB_Tree<T>::RB_Tree() {
    root = NULL;
    T *nildatap = new T; 
    nil = new Node(nildatap);    // sentinel node
}

// ---------------------------------------------------------------------------
// ~RB_Tree: Destructor
template <typename T>
RB_Tree<T>::~RB_Tree() {
    makeEmpty(root);    // Empty the tree
    delete nil->key; // delete sentinel node and data
    delete nil;
    nil = NULL;
}

// ---------------------------------------------------------------------------
// makeEmpty:
// Deletes the tree nodes, one at a time from leaf to root
// Parameters: pointer to tree node
template <typename T>
void RB_Tree<T>::makeEmpty(Node *treeNode) {
    if (treeNode != nil) {        
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
// Adds root node to the tree if tree is empty, if tree is not empty
//     'insert' function is responsible for inserting the node at proper place
// Paratmeters: Pointer to an object of T class
// Return: True-> if new node is created and insertion is successful
//         False -> If the item is already present or node could not 
//                  created
template <typename T>
bool RB_Tree<T>::add(T *dataptr) {
    // RB_Tree is empty
    if (root == NULL) {        
        Node *temp = new Node(dataptr,nil);
        if (temp == NULL) {
            return false; // out of memory
        }
        // First item is the root
        root = temp;
		root->color = BLACK;
        return true;
    }
    else { 
	return insert(dataptr, root);
    }
    
}

// ---------------------------------------------------------------------------
// insert:
// Inserts an item into tree, operator <, > and == of T class is 
//     resonsible for the sorting criteria
// Paratmeters: Pointer to an object of T class
// Return: True-> if new node is created and insertion is successful
//         False -> If the item is already present or node could not be
//                  created

template <typename T>
bool RB_Tree<T>::insert(T *dataptr, Node *current){
    if(current == NULL){
        return false;
    }
    // data already exists in tree, increment the count
    if(*current->key == *dataptr){ 
        current->count++; 
        return false;
    }
    // Data is less than the current key
    else if(*dataptr < *current->key){
        // Insertion point found
        if(current->left == nil){
            Node *leaf = new Node(dataptr,nil);
 	        if(leaf == NULL){
                return false; // out of memory
            }
            current->left = leaf;
            leaf->parent = current;
            // Check if all the RB tree properties are intact after insertion
            // Restore the property if violated
            rb_insert_fix(current, LEFT);
            return true;
        }
        else{
            // Find insertion point in left subtree
            return insert(dataptr, current->left);
        }
    }
    // data is greater than the current key
    else{ 
        if(current->right == nil){ // insertion point found
            Node *leaf = new Node(dataptr,nil);
            if(leaf == NULL){
                return false; // out of memory
	        }
            current->right = leaf;
            leaf->parent = current;
            // Check if all the RB tree properties are intact after insertion
            // Restore the property if violated
            rb_insert_fix(current, RIGHT);
            return true;
        }
        else{
            // Find insertion point in left subtree
            return insert(dataptr, current->right);
        }
    }
}

// ---------------------------------------------------------------------------
// rb_insert_fix:
// After new node is inserted into the tree, this function checks for any 
// RB tree rule violation, if violations are found it fixes the violations by 
//   rotations and colour changes on Red Black subtree
// Paratmeters: Pointer to current node at which Node is inserted
//              orient-> 1 : Leaf is left child of current node
//                       2: Leaft is right child of current node
// Return: None
template <typename T>
void RB_Tree<T>::rb_insert_fix(Node *current, int orient) {
    // Update leaf node
    Node *leaf;
    if (orient == LEFT) {
        leaf = current->left;
    }
    else {
        leaf = current->right;
    }
    // Current(parent of leaf) is RED
    // Violates the rule "No RED node can have RED node as child"
    if (current->color == RED) {
        int curr_orient = 0;
        Node *gparent = current->parent;
        Node *uncle;
        // Current is left child, uncle is right child of grandparent
        if (current == gparent->left) {
            curr_orient = LEFT;
            uncle = gparent->right;
        }
        else { // current is right child, uncle is left child
            curr_orient = RIGHT;
            uncle = gparent->left;
        }
        // case 1:
        // Check if "uncle" of "leaf" is also RED
        // Push redness to grand parent if it is not root
        if (uncle->color == RED) {
            uncle->color = BLACK;
            current->color = BLACK;
            if (gparent != root) {
                gparent->color = RED;
                // handle great grand parent red condition
                // Recursively fix violations
                if (gparent == gparent->parent->left) {
                    rb_insert_fix(gparent->parent, LEFT);
                }
                else {
                    rb_insert_fix(gparent->parent, RIGHT);
                }
            }
        }
        else {// uncle is black
            if (orient == LEFT) { 
                if (curr_orient == LEFT) { 
                    // Case 3:
                    //      o    gparent
                    //    o/     current
                    //  o/       leaf
                    right_rotate(gparent);
                    gparent->color = RED;
                    current->color = BLACK;
                }
                else { 
                    // Case 2:
                    //      o      gparent
                    //       \o    current
                    //      o/     leaf
                    right_rotate(current);
                    // Case 3:
                    //      o      gparent
                    //       \o    leaf
                    //        \o   current                    
                    left_rotate(gparent);
                    leaf->color = BLACK;
                    gparent->color = RED;
                }
            }
            else { // leaf is right child
                if (curr_orient == RIGHT) { // current node is right child
                    left_rotate(gparent);
                    gparent->color = RED;
                    current->color = BLACK;
                }
                else {                    
                    left_rotate(current); //current node is left child
                    right_rotate(gparent);
                    leaf->color = BLACK;
                    gparent->color = RED;
                }
            }
        }
    }
}
// ---------------------------------------------------------------------------
// walk: visits every node in the specified order and prints out the data
// Parameters: function pointer(function is responsible for processing data
//             enum order -> specifies the order in which data is processed
// Return: Void
template <typename T>
void RB_Tree<T>::walk(WalkPfn function, enum Order printorder)const{
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
// Note: This function also checks for the Black height of Red Black tree.
//       To turn off debugging feature #define DEBUG_RBTREE should be 
//       uncommented at the starting of file
template <typename T>
void RB_Tree<T>::inorder(Node *treeNode, WalkPfn function) const{
    if (treeNode == nil) {
        return;
    }
#ifdef DEBUG_RBTREE
    if (treeNode->color == BLACK) {
        gBlack_height++;
    }
#endif

    inorder(treeNode->left, function);

#ifdef DEBUG_RBTREE
    if (treeNode->left != nil && (treeNode->left->color == BLACK)) {
        gBlack_height--;
    }
    // Verify whether all invariants are satisfied
    verify(treeNode);
#endif    
    (*function)(treeNode);
    inorder(treeNode->right, function);

#ifdef DEBUG_RBTREE
    if (treeNode->left == nil && treeNode->right == nil) {
        std::cout << "Black height is " << gBlack_height << std::endl;
    }
    if (treeNode->right != nil && treeNode->right->color == BLACK) {
        gBlack_height--;
    }    
#endif

}

// ---------------------------------------------------------------------------
// preoder: Traverses the tree in 'preorder' fashion recursively
// Parameters: function pointer(function is responsible for action on data)
//             Pointer to tree node
template <typename T>
void RB_Tree<T>::preorder(Node *treeNode, WalkPfn function) const 
{
    if (treeNode == nil) {
        return;
    }
    (*function)(treeNode);
    preorder(treeNode->left, function);
    preorder(treeNode->right, function);
}

// ---------------------------------------------------------------------------
// postorder: Traverses the tree in 'postorder' fashion recursively
// Parameters: function pointer(function is responsible for action on data)
//             Pointer to tree node
template <typename T>
void RB_Tree<T>::postorder(Node *treeNode, WalkPfn function)const {
    if (treeNode == nil) {
        return;
    }
    postorder(treeNode->left, function);
    postorder(treeNode->right, function);
    (*function)(treeNode);
}

template <typename T>
void RB_Tree<T>::print(Node *treeNode) {
    std::cout.width(3);
    std::cout << std::right << treeNode->count << std::setw(1) << " ";
    std::cout << *treeNode->key;
    std::cout << std::endl;
}

// ---------------------------------------------------------------------------
// verify:
// Function to verify whether constructed Red Black Tree conforms to below
//    mentioned invariants
// 1. Root is a Black node
// 2. Every node is either Red or Black
// 3. No two Red nodes in a row, i.e Red parent should have a Black node
// 4. Every root to null path in the tree should have same black height
//    Implementation of 4th invariant is in 'inorder' function
// Enabled only if DEBUG_RBTREE is defined 
#ifdef DEBUG_RBTREE
template <typename T>
void RB_Tree<T>::verify(Node *current)const {
    
    // Flag to keep track violations, violation sets the flag to false
    if (current->left != nil) {
        if (current->left->parent != current) {
            std::cout << *current->left->key;
        }
        // No two RED nodes in a row
        if (current->color == RED && current->left == RED) {
            std::cout << "Two red in a row";
            std::cout << "left child of " << *current->key;
            std::cout << "violates" << std::endl;
        }
    }
    if (current->right != nil) {
        if (current->right->parent != current) {
            std::cout << *current->right->key;
        }
        // No two RED nodes in a row
        if (current->color == RED && current->right == RED) {
            std::cout << "Two red in a row";
            std::cout << "right child of " << *current->key;
            std::cout << "violates" << std::endl;
        }
    }
    // Verify if all the invariants of RB tree are satisfied
    // Every node is either BLACK or RED
    if (current->color != RED && current->color != BLACK) {
        std::cout << "Node is neither RED nor BLACK";
        std::cout << *current->key << std::endl;
    }
    // Root is always black
    if (current == root) {
        if (current->color != BLACK) {
            std::cout << "root is not Black" << std::endl;
        }
    }
}
#endif

// ---------------------------------------------------------------------------
// right_rotate: rotate the subtree to right keeping 'x' as pivot
//               Reference: Introduction to algorithms(Cormen, Leiserson)
//     |                                  |
//    (y)     --------------------->     (x)
//    / \                                / \
//  (x)  A    ---------------------->   B  (y)
//  / \           right_rotate()           / \
// B   C                                  C   A

template <typename T>
void RB_Tree<T>::right_rotate(Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        root = x;
    }
    else if (y == y->parent->left) {
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}

// ---------------------------------------------------------------------------
// left_rotate: rotate the subtree to left keeping 'y' as pivot
//              Reference: Introduction to algorithms(Cormen, Leiserson)
// --------------------------------------------------
//     |          left_rotate()           |
//    (y)     <---------------------     (x)
//    / \                                / \
//  (x)  A    <----------------------   B  (y)
//  / \                                    / \
// B   C                                  C   A

template <typename T>
void RB_Tree<T>::left_rotate(Node *x) {
    // set y
    Node *y = x->right;
    x->right = y->left;
    if (y->left != nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    }
    else if (x->parent->left == x) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// ---------------------------------------------------------------------------
// dump:
//      Dump all the nodes on standard output for inspection
//      Enabled only if DEBUG_RBTREE is defined 
#ifdef DEBUG_RBTREE
template <typename T>
void RB_Tree<T>::dump(Node *temp, int count) {
    if (temp == nil) {
        return;
    }
    for (int i = 0; i < count; i++) {
        std::cout << "+--------";
    }
    std::cout << temp << " " << *temp->key << std::endl;
    count++;    
    dump(temp->left, count);   
    dump(temp->right, count);
}


template <typename T>
void RB_Tree<T>::dumptree(void) {
    dump(root, 0);
}
#endif

#endif

