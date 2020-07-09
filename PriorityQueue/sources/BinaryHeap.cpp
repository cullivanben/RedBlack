#include "../headers/BinaryHeap.h"
#include <vector>


// constructor
// O(n) time (the heap must be built)
// O(n) space (if the vector needs to be copied, most compilers are able to avoid this, however)
// O(1) space (usually)
template<typename T>
BinaryHeap<T>::BinaryHeap(std::vector<T> arr) {
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
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

// retrieves the minimum element from the heap
// O(1) time
// O(1) space
template<typename T>
T BinaryHeap<T>::getMin() {
    return heap[0];
}

// retrieves and removes the minimum element from the heap
// O(log(n)) time
// O(1) space
template<typename T>
T BinaryHeap<T>::extractMin() {
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

// returns the vector of all the elements in the heap
// O(n) time (if the vector is copied, most compilers are able to avoid this, however)
// O(1) time (usually)
// O(n) space (if the vector is copied, most compilers are able to avoid this, however)
// O(1) space (usually)
template<typename T>
std::vector<T> BinaryHeap<T>::getHeap() {
    return heap;
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
    // as long as the element at i is not the smallest of it and its children,
    // swap it with its smallest child
    while (1) {
        int left = leftChild(i);
        int right = rightChild(i);

        // set the element at i as the current smallest element
        int smallest = i;

        // if the left child is smaller than the current smallest element,
        // set the left child as the smallest
        if (left < heap.size() && heap[left] < heap[smallest]) smallest = left;

        // if the right child is samller than the current smallest element, 
        // set the right child as the smallest
        if (right < heap.size() && heap[right] < heap[smallest]) smallest = right;

        // if the element at i is the smallest, the heap has been minified
        if (smallest == i) return;

        // swap the element at i with the smallest element and move down the heap
        swap(heap[i], heap[smallest]);
        i = smallest;
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
    while (start >= 0) {
        minHeapify(start);
        start--;
    }
}


// HEAPSORT

// uses heapsort to sort a vector
// the sorted array will be in non-increasing order
template<typename T>
void BinaryHeap<T>::heapsort(std::vector<T>& arr) {
    // convert the vector to a heap
    sBuildHeap(arr);
    // repeatedly take the smallest element from the heap and put it at 
    // the end of the vector and then restore the heap
    int end = arr.size();
    while (end > 1) {
        swap(arr[0], arr[--end]);
        sMinHeapify(0, arr, end);
    }
}


// HEAPSORT HELPERS

// converts the heap to a min heap, assuming that all subtrees are valid min heaps
// O(log(n)) time
// O(1) space
template<typename T>
void BinaryHeap<T>::sMinHeapify(int i, std::vector<T>& arr, int end) {
    // as long as the element at i is not the smallest of it and its children,
    // swap it with its smallest child
    while (1) {
        int left = leftChild(i);
        int right = rightChild(i);

        // set the element at i as the current smallest element
        int smallest = i;

        // if the left child is smaller than the current smallest element,
        // set the left child as the smallest
        if (left < end && arr[left] < arr[smallest]) smallest = left;

        // if the right child is samller than the current smallest element, 
        // set the right child as the smallest
        if (right < end && arr[right] < arr[smallest]) smallest = right;

        // if the element at i is the smallest, the heap has been minified
        if (smallest == i) return;

        // swap the element at i with the smallest element and move down the heap
        swap(arr[i], arr[smallest]);
        i = smallest;
    }
}

// turns a vector into a min heap
// O(n) time
// O(1) space
template<typename T>
void BinaryHeap<T>::sBuildHeap(std::vector<T>& arr) {
    // find the last non-leaf element
    // min heapify at every element from that to the beginning of the vector
    int start = parent(arr.size() - 1);
    while (start >= 0) {
        sMinHeapify(start, arr, arr.size());
        start--;
    }
}

