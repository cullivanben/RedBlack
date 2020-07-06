#include "MapNode.h"

#ifndef BC_TREE_MAP
#define BC_TREE_MAP

// this class uses a red black tree to implement a map
template<typename T1, typename T2>
class BCTreeMap {
    MapNode* root;
    long long s;
    public:
        BCTreeMap();
        void put(T1 key, T2 value);
        void remove(T1 key);
        bool containsKey(T1 key);
        bool isEmpty();
        long long size();
};

// public constructor
template<typename T1, typename T2>
BCTreeMap<T1, T2>::BCTreeMap() {
    root = 0;
    s = 0;
}

// method to add a key-value pair to the map
template<typename T1, typename T2>
void BCTreeMap<T1, T2>::put(T1 key, T2 value) {

}

// method to remove a key value pair from the map
template<typename T1, typename T2>
void BCTreeMap<T1, T2>::remove(T1 key) {

}

// method to check if the map contains a certain key
template<typename T1, typename T2>
bool BCTreeMap<T1, T2>::containsKey(T1 key) {
    MapNode* curr = root;

    while (curr) {
        if (curr->key == key) return true;
        if (value < curr->key) curr = curr->left;
        else curr = curr->right;
    }

    return false;
}

// method to check if the map is empty
template<typename T1, typename T2>
bool BCTreeMap<T1, T2>::isEmpty() {
    return !root;
}

// method to check the number of key-value pairs in the map
template<typename T1, typename T2>
long long BCTreeMap<T1, T2>::size() {
    return s;
}

#endif