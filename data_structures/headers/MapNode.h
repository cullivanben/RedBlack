#ifndef MAP_NODE
#define MAP_NODE

template<typename T1, typename T2>
struct MapNode {
    T1 key;         
    T2 value;
    bool black; 
    MapNode<T1, T2>* parent;
    MapNode<T1, T2>* left;  
    MapNode<T1, T2>* right;      
    MapNode(T1 key, T2 value, bool black, MapNode<T1, T2>* parent, MapNode<T1, T2>* left, MapNode<T1, T2>* right) {
        this->key = key;
        this->value = value;
        this->black = black;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }  
};

#endif
