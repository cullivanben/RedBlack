#include "MapNode.h"
#include <vector>
#include <deque>
#include <tuple>


#ifndef BC_TREE_MAP
#define BC_TREE_MAP

// this class uses a red black tree to implement a map
template<typename T1, typename T2>
class BCTreeMap {
    MapNode<T1, T2>* root;
    long long s;

    // private helper methods
    void insertRestore(MapNode<T1, T2>* curr);
    MapNode<T1, T2>* rotateLeft(MapNode<T1, T2>* curr, MapNode<T1, T2>* parent);
    MapNode<T1, T2>* rotateRight(MapNode<T1, T2>* curr, MapNode<T1, T2>* parent);
    void recolor(MapNode<T1, T2>* curr, bool color);
    void inorderHelp(MapNode<T1, T2>* curr, std::vector<MapNode<T1, T2>*>& arr);

    public:
        BCTreeMap();
        void put(T1 key, T2 value);
        void remove(T1 key);
        bool containsKey(T1 key);
        bool isEmpty();
        long long size();
        std::vector<MapNode<T1, T2>*> inorder();
        std::vector<std::vector<MapNode<T1, T2>*>> levelOrder();
};
// include the source file so that it is accessible to the compiler
#include "../sources/BCTreeMap.cpp"

#endif