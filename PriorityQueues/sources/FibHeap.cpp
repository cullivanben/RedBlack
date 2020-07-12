#include "../headers/FibHeap.h"
#include <unordered_map>
#include <queue>
#include <iostream>


// constructor
template<typename T>
FibHeap<T>::FibHeap() {
    min = 0;
}

// inserts a node into the heap
// O(1) time
// O(1) space
template<typename T>
void FibHeap<T>::insert(T key) {
    numNodes++;
    FibNode<T>* node = new FibNode(key, 0);
    if (min) {
        // node->left = min->left;
        // min->left->right = node;
        // node->right = min;
        // min->left = node;
        spliceIn(min, node);
        if (node->key < min->key) min = node;
    } else {
        node->left = node;
        node->right = node;
        min = node;
    }
}

// returns the minimum key in the heap
// O(1) time
// O(1) space
template<typename T>
T FibHeap<T>::getMin() {
    return min->key;
}

// extracts the minimum node and returns its key
// O(log(n)) time
// O(log(n)) space
template<typename T>
T FibHeap<T>::extractMin() {
    if (!min) throw "You can not extract the minimum key from an empty heap.";
    FibNode<T> *toDelete = 0, *start = 0, *curr = 0;
    // the minimum key
    T key = min->key;
    // if there is only one node in the heap
    if (min->right == min && !min->child) {
        delete min;
        min = 0;
        return key;
    }
    // if there is only one node in the root list
    else if (min->right == min) {
        toDelete = min;
        min = min->child;
        delete toDelete;
        fixHeap();
    }
    // get the degree of the node to be deleted
    int degree = min->degree;
    // get the node that is the child of the min node
    curr = min->child;
    // set the min node to the sibling of the node to be deleted
    toDelete = min;
    min = min->right;
    // splice out and delete the node to be deleted
    spliceOut(toDelete);
    delete toDelete;
    // merge the child trees of the node that was deleted with the main heap
    merge(curr);
    // fix the heap
    fixHeap();

    return key;
}

// prints the heap
template<typename T> 
void FibHeap<T>::printHeap() {
    std::cout << "Fibonacci heap:\n";
    FibNode<T> *temp = min, *start = min;
    int i = 1;
    do {
        std::cout << "Tree " << i++ << ": [ ";
        std::queue<FibNode<T>*> q;
        q.push(temp);
        while (!q.empty()) {
            FibNode<T>* node = q.front();
            q.pop();
            std::cout << node->key << ", ";
            if (node->child) {
                FibNode<T> *a = node->child, *b = node->child;
                do {
                    q.push(a);
                    a = a->right;
                } while (a != b);
            }
        }
        std::cout << "]\n";
        temp = temp->right;
    } while (temp != start);
}


// HELPER METHODS

// fixes the fib heap, making sure every node in the root list has a unique degree
// O(log(n)) time
// O(log(n)) space
template<typename T>
void FibHeap<T>::fixHeap() {
    std::unordered_map<int, FibNode<T>*> nodeMap;
    FibNode<T> *curr = min->right, *start = min, *other = 0, *holder = 0;
    start->parent = 0;
    start->loser = 0;
    // find the new min (this will stay in the root list)
    while (curr != start) {
        if (curr->key < min->key) min = curr;
        curr->parent = 0;
        curr->loser = 0;
        curr = curr->right;
    }
    if (min->right == min) return;
    start = 0;
    curr = min;
    do {
        start = curr;
        holder = curr;
        curr = curr->right;
        spliceOut(start);
        int degree = start->degree;
        while (nodeMap.find(degree) != nodeMap.end()) {
            other = nodeMap[degree];
            start = other->key < start->key ? link(other, start) : link(start, other);
            degree = start->degree;
        }
        nodeMap[degree] = start;
    } while (holder != curr);

    // rebuild the heap from the map
    for (auto it = nodeMap.begin(); it != nodeMap.end(); it++) {
        if (it->second != min) spliceIn(min, it->second);
    }
}

// splices a node out of its circular dll
// O(1) time
// O(1) space
template<typename T>
void FibHeap<T>::spliceOut(FibNode<T>* node) {
    node->right->left = node->left;
    node->left->right = node->right;
    node->left = node;
    node->right = node;
}

// splices a node into the circular dll of another node
// O(1) time
// O(1) space
template<typename T>
void FibHeap<T>::spliceIn(FibNode<T>* node, FibNode<T>* other) {
    other->left = node->left;
    other->right = node;
    node->left->right = other;
    node->left = other;
}

// links two nodes in a parent-child relationship
// O(1) time
// O(1) space
template<typename T>
FibNode<T>* FibHeap<T>::link(FibNode<T>* parent, FibNode<T>* child) {
    // splice the child out of its circular dll
    spliceOut(child);
    // if there is only one node left in the base list, set the min
    if (parent->left == parent) min = parent;
    // set parent as the parent of child
    child->parent = parent;
    // splice the child node into the parent's list of children
    if (!parent->child) parent->child = child;
    else spliceIn(parent->child, child);
    // set the child of the parent
    if (child->key < parent->child->key) parent->child = child;
    // increase the degree of parent and return parent
    parent->degree++;
    return parent;
}

// merges two fib heaps
// O(1) time
// O(1) space
template<typename T>
void FibHeap<T>::merge(FibNode<T>* other) {
    if (!min) {
        min = other;
        return;
    } 
    if (!other) return;
    // link the two heaps together
    FibNode<T>* thisRight = min->right;
    FibNode<T>* otherLeft = other->left;
    min->right = other;
    other->left = min;
    thisRight->left = otherLeft;
    otherLeft->right = thisRight;
    // update min
    if (other->key < min->key) min = other;
}

// // merges two circular doubly linked lists
// // O(1) time
// // O(1) space
// template<typename T>
// void FibHeap<T>::mergeLists(FibNode<T>* node, FibNode<T>* other) {
//     FibNode<T>* thisRight = node->right;
//     FibNode<T>* otherLeft = other->left;
//     node->right = other;
//     other->left = node;
//     thisRight->left = otherLeft;
//     otherLeft->right = thisRight;
// }

