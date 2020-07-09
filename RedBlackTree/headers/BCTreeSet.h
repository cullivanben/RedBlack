#include "SetNode.h"
#include <vector>
#include <deque>
#include <tuple>

#ifndef BC_TREE_SET
#define BC_TREE_SET

// this template class uses a red black tree to implement a set
template<typename T>
class BCTreeSet {
    SetNode<T>* root; 
    long long s; 

    // private helper methods
    void insertRestore(SetNode<T>* curr);
    SetNode<T>* rotateLeft(SetNode<T>* curr, SetNode<T>* parent);
    SetNode<T>* rotateRight(SetNode<T>* curr, SetNode<T>* parent);
    void recolor(SetNode<T>* curr, bool color);  
    T successor(SetNode<T>* curr);
    void deleteNode(SetNode<T>* curr, SetNode<T>* child);
    void redDelete(SetNode<T>* curr, SetNode<T>* child);
    void blackDelete(SetNode<T>* curr, SetNode<T>* child);
    void fixTree(SetNode<T>* curr, SetNode<T>* parent, SetNode<T>* sibling, bool left);
    void deleteRotate(SetNode<T>* parent, SetNode<T>* sibling);
    int validHelp(SetNode<T>* curr);
    bool bst();
    bool bstHelp(SetNode<T>* curr, T* prev, bool* lowest);

    public:
        BCTreeSet();
        void add(T value);
        void remove(T value, SetNode<T>* curr = 0);
        bool contains(T value);
        bool isEmpty();
        long long size();
        std::vector<std::vector<SetNode<T>*>> levelOrder();
        bool isValid();
        void setRootForTest(SetNode<T>* node); // this method is purely for testing 
        // so that invalid trees can be tested, this method would not be included in 
        // an actual software release
};
// include the source file so that the compiler can access it 
#include "../sources/BCTreeSet.cpp"

#endif
