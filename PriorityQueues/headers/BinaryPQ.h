#include "BinaryHeap.h"
#include <vector>

#pragma once

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
