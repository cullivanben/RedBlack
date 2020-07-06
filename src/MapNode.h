#ifndef MAP_NODE
#define MAP_NODE

template<typename T1, typename T2>
class MapNode {
    MapNode* left;  
    MapNode* right; 
    T1 key;         
    T2 value;       
    public:
        MapNode(T1 key, T2 value, MapNode* left, MapNode* right);
        T1 getKey();
        T2 getValue();
        MapNode<T1, T2>* getLeft();
        MapNode<T1, T2>* getRight();
};

template <typename T1, typename T2>
MapNode<T1, T2>::MapNode(T1 key, T2 value, MapNode* left, MapNode* right) {
    this->key = key;
    this->value = value;
    this->left = left;
    this->right = right;
}

template <typename T1, typename T2>
T1 MapNode<T1, T2>::getKey() {
    return key;
}

template <typename T1, typename T2>
T2 MapNode<T1, T2>::getValue() {
    return value;
}

template <typename T1, typename T2>
MapNode<T1, T2>* MapNode<T1, T2>::getLeft() {
    return left;
}

template <typename T1, typename T2>
MapNode<T1, T2>* MapNode<T1, T2>::getRight() {
    return right;
}

#endif