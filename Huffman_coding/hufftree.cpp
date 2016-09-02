// Hufftree: destructor
template <typename Y>
Hufftree<Y>::~Hufftree() {
    destroy_tree(root);
}

// destroy_tree: responisble for deleting the nodes of huffman tree
template <typename Y>
void Hufftree<Y>::destroy_tree(Huffnode<Y>* current) {
    if (current == nullptr)
        return;
    destroy_tree(current->left);
    destroy_tree(current->right);
    delete current;
    current = nullptr;
}

// walk: Traverse the huffman tree in inorder fashion
template <typename Y>
void Hufftree<Y>::walk(walkpfn action) const {
    inorder(root, action);
}

// inorder: Visits the every node in huffman tree in inorder fashion
//       and performas the action on every node as specified by 
//       walkpfn function pointer
template <typename Y>
void Hufftree<Y>::inorder(Huffnode<Y> *current, walkpfn action) const {
    if (current == nullptr) {
        return;
    }
    inorder(current->left, action);
    action(current);
    inorder(current->right, action);
}

// print: display contents of the node
template <typename Y>
void Hufftree<Y>::print(Huffnode<Y> *current) {
    std::cout << current->key;
}


// build_symbol_table: Builds symbol table from huff tree
// Symbol table is built from huffman tree by traversing the tree
// Everytime a leaf node is reached fetch the code for the symbol
template<typename Y>
Char_encode Hufftree<Y>::build_symb_table()const {
    Char_encode tsymb_table;
    build_symbol_code(root, 0, 0, -1, tsymb_table);
    return tsymb_table;
}

/* build_symbol_code:  builds symbol table from huffman tree
// Function used by encoder
//    o
//   / \
// t:o o
//    / \
//  b:  e: 
// Coded symbol for t -> bit_count = 1, code = 0
// Coded symbol for b -> bit_count = 2, code = 10
// Coded symbol for e -> bit_count = 2, code = 11*/
template <typename Y>
void Hufftree<Y>::build_symbol_code(Huffnode<Y> *current, uint64_t code, unsigned int count, int dir, Char_encode &ce) const {
    if (current == nullptr)
        return;
    // left: dir = 0
    // right: dir = 1
    if (dir == 0 || dir == 1) {
        count++;
        code = code << 1; 
        if (dir == 1) { // current is right child of parent
            code = code | 1; 
        }
    }
    if (current->isleaf) {
        // keep the encoded value left aligned
        // for ex: if encoded value is 1011 then pack it in a byte as 1011 0000
        uint64_t dummy_code = 0;
        dummy_code = code << (64 - count);
        uchar_t c = current->key->get_symbol();
        ce.set_members(c, count, dummy_code);
#ifdef DEBUG_HUFF
        std::cout << uchar_t(current->key->get_symbol()) << "->" << count << ":" << std::hex << dummy_code << std::endl;
#endif
    }
    build_symbol_code(current->left, code, count, 0, ce);
    build_symbol_code(current->right, code, count, 1, ce);
    if (!current->isleaf) {
        code = code >> 1;
        count--;
    }
    if (!current->isleaf) {
        code = code >> 1;
        count--;
    }
}

/* build_hufftree: Build huff tree from the symbol table
// Function used by decoder
// If the coded symbol for following characters are given by
// Coded symbol for t -> bit_count = 1, code = 0
// Coded symbol for b -> bit_count = 2, code = 10
// Coded symbol for e -> bit_count = 2, code = 11
// Then the huffman tree constructed from symbol table looks like below
//    o
//   / \
// t:o o
//    / \
//  b:  e: */

template <typename Y>
void Hufftree<Y>::build_hufftree(Char_encode &dec_symbtable) {
    Huffnode<Data> *current = root;
    // For each character in symbol table
    for (int i = 0; i <= UCHAR_MAX; i++) {
        uchar_t bit_count;
        uint64_t code;
        dec_symbtable.get_members(i, bit_count, code);
        uchar_t* chp = (uchar_t*)(&code);
        while (bit_count > 0) {
            current->isleaf = false;
            // Extract first n bits of the code
            // n is the number of bits used to represent the symbol
            if (chp[7] & 128) {// bit is 1
                // if right child is null insert a node to the right
                if (current->right == nullptr) {
                    Data *tempdata = new Data('\0', 0);
                    Huffnode<Data> *tempnode = new Huffnode<Data>(tempdata);
                    current->right = tempnode;
                }
                // right child is not null go to right
                current = current->right;
            }
            else {// bit is 0
                // if left child is null, insert node to the left
                if (current->left == nullptr) {
                    Data *tempdata = new Data('\0', 0);
                    Huffnode<Data> *tempnode = new Huffnode<Data>(tempdata);
                    current->left = tempnode;
                }
                // left child present, go to left
                current = current->left;
            }
            bit_count--;
            code = code << 1;
        }
        // Set the symbol of the leaf node to the character being processed
        if (current->key) current->key->set_symbol(uchar_t(i));
        // Start from root for the next symbol in symbol table
        current = root;
    }
}

// validate: wrapper function to validate the huffman tree
// Tree is said to be valid if all internals(non leaf) nodes have two children
template <typename Y>
void Hufftree<Y>::validate(Huffnode<Y> *current)const {
    // if current is nullpointer return 
    if (!current) return;
    // current node is internal node, must have 2 children
    if (!current->isleaf) { // node is not leaf
                            // one of the children or both the children are absent
        if (!(current->left && current->right)) {
            std::cout << "error:interior node: does not contain one or both the children" << std::endl;
        }
    }
    else {// Check if node is really a leaf node
        if (current->left || current->right)
            std::cout << "error:leaf node with children" << std::endl;
    }
    validate(current->left);
    validate(current->right);
}

// validate_hufftree: validates if huffman tree is valid
template <typename Y>
void Hufftree<Y>::validate_hufftree()const {
    validate(this->root);
}

template <typename Y>
Huffnode<Y>* Hufftree<Y>::get_root() {
    return root;
}


#ifdef DEBUG_HUFF
template <typename Y>
void Hufftree<Y>::dump()const {
    dumptree(root, 0);
}

template <typename Y>
void Hufftree<Y>::dumptree(Huffnode<Y> *current, int count)const {
    if (current == nullptr)
        return;
    for (int i = 0; i < count; i++) {
        std::cout << "+--------";
    }
    std::cout << *current->key << std::endl;
    count++;
    dumptree(current->left, count);
    dumptree(current->right, count);
}

template <typename Y>
void Hufftree<Y>::display(Huffnode<Y> *current)const {
    if (!current)
        return;
    std::cout << *current->key;
    std::cout << "+--------";
    if (current->left) display(current->left);
    if (current->right) display(current->right);
}

#endif
