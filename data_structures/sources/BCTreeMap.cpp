#include "../headers/BCTreeMap.h"
#include "../headers/MapNode.h"
#include <vector>
#include <deque>
#include <tuple>


// PUBLIC METHODS

// constructor
template<typename T1, typename T2>
BCTreeMap<T1, T2>::BCTreeMap() {
    root = 0;
    s = 0;
}

// method to add a key-value pair to the map
// O(log(n)) time
// O(1) space
template<typename T1, typename T2>
void BCTreeMap<T1, T2>::put(T1 key, T2 value) {
    // if this is the first node to be inserted
    if (!root) {
        root = new MapNode<T1, T2>(key, value, 1, 0, 0, 0);
        s = 1;
        return;
    }
    // perform normal bst insertion
    MapNode<T1, T2>* curr = root;
    while (1) {
        // if this key is already present in the map, update its value and return
        if (key == curr->key) {
            curr->value = value;
            return;
        }
        // if the key is less than the key of this node, move left
        if (key < curr->key) {
            if (curr->left) curr = curr->left;
            else {
                curr->left = new MapNode<T1, T2>(key, value, 0, curr, 0, 0);
                curr = curr->left;
                s++;
                break;
            }
        }
        // if the key is greater than the key of this node, move right
        else {
            if (curr->right) curr = curr->right;
            else {
                curr->right = new MapNode<T1, T2>(key, value, 0, curr, 0, 0);
                curr = curr->right;
                s++;
                break;
            }
        }
    }
    // restore the red black properties of the tree
    insertRestore(curr);
}

// method to remove a key value pair from the map
// O(log(n)) time
// O(1) space
template<typename T1, typename T2>
void BCTreeMap<T1, T2>::remove(T1 key) {
    if (!root) return;
    // perform normal bst deletion 
} 

