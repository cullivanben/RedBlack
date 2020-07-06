#include "SetNode.h"

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

    public:
        BCTreeSet();
        void add(T value);
        void remove(T value);
        bool contains(T value);
        bool isEmpty();
        long long size();
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
        root = new SetNode(value, 1, 0, 0, 0);
        s = 1;
        return;
    }

    // perform normal bst insertion
    SetNode* curr = root;
    while (1) {
        // if this value is already in the set, do nothing and return
        if (value == curr->value) return;
        // if the value is less than the value of this node, move left
        if (value < curr->value) {
            if (curr->left) curr = curr->left;
            else {
                curr->left = new SetNode(value, 0, curr, 0, 0);
                curr = curr->left;
                break;
            }
        } 
        // if the value is greater than the value of this node, move right
        else {
            if (curr->right) curr = curr->right;
            else {
                curr->right = new SetNode(value, 0, curr, 0, 0);
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

// method for restoring the red black properties upon insertion
// O(1) time
// O(1) space
template<typename T>
void BCTreeSet<T>::insertRestore(SetNode<T>* curr) {
    // the grandparent node of the current node
    SetNode* grand = curr->parent->parent;
    // the parent node of the current node
    SetNode* parent = curr->parent;
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
    SetNode* curr = root;

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

#endif