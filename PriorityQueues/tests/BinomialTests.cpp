#include "../headers/BinomialHeap.h"
#include "../headers/Node.h"
#include <iostream>
#include <queue>

using namespace std;


// tests the binomial heap to make sure that it works
void heapTest1() {
    BinomialHeap<int> heap;
    heap.insert(8);
    cout << "\nInserting " << 8 << "...\n";
    heap.printHeap();
    heap.insert(9);
    cout << "\nInserting " << 9 << "...\n";
    heap.printHeap();
    heap.insert(2);
    cout << "\n\nInserting " << 2 << "...\n";
    heap.printHeap();
    heap.insert(40);
    cout << "\nInserting " << 40 << "...\n";
    heap.printHeap();
    heap.insert(1);
    cout << "\nInserting " << 1 << "...\n";
    heap.printHeap();
    heap.insert(7);
    cout << "\nInserting " << 7 << "...\n";
    heap.printHeap();
    heap.insert(8);
    cout << "\nInserting " << 8 << "...\n";
    heap.printHeap();
    heap.insert(8);
    cout << "\nInserting " << 8 << "...\n";
    heap.printHeap();
    heap.insert(45);
    cout << "\nInserting " << 45 << "...\n";
    heap.printHeap();
    heap.insert(435);
    cout << "\nInserting " << 435 << "...\n";
    heap.printHeap();
    heap.insert(3452435);
    cout << "\nInserting " << 3452435 << "...\n";
    heap.printHeap();
    cout << "\nGet min: " << heap.getMin() << "\n"; 
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    heap.printHeap();
}


int main() {
    heapTest1();
    return 0;
}
