#include "../headers/BCTreeMap.h"

#include <deque>
#include <tuple>
#include <vector>

// PUBLIC METHODS

// constructor
template <typename T1, typename T2>
BCTreeMap<T1, T2>::BCTreeMap() {
    root = 0;
    s = 0;
}

// method to add a key-value pair to the map
// O(log(n)) time
// O(log(n)) space
template <typename T1, typename T2>
void BCTreeMap<T1, T2>::put(T1 key, T2 value) {
    // if this is the first node to be inserted
    if (!root) {
        root = new MapNode<T1, T2>(key, value, 1, 0, 0, 0);
        s = 1;
        return;
    }
    // perform normal bst insertion
    MapNode<T1, T2> *curr = root;
    while (1) {
        // if this key is already present in the map, update its value and
        // return
        if (key == curr->key) {
            curr->value = value;
            return;
        }
        // if the key is less than the key of this node, move left
        if (key < curr->key) {
            if (curr->left)
                curr = curr->left;
            else {
                curr->left = new MapNode<T1, T2>(key, value, 0, curr, 0, 0);
                curr = curr->left;
                s++;
                break;
            }
        }
        // if the key is greater than the key of this node, move right
        else {
            if (curr->right)
                curr = curr->right;
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
template <typename T1, typename T2>
void BCTreeMap<T1, T2>::remove(T1 key, MapNode<T1, T2> *curr) {
    if (!root) return;
    if (!curr) curr = root;
    // perform normal bst deletion
    while (curr) {
        if (key == curr->key) {
            // if this node has two children
            if (curr->left && curr->right) {
                std::tuple<T1, T2> success = successor(curr);
                curr->key = std::get<0>(success);
                curr->value = std::get<1>(success);
                remove(curr->key, curr->right);
            }
            // if this node has only a left child
            else if (curr->left)
                deleteNode(curr, curr->left);
            // if this node has only a right child or has no children
            else
                deleteNode(curr, curr->right);
            return;
        }
        // if the key is smaller than the current key, move left
        else if (key < curr->key)
            curr = curr->left;
        // if the key is larger than the current key, move right
        else
            curr = curr->right;
    }
}

// method to check if the map contains a certain key
// O(log(n)) time
// O(1) space
template <typename T1, typename T2>
bool BCTreeMap<T1, T2>::containsKey(T1 key) {
    MapNode<T1, T2> *curr = root;
    while (curr) {
        if (key == curr->key)
            return true;
        else if (key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return false;
}

// method to check if the map is empty
// O(1) time
// O(1) space
template <typename T1, typename T2>
bool BCTreeMap<T1, T2>::isEmpty() {
    return !root;
}

// method to check the number of key-value pairs in the map
// O(1) time
// O(1) space
template <typename T1, typename T2>
long long BCTreeMap<T1, T2>::size() {
    return s;
}

// method to perform a level order traversal and return a vector consisting of
// vectors of all the levels O(n) time O(n) space
template <typename T1, typename T2>
std::vector<std::vector<MapNode<T1, T2> *>> BCTreeMap<T1, T2>::levelOrder() {
    if (!root) return {};
    std::vector<std::vector<MapNode<T1, T2> *>> arr;
    arr.reserve(s);
    std::deque<std::tuple<MapNode<T1, T2> *, long long>> d;
    // initialize the deque with only the root node
    d.push_back(std::make_tuple(root, 0));
    while (d.size()) {
        std::tuple<MapNode<T1, T2> *, long long> curr = d.front();
        d.pop_front();
        // add this node's info to the array corresponding to this node's level
        if (arr.size() <= std::get<1>(curr)) arr.push_back({});
        arr[std::get<1>(curr)].push_back(std::get<0>(curr));
        // add the child nodes to the deque if they exist
        if (std::get<0>(curr)->left)
            d.push_back(std::make_tuple(std::get<0>(curr)->left,
                                        std::get<1>(curr) + 1));
        if (std::get<0>(curr)->right)
            d.push_back(std::make_tuple(std::get<0>(curr)->right,
                                        std::get<1>(curr) + 1));
    }
    return arr;
}

// checks that the tree satisfies all of the red black tree properties
// O(n) time
// O(log(n)) space
template <typename T1, typename T2>
bool BCTreeMap<T1, T2>::isValid() {
    // property one is that all nodes must be either red or black
    // in this implementation of a red black true that will always be true

    // if there are no nodes, the tree is vaid
    if (!root) return 1;

    // property two is that the root must be black
    // if the root is red, the tree is not valid
    if (!root->black) return 0;

    // property three is that all children of leaf nodes are black
    // this does not need to be checked because all the children of leaf
    // are NULL and thus black and if all NULL nodes are black this does
    // not affect whether the black depths of every leaf are equal

    // property four is that if a node is red, then both its children are black
    // property five is that every simple path from a node to a descendant leaf
    // contains the same number of black nodes

    // perform a postorder traversal to check properties four and five
    // perform an inorder traversal to make sure that the tree is a valid BST
    return validHelp(root) != -1 && bst();
}

// sets the root so that invalid trees can be tested
// O(1) time
// O(1) space
template <typename T1, typename T2>
void BCTreeMap<T1, T2>::setRootForTest(MapNode<T1, T2> *node) {
    root = node;
}

// PRIVATE HELPER METHODS

// restores the red black properties upon insertion
// O(log(n)) time (because it is recursive, a single execution of this function
// only takes O(1) time) O(log(n)) space
template <typename T1, typename T2>
void BCTreeMap<T1, T2>::insertRestore(MapNode<T1, T2> *curr) {
    // the parent of the current node
    MapNode<T1, T2> *parent = curr->parent;
    // if the current node is the root
    if (!parent) {
        // set the root to black
        root = curr;
        curr->black = 1;
        return;
    }
    // if the parent is black, nothing needs to be done
    else if (parent->black)
        return;

    // the grandparent of the current node
    MapNode<T1, T2> *grand = parent->parent;
    // if there is no grandparent node then this node is a child of the root
    if (!grand) {
        // ensure that the root is black
        root = parent;
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

// performs a left rotation
// O(1) time
// O(1) space
template <typename T1, typename T2>
MapNode<T1, T2> *BCTreeMap<T1, T2>::rotateLeft(MapNode<T1, T2> *curr,
                                               MapNode<T1, T2> *parent) {
    // set the parent node as the parent of the current node's left child if it
    // exists
    if (curr->left) curr->left->parent = parent;
    // if the parent is not the root
    if (parent->parent) {
        // if the parent is the left child of its parent
        if (parent->key < parent->parent->key) parent->parent->left = curr;
        // if the parent is the right child of its parent
        else
            parent->parent->right = curr;
    }
    // if the parent is the root set the root to the current node
    else
        root = curr;
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

// performs a right rotation
// O(1) time
// O(1) space
template <typename T1, typename T2>
MapNode<T1, T2> *BCTreeMap<T1, T2>::rotateRight(MapNode<T1, T2> *curr,
                                                MapNode<T1, T2> *parent) {
    // set the parent node as the parent of the current node's right child if it
    // exists
    if (curr->right) curr->right->parent = parent;
    // if the parent node is not the root
    if (parent->parent) {
        // if the parent is the left child of its parent node
        if (parent->key < parent->parent->key) parent->parent->left = curr;
        // if the parent is the right child of its parent node
        else
            parent->parent->right = curr;
    }
    // if the parent node is the root set the root to the current node
    else
        root = curr;
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

// sets the current node to the specified color and its children nodes to the
// other color O(1) time O(1) space
template <typename T1, typename T2>
void BCTreeMap<T1, T2>::recolor(MapNode<T1, T2> *curr, bool color) {
    curr->black = color;
    if (curr->left) curr->left->black = !color;
    if (curr->right) curr->right->black = !color;
}

// finds the successor of a node
// O(log(n)) time
// O(1) space
template <typename T1, typename T2>
std::tuple<T1, T2> BCTreeMap<T1, T2>::successor(MapNode<T1, T2> *curr) {
    curr = curr->right;
    while (curr->left) curr = curr->left;
    return std::make_tuple(curr->key, curr->value);
}

// deletes a node from the tree
// O(log(n)) time
// O(1) space
template <typename T1, typename T2>
void BCTreeMap<T1, T2>::deleteNode(MapNode<T1, T2> *curr,
                                   MapNode<T1, T2> *child) {
    // if this node is red or its child is red
    if (!curr->black || (child && !child->black)) redDelete(curr, child);
    // this node and its child are both black
    else
        blackDelete(curr, child);
    // decrease te size
    s--;
}

// deletes a node in the case that it or its child is red
// O(1) time
// O(1) space
template <typename T1, typename T2>
void BCTreeMap<T1, T2>::redDelete(MapNode<T1, T2> *curr,
                                  MapNode<T1, T2> *child) {
    // the parent of the node that is being deleted
    MapNode<T1, T2> *parent = curr->parent;
    // if the node that is being deleted has a child
    if (child) {
        // if the node that is being deleted is not the root
        if (parent) {
            // if this node is the left child of its parent
            if (curr->key < parent->key) parent->left = child;
            // if this node is the right child of its parent
            else
                parent->right = child;
            // set the parent of the child to the parent of the node that is
            // being deleted
            child->parent = parent;
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
            if (curr->key < parent->key)
                parent->left = 0;
            else
                parent->right = 0;
        }
        // the node that is being deleted is the root
        else
            root = 0;
    }
    // delete the current node
    delete curr;
}

// deletes a node in the case that it and its children are black
// O(log(n)) time
// O(1) space
template <typename T1, typename T2>
void BCTreeMap<T1, T2>::blackDelete(MapNode<T1, T2> *curr,
                                    MapNode<T1, T2> *child) {
    // the parent of the node that is being deleted
    MapNode<T1, T2> *parent = curr->parent;
    // if the node that is being deleted is the root
    if (!parent) {
        // set the child as the root
        root = child;
        if (child) child->parent = 0;
        // delete the current node
        delete curr;
        return;
    }
    // whether the current node is the left child of its parent
    bool left = curr->key < parent->key;
    // splice out the current node
    if (left)
        parent->left = child;
    else
        parent->right = child;
    if (child) child->parent = parent;
    delete curr;
    // find the sibling
    MapNode<T1, T2> *sibling = left ? parent->right : parent->left;
    // fix the tree
    fixTree(child, parent, sibling, left);
}

// restores the red black properties of the tree
// O(log(n)) time
// O(1) space
template <typename T1, typename T2>
void BCTreeMap<T1, T2>::fixTree(MapNode<T1, T2> *curr, MapNode<T1, T2> *parent,
                                MapNode<T1, T2> *sibling, bool left) {
    // continue to fix the tree while it is not balanced
    // I have chosen to use iteration instead of recursion because in this case
    // iteration is more space efficient
    while (1) {
        // if the curren node is the root node, make it black and return
        if (curr && !curr->parent) {
            root = curr;
            curr->black = 1;
            return;
        }
        // if the current node is not null, reset the pointers
        if (curr) {
            parent = curr->parent;
            left = curr->key < parent->key;
            if (left)
                sibling = parent->right;
            else
                sibling = parent->left;
        }
        // the sibling will not be null because that would mean there was
        // already a violation of the black depth property before this remove
        // operation was performed and that will not happen precautionary check
        // anyway
        if (!sibling) return;
        // if the sibling is black
        if (sibling->black) {
            // if one of the sibling's children is red
            if ((sibling->left && !sibling->left->black) ||
                (sibling->right && !sibling->right->black)) {
                // perform a rotation to rebalance the tree
                deleteRotate(parent, sibling);
                return;
            }
            // both of the sibling's children are black
            else {
                // make the sibling red
                sibling->black = 0;
                // if the parent is red, make it black and return
                if (!parent->black) {
                    parent->black = 1;
                    return;
                }
                // if the parent is black, update the current node to
                // the parent and allow the loop to continue
                else
                    curr = parent;
            }
        }
        // if the sibling is red
        else {
            // recolor
            sibling->black = 1;
            parent->black = 0;
            // if the current node is the left child of its parent
            if (left) {
                // rotate left
                rotateLeft(sibling, parent);
                // update the sibling
                sibling = parent->right;
            }
            // if the current node is the right child of its parent
            else {
                // rotate right
                rotateRight(sibling, parent);
                // update the sibling
                sibling = parent->left;
            }
            // in the next iteration of the loop this will lead to the situation
            // where the sibling is black
        }
    }
}

// rotates the tree upon deletion in order to re-balance it
// O(1) time
// O(1) space
template <typename T1, typename T2>
void BCTreeMap<T1, T2>::deleteRotate(MapNode<T1, T2> *parent,
                                     MapNode<T1, T2> *sibling) {
    // if the sibling is the left child of the parent
    if (sibling->key < parent->key) {
        // if the red node is the right child of the sibling, perform a pre
        // rotation
        if (sibling->right && !sibling->right->black &&
            (!sibling->left || sibling->left->black)) {
            sibling->right->black = 1;
            sibling = rotateLeft(sibling->right, sibling);
        }
        // make the sibling the color of the parent
        sibling->black = parent->black;
        // make the parent black
        parent->black = 1;
        // make the left child of the sibling black
        if (sibling->left) sibling->left->black = 1;
        // rotate right
        rotateRight(sibling, parent);
    }
    // the sibling is the right child of the parent
    else {
        // if the red node is the left child of the sibling, perform a pre
        // rotation
        if (sibling->left && !sibling->left->black &&
            (!sibling->right || sibling->right->black)) {
            sibling->left->black = 1;
            sibling = rotateRight(sibling->left, sibling);
        }
        // make the sibling the color of the parent
        sibling->black = parent->black;
        // make the parent black
        parent->black = 1;
        // make the right child of the sibling black
        if (sibling->right) sibling->right->black = 1;
        // rotate left
        rotateLeft(sibling, parent);
    }
}

// heler method for tree validation
// -1 is returned when the tree is not valid, else the black height of the
// tree is returned
// O(n) time
// O(log(n)) space
template <typename T1, typename T2>
int BCTreeMap<T1, T2>::validHelp(MapNode<T1, T2> *curr) {
    // if this node is NULL its black height is zero and it is valid
    if (!curr) return 0;

    // check to make sure this node obeys property four
    // if this node is red and it has a red child, it is not valid
    if (!curr->black && ((curr->left && !curr->left->black) ||
                         (curr->right && !curr->right->black))) {
        return -1;
    }

    // get the black height of the left subtree
    int leftBlack = validHelp(curr->left);
    // get the black height of the right subtree
    int rightBlack = validHelp(curr->right);

    // check to make sure that both subtrees are valid and that
    // they have equal black heights
    if (leftBlack == -1 || rightBlack == -1 || leftBlack != rightBlack) {
        return -1;
    }

    // return the black height of the subtrees including
    // this node if it is black
    return leftBlack + (curr->black ? 1 : 0);
}

// determines whether the tree is a valid BST
// O(n) time
// O(log(n)) space
template <typename T1, typename T2>
bool BCTreeMap<T1, T2>::bst() {
    // the first node visited will be the lowest
    bool lowest = 1;
    // the key of the previous node
    T1 prev;
    // check if the tree is valid
    return bstHelp(root, &prev, &lowest);
}

// helper method for bst validation
// O(n) time
// O(log(n)) space
template <typename T1, typename T2>
bool BCTreeMap<T1, T2>::bstHelp(MapNode<T1, T2> *curr, T1 *prev, bool *lowest) {
    if (!curr) return 1;
    // if the left subtree is not valid, return false
    if (!bstHelp(curr->left, prev, lowest)) return 0;
    // if this is the lowest node, set lowest to false
    if (*lowest) *lowest = 0;
    // if this is not the lowest node, make sure this key is
    // greater than the key of the previous node
    else if (curr->key <= *prev)
        return 0;
    // set the key of the previous node to the key of this node
    *prev = curr->key;
    // return true if the right subtree is valid
    return bstHelp(curr->right, prev, lowest);
}
