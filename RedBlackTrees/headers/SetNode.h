#pragma once

template<typename T>
struct SetNode {
    T value;        
    bool black;
    SetNode<T>* parent;
    SetNode<T>* left; 
    SetNode<T>* right; 
    SetNode(T value, bool black, SetNode<T>* parent, SetNode<T>* left, SetNode<T>* right) 
        : value(value), black(black), parent(parent), left(left), right(right)
        {}
    // {
    //     this->value = value;
    //     this->black = black;
    //     this->parent = parent;
    //     this->left = left;
    //     this->right = right;
    // }
};
