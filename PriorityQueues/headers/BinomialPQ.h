#include "BinomialHeap.h"

#ifndef BINOMIAL_P_Q
#define BINOMIAL_P_Q

template<typename T>
class BinomialPQ {
    // The underlying heap
    BinomialHeap<T> heap;
    public:
        bool isEmpty();
        int size();
        T top();
        void push(T element);
        T pop();
};
// include the source file so the compiler can access it
#include "../sources/BinomialPQ.cpp"

#endif