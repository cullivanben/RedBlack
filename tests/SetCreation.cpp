#include "../headers/BCTreeSet.h"

// INVALID TREES

// creates a tree that is invalid because it has a red root
BCTreeSet<int> createInvalidTree1() {
    SetNode<int>* root = new SetNode<int>(1, 0, 0, 0, 0);
    // create the set
    BCTreeSet<int> invalid;
    invalid.setRootForTest(root);
    return invalid;
}

// creates a tree that is invalid because it has consecutive red nodes
BCTreeSet<int> createInvalidTree2() {
    SetNode<int>* root = new SetNode<int>(10, 1, 0, 0, 0);
    SetNode<int>* six = new SetNode<int>(6, 1, root, 0, 0);
    root->left = six;
    SetNode<int>* five = new SetNode<int>(5, 0, six, 0, 0);
    six->left = five;
    SetNode<int>* twelve = new SetNode<int>(12, 1, root, 0, 0);
    root->right = twelve;
    SetNode<int>* eleven = new SetNode<int>(11, 0, twelve, 0, 0);
    twelve->left = eleven;
    SetNode<int>* thirteen = new SetNode<int>(13, 0, twelve, 0, 0);
    twelve->right = thirteen;
    SetNode<int>* fourteen = new SetNode<int>(14, 0, thirteen, 0, 0);
    thirteen->right = fourteen;
    // create the set
    BCTreeSet<int> invalid;
    invalid.setRootForTest(root);
    return invalid;
}

// creates a tree that is invalid because it has unequal black depths
BCTreeSet<int> createInvalidTree3() {
    SetNode<int>* root = new SetNode<int>(10, 1, 0, 0, 0);
    SetNode<int>* six = new SetNode<int>(6, 1, root, 0, 0);
    root->left = six;
    SetNode<int>* five = new SetNode<int>(5, 1, six, 0, 0);
    six->left = five;
    SetNode<int>* twelve = new SetNode<int>(12, 0, root, 0, 0);
    root->right = twelve;
    SetNode<int>* eleven = new SetNode<int>(11, 1, twelve, 0, 0);
    twelve->left = eleven;
    SetNode<int>* thirteen = new SetNode<int>(13, 1, twelve, 0, 0);
    twelve->right = thirteen;
    SetNode<int>* fourteen = new SetNode<int>(14, 0, thirteen, 0, 0);
    thirteen->right = fourteen;
    // create the set
    BCTreeSet<int> invalid;
    invalid.setRootForTest(root);
    return invalid;
}

// creates a tree that is invalid because it is not a valid BST
BCTreeSet<int> createInvalidTree4() {
    SetNode<int>* root = new SetNode<int>(10, 1, 0, 0, 0);
    SetNode<int>* six = new SetNode<int>(6, 1, root, 0, 0);
    root->left = six;
    SetNode<int>* five = new SetNode<int>(5, 0, six, 0, 0);
    six->left = five;
    SetNode<int>* twelve = new SetNode<int>(12, 1, root, 0, 0);
    root->right = twelve;
    SetNode<int>* ten = new SetNode<int>(10, 0, twelve, 0, 0);
    twelve->left = ten;
    SetNode<int>* thirteen = new SetNode<int>(13, 0, twelve, 0, 0);
    twelve->right = thirteen;
    // create the set
    BCTreeSet<int> invalid;
    invalid.setRootForTest(root);
    return invalid;
}

// INSERTION TREES

