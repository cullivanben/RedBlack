#include "SetNode.h"
#include <vector>
#include <deque>
#include <tuple>

#ifndef BC_TREE_SET
#define BC_TREE_SET

// this template class uses a red black tree to implement a set
template<typename T>
class BCTreeSet {
    SetNode<T>* root; 
    long long s; 

    // private helper methods
    void insertRestore(SetNode<T>* curr);
    void rotateLeft(SetNode<T>* curr, SetNode<T>* parent);
    void rotateRight(SetNode<T>* curr, SetNode<T>* parent);
    void recolor(SetNode<T>* curr, bool color);  
    void inorderHelp(SetNode<T>* curr, std::vector<T>& arr);
    void levelOrderHelp(SetNode<T>* curr, std::vector<std::vector<T>>& arr);

    public:
        BCTreeSet();
        void add(T value);
        void remove(T value);
        bool contains(T value);
        bool isEmpty();
        long long size();
        std::vector<T> inorder();
        std::vector<std::vector<T>> levelOrder();
};

// public constructor for the set
template<typename T> 
BCTreeSet<T>::BCTreeSet() {
    root = 0;
    s = 0;
}

// method to add a value to the set
// O(log(n)) time
// O(1) space
template<typename T> 
void BCTreeSet<T>::add(T value) {
    // the case where this is the first node to be inserted
    if (!root) {
        root = new SetNode<T>(value, 1, 0, 0, 0);
        s = 1;
        return;
    }

    // perform normal bst insertion
    SetNode<T>* curr = root;
    while (1) {
        // if this value is already in the set, do nothing and return
        if (value == curr->value) return;
        // if the value is less than the value of this node, move left
        if (value < curr->value) {
            if (curr->left) curr = curr->left;
            else {
                curr->left = new SetNode<T>(value, 0, curr, 0, 0);
                curr = curr->left;
                break;
            }
        } 
        // if the value is greater than the value of this node, move right
        else {
            if (curr->right) curr = curr->right;
            else {
                curr->right = new SetNode<T>(value, 0, curr, 0, 0);
                curr = curr->right;
                break;
            }
        }
    }

    // if the parent of the node that was just inserted is red
    if (!curr->parent->black) {
        // restore the red black property
        insertRestore(curr);
    }
}

// helper method for restoring the red black properties upon insertion
// O(1) time
// O(1) space
template<typename T>
void BCTreeSet<T>::insertRestore(SetNode<T>* curr) {
    // the grandparent node of the current node
    SetNode<T>* grand = curr->parent->parent;
    // the parent node of the current node
    SetNode<T>* parent = curr->parent;
    // whether this node's parent is the left child of the grandparent
    bool left = parent->value < grand->value;

    if (left) {
        // if there is an uncle node and it is red
        if (grand->right && !grand->right->black) {
            recolor(grand, 0);
            // if this recolor caused a double red situation, recurse
            if (grand->parent && !grand->parent->black) insertRestore(grand);
        }
        // the uncle node must be either null or black
        else {
            // perform a pre rotation if one is needed
            if (parent->value < curr->value) {
                rotateLeft(curr, parent);
                parent = curr;
            }
            // rotate and recolor
            rotateRight(parent, grand);
            recolor(parent, 1);
            // set the root if necessary
            if (!parent->parent) root = parent;
        }
    } else {
        // if there is an uncle node and it is red
        if (grand->left && !grand->left->black) {
            recolor(grand, 0);
            // if this recolor caused a double red situation, recurse
            if (grand->parent && !grand->parent->black) insertRestore(grand);
        }
        // the uncle node must be either null or black
        else {
            // perform a pre rotation if one is needed
            if (curr->value < parent->value) {
                rotateRight(curr, parent);
                parent = curr;
            }
            // rotate and recolor
            rotateLeft(parent, grand);
            recolor(parent, 1);
            // set the root if necessary
            if (!parent->parent) root = parent;
        }
    }
}

// helper method to perform a left rotation
// O(1) time
// O(1) space
template<typename T>
void BCTreeSet<T>::rotateLeft(SetNode<T>* curr, SetNode<T>* parent) {
    curr->parent = parent->parent;
    parent->parent = curr;
    parent->right = curr->left;
    curr->left = parent;
}

// helper method to perform a right rotation
// O(1) time 
// O(1) space
template<typename T> 
void BCTreeSet<T>::rotateRight(SetNode<T>* curr, SetNode<T>* parent) {
    curr->parent = parent->parent;
    parent->parent = curr;
    parent->left = curr->right;
    curr->right = parent;
}

// helper method to set the current node to the specified color and its children nodes to the other color
// O(1) time
// O(1) space
template<typename T>
void BCTreeSet<T>::recolor(SetNode<T>* curr, bool color) {
    curr->black = color;
    if (curr->left) curr->left->black = !color;
    if (curr->right) curr->right->black = !color;
}

// method to remove a value from the set
// O(log(n)) time
// O(1) space
template<typename T> 
void BCTreeSet<T>::remove(T value) {
    if (!root) return;
}

// method to check if the set contains a value
// O(log(n)) time
// O(1) space
template<typename T>
bool BCTreeSet<T>::contains(T value) {
    SetNode<T>* curr = root;

    while (curr) {
        if (curr->value == value) return true;
        if (value < curr->value) curr = curr->left;
        else curr = curr->right;
    }

    return false;
}

// method to check if the set is empty
// O(1) time
// O(1) space
template<typename T> 
bool BCTreeSet<T>::isEmpty() {
    return !root;
}

// method to check the size of the set
// O(1) time
// O(1) space
template<typename T>
long long BCTreeSet<T>::size() {
    return s;
}

// helper method for the inorder traversal
template<typename T> 
void BCTreeSet<T>::inorderHelp(SetNode<T>* curr, std::vector<T>& arr) {
    if (curr->left) inorderHelp(curr->left, arr);
    arr.push_back(curr->value);
    if (curr->right) inorderHelp(curr->right, arr);
}

// method to perform an inorder traversal and return a vector of all the nodes in sorted order
template<typename T>
std::vector<T> BCTreeSet<T>::inorder() {
    if (!root) return {};
    std::vector<T> arr(s);
    inorderHelp(root, arr);
    return arr;
}

// method to perform a level order traversal and return a vector consisting of vectors of all the levels
template<typename T>
std::vector<std::vector<T>> BCTreeSet<T>::levelOrder() {
    if (!root) return {};
    std::vector<std::vector<T>> arr;
    std::deque<std::tuple<SetNode<T>*, long long>> d;
    // initialize the deque with only the root node
    d.push_back(std::make_tuple(root, 0));
    while (d.size() > 0) {
        std::tuple<SetNode<T>*, long long> curr = d.front();
        d.pop_front();
        // add the value of this node to the array corresponding to this node's level
        if (arr.size() <= std::get<1>(curr)) arr.push_back({});
        arr[std::get<1>(curr)].push_back(std::get<0>(curr)->value);
        // add the child nodes to the deque if they exist
        if (std::get<0>(curr)->left) d.push_back(std::make_tuple(std::get<0>(curr)->left, std::get<1>(curr)+1));
        if (std::get<0>(curr)->right) d.push_back(std::make_tuple(std::get<0>(curr)->right, std::get<1>(curr)+1));
    }
    return arr;
}

#endif