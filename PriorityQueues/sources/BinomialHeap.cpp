#include "../headers/BinomialHeap.h"
#include "../headers/Node.h"
#include <iostream>
#include <queue>


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
    if (!other) return;
    if (!head) {
        head = other;
        return;
    }
    // get pointers to the two heads 
    Node<T> *a, *b, *t;
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
    }

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
    Node<T>* temp = head;
    int i = 1;
    while (temp) {
        std::cout << "Tree " << i++ << ": [ ";
        std::queue<Node<T>*> q;
        q.push(temp);
        while (!q.empty()) {
            Node<int>* node = q.front();
            q.pop();
            std::cout << node->data << ", ";
            if (node->child) {
                Node<int>* chi = node->child;
                while (chi) {
                    q.push(chi);
                    chi = chi->sibling;
                }
            }
        }
        std::cout << "]\n";
        temp = temp->sibling;
    }
}
