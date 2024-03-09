
#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>
#include <iomanip>
#include <math.h>
#include <list>
using std::cout;
using std::endl;
using std::setw;

template<typename K, typename V>
class AVL_Tree{
private:
    AVL_Tree(const AVL_Tree&){};
    class TreeNode {
    public:
        K key;
        V value;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        int height = 0;//for finding max height
    };
    void returnallvalues(TreeNode *curr, std::list<std::pair<K,V>>&);
    TreeNode* root = nullptr;
    int getHeight(TreeNode* curr);
    //private insert function
    V& insert(TreeNode*& node, const K& k, const V& v);//return V& later
    void deleteleaf(TreeNode*& node);
    void inorder_print(TreeNode* curr, int level) {
        if(curr != nullptr) {
            inorder_print(curr -> left, level + 1);
            cout << curr->key << " : " << endl;
            inorder_print(curr -> right, level + 1);
        }
    }
    void rotateWithRightChild(TreeNode*& curr);
    void rotateWithLeftChild(TreeNode*& curr);
    void DoubleWithRightChild(TreeNode*& curr);
    void DoubleWithLeftChild(TreeNode*& curr);
    V find(K, TreeNode * curr= nullptr);
public:
    int treeSize = 0;
    void returnallvalues(std::list<std::pair<K,V>>&);
    V search(K key);
    void balance(TreeNode*& node);//return V& later
    //constructor
    AVL_Tree(): root(nullptr) {}
    //desturctor
    ~AVL_Tree();
    //public insert function
    V& insert(const K&, const V&);//return V& later
    void print() { inorder_print(root, 0); }
    //Max function
    int max(int a, int b){
        return (a < b) ? b : a;
    }
};
//User insert function which calls the private insert with root as its pointer
template<typename K, typename V>
V& AVL_Tree<K, V>::insert(const K& k, const V& v) {//return V& later
    return insert(root, k, v);
}
//returns all the values using pre order main use is persistant indexing
template<typename K, typename V>
void AVL_Tree<K, V>::returnallvalues(TreeNode *curr, std::list<std::pair<K,V>>& list) {
    if(curr!= nullptr){
        std::pair<K,V> temp(curr->key, curr->value);
        list.push_front(temp);
        returnallvalues(curr->left, list);
        returnallvalues(curr->right, list);
    }
}
//private recursive insert function. uses rotations to self balance
template<typename K, typename V>
V& AVL_Tree<K, V>::insert(AVL_Tree<K, V>::TreeNode*& node, const K& k, const V&v) {//ref to node // return v later
    if(node == nullptr) {
        //time to insert
        node = new AVL_Tree<K, V>::TreeNode();
        node -> key = k;
        node -> value = v;
        treeSize++;
        return node->value;
    } else if (node->key < k) {
        V * temp = &insert(node -> right, k, v);//return
        //balancing later
        balance(node);
        return *temp;
    } else if (k < node->key) {
        V*  temp = &insert(node -> left, k, v);//return
        //balancing later
        balance(node);
        return *temp;
    } else {
        return node->value; //handle duplicates v by ref return
    }
}

//checks for an imbalance and rotates accordingly to keep to the rules of an avl tree
template<typename K, typename V>
void AVL_Tree<K, V>::balance(AVL_Tree::TreeNode *&node) {
    if(node== nullptr){
        return;
    }
    if(getHeight(node->left)- getHeight(node->right) > 1) {//imbalance
        if(getHeight(node->left->left) >= getHeight(node->left->right)){
            rotateWithLeftChild(node);
        }else{
            DoubleWithLeftChild(node);
        }
    }else{
        if(getHeight(node->right) - getHeight(node->left) > 1){//basically ==2
            if(getHeight(node->right->right) >= getHeight(node->right->left)){
                rotateWithRightChild(node);
            }else{
                DoubleWithRightChild(node);
            }
        }
        node->height = max(getHeight(node->left), getHeight(node->right))+1;
        return;
    }
}

//recursive destructor
template<typename K, typename V>
AVL_Tree<K, V>::~AVL_Tree() {
    if(root!= nullptr) {
        deleteleaf(root->left);
        deleteleaf(root->right);
    }
    delete root;
}

//deletes a leaf from the tree
template<typename K, typename V>
void AVL_Tree<K, V>::deleteleaf(AVL_Tree::TreeNode *&node) {
    if(node != nullptr){
        deleteleaf(node->left);
        deleteleaf(node->right);
        delete node;
    }
}

//returns height and catches nullpointer errors. used in balancing
template<typename K, typename V>
int AVL_Tree<K, V>::getHeight(AVL_Tree::TreeNode *curr) {
    if(curr == nullptr)
    return -1;
    else
        return curr->height;
}
//All rotations change the pointers of the tree to move nodes to an even balanced binary search tree
//rotate case 1
template<typename K, typename V>
void AVL_Tree<K, V>::rotateWithRightChild(AVL_Tree::TreeNode *&curr) {
    //only if has right child
    TreeNode* curr_rightchild = curr->right;// was null
    curr->right = curr_rightchild->left;
    curr_rightchild->left = curr;
    curr-> height = max(getHeight(curr->left), getHeight(curr->right))+1;curr-> height = max(getHeight(curr->left), getHeight(curr->right))+1;
    curr_rightchild-> height = max(getHeight(curr_rightchild->right), getHeight(curr))+1;
    curr = curr_rightchild;
}
//rotate case 2
template<typename K, typename V>
void AVL_Tree<K, V>::DoubleWithRightChild(AVL_Tree::TreeNode *&curr) {
    rotateWithLeftChild(curr->right);
    rotateWithRightChild(curr);
}
//rotate case 4
template<typename K, typename V>
void AVL_Tree<K, V>::rotateWithLeftChild(AVL_Tree::TreeNode *&curr) {
    //only if has left child
    TreeNode* curr_leftchild = curr->left;
    curr->left = curr_leftchild->right;
    curr_leftchild->right = curr;
    curr-> height = max(getHeight(curr->left), getHeight(curr->right))+1;
    curr_leftchild-> height = max(getHeight(curr_leftchild->left), getHeight(curr))+1;//getHeight(curr->height) curr->height
    curr = curr_leftchild;
}
//rotate case 3
template<typename K, typename V>
void AVL_Tree<K, V>::DoubleWithLeftChild(AVL_Tree::TreeNode *&curr) {
    rotateWithRightChild(curr->left);
    rotateWithLeftChild(curr);
}


//recursivly searches the nodes using the properties
//of binary search trees and throws an error if its unable to find it. Private internal use
template<typename K, typename V>
V AVL_Tree<K, V>::find(K key, TreeNode * curr) {
    if(key == curr->key){
        return curr->value;//from key
    }else if( curr->key < key){
        if(curr->right != nullptr){
            return find(key, curr->right);
        }else{
            throw std::runtime_error("doesnt exist");//trycatch to catch error
        }
    }else if( key < curr->key){//swapping < to >
        if(curr->left != nullptr){
        return find(key, curr->left);
        }else{
            throw std::runtime_error("doesnt exist");
        }
    }
//warning no return
return curr->value;
}
//User search function which uses find to locate the element and return the value
template<typename K, typename V>
V AVL_Tree<K, V>::search(K key){
    return find(key, root);
}
//public returnallvalues
template<typename K, typename V>
void AVL_Tree<K, V>::returnallvalues(std::list<std::pair<K, V>> &list) {
    returnallvalues(root, list);
}

#endif // AVL_TREE_H
