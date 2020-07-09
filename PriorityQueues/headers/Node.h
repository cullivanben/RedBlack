#ifndef NODE
#define NODE

// the node struct that will be used in BinomialHeap
template <typename T>
struct Node {
    T data;
    int degree; 
    Node *parent, *child, *sibling;
    Node(T data, int degree) {
        this->data = data;
        this->degree = degree;
        parent = 0;
        child = 0;
        sibling = 0;
    }
};

#endif