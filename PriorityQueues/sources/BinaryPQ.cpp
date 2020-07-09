#include "../headers/BinaryHeap.h"
#include "../headers/BinaryPQ.h"
#include <vector>


// constructors
template<typename T>
BinaryPQ<T>::BinaryPQ() {}
// O(n) time (the heap must be built)
// O(n) space (if the vector needs to be copied, most compilers are able to avoid this, however)
// O(1) space (usually)
template<typename T>
BinaryPQ<T>::BinaryPQ(std::vector<T> arr) {
    heap.setVector(arr);
}

// tests whether the priority queue is empty
// O(1) time
// O(1) space
template<typename T> 
bool BinaryPQ<T>::isEmpty() {
    return heap.size() == 0;
}

// gets the size of the priority queue
// O(1) time
// O(1) space
template<typename T>
int BinaryPQ<T>::size() {
    return heap.size();
}

// returns the min element in the priority queue
// O(1) time
// O(1) space
template<typename T>
T BinaryPQ<T>::top() {
    if (heap.size() == 0) throw "You cannot access the top of an empty BinaryPQ.";
    return heap.getMin();
}

// adds an element to the priority queue
// O(log(n)) time
// O(1) space
template<typename T>
void BinaryPQ<T>::push(T element) {
    heap.add(element);
}

// removes and returns the minimum element
// O(log(n)) time
// O(1) space
template<typename T>
T BinaryPQ<T>::pop() {
    if (heap.size() == 0) throw "You cannot pop from an empty BinaryPQ.";
    return heap.extractMin();
}

// removes every element from the priority queue
// O(n) time 
// O(1) space
template<typename T>
void BinaryPQ<T>::clear() {
    heap.clear();
}

// prints the heap to the console
// O(n) time
// O(1) space
template<typename T>
void BinaryPQ<T>::print() {
    heap.print();
}
