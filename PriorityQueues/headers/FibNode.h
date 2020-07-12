#pragma once

template<typename T>
struct FibNode {
    FibNode<T>* parent;
    FibNode<T>* child;
    FibNode<T>* left;
    FibNode<T>* right;
    T key;
    int degree;
    bool loser;
    FibNode(T key, int degree) 
        : key(key), degree(degree), loser(0), parent(0), child(0), left(0), right(0) 
        {}
        // this->key = key;
        // this->degree = degree;
        // loser = 0;
        // parent = 0; 
        // child = 0;
        // left = 0;
        // right = 0;
};
