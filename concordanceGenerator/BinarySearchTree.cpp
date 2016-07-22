// ---------------------------------------------------------------------------
// Author: Mukambika Hegde
// Date:   12/4/2015
// Course: 501 Assignment 6
// ---------------------------------------------------------------------------

#include "BinarySearchTree.h"
using namespace std;

//--------------------------  class BinarySearchTree  ------------------------
// ADT BinarySearchTree: finite, ordered collection of zero or more items.
//      Items are ordered in alphabetical order/
//      If a word occurs multiple times, its context information is stored 
//      as a hash map.
//      Each node contains "keyword" and "context" associated with it as data.
//      Collection should exclude stop words if it is provided.
//      Tree Node
//      |-----------|           /| left1 | left2 | left3 | left4 | lfet5| (
//      | keyWord   |          /      
//      |-----------|         /  | right1 | right2 | right3 | right4 | right5|
//      | Context  -|------>|/------------| /           |-------------|
//      |-----------|       | words_before|/            | words_before|
//      |left |right|       |-------------/             |-------------|
//      /-----------\       | words_after/|             | words_after |
//     /             \      |-------------|             |-------------|
//  |------|      |-------| |  next     --|------------>| next        |
//  | left |      | right | | ------------|             |-------------|
//  | child|      | child |
//  |------|      |-------|
// Assumptions:  
//   -- There is no dummy root node, root points to first node in tree.  
//      If the tree is empty, root is NULL.
//   -- Insert function inserts a node at appropriate position in tree  
//   -- Tree nodes with data < root data node are inserted in left sub tree
//      nodes with data > root data are inserted in right subtree
//      this process is repeated for every node under consideration
//   -- The insert allocates memory for a Node, data is passed in as argument
//      Allocating memory and setting data is the responsibility of the caller
//   -- Numbers are also considered as strings
//   -- Stop words file is already sorted
//   -- 


// ---------------------------------------------------------------------------
// binarySearch: Public function not associated with any class
// Searches for "key" in "stopwords" array and returns the index 
//   if the key is found, returns -1 if "key" is not found in array
int binarySearch(string key, string *stopwords, int min, int max) {
    if (min > max) { // key not found
        return -1;
    }
    int mid = (min + max) / 2;   // get the middle element 
    if (key == stopwords[mid]) { // key found
        return mid; // return the index
    }
    else if (key > stopwords[mid]) {
        // key is greater than the middle element of subarray
        // Look for the key in right half of the array
        return binarySearch(key, stopwords, mid + 1, max);
    }
    else if (key < stopwords[mid]) {
        // key is less than the middle element of subarray 
        // Look for the key in left half of the array
        return binarySearch(key, stopwords, min, mid - 1);
    }
}


// ---------------------------------------------------------------------------
// BinarySearchTree: Constructor
BinarySearchTree::BinarySearchTree() {
    root = NULL;
}

// ---------------------------------------------------------------------------
// BinarySearchTree: Destructor
// Destroys the binary search tree
BinarySearchTree::~BinarySearchTree() {
    emptyTree(root);
}

// ---------------------------------------------------------------------------
// getRootNode:
// Returns the root node of the BST
TreeNode* BinarySearchTree::getRootNode(void)const {
    return root;
}

// ---------------------------------------------------------------------------
// emptyTree:
// Deletes the tree nodes, one at a time from leaf to root
void BinarySearchTree::emptyTree(TreeNode *leaf) {
    if (leaf != NULL) { // node with no children
        emptyTree(leaf->left); // empty left child if it exists
        emptyTree(leaf->right); // empty right child first if it exists
        leaf->context->makeEmpty(); // Free the memory allocated for context
        delete leaf->context; // Delete the context 
        delete leaf; // delete the node
    }
    return; // leaf is NULL
}

