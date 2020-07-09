#include "Node.h"

#ifndef BINOMIAL_HEAP
#define BINOMIAL_HEAP

template<typename T>
class BinomialHeap {
    // helper method to merge two binomial trees of the same degree
    void mergeNodes(Node<T>* a, Node<T>* b);
    // helper method to merge two heaps
    void merge(BinomialHeap<T> other);

    // the head of the heap
    Node<T>* heap;
    public: 
        Node<T>* getHead();
        void setHead(Node<T>* newHead);
        void insert(T data);
        T getMin();
        T extractMin();
};
// include the source file so the compiler can access it
#include "../sources/BinomialHeap.cpp"

# endif