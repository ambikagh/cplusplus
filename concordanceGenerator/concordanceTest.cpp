#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "List.h"
#include "BinarySearchTree.h"

#define MIN_ARG 2
#define MAX_STOPWORDS 200

using namespace std;


// ---------------------------------------------------------------------------
// Problem statement:
// Program should read a text corpus from a file and output its concordance 
//  in KWIC(Key Words In Context) format using "cout".
// Stop words should be excluded from the concordance, stop words will 
// be provided by "stopwords.txt", if the file is not provided program 
// should proceed without excluding any word from concordance.
// Program should take the file name for corpus file as the sole command 
// line argument. Program should use BST to collect concordance information.
// Nodes in the BST should be indexed using non - stop word in the corpus.
// Each tree node should contain a linked list of context information.
// In other words
// •	Each Node in BST should have a non - stop - word as the key
// •	Every keyword in the Node should contain 5 words appearing 
//      before it and 5 words appearing after it as the context 
//      information.Context information should be implemented as linked list.


// ---------------------------------------------------------------------------
// Assumptions: 
//         -- stop words file has words in sorted format
//         -- Maximum number of stop words is 200
// Constraints: Words are not case sensitive
//              "The" is considered as "the"
//         -- Numbers are also considered as words.

int main(int argc, char *argv[]) {
   
    
        BinarySearchTree corpustree;
        // Create a stop word array by allocating memory
        string *stopWords = new string[MAX_STOPWORDS]; 
        // "temp" points to the same memory as stopwords
        string *temp = stopWords;
        bool flag = true; // Flag to indicate presence of stopword file

        ifstream infile("stopwords.txt");
        if (!infile) { // File not found
            cout << "Cannot open the stopwords file" << endl;
            flag = false; // Indicate stopword file does not exist
        }
        // Stop words file does not exist
        if (!flag) {
            stopWords = NULL;
        }
        
        int i = 0; // Keeps count of number of stop words
        // If file exists and not EOF file read the words from file
        while (!infile.eof() && flag) { 
            infile >> stopWords[i++]; 
        }
        // Check if corpus file is passed as command line argument
        if (argc < MIN_ARG) {
            cout << "Not enough arguments to continue!!";
            cout << "Please enter valid number of arguments";
            return 0; // exit the program
        }        
        // Second argument of command line is the corpus file
        ifstream infile3(argv[1]);
                
        if (!infile3) {
            cout << "Error opening the file" << endl;
        }        
        // Build binary search tree
        corpustree.buildTree(infile3, stopWords, i);
        // Display the generated concordance
        display(corpustree.getRootNode()); 
        // Delete the allocated string array
        delete [] temp;
    return 0;
}