// ---------------------------------------------------------------------------
// getNode:
// create a new treeNode by allocating memory, fill node with "key word" info
// Return pointer to newly allocated memory
TreeNode* BinarySearchTree::getNode(string keyword) {
    TreeNode* newNode = new TreeNode; // create a new tree node
    newNode->context = new List; // Create list for context information
    newNode->key = keyword;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ---------------------------------------------------------------------------
// insert:
// Create a new tree node, fill the node with "keyword" and context info
//    passes as an argument
// Insertion point is determined by traversing 
void BinarySearchTree::insert(string keyWord,
    string*& beforeWords, string*& afterWords) {

    // Tree is empty, make the first keyword as root node
    if (root == NULL) {
        // Prepare the tree node to be inserted into BST
        TreeNode *tempNode = getNode(keyWord);
        // Update the context information
        tempNode->context->insertEnd(beforeWords, afterWords);
        root = tempNode;
        return;
    }
    // Tree is not empty, traverse the tree and insert the node
    TreeNode *current, *previous;
    current = previous = root;
    // Traverse the binary tree until either node contains the keyWord or
    //       all insert point is found
    while (keyWord.compare(previous->key) != 0 && current != NULL) {
        previous = current;
        if (keyWord.compare(previous->key) > 0) { // keyWord is bigger
                                                  // Visit right sub tree 
            current = previous->right;
        }
        else {
            // Visit left sub tree
            current = previous->left;
        }
    }
    // keyWord already present in tree
    if (keyWord.compare(previous->key) == 0) {
        // Insert the context information
        previous->context->insertEnd(beforeWords, afterWords);
        return;
    }
    // Prepare the tree node to be inserted into BST
    TreeNode *temp = getNode(keyWord);
    if (keyWord.compare(previous->key) > 0) {
        // Insert keyWord as a left leaf
        temp->context->insertEnd(beforeWords, afterWords);
        previous->right = temp;
    }
    else {
        // Insert keyWord as right leaf
        temp->context->insertEnd(beforeWords, afterWords);
        previous->left = temp;
    }
}

// ---------------------------------------------------------------------------
// buildTree:
// Read the words from corpus text one at a time, if the word is non stop
//      word, insert the word into tree, with the context information.
// If the word is stop word, insert the word in before queue,
//   fetch the next word from after queue
// If the word has punctuation or colon, remove the characters.
// 
void BinarySearchTree::buildTree(ifstream& inputfile,
    string*& stopwords, int length) {
    // Queue of words appearing after the "key word"
    // This is a working queue which keeps changing as and when 
    // keyWord is processed
    WordQueue afterList;
    // Queue of words appearing before the "key word"
    WordQueue beforeList;

    string currentWord; // Stores the current "key word"
    string currentWordLower; // Store the transformed key word(in lower case)  

                             // Read the first word
    inputfile >> currentWord;
    // For the first word there are no words before it
    string wordsAfter[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        inputfile >> wordsAfter[i];
        // Queue up the 5 words appearing after the first word
        afterList.insertEnd(wordsAfter[i]);
    }

    do {
        // Holds the current word before applying transform function to 
        //  current word
        string dummyWord = currentWord;
        transform(currentWord.begin(), currentWord.end(),
            currentWord.begin(), ::tolower);
        // Check if the word is a stop word
        while (stopwords != NULL && binarySearch(currentWord, stopwords, LOW, length) != -1) {
            // Word is a stop word, queue it in the before words list
            beforeList.insertEnd(dummyWord);
            // if there are more than 5 words in the before queue 
            //         remove first entry
            if (beforeList.getCount() > MAX_SIZE) {
                beforeList.deleteBegin();
            }
            // fetch the next word from afterList
            dummyWord = currentWord = afterList.deleteBegin();
            // Read next word from input file 
            inputfile >> currentWordLower;
            // Queue the new word in after words list to process it later
            afterList.insertEnd(currentWordLower);
            // Transform the word to lower case for ex "The" -> the
            transform(currentWord.begin(), currentWord.end(),
                currentWord.begin(), ::tolower);
        }

        // array to store 5 words occurring before the word
        string *beforeTheWord = new string[MAX_SIZE];
        // Array to store 5 words occurring after the word
        string *afterTheWord = new string[MAX_SIZE];

        // copy the words from beforeList queue to array "beforeTheWord"
        copyWordsToArray(beforeList, beforeTheWord);
        // copy the words from afterList queue to array "afterTheWord"
        copyWordsToArray(afterList, afterTheWord);
        // Trim the characters "." or "," if it appears at the end of the word
        string tempCurr = currentWord;
        string special = tempCurr.substr(tempCurr.length() - 1);
        if (special == "." || special == "," || special == ":" ||
            special == ";") {
            tempCurr.erase(tempCurr.length() - 1);
        }

        // Insert a binary tree node with trimmed word as the key
        // Value of the node is given by beforeTheWord and afterTheWord arrays
        insert(currentWord, beforeTheWord, afterTheWord);

        // queue the current word in before words list
        beforeList.insertEnd(dummyWord);
        // if there are more than 5 words in the before queue 
        //         remove first entry
        if (beforeList.getCount() > MAX_SIZE) {
            beforeList.deleteBegin();
        }
        // fetch the next word from afterList
        dummyWord = currentWord = afterList.deleteBegin();
        // Read the next word from input file and queue it up to process later
        inputfile >> currentWordLower;
        afterList.insertEnd(currentWordLower);
    } while (!inputfile.eof());

}

// ---------------------------------------------------------------------------
// display:
// Output the Binary Search Tree content to the console in readable form
void display(TreeNode* rootNode) {
    if (rootNode == NULL) {
        return;
    }
    // Recursively traverse the nodes until leaf node is reached
    display(rootNode->left);
    rootNode->context->display(rootNode->key);
    display(rootNode->right);
}

