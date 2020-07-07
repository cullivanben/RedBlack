#include "../headers/BCTreeSet.h"
#include "../headers/SetNode.h"
#include <vector>
#include <deque>
#include <tuple>


// PUBLIC METHODS

// constructor
template<typename T> 
BCTreeSet<T>::BCTreeSet() {
    root = 0;
    s = 0;
}

// method to add a value to the set
// O(log(n)) time
// O(1) space
template<typename T> 
void BCTreeSet<T>::add(T value) {
    // the case where this is the first node to be inserted
    if (!root) {
        root = new SetNode<T>(value, 1, 0, 0, 0);
        s = 1;
        return;
    }
    // perform normal bst insertion
    SetNode<T>* curr = root;
    while (1) {
        // if this value is already in the set, do nothing and return
        if (value == curr->value) return;
        // if the value is less than the value of this node, move left
        if (value < curr->value) {
            if (curr->left) curr = curr->left;
            else {
                curr->left = new SetNode<T>(value, 0, curr, 0, 0);
                curr = curr->left;
                s++;
                break;
            }
        } 
        // if the value is greater than the value of this node, move right
        else {
            if (curr->right) curr = curr->right;
            else {
                curr->right = new SetNode<T>(value, 0, curr, 0, 0);
                curr = curr->right;
                s++;
                break;
            }
        }
    }
    // restore the red black properties of the tree
    insertRestore(curr);
}

// method to remove a value from the set
// O(log(n)) time
// O(1) space
template<typename T> 
void BCTreeSet<T>::remove(T value, SetNode<T>* curr = root) {
    if (!root) return;
    // perform normal BST deletion
    while (curr) {
        if (value == curr->value) {
            // if this node has two children
            if (curr->left && curr->right) {
                curr->value = successor(curr);
                remove(curr->value, curr->right);
            }
            // if this node has only a left child
            else if (curr->left) deleteNode(curr, curr->left);
            // if this node has only a right child or has no children
            else deleteNode(curr, curr->right);
            return;
        } 
        // if the value is smaller than the current value, move left
        else if (value < curr->value) curr = curr->left;
        // if the value is larger than the current value, move right
        else curr = curr->right;
    }
}

// method to check if the set contains a value
// O(log(n)) time
// O(1) space
template<typename T>
bool BCTreeSet<T>::contains(T value) {
    SetNode<T>* curr = root;
    while (curr) {
        if (value == curr->value) return true;
        else if (value < curr->value) curr = curr->left;
        else curr = curr->right;
    }
    return false;
}

// method to check if the set is empty
// O(1) time
// O(1) space
template<typename T> 
bool BCTreeSet<T>::isEmpty() {
    return !root;
}

// method to check the size of the set
// O(1) time
// O(1) space
template<typename T>
long long BCTreeSet<T>::size() {
    return s;
}

// method to perform an inorder traversal and return a vector of all the nodes in sorted order
// O(n) time
// O(n) space
template<typename T>
std::vector<SetNode<T>*> BCTreeSet<T>::inorder() {
    if (!root) return {};
    std::vector<std::string> arr;
    arr.reserve(s);
    inorderHelp(root, arr);
    return arr;
}

