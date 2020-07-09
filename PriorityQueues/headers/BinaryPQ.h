#include "BinaryHeap.h"
#include <vector>

#ifndef BINARY_P_Q
#define BINARY_P_Q

template<typename T>
class BinaryPQ {
    BinaryHeap<T> heap;

    public:
        BinaryPQ();
        BinaryPQ(std::vector<T> arr);
        bool isEmpty();
        int size();
        T top();
        void push(T element);
        T pop();
        void clear();
        void print();
};
// include the source file so that the compiler can access it
#include "../sources/BinaryPQ.cpp"

#endif