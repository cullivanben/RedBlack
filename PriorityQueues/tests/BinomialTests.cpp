#include "../headers/BinomialHeap.h"
#include "../headers/Node.h"
#include <iostream>
#include <queue>

using namespace std;


// prints a heap 
void printHeap(BinomialHeap<int> heap) {
    cout << "Binomial Heap:\n";
    Node<int>* head = heap.getHead();
    int i = 1;
    while (head) {
        cout << "Tree " << i++ << ": [" << head->data;
        if (head->child) cout << ", ";
        Node<int>* down = head->child;
        while (down) {
            Node<int>* curr = down;
            while (curr) {
                cout << curr->data;
                if (curr->sibling || down->child) cout << ", ";
                curr = curr->sibling;
            }
            down = down->child;
        }
        cout << "]\n";
        head = head->sibling;
    }
}

void heapTest1() {
    BinomialHeap<int> heap;
    heap.insert(8);
    cout << "\nInserting " << 8 << "...\n";
    printHeap(heap);
    heap.insert(9);
    cout << "\nInserting " << 9 << "...\n";
    printHeap(heap);
    heap.insert(2);
    cout << "\n\nInserting " << 2 << "...\n";
    printHeap(heap);
    heap.insert(40);
    cout << "\nInserting " << 40 << "...\n";
    printHeap(heap);
    heap.insert(1);
    cout << "\nInserting " << 1 << "...\n";
    printHeap(heap);
    heap.insert(7);
    cout << "\nInserting " << 7 << "...\n";
    printHeap(heap);
    heap.insert(8);
    cout << "\nInserting " << 8 << "...\n";
    printHeap(heap);
    heap.insert(8);
    cout << "\nInserting " << 8 << "...\n";
    printHeap(heap);
    heap.insert(45);
    cout << "\nInserting " << 45 << "...\n";
    printHeap(heap);
    heap.insert(435);
    cout << "\nInserting " << 435 << "...\n";
    printHeap(heap);
    heap.insert(3452435);
    cout << "\nInserting " << 3452435 << "...\n";
    printHeap(heap);
    cout << "\nGet min: " << heap.getMin() << "\n"; 
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    cout << "\nExtracting min...\nMin: " << heap.extractMin() << "\n";
    printHeap(heap);
    
}
int main() {
    heapTest1();
    return 0;
}
