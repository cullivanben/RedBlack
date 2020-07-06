#ifndef SET_NODE
#define SET_NODE

template<typename T>
struct SetNode {
    T value;        
    bool black;
    SetNode* parent;
    SetNode* left; 
    SetNode* right; 
    SetNode(T value, bool black, SetNode* parent, SetNode* left, SetNode* right) {
        this->value = value;
        this->black = black;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }
};

#endif