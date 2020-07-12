#include "../headers/FibHeap.h"
#include <iostream>

using namespace std;


void fibTest1() {
    FibHeap<int> heap;
    heap.insert(4);
    heap.insert(6);
    heap.insert(2);
    heap.insert(-5);
    heap.insert(10);
    heap.printHeap();
    cout << "Min: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "Min: " << heap.extractMin() << "\n";
    heap.printHeap();
}

int main() {
    fibTest1();
    return 0;
}