#ifndef NODE
#define NODE

// the node struct that will be used in BinomialHeap
template <typename T>
struct Node {
    T data;
    int degree; 
    Node *child, *sibling;
    Node(T data, int degree) {
        this->data = data;
        this->degree = degree;
        child = 0;
        sibling = 0;
    }
};

#endif