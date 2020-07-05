#ifndef SET_NODE
#define SET_NODE

template<typename T>
class SetNode {
    SetNode* left;
    SetNode* right;
    T value;
    public:
        SetNode(T value, SetNode* left, SetNode* right);
};

// public constructor
template<typename T>
SetNode<T>::SetNode(T value, SetNode* left, SetNode* right) {
    this->value = value;
    this->left = left;
    this->right = right;
}

#endif