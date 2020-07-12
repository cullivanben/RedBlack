#pragma once 

// the node struct that will be used in BinomialHeap
template <typename T>
struct Node {
    T data;
    int degree; 
    Node *child, *sibling;
    Node(T data, int degree) 
        : data(data), degree(degree), child(0), sibling(0)
        {}
    //     this->data = data;
    //     this->degree = degree;
    //     child = 0;
    //     sibling = 0;
};
