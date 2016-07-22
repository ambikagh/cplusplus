#include <iostream>
#include "List.h"
using namespace std;

class TreeNode {
    //friend BinarySearchTree;
    string key;
    List* value;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(); // constructor
    TreeNode(string); 
    ~TreeNode(); // Destructor
    string getkey(void)const;
    void setkey(string);
    List* getvalue(void)const;
    void setvalue(List*);
    TreeNode* getleft(void)const;
    void setleft(TreeNode*);
    TreeNode* getright(void)const;
    void setright(TreeNode*);
};

TreeNode::TreeNode() {
    key = "";
    value = NULL;
    left = NULL;
    right = NULL;
}

TreeNode::TreeNode(string keyword) {
    key = keyword;
    value = NULL;
    left = NULL;
    right = NULL;
}

TreeNode::~TreeNode() {
    delete this;
}

string TreeNode::getkey()const {
    return key;
}

void TreeNode::setkey(string keyword) {
    key = keyword;
}

List* TreeNode::getvalue()const {
    return value;
}

void TreeNode::setvalue(List* valueHead) {
    value = valueHead;
}

TreeNode* TreeNode::getleft(void)const {
    return left;
}

void TreeNode::setleft(TreeNode* nextleft) {
    /*if (this == NULL) {
        cout << "error void insertion";
    }*/
    left = nextleft;
}

TreeNode* TreeNode::getright(void)const {
    return right;
}

void TreeNode::setright(TreeNode* nextright) {
    right = nextright;
}