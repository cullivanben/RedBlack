#include <iostream>
#ifndef SET_NODE
#define SET_NODE

template<typename T>
struct SetNode {
    T value;        
    bool black;
    SetNode<T>* parent;
    SetNode<T>* left; 
    SetNode<T>* right; 
    SetNode(T value, bool black, SetNode<T>* parent, SetNode<T>* left, SetNode<T>* right) {
        this->value = value;
        this->black = black;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }
};

#endif
