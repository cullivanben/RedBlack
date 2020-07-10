#include "../headers/BinomialPQ.h"
#include "../headers/BinomialHeap.h"


// tests whether the priority queue is empty
// O(1) time
// O(1) space
template<typename T>
bool BinomialPQ<T>::isEmpty() {
    return heap.size() == 0;
}

// checks the size of the priority queue
// O(1) time
// O(1) space
template<typename T> 
int BinomialPQ<T>::size() {
    return heap.size();
}

// gets the smallest element from the priority queue
// O(log(n)) time
// O(1) space
template<typename T>
T BinomialPQ<T>::top() {
    return heap.getMin();
}

// adds an element to the priority queue
// O(log(n)) time
// O(1) space
template<typename T>
void BinomialPQ<T>::push(T element) {
    heap.insert(element);
}

// extracts the minimum element from the priority queue
// O(log(n)) time
// O(1) space
template<typename T>
T BinomialPQ<T>::pop() {
    return heap.extractMin();
}
