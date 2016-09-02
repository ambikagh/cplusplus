#include <iostream>
#include <fstream>
#include <string>
#include "puff.h"

// Implements decoder logic of huffman algorithm
// Program reads compressed file and generates the decoded file
// Note: Program takes huff file as command line argument,
//       replaces .huff with .puff
// Its assumed that huff file ends with .huff extenstion, and 
//       only 1 '.' in file name
using namespace std;

int main(int argc, char *argv[]) {
    // .huff file is passed as command line argument
    if (!(argc >= 2)) {
        cout << "Enter atleast 2 arguments" << endl;
    }        
    fstream huffile;
    huffile.open(argv[1], ios_base::binary | ios_base::in | ios_base::out);
    if (!huffile) {
        cerr << "cannot create file " << endl;
    }
    string puff_filename;
    string huff_filename = argv[1];
    // Check if file has .huff extension
    size_t pos = huff_filename.find(".");
    if (huff_filename.substr(pos) != "huff") {
        cerr << "invalid file, provide a file with .huff extension" << endl;
    }

    // Extract .huff filename and replace .huff with .puff
    puff_filename = huff_filename;
    puff_filename.replace((pos + 1), 1, "p");
    Puff p;
    ofstream puffile(puff_filename, ios_base::binary);
    if (!puffile) {
        cerr << "File could not be created";
    }

    p.decoder(huffile, puffile);
    puffile.close();
    huffile.close();
    return 0;
}
