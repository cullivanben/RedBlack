#include "../headers/BinomialHeap.h"
#include "../headers/Node.h"


// returns the head of this heap
// O(1) time
// O(1) space
template<typename T>
Node<T>* BinomialHeap<T>::getHead() {
    return head;
}

// sets the head of this heap
template<typename T>
void BinomialHeap<T>::setHead(Node<T>* newHead) {
    head = newHead;
}

// inserts a node into the heap
template<typename T>
void BinomialHeap<T>::insert(T data) {

}

// returns the minimum value of this heap
template<typename T>
T BinomialHeap<T>::getMin() {

}

// extracts the minimum value of this heap
template<typename T>
T BinomialHeap<T>::extractMin() {

}
