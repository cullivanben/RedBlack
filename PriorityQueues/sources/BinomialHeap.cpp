#include "../headers/BinomialHeap.h"
#include "../headers/Node.h"
#include <iostream>


// constructor
template<typename T>
BinomialHeap<T>::BinomialHeap() {
    head = 0;
}

// returns the head of this heap
// O(1) time
// O(1) space
template<typename T>
Node<T>* BinomialHeap<T>::getHead() {
    return head;
}

// sets the head of this heap
// O(1) time
// O(1) space
template<typename T>
void BinomialHeap<T>::setHead(Node<T>* newHead) {
    head = newHead;
}

// inserts a node into the heap
// O(log(n)) time
// O(1) space
template<typename T>
void BinomialHeap<T>::insert(T data) {
    // create a heap consisting of only one node that contains 
    // the data to be inserted
    // BinomialHeap<T> other;
    // other.setHead(new Node(data, 0));
    merge(new Node(data, 0));
}

// returns the minimum value of this heap
// O(log(n)) time 
// O(1) space
template<typename T>
T BinomialHeap<T>::getMin() {
    T min = head->data;
    Node<T>* curr = head->sibling;
    while (curr) {
        if (curr->data < min) min = curr->data;
        curr = curr->sibling;
    }
    return min;
}

// extracts the minimum value of this heap
// O(log(n)) time
// O(1) space
template<typename T>
T BinomialHeap<T>::extractMin() {
    if (!head) throw "You cannot extract the min from an empty heap.";
    // find the node with the smallest value
    Node<T> *min = head, *minPrev = 0, *curr = head, *prev = 0;
    while (curr) {
        if (curr->data < min->data) {
            min = curr;
            minPrev = prev;
        }
        prev = curr;
        curr = curr->sibling;
    }
    // splice out the node that is being deleted
    if (minPrev) minPrev->sibling = min->sibling;
    else head = min->sibling;
    // get the child node
    curr = min->child;
    // get the value of the min node
    T val = min->data;
    // delete the min node
    delete min;
    // if there is no child, return
    if (!curr) return val;
    // reverse the list of the min node's children
    prev = 0;
    Node<T>* next = curr->sibling;
    while (next) {
        curr->sibling = prev;
        prev = curr;
        curr = next;
        next = next->sibling;
    }
    curr->sibling = prev;

    merge(curr);
    return val;
}


// MERGE

// merges two binomial heaps
// O(log(n)) time
// O(1) space
template<typename T>
void BinomialHeap<T>::merge(Node<T>* other) {
    // // create the heap to merge with the main heap
    // BinomialHeap<T> hPrime;
    // hPrime.setHead(other);
    // // merge hPrime with this heap
    // std::cout << "\nhprime\n";
    // hPrime.printHeap();
    // std::cout << "\n\n";
    if (!other) return;
    if (!head) {
        head = other;
        return;
    }
    // get pointers to the two heads 
    Node<T> *a, *b, *t;
    //head = head->degree < other->degree ? head : other;
    // if (head->degree < other->degree) {
    //     a = head;
    //     b = other;
    // } else {
    //     a = other;
    //     b = head;
    //     std::cout << "OTHERRRRR" << other->data << "\n";
    //     head = other;
    // }
    a = head;
    b = other;
    if (other->degree < head->degree) head = other;

    // merge the heaps base on degree
    while(a && b) {
        if (a->degree <= b->degree) {
            while (a->sibling && a->sibling->degree < b->degree) {
                a = a->sibling;
            }
            t = a;
            a = a->sibling;
            t->sibling = b;
        } else {
            while (b->sibling && b->sibling->degree < a->degree) {
                b = b->sibling;
            }
            t = b;
            b = b->sibling;
            t->sibling = a;
        }
        // while (a->sibling && b->degree > a->sibling->degree) a = a->sibling;
        // Node<T>* curr = b;
        // b = b->sibling;
        // // splice the node from b into a's heap
        // curr->sibling = a->sibling;
        // a->sibling = curr;
        // a = a->sibling;
    }
    // if (a) a->sibling = b;
    // Node<T>* y = head;
    // while (y) {
    //     std::cout << "curr:" << y->data << " ";
    //     y = y->sibling;
    // }
    // std::cout << "\n";
    // std::cout << "printing after degree merge: \n";
    // printHeap();
    // std::cout << "doneaosdnf\n\n";

    // set pointers for the merging process of heaps with the same degree
    Node<T> *prev = 0, *curr = head, *next = head->sibling;
    
    // merge heaps of the same degree
    while (next) {
        // if the degrees are different, or if the degree of next->sibling is 
        // the same as that of next and curr move forward
        if (curr->degree != next->degree || (next->sibling && curr->degree == 
            next->degree && next->degree == next->sibling->degree)) {
            prev = curr;
            curr = next;
            next = next->sibling;
        } 
        // if the value of curr is less than the value of next, make next 
        // the left child of curr
        else if (curr->data < next->data) {
            curr->degree++;
            curr->sibling = next->sibling;
            next->sibling = curr->child;
            curr->child = next;
            next = curr->sibling;
        }
        // if the degree of next is less than or equal to the degree of curr,
        // make curr the left child of next
        else {
            if (prev) prev->sibling = next;
            else head = next;
            next->degree++;
            curr->sibling = next->child;
            next->child = curr;
            curr = next;
            next = next->sibling;
        }
    }
}

// prints the heap
template<typename T>
void BinomialHeap<T>::printHeap() {
    std::cout << "Binomial Heap:\n";
    int i = 1;
    while (head) {
        std::cout << "Tree " << i++ << ": [" << head->data;
        if (head->child) std::cout << ", ";
        Node<T>* down = head->child;
        while (down) {
            Node<T>* curr = down;
            while (curr) {
                std::cout << curr->data;
                if (curr->sibling || down->child) std::cout << ", ";
                curr = curr->sibling;
            }
            down = down->child;
        }
        std::cout << "]\n";
        head = head->sibling;
    }
}