// creates a tree that will have a red node inserted to a black parent
BCTreeSet<int> createInsertionTree1() {
    SetNode<int>* root = new SetNode<int>(0, 1, 0, 0, 0);
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree that will have a node inserted to a parent and
// uncle that are both red
BCTreeSet<int> createInsertionTree2() {
    SetNode<int>* root = new SetNode<int>(0, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(-2, 1, root, 0, 0);
    root->left = left;
    SetNode<int>* right = new SetNode<int>(2, 0, root, 0, 0);
    root->right = right;
    SetNode<int>* rl = new SetNode<int>(1, 1, right, 0, 0);
    right->left = rl;
    SetNode<int>* rr = new SetNode<int>(6, 1, right, 0, 0);
    right->right = rr;
    SetNode<int>* rrl = new SetNode<int>(5, 0, rr, 0, 0);
    rr->left = rrl;
    SetNode<int>* rrr = new SetNode<int>(7, 0, rr, 0, 0);
    rr->right = rrr;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the parent is red and the uncle is black
BCTreeSet<int> createInsertionTree3() {
    SetNode<int>* root = new SetNode<int>(0, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(-10, 0, root, 0, 0);
    root->left = left;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// DELETION TREES

// creates a tree where the node being deleted is red
BCTreeSet<int> createDeletionTree1() {
    SetNode<int>* root = new SetNode<int>(0, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(-5, 0, root, 0, 0);
    root->left = left;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the node that is being removed will have a red child
BCTreeSet<int> createDeletionTree2() {
    SetNode<int>* root = new SetNode<int>(0, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(-2, 1, root, 0, 0);
    root->left = left;
    SetNode<int>* right = new SetNode<int>(1, 1, root, 0, 0);
    root->right = right;
    SetNode<int>* lr = new SetNode<int>(-1, 0, left, 0, 0);
    left->right = lr;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the sibling is black and has a red child
BCTreeSet<int> createDeletionTree3Left() {
    SetNode<int>* root = new SetNode<int>(30, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(20, 1, root, 0, 0);
    root->left = left;
    SetNode<int>* right = new SetNode<int>(40, 1, root, 0, 0);
    root->right = right;
    SetNode<int>* ll = new SetNode<int>(15, 0, left, 0, 0);
    left->left = ll;
    SetNode<int>* lr = new SetNode<int>(25, 0, left, 0, 0);
    left->right = lr;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the sibling is black and has a red child
BCTreeSet<int> createDeletionTree3Right() {
    SetNode<int>* root = new SetNode<int>(30, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(20, 1, root, 0, 0);
    root->left = left;
    SetNode<int>* right = new SetNode<int>(40, 1, root, 0, 0);
    root->right = right;
    SetNode<int>* rl = new SetNode<int>(35, 0, right, 0, 0);
    right->left = rl;
    SetNode<int>* rr = new SetNode<int>(45, 0, right, 0, 0);
    right->right = rr;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the sibling is black and has a red child
// and a pre rotation must be performed
BCTreeSet<int> createDeletionTree4Left() {
    SetNode<int>* root = new SetNode<int>(30, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(20, 1, root, 0, 0);
    root->left = left;
    SetNode<int>* right = new SetNode<int>(40, 1, root, 0, 0);
    root->right = right;
    SetNode<int>* lr = new SetNode<int>(25, 0, left, 0, 0);
    left->right = lr;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the sibling is black and has a red child
// and a pre rotation must be performed
BCTreeSet<int> createDeletionTree4Right() {
    SetNode<int>* root = new SetNode<int>(30, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(20, 1, root, 0, 0);
    root->left = left;
    SetNode<int>* right = new SetNode<int>(40, 1, root, 0, 0);
    root->right = right;
    SetNode<int>* rl = new SetNode<int>(35, 0, right, 0, 0);
    right->left = rl;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the sibling is black and its children
// are black and the parent is red
BCTreeSet<int> createDeletionTree5() {
    SetNode<int>* root = new SetNode<int>(50, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(25, 0, root, 0, 0);
    root->left = left;
    SetNode<int>* right = new SetNode<int>(75, 1, root, 0, 0);
    root->right = right;
    SetNode<int>* ll = new SetNode<int>(20, 1, left, 0, 0);
    left->left = ll;
    SetNode<int>* lr = new SetNode<int>(30, 1, left, 0, 0);
    left->right = lr;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where where the sibling is black and its children
// are black and the parent is black
BCTreeSet<int> createDeletionTree6() {
    SetNode<int>* root = new SetNode<int>(100, 1, 0, 0, 0);
    SetNode<int>* right = new SetNode<int>(150, 1, root, 0, 0);
    root->right = right;
    SetNode<int>* rl = new SetNode<int>(125, 1, right, 0, 0);
    right->left = rl;
    SetNode<int>* rr = new SetNode<int>(175, 1, right, 0, 0);
    right->right = rr;
    SetNode<int>* left = new SetNode<int>(50, 0, root, 0, 0);
    root->left = left;
    SetNode<int>* ll = new SetNode<int>(25, 1, left, 0, 0);
    left->left = ll;
    SetNode<int>* lll = new SetNode<int>(24, 1, ll, 0, 0);
    ll->left = lll;
    SetNode<int>* llr = new SetNode<int>(26, 1, ll, 0, 0);
    ll->right = llr;
    SetNode<int>* lr = new SetNode<int>(75, 1, left, 0, 0);
    left->right = lr;
    SetNode<int>* lrl = new SetNode<int>(74, 1, lr, 0, 0);
    lr->left = lrl;
    SetNode<int>* lrr = new SetNode<int>(76, 1, lr, 0, 0);
    lr->right = lrr;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the sibling is red
BCTreeSet<int> createDeletionTree7Left() {
    SetNode<int>* root = new SetNode<int>(20, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(10, 0, root, 0, 0);
    root->left = left;
    SetNode<int>* right = new SetNode<int>(30, 1, root, 0, 0);
    root->right = right;
    SetNode<int>* ll = new SetNode<int>(5, 1, left, 0, 0);
    left->left = ll;
    SetNode<int>* lr = new SetNode<int>(15, 1, left, 0, 0);
    left->right = lr;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the sibling is red
BCTreeSet<int> createDeletionTree7Right() {
    SetNode<int>* root = new SetNode<int>(20, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(10, 1, root, 0, 0);
    root->left = left;
    SetNode<int>* right = new SetNode<int>(30, 0, root, 0, 0);
    root->right = right;
    SetNode<int>* rl = new SetNode<int>(25, 1, right, 0, 0);
    right->left = rl;
    SetNode<int>* rr = new SetNode<int>(35, 1, right, 0, 0);
    right->right = rr;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}
