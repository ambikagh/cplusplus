Puff::Puff() {
    pt = nullptr;
    total_char_count = 0;
}

Puff::~Puff() {
    delete pt;
    pt = nullptr;
}

// reconstruct_symb_table:
// Function takes .huff file as parameter reads .huff file and 
//   builds the symbol table
// it also reads the total encoded char from file
void Puff::reconstruct_symb_table(std::fstream& huffile) {
    // Start reading the file from beginning
    huffile.clear();
    huffile.seekg(std::ios_base::beg);

    uchar_t bitcount = 0;
    int i = 0;  // represents ascii value of characters
    uchar_t *ch_arrp;
    while (!huffile.eof() && i<= UCHAR_MAX) {
        if (huffile.good() && !huffile.fail()) {
            bitcount = huffile.get();
#ifdef DEBUG_HUFF
            std::cout << uchar_t(i) << "->" << int(bitcount) << ":";
#endif
            uint64_t code = 0;
            if (bitcount) {// bit_count used for character i
                // calculate no of bytes used for the character code
                int no_of_bytes = ((bitcount + 7) & (~7)) >> 3;
                ch_arrp = (uchar_t*)(&code);
                for (int j = 0; j < no_of_bytes; j++) {
                    ch_arrp[7 - j] = huffile.get();  
#ifdef DEBUG_HUFF
                    std::cout << int(ch_arrp[7 - j]);
#endif
                }
                decoded_symbtable.set_members(i, bitcount, code);
            }
#ifdef DEBUG_HUFF
            std::cout << std::endl;
#endif
            i++;
        }
    }
    // Read the total characters encoded from .huff file
    ch_arrp = reinterpret_cast<uchar_t *>(&total_char_count);
    for (unsigned int i = 0; i < sizeof(total_char_count); i++) {
        ch_arrp[i] = huffile.get();
    }
#ifdef DEBUG_HUFF
    std::cout << total_char_count << std::endl;
#endif    
}

// reconstruct_hufftree: constructs the hufftree from decoded symbol table
void Puff::reconstruct_hufftree() {
    // create root node
    Data *tdata = new Data('\0', 0);
    Huffnode<Data> *temp = new Huffnode<Data>(tdata);
    pt = new Hufftree<Data>(temp);
    pt->build_hufftree(decoded_symbtable);
}

// Read the encoded huff file and output the decoded contents to puff file
void Puff::read_huff_file(std::fstream& huffile, std::ofstream& puffile) {    
    uchar_t buffer = huffile.get();
    int nbits = CHAR_BIT;
    Huffnode<Data> *current = pt->get_root();
    while (!huffile.eof()) {
        while (nbits > 0 && total_char_count) {
            if (!current->isleaf) {
                if (buffer & 128) current = current->right;
                else current = current->left;
                buffer = buffer << 1;
                nbits--;
            }
            else {
                total_char_count--;
                // Output the decoded character to .puff file
                puffile.put(current->key->get_symbol());
                std::cout << current->key->get_symbol();
                current = pt->get_root();
            }
        }
        nbits = CHAR_BIT;
        buffer = huffile.get();
    }
}

// decoder: responsible for decoding the huff file
void Puff::decoder(std::fstream& huffile, std::ofstream& puffile) {
    // Reconstruct the symbol table from file header
    reconstruct_symb_table(huffile);
    // Reconstruct the huffman tree from the symbol table    
    reconstruct_hufftree();
#ifdef DEBUG_HUFF
    pt->validate_hufftree();
    pt->dump();
    //pt->display(pt->get_root());
#endif
    // Read huff file and output the text to puff file
    read_huff_file(huffile, puffile);
}

