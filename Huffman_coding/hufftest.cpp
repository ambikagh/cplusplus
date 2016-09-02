#include <iostream>
#include <fstream>
#include "huff.h"

using namespace std;
// ---------------------------------------------------------------------------
// This program implements encoding part of huffman coding algorithm
// Input text file is passed as a command line argument
// Huffman encoding is implemented in Huff class
int main(int argc, char *argv[]) {
            // Input text file is passed as command line argument
            if (!(argc >= 2)) {
                cout << "Enter atleast 2 arguments" << endl;
            }
            // input text file
            ifstream infile(argv[1]);
            if (!infile) {
                cerr << "File could not be opened" << endl;
            }
            // .huff -> encoded file
            string huf_filename = "compressed.huff";
            fstream huffile;
            huffile.open(huf_filename, ios_base::binary | ios_base::out);
            if (!huffile) {
                std::cerr << "cannot create file \n";
            }     
            
            Huff h;
            h.encoder(infile, huffile);
            cout << h;
            huffile.close();
    
    return 0;
}
