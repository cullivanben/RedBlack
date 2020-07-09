#include <vector>

#ifndef BINARY_HEAP
#define BINARY_HEAP

template<typename T>
class BinaryHeap {
    std::vector<T> heap;

    // private helper methods
    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    void minHeapify(int i);
    void buildHeap();

    // static helpers for heapsort
    static int sParent(int i);
    static int sLeftChild(int i);
    static int sRightChild(int i);
    static void sMaxHeapify(int i, std::vector<T>& arr, int end);
    static void sBuildHeap(std::vector<T>& arr);

    public:
        BinaryHeap();
        BinaryHeap(std::vector<T> arr);
        void add(T element);
        T getMin();
        T extractMin();
        int size();
        void clear();
        std::vector<T> getHeap();
        
        // static heapsort method
        static void heapsort(std::vector<T>& arr);
};
// include the source file so that the compiler can access it
#include "../sources/BinaryHeap.cpp"

#endif