// method to check if the map contains a certain key
// O(1) time
// O(1) space
template<typename T1, typename T2>
bool BCTreeMap<T1, T2>::containsKey(T1 key) {
    MapNode<T1, T2>* curr = root;
    while (curr) {
        if (key == curr->key) return true;
        else if (key < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    return false;
}

// method to check if the map is empty
// O(1) time
// O(1) space
template<typename T1, typename T2>
bool BCTreeMap<T1, T2>::isEmpty() {
    return !root;
}

// method to check the number of key-value pairs in the map
// O(1) time
// O(1) space
template<typename T1, typename T2>
long long BCTreeMap<T1, T2>::size() {
    return s;
}

// method to perform an inorder traversal and return a vector of all the nodes in sorted order
// O(n) time
// O(n) space
template<typename T1, typename T2>
std::vector<MapNode<T1, T2>*> BCTreeMap<T1, T2>::inorder() {
    if (!root) return {};
    std::vector<MapNode<T1, T2>*> arr;
    arr.reserve(s);
    inorderHelp(root, arr);
    return arr;
}

// method to perform a level order traversal and return a vector consisting of vectors of all the levels
// O(n) time
// O(n) space
template<typename T1, typename T2>
std::vector<std::vector<MapNode<T1, T2>*>> BCTreeMap<T1, T2>::levelOrder() {
    if (!root) return {};
    std::vector<std::vector<MapNode<T1, T2>*>> arr;
    arr.reserve(s);
    std::deque<std::tuple<MapNode<T1, T2>*, long long>> d;
    // initialize the deque with only the root node
    d.push_back(std::make_tuple(root, 0));
    while (d.size()) {
        std::tuple<MapNode<T1, T2>*, long long> curr = d.front();
        d.pop_front();
        // add this node's info to the array corresponding to this node's level
        if (arr.size() <= std::get<1>(curr)) arr.push_back({});
        arr[std::get<1>(curr)].push_back(std::get<0>(curr));
         // add the child nodes to the deque if they exist
        if (std::get<0>(curr)->left) d.push_back(std::make_tuple(std::get<0>(curr)->left, std::get<1>(curr)+1));
        if (std::get<0>(curr)->right) d.push_back(std::make_tuple(std::get<0>(curr)->right, std::get<1>(curr)+1));
    }
    return arr;
}


// PRIVATE HELPER METHODS

// helper method for restoring the red black properties upon insertion
// O(log(n)) time (because it is recursive, a single execution of this function only takes O(1) time)
// O(1) space
template<typename T1, typename T2> 
void BCTreeMap<T1, T2>::insertRestore(MapNode<T1, T2>* curr) {
    // the parent of the current node
    MapNode<T1, T2>* parent = curr->parent;
    // if the current node is the root
    if (!parent) {
        // set the root to black
        curr->black = 1; 
        return;
    }
    // if the parent is black, nothing needs to be done
    else if (parent->black) return;

    // the grandparent of the current node
    MapNode<T1, T2>* grand = parent->parent;
    // if there is no grandparent node then this node is a child of the root
    if (!grand) {
        // ensure that the root is black
        parent->black = 1;
        return;
    }

    // whether this node's parent is the left child of the grandparent
    bool left = parent->key < grand->key;

    if (left) {
        // if there is an uncle node and it is red
        if (grand->right && !grand->right->black) {
            recolor(grand, 0);
            insertRestore(grand);
        }
        // the uncle node must be either null or black
        else {
            // perform a pre rotation if one is needed
            if (parent->key < curr->key) parent = rotateLeft(curr, parent);
            // rotate and recolor
            rotateRight(parent, grand);
            recolor(parent, 1);
        }
    } else {
        // if there is an uncle node and it is red
        if (grand->left && !grand->left->black) {
            recolor(grand, 0);
            insertRestore(grand);
        }
        // the uncle node must be either null or black
        else {
            // performe a pre rotation if one is needed
            if (curr->key < parent->key) parent = rotateRight(curr, parent);
            // rotate and recolor
            rotateLeft(parent, grand);
            recolor(parent, 1);
        }
    }
}

// helper method to perform a left rotation
// O(1) time
// O(1) space
template<typename T1, typename T2> 
MapNode<T1, T2>* BCTreeMap<T1, T2>::rotateLeft(MapNode<T1, T2>* curr, MapNode<T1, T2>* parent) {
    // set the parent node as the parent of the current node's left child if it exists
    if (curr->left) curr->left->parent = parent;
    // if the parent is not the root
    if (parent->parent) {
        // if the parent is the left child of its parent
        if (parent->key < parent->parent->key) parent->parent->left = curr;
        // if the parent is the right child of its parent
        else parent->parent->right = curr;
    } 
    // if the parent is the root set the root to the current node
    else root = curr;
    // set the current node's parent as the parent of the parent node
    curr->parent = parent->parent;
    // set the parent's parent as the current node
    parent->parent = curr;
    // set the right child of the parent to the left child of the current node
    parent->right = curr->left;
    // set the left child of the current node to the parent node
    curr->left = parent;
    // return a pointer to the current node
    return curr;
}

// helper method to perform a right rotation
// O(1) time 
// O(1) space
template<typename T1, typename T2> 
MapNode<T1, T2>* BCTreeMap<T1, T2>::rotateRight(MapNode<T1, T2>* curr, MapNode<T1, T2>* parent) {
    // set the parent node as the parent of the current node's right child if it exists
    if (curr->right) curr->right->parent = parent;
    // if the parent node is not the root
    if (parent->parent) {
        // if the parent is the left child of its parent node
        if (parent->key < parent->parent->key) parent->parent->left = curr;
        // if the parent is the right child of its parent node
        else parent->parent->right = curr;
    }
    // if the parent node is the root set the root to the current node
    else root = curr;
    // set the current node's parent as the parent of the current node
    curr->parent = parent->parent;
    // set the parent's parent as the current node
    parent->parent = curr;
    // set the right child of the parent to the left child of the current node
    parent->left = curr->right;
    // set the right child of the current node to the parent node
    curr->right = parent;
    // return a pointer to the current node
    return curr;
}

// helper method to set the current node to the specified color and its children nodes to the other color
// O(1) time
// O(1) space
template<typename T1, typename T2>
void BCTreeMap<T1, T2>::recolor(MapNode<T1, T2>* curr, bool color) {
    curr->black = color;
    if (curr->left) curr->left->black = !color;
    if (curr->right) curr->right->black = !color;
}



// helper method for the inorder traversal
// O(1) time
// O(1) space
template<typename T1, typename T2>
void inorderHelp(MapNode<T1, T2>* curr, std::vector<MapNode<T1, T2>*>& arr) {
    if (curr->left) inorderHelp(curr->left, arr);
    arr.push_back(curr);
    if (curr->right) inorderHelp(curr->right, arr);
}
