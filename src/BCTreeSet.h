#include "SetNode.h"

#ifndef BC_TREE_SET
#define BC_TREE_SET

// this template class uses a red black tree to implement a set
template<typename T>
class BCTreeSet {
    SetNode<T>* root; 
    long long s;      
    public:
        BCTreeSet();
        void add(T value);
        void remove(T value);
        bool contains(T value);
        bool isEmpty();
        long long size();
};

// public constructor for the set
template<typename T> 
BCTreeSet<T>::BCTreeSet() {
    root = 0;
    s = 0;
}

// method to add a value to the set
// O(log(n)) time
// O(1) space
template<typename T> 
void BCTreeSet<T>::add(T value) {
    // in the case where this is the first value to be added to the set
    if (!root) {
        root = new SetNode<T>(value, 0, 0);
        s++;
        return;
    }
}

// method to remove a value from the set
// O(log(n)) time
// O(1) space
template<typename T> 
void BCTreeSet<T>::remove(T value) {
    if (!root) return;
}

// method to check if the set contains a value
// O(log(n)) time
// O(1) space
template<typename T>
bool BCTreeSet<T>::contains(T value) {
    SetNode* curr = root;

    while (curr) {
        if (curr->getValue() == value) return true;
        if (value < curr->getValue()) curr = curr->getLeft();
        else curr = curr->getRight();
    }

    return false;
}

// method to check if the set is empty
// O(1) time
// O(1) space
template<typename T> 
bool BCTreeSet<T>::isEmpty() {
    return !root;
}

// method to check the size of the set
// O(1) time
// O(1) space
template<typename T>
long long BCTreeSet<T>::size() {
    return s;
}

#endif