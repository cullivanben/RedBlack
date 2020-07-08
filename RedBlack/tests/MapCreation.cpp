#include "../headers/BCTreeMap.h"
#include "../headers/MapNode.h"
#include <string>
#include <iostream>

using namespace std;


// INVALID TREES

// creates a tree that is invalid because it has a red root
BCTreeMap<int, string> createInvalidTree1() {
    MapNode<int, string>* root = new MapNode<int, string>(1, "", 0, 0, 0, 0);
    // create the map
    BCTreeMap<int, string> invalid;
    invalid.setRootForTest(root);
    return invalid;
}

// creates a tree that is invalid because it has consecutive red nodes
BCTreeMap<int, string> createInvalidTree2() {
    MapNode<int, string>* root = new MapNode<int, string>(10, "", 1, 0, 0, 0);
    MapNode<int, string>* six = new MapNode<int, string>(6, "", 1, root, 0, 0);
    root->left = six;
    MapNode<int, string>* five = new MapNode<int, string>(5, "", 0, six, 0, 0);
    six->left = five;
    MapNode<int, string>* twelve = new MapNode<int, string>(12, "", 1, root, 0, 0);
    root->right = twelve;
    MapNode<int, string>* eleven = new MapNode<int, string>(11, "", 0, twelve, 0, 0);
    twelve->left = eleven;
    MapNode<int, string>* thirteen = new MapNode<int, string>(13, "", 0, twelve, 0, 0);
    twelve->right = thirteen;
    MapNode<int, string>* fourteen = new MapNode<int, string>(14, "", 0, thirteen, 0, 0);
    thirteen->right = fourteen;
    // create the map
    BCTreeMap<int, string> invalid;
    invalid.setRootForTest(root);
    return invalid;
}

// creates a tree that is invalid beause it has unequal black depths
BCTreeMap<int, string> createInvalidTree3() {
    MapNode<int, string>* root = new MapNode<int, string>(10, "", 1, 0, 0, 0);
    MapNode<int, string>* six = new MapNode<int, string>(6, "", 1, root, 0, 0);
    root->left = six;
    MapNode<int, string>* five = new MapNode<int, string>(5, "", 1, six, 0, 0);
    six->left = five;
    MapNode<int, string>* twelve = new MapNode<int, string>(12, "", 0, root, 0, 0);
    root->right = twelve;
    MapNode<int, string>* eleven = new MapNode<int, string>(11, "", 1, twelve, 0, 0);
    twelve->left = eleven;
    MapNode<int, string>* thirteen = new MapNode<int, string>(13, "", 1, twelve, 0, 0);
    twelve->right = thirteen;
    MapNode<int, string>* fourteen = new MapNode<int, string>(14, "", 0, thirteen, 0, 0);
    thirteen->right = fourteen;
    // create the map
    BCTreeMap<int, string> invalid;
    invalid.setRootForTest(root);
    return invalid;
}

// creates a tree that is invalid because it is not a valid BST
BCTreeMap<int, string> createInvalidTree4() {
    MapNode<int, string>* root = new MapNode<int, string>(10, "", 1, 0, 0, 0);
    MapNode<int, string>* six = new MapNode<int, string>(6, "", 1, root, 0, 0);
    root->left = six;
    MapNode<int, string>* five = new MapNode<int, string>(5, "", 0, six, 0, 0);
    six->left = five;
    MapNode<int, string>* twelve = new MapNode<int, string>(12, "", 1, root, 0, 0);
    root->right = twelve;
    MapNode<int, string>* ten = new MapNode<int, string>(10, "", 0, twelve, 0, 0);
    twelve->left = ten;
    MapNode<int, string>* thirteen = new MapNode<int, string>(13, "", 0, twelve, 0, 0);
    twelve->right = thirteen;
    // create the map
    BCTreeMap<int, string> invalid;
    invalid.setRootForTest(root);
    return invalid;
}


// INSERTION TREES

// creates a tree that will have a red node inserted to a black parent
BCTreeMap<int, string> createInsertionTree1() {
    MapNode<int, string>* root = new MapNode<int, string>(0, "", 1, 0, 0, 0);
    // create the map
    BCTreeMap<int, string> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree that will have a node inserted to a parent and
// uncle that are both red
BCTreeMap<int, string> createInsertionTree2() {
    MapNode<int, string>* root = new MapNode<int, string>(0, "", 1, 0, 0, 0);
    MapNode<int, string>* left = new MapNode<int, string>(-2, "", 1, root, 0, 0);
    root->left = left;
    MapNode<int, string>* right = new MapNode<int, string>(2, "", 0, root, 0, 0);
    root->right = right;
    MapNode<int, string>* rl = new MapNode<int, string>(1, "", 1, right, 0, 0);
    right->left = rl;
    MapNode<int, string>* rr = new MapNode<int, string>(6, "", 1, right, 0, 0);
    right->right = rr;
    MapNode<int, string>* rrl = new MapNode<int, string>(5, "", 0, rr, 0, 0);
    rr->left = rrl;
    MapNode<int, string>* rrr = new MapNode<int, string>(7, "", 0, rr, 0, 0);
    rr->right = rrr;
    // create the map
    BCTreeMap<int, string> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the parent is red and the uncle is black
BCTreeMap<int, string> createInsertionTree3() {
    MapNode<int, string>* root = new MapNode<int, string>(0, "", 1, 0, 0, 0);
    MapNode<int, string>* left = new MapNode<int, string>(-10, "", 0, root, 0, 0);
    root->left = left;
    // create the map
    BCTreeMap<int, string> tree;
    tree.setRootForTest(root);
    return tree;
}
