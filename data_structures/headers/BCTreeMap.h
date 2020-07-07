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
    std::tuple<T1, T2> successor(MapNode<T1, T2>* curr);
    void deleteNode(MapNode<T1, T2>* curr, MapNode<T1, T2>* child);
    void redDelete(MapNode<T1, T2>* curr, MapNode<T1, T2>* child);
    void blackDelete(MapNode<T1, T2>* curr, MapNode<T1, T2>* child);
    void fixTree(MapNode<T1, T2>* curr, MapNode<T1, T2>* parent, MapNode<T1, T2>* sibling, bool left);
    void deleteRotate(MapNode<T1, T2>* parent, MapNode<T1, T2>* sibling);
    void inorderHelp(MapNode<T1, T2>* curr, std::vector<MapNode<T1, T2>*>& arr);
    int validHelp(MapNode<T1, T2>* curr);
    bool bst();
    bool bstHelp(MapNode<T1, T2>* curr, MapNode<T1, T2>* prev, bool* lowest);

    public:
        BCTreeMap();
        void put(T1 key, T2 value);
        void remove(T1 key, MapNode<T1, T2>* curr = 0);
        bool containsKey(T1 key);
        bool isEmpty();
        long long size();
        std::vector<MapNode<T1, T2>*> inorder();
        std::vector<std::vector<MapNode<T1, T2>*>> levelOrder();
        bool isValid();
};
// include the source file so that it is accessible to the compiler
#include "../sources/BCTreeMap.cpp"

#endif