// method to perform a level order traversal and return a vector consisting of vectors of all the levels
// O(n) time
// O(n) space
template<typename T>
std::vector<std::vector<SetNode<T>*>> BCTreeSet<T>::levelOrder() {
    if (!root) return {};
    std::vector<std::vector<SetNode<T>*>> arr;
    std::deque<std::tuple<SetNode<T>*, long long>> d;
    // initialize the deque with only the root node
    d.push_back(std::make_tuple(root, 0));
    while (d.size()) {
        std::tuple<SetNode<T>*, long long> curr = d.front();
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
// O(1) time
// O(1) space
template<typename T>
void BCTreeSet<T>::insertRestore(SetNode<T>* curr) {
    // the parent node of the current node
    SetNode<T>* parent = curr->parent;
    // if the current node is the root
    if (!parent) {
        // set the root to black
        curr->black = 1;
        return;
    }
    // if the parent is black nothing needs to be done
    else if (parent->black) return;

    // the grandparent node of the current node
    SetNode<T>* grand = parent->parent;
    // if there is no grandparent node then this node is a child of the root
    if (!grand) {
        // ensure that the root is black
        parent->black = 1;
        return;
    }
    // whether this node's parent is the left child of the grandparent
    bool left = parent->value < grand->value;

    if (left) {
        // if there is an uncle node and it is red
        if (grand->right && !grand->right->black) {
            insertRecolor(grand, 0);
            insertRestore(grand);
        }
        // the uncle node must be either null or black
        else {
            // perform a pre rotation if one is needed
            if (parent->value < curr->value) parent = rotateLeft(curr, parent);
            // rotate and recolor
            rotateRight(parent, grand);
            insertRecolor(parent, 1);
        }
    } else {
        // if there is an uncle node and it is red
        if (grand->left && !grand->left->black) {
            insertRecolor(grand, 0);
            insertRestore(grand);
        }
        // the uncle node must be either null or black
        else {
            // perform a pre rotation if one is needed
            if (curr->value < parent->value) parent = rotateRight(curr, parent);
            // rotate and recolor
            rotateLeft(parent, grand);
            insertRecolor(parent, 1);
        }
    }
}

// helper method to perform a left rotation
// O(1) time
// O(1) space
template<typename T>
SetNode<T>* BCTreeSet<T>::rotateLeft(SetNode<T>* curr, SetNode<T>* parent) {
    // set the parent node as the parent of the current node's left child if it exists
    if (curr->left) curr->left->parent = parent;
    // if the parent is not the root
    if (parent->parent) {
        // if the parent is the left child of its parent
        if (parent->value < parent->parent->value) parent->parent->left = curr;
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
template<typename T> 
SetNode<T>* BCTreeSet<T>::rotateRight(SetNode<T>* curr, SetNode<T>* parent) {
    // set the parent node as the parent of the current node's right child if it exists
    if (curr->right) curr->right->parent = parent;
    // if the parent node is not the root
    if (parent->parent) {
        // if the parent is the left child of its parent node
        if (parent->value < parent->parent->value) parent->parent->left = curr;
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
template<typename T>
void BCTreeSet<T>::insertRecolor(SetNode<T>* curr, bool color) {
    curr->black = color;
    if (curr->left) curr->left->black = !color;
    if (curr->right) curr->right->black = !color;
}

// helper method to find the successor of the current node
// O(log(n)) time
// O(1) space
template<typename T>
T BCTreeSet<T>::successor(SetNode<T>* curr) {
    curr = curr->right;
    while (curr->left) curr = curr->left;
    return curr->value;
}

// deletes a node from the tree
// O(log(n)) time 
// O(1) space
template<typename T>
void BCTreeSet<T>::deleteNode(SetNode<T>* curr, SetNode<T>* child) {
    // if this node is red or its child is red
    if (!curr->black || (child && !child->black)) redDelete(curr, child);
    // this node and its child are both black
    else blackDelete(curr, child);
    // decrease the size
    s--;
}

// deletes a node in the case that it or its child is red
// O(1) time
// O(1) space
template<typename T>
void BCTreeSet<T>::redDelete(SetNode<T>* curr, SetNode<T>* child) {
    // the parent of the node that is being deleted
    SetNode<T>* parent = curr->parent;
    // if the node that is being deleted has a child
    if (child) {
        // if the node being deleted is not the root
        if (parent) {
            // if this node is the left child of its parent
            if (curr->value < parent->value) parent->left = child;
            // if this node is the right child of its parent
            else parent->right = child;
            // set the parent of the child to the parent of the node that is being deleted
            child->parent = parent
        }
        // the node that is being deleted is the root
        else {
            // set the parent of the child to null
            child->parent = 0;
            // set the child node as the root
            root = child;
        }
        // set the child node's color to black
        child->black = 1;
    } 
    // there is no child
    else {
        // since this node is red there must be a parent
        // however, perform this check for safety
        if (parent) {
            // remove the current node as a child from its parent
            if (curr->value < parent->value) parent->left = 0;
            else parent->right = 0;
        } else root = 0;
    }
    // delete the current node
    delete curr;
}

// deletes a node in the case that it and its child are black
template<typename T> 
void BCTreeSet<T>::blackDelete(SetNode<T>* curr, SetNode<T>* child) {
    // the parent of the node that is being deleted
    SetNode<T>* parent = curr->parent;
    // whether the current node is the left child of its parent
    bool left = curr->value < parent->value;
    // if the node that is being deleted is the root
    if (!parent) {
        // set the child as the root
        root = child;
        if (child) child->parent = 0;
        // delete the current node
        delete curr;
        return;
    }
    // splice out the current node
    if (left) parent->left = child;
    else parent->right = child;
    if (child) child->parent = parent;
    delete curr;
    // find the sibling
    SetNode<T>* sibling = left ? parent->right:parent->left;
    // fix the tree
    fixTree(child, parent, sibling, left);
}

// parameters are supplied in case curr is null
template<typename T>
void fixTree(SetNode<T>* curr, SetNode<T>* parent, SetNode<T>* sibling, bool left) {
    // if the current node is the root node, make it black and return
    if (curr && !curr->parent) {
        root = curr;
        curr->black = 1;
        return;
    }
    // if the current node is not null, the parameter values are not correct and they must be reset
    if (curr) {
        parent = curr->parent;
        left = curr->value < parent->value;
        if (left) sibling = parent->right;
        else sibling = parent->left;
    }
    // the sibling will not be null because that would mean there was already a violation of 
    // the black depth property before this remove operation was performed and that will not happen
    // precautionary check anyway
    if (!sibling) return;
    // the sibling is black
    if (sibling->black) {
        // if one of the sibling's children is red
        if ((sibling->left && !sibling->left->black) || (sibling->right && !sibling->right->black)) deleteRotate(parent, sibling);
        // both of the sibling's children are black
        else deleteRecolor(parent, sibling);
    } 
    // the sibling is red
    else deleteAdjust(curr, sibling, left);
}

template<typename T>
void BCTreeSet<T>::deleteRotate(SetNode<T>* parent, SetNode<T>* sibling) {
    // the sibling is the left child of the parent
    if (sibling->value < parent->value) {
        // if the red node is the right child of the sibling, perform a pre rotation
        if (sibling->right && !sibling->right->black && (!sibling->left || sibling->left->black)) {
            sibling->right->black = 1;
            sibling = rotateLeft(sibling->right, sibling);
        }
        // make the left child of the sibling black
        if (sibling->left) sibling->left->black = 1;
        // rotate right
        rotateRight(sibling, parent);
    }
    // the sibling is the right child of the parent
    else {
        // if the red node is the left child of the sibling, perform a pre rotation
        if (sibling->left && !sibling->left->black && (!sibling->right || sibling->right->black)) {
            sibling->left->black = 1;
            sibling = rotateRight(sibling->left, sibling);
        }
        // make the right child of the sibling black
        if (sibling->right) sibling->right->black = 1;
        // rotate left
        rotateLeft(sibling, parent);
    }
}

template<typename T> 
void BCTreeSet<T>::deleteRecolor(SetNode<T>* parent, SetNode<T>* sibling) {
    // make the sibling red
    sibling->black = 0;
    // if the parent is red, make it black
    if (!parent->black) parent->black = 1;
    // recurse on the parent
    // when we recurse, as long as the parent is not the root, the sibling will not be null
    // this is because if the sibling were null in this case the black depth property would be violated
    else fixTree(parent, 0, 0, 0);
}

template<typename T> 
void BCTreeSet<T>::deleteAdjust(SetNode<T>* curr, SetNode<T>* sibling, bool left) {
    // recolor
    sibling->black = 1;
    sibling->parent->black = 0;
    // if the current node is the left child of its parent
    if (left) {
        // rotate left
        rotateLeft(sibling, sibling->parent);
        // fix the tree
        fixTree(curr, parent, parent->right, left);
    }
    // if the current node is the right child of its parent
    else {
        // rotate right
        rotateRight(sibling, sibling->parent);
        // fix the tree
        fixTree(curr, parent, parent->left, left);
    }
}

// helper method for the inorder traversal
// O(1) time
// O(1) space
template<typename T> 
void BCTreeSet<T>::inorderHelp(SetNode<T>* curr, std::vector<SetNode<T>*>& arr) {
    if (curr->left) inorderHelp(curr->left, arr);
    arr.push_back(curr);
    if (curr->right) inorderHelp(curr->right, arr);
}
