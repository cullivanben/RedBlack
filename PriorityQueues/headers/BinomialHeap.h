#include "Node.h"

#ifndef BINOMIAL_HEAP
#define BINOMIAL_HEAP

template<typename T>
class BinomialHeap {
    // the head of the heap
    Node<T>* head;
    // helper method to merge two heaps
    void merge(Node<T>* other);
    public: 
        BinomialHeap();
        Node<T>* getHead();
        void setHead(Node<T>* newHead);
        void insert(T data);
        T getMin();
        T extractMin();
        void printHeap();
};
// include the source file so the compiler can access it
#include "../sources/BinomialHeap.cpp"

# endif