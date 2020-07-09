#include "../headers/BinaryHeap.h"
#include <vector>
#include <iostream>


// constructors
template<typename T>
BinaryHeap<T>::BinaryHeap() {}
// O(n) time (the heap must be built)
// O(n) space (if the vector needs to be copied, most compilers are able to avoid this, however)
// O(1) space (usually)
template<typename T>
BinaryHeap<T>::BinaryHeap(std::vector<T> arr) {
    heap = arr;
    buildHeap();
}

// sets the underlying vector of this heap
// O(n) time (the heap must be built)
// O(n) space (if the vector needs to be copied, most compilers are able to avoid this, however)
// O(1) space (usually)
template<typename T>
void BinaryHeap<T>::setVector(std::vector<T> arr) {
    heap = arr;
    buildHeap();
}

// inserts an element into the heap
// O(log(n)) time
// O(1) space
template<typename T>
void BinaryHeap<T>::add(T element) {
    // add at the end of the vector and swap with its parent while it is smaller
    heap.push_back(element);
    int i = heap.size() - 1;
    while (i > 0 && heap[i] < heap[parent(i)]) {
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

// retrieves the minimum element from the heap
// O(1) time
// O(1) space
template<typename T>
T BinaryHeap<T>::getMin() {
    if (heap.size() == 0) throw "An empty heap does not have a minimum.";
    return heap[0];
}

// retrieves and removes the minimum element from the heap
// O(log(n)) time
// O(1) space
template<typename T>
T BinaryHeap<T>::extractMin() {
    if (heap.size() == 0) throw "You cannot extractMin from an empty heap.";
    // get the smallest element
    T min = heap[0];
    // replace the head of the heap with the last element
    // then remove the last element from the heap
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    // restore the min heap
    minHeapify(0);
    // return the minimum element
    return min;
}

// returns the number of elements in the heap
// O(1) time
// O(1) space
template<typename T>
int BinaryHeap<T>::size() {
    return heap.size();
}

// removes every value from the heap
// O(n) time 
// O(1) space
template<typename T>
void BinaryHeap<T>::clear() {
    heap.clear();
}

// prints the heap to the console
// O(n) time 
// O(1) space
template<typename T>
void BinaryHeap<T>::print() {
    std::cout << '[';
    for (int i = 0; i < heap.size(); i++) {
        std::cout << heap[i];
        if (i < heap.size()-1) std::cout << ", ";
    }
    std::cout << "]\n";
}


// PRIVATE HELPER METHODS

// calculates the index of the parent of the element at index i
// O(1) time
// O(1) space
template<typename T>
int BinaryHeap<T>::parent(int i) {
    return (i - 1) / 2;
}

// calculates the index of the left child of the element at index i
// O(1) time
// O(1) space
template<typename T>
int BinaryHeap<T>::leftChild(int i) {
    return 2 * i + 1;
}

// calculates the index of the right child of the element at index i
// O(1) time
// O(1) space
template<typename T>
int BinaryHeap<T>::rightChild(int i) {
    return 2 * i + 2;
}

// converts the heap to a min heap, assuming that all subtrees are valid min heaps
// O(log(n)) time
// O(1) space
template<typename T>
void BinaryHeap<T>::minHeapify(int i) {
    // as long as the element at i is not the largest of it and its children,
    // swap it with its largest child
    while (1) {
        int left = leftChild(i);
        int right = rightChild(i);

        // set the element at i as the current largest element
        int largest = i;

        // if the left child is smaller than the current largest element,
        // set the left child as the largest
        if (left < heap.size() && heap[left] < heap[largest]) largest = left;

        // if the right child is samller than the current largest element, 
        // set the right child as the largest
        if (right < heap.size() && heap[right] < heap[largest]) largest = right;

        // if the element at i is the largest, the heap has been minified
        if (largest == i) return;

        // swap the element at i with the largest element and move down the heap
        std::swap(heap[i], heap[largest]);
        i = largest;
    }
}

// turns a vector into a min heap
// O(n) time
// O(1) space
template<typename T>
void BinaryHeap<T>::buildHeap() {
    // find the last non-leaf element
    // min heapify at every element from that to the beginning of the vector
    int start = parent(heap.size() - 1);
    while (start >= 0) minHeapify(start--);
}


// HEAPSORT

// uses heapsort to sort a vector
// the sorted array will be in non-decreasing order
template<typename T>
void BinaryHeap<T>::heapsort(std::vector<T>& arr) {
    // convert the vector to a heap
    sBuildHeap(arr);
    // repeatedly take the smallest element from the heap and put it at 
    // the end of the vector and then restore the heap
    int end = arr.size();
    while (end > 1) {
        std::swap(arr[0], arr[--end]);
        sMaxHeapify(0, arr, end);
    }
}


// HEAPSORT HELPERS

// calculates the index of the parent of the element at index i
// O(1) time
// O(1) space
template<typename T>
int BinaryHeap<T>::sParent(int i) {
    return (i - 1) / 2;
}

// calculates the index of the left child of the element at index i
// O(1) time
// O(1) space
template<typename T>
int BinaryHeap<T>::sLeftChild(int i) {
    return 2 * i + 1;
}

// calculates the index of the right child of the element at index i
// O(1) time
// O(1) space
template<typename T>
int BinaryHeap<T>::sRightChild(int i) {
    return 2 * i + 2;
}

// converts the heap to a max heap, assuming that all subtrees are valid min heaps
// O(log(n)) time
// O(1) space
template<typename T>
void BinaryHeap<T>::sMaxHeapify(int i, std::vector<T>& arr, int end) {
    // as long as the element at i is not the largest of it and its children,
    // swap it with its largest child
    while (1) {
        int left = sLeftChild(i);
        int right = sRightChild(i);

        // set the element at i as the current largest element
        int max = i;

        // if the left child is larger than the current largest element,
        // set the left child as the largest
        if (left < end && arr[left] > arr[max]) max = left;

        // if the right child is larger than the current largest element, 
        // set the right child as the largest
        if (right < end && arr[right] > arr[max]) max = right;

        // if the element at i is the largest, the heap has been maxified
        if (max == i) return;

        // swap the element at i with the largest element and move down the heap
        std::swap(arr[i], arr[max]);
        i = max;
    }
}

// turns a vector into a max heap
// O(n) time
// O(1) space
template<typename T>
void BinaryHeap<T>::sBuildHeap(std::vector<T>& arr) {
    // find the last non-leaf element
    // max heapify at every element from that to the beginning of the vector
    int start = sParent(arr.size() - 1);
    while (start >= 0) sMaxHeapify(start--, arr, arr.size());
}

