
#include <iostream>
#include <cstddef>
#include <fstream>

using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node(int d) {
        data = d;
        left = NULL;
        right = NULL;
    }
};
class Solution {
public:
    Node* insert(Node* root, int data) {
        if (root == NULL) {
            return new Node(data);
        }
        else {
            Node* cur;
            if (data <= root->data) {
                cur = insert(root->left, data);
                root->left = cur;
            }
            else {
                cur = insert(root->right, data);
                root->right = cur;
            }

            return root;
        }
    }

    int getHeight(Node* root) {
        //Write your code here
        int height = 0;
        inorder(root, &height, 0);
        return height;
    }

    void inorder(Node *root, int* height, int h) {
        if (root != NULL) {
            if (root->left) {
                inorder(root->left, height, h + 1);
            }
            if (*height < h) {
                *height = h;
            }
            if (root->right) {
                inorder(root->right, height, h + 1);
            }
        }
    }

}; //End of Solution

int main() {
    fstream myfile("Text.txt", std::ios_base::in);
    Solution myTree;
    Node* root = NULL;
    int t;
    int data;

    myfile >> t;

    while (t-- > 0) {
        myfile >> data;
        root = myTree.insert(root, data);
    }
    int height = myTree.getHeight(root);
    cout << height;

    return 0;
}



