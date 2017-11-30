#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

typedef Node *NODEPTR;

NODEPTR get_node(int data) {
    NODEPTR temp = new Node();
    if (temp == NULL) cout << "Mem allocation error" << endl;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void insert(NODEPTR root, int data) {
    if (root == NULL) return;

    if (data < root->data) {
        if (root->left) return insert(root->left, data);
        root->left = get_node(data);
        return;
    }
    else {
        if (root->right) return insert(root->right, data);
        root->right = get_node(data);
        return;
    }
}

NODEPTR tree_minimum(NODEPTR root) {
    while (root->left) {
        root = root->left;
    }
    return root;
}

NODEPTR tree_maximum(NODEPTR root) {
    while (root->right) root = root->right;
    return root;
}


// returns predecessor of a node, NULL if there is no predecessor
/*
NODEPTR predecessor(NODEPTR root) {
if(root == NULL) return root;
if(root->left){
while
}
}
*/

void inorder(NODEPTR root) {
    if (root == NULL) return;
    if (root->left) inorder(root->left);
    cout << root->data << " ";
    if (root->right) inorder(root->right);
}

int main() {
    NODEPTR bs_tr = get_node(8);
    insert(bs_tr, 6);
    insert(bs_tr, 7);
    insert(bs_tr, 15);

    inorder(bs_tr);
    return 0;
}
