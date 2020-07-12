#include "FibNode.h"

#pragma once

template<typename T>
class FibHeap {
    FibNode<T>* min;
    int numNodes;

    // private helper methods
    void fixHeap();
    void spliceOut(FibNode<T>* node);
    void spliceIn(FibNode<T>* node, FibNode<T>* other);
    FibNode<T>* link(FibNode<T>* parent, FibNode<T>* child);
    void merge(FibNode<T>* other);
    // void mergeLists(FibNode<T>* node, FibNode<T>* other);

    public:
        FibHeap();
        void insert(T key);
        T getMin();
        T extractMin();
        void decreaseKey(FibNode<T>* node, T key);
        void printHeap();
};
// include the source file so it is accessible to the compiler
#include "../sources/FibHeap.cpp"
