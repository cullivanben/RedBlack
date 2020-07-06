#ifndef SET_NODE
#define SET_NODE

template<typename T>
class SetNode {
    SetNode* left; 
    SetNode* right; 
    T value;        
    public:
        SetNode(T value, SetNode* left, SetNode* right);
        T getValue();
        SetNode<T>* getLeft();
        SetNode<T>* getRight();
};

template<typename T>
SetNode<T>::SetNode(T value, SetNode* left, SetNode* right) {
    this->value = value;
    this->left = left;
    this->right = right;
}

template<typename T>
T SetNode<T>::getValue() {
    return value;
}

template<typename T> 
SetNode<T>* SetNode<T>::getLeft() {
    return left;
}

template<typename T>
SetNode<T>* SetNode<T>::getRight() {
    return right;
}

#endif