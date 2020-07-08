#include "../headers/BCTreeSet.h"
#include "../headers/SetNode.h"
#include <vector>
#include <iostream>

using namespace std;

// prints the tree to the console level by level
void display(vector<vector<SetNode<int>*>>& levels) {
    for (int i = 0; i < levels.size(); i++) {
        for (int j = 0; j < levels[i].size(); j++) {
            SetNode<int>* curr = levels[i][j];
            cout << "Value:" << curr->value;
            cout << " Color:" << (curr->black ? 'B' : 'R');
            if (curr->left) cout << " Left:" << curr->left->value;
            else cout << " Left:NULL";
            if (curr->right) cout << " Right:" << curr->right->value;
            else cout << " Right:NULL";
            cout << "   ";
        }
        cout << "\n";
    }
}

// checks if the tree is valid
void check(BCTreeSet<int> set) {
    set.isValid() ? cout << "PASS\n" : cout << "FAIL\n"; 
}

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

// performs the invalid tests which should all fail
void performInvalidTreeTests() {
    cout << "\nPerforming invalid tree tests... (these should all fail)\n";
    cout << "\nTesting tree with red root... \n";
    BCTreeSet<int> first = createInvalidTree1();
    check(first);
    cout << "Testing tree with consecutive red nodes... \n";
    BCTreeSet<int> second = createInvalidTree2();
    check(second);
    cout << "Testing tree with unequal black depth... \n";
    BCTreeSet<int> third = createInvalidTree3();
    check(third);
    cout << "Testing tree that is not a valid BST... \n";
    BCTreeSet<int> fourth = createInvalidTree4();
    check(fourth);
}

// creates a tree that will have a red node inserted to a black parent
BCTreeSet<int> createInsertionTree1() {
    SetNode<int>* root = new SetNode<int>(0, 1, 0, 0, 0);
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree that will have a node inserted to a parent and uncle that are both red
BCTreeSet<int> createInsertionTree2() {
    SetNode<int>* root = new SetNode<int>(0, 1, 0, 0, 0);
    SetNode<int>* left = new SetNode<int>(-2, 0, root, 0, 0);
    root->left = left;
    SetNode<int>* right = new SetNode<int>(1, 1, root, 0, 0);
    root->right = right;
    SetNode<int>* ll = new SetNode<int>(-4, 1, left, 0, 0);
    left->left = ll;
    SetNode<int>* lr = new SetNode<int>(-1, 1, left, 0, 0);
    left->right = lr;
    SetNode<int>* lll = new SetNode<int>(-5, 0, ll, 0, 0);
    ll->left = lll;
    SetNode<int>* llr = new SetNode<int>(-3, 0, ll, 0, 0);
    ll->right = llr;
    // create the set 
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// creates a tree where the parent is red and the uncle is black
BCTreeSet<int> createInsertionTree3() {
    SetNode<int>* root = new SetNode<int>(0, 1, 0, 0, 0);
    SetNode<int>* right = new SetNode<int>(10, 0, root, 0, 0);
    root->right = right;
    // create the set
    BCTreeSet<int> tree;
    tree.setRootForTest(root);
    return tree;
}

// tests each insertion case to make sure they all work correctly
void performInsertionTests() {
    cout << "\n\nPerforming tests for each insertion case...\n";
    cout << "\nCase where the parent is black...\n";
    BCTreeSet<int> first = createInsertionTree1();
    first.add(1);
    check(first);
    cout << "Case where the parent and uncle are both red...\n";
    BCTreeSet<int> second = createInsertionTree2();
    second.add(-6);
    check(second);
    cout << "Case where the parent is red and the uncle is black...\n";
    BCTreeSet<int> third = createInsertionTree3();
    third.add(11);
    check(third);
    cout << "Case where the parent is red and the uncle is black and at least two rotations must be performed...\n";
    BCTreeSet<int> fourth = createInsertionTree3();
    fourth.add(9);
    check(fourth);
}

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

}

// creates a tree where the sibling is black and has a red child
BCTreeSet<int> createDeletionTree3Right() {

}

// creates a tree where the sibling is black and has a red child and a pre rotation must be performed
BCTreeSet<int> createDeletionTree4Left() {

}

// creates a tree where the sibling is black and has a red child and a pre rotation must be performed
BCTreeSet<int> createDeletionTree4Right() {
    
}


// tests each deletion case
void performDeletionTests() {
    cout << "\n\nPerforming tests for each deletion case...\n";
    cout << "\nCase where the node being deleted is red...\n";
    BCTreeSet<int> first = createDeletionTree1();
    first.remove(-5);
    check(first);
    cout << "Case where the child of the node being deleted is red...\n";
    BCTreeSet<int> second = createDeletionTree2();
    second.remove(-2);
    check(second);
    cout << "Case where the sibling is black and has a red child...\n";
    cout << "Case where the sibling is black and has a red child and a pre rotation must be performed...\n";
    cout << "Case where the sibling is black and its children are black and the parent is red...\n";
    cout << "Case where the sibling is black and its children are black and the parent is black...\n";
    cout << "Case where the sibling is red...\n";

}

// builds a tree and then deletes every node, checking to make sure the 
// tree is valid after every operation
void performValidTreeTest() {
    cout << "\n\nBuilding and deleting every node of a tree...\n";
    cout << "\nTesting empty tree...\n";
    BCTreeSet<int> empty;
    check(empty);
    cout << "\nPerforming insertions...\n";
    BCTreeSet<int> valid;
    valid.add(5);
    check(valid);
    valid.add(6);
    check(valid);
    valid.add(7);
    check(valid);
    valid.add(8);
    check(valid);
    valid.add(9);
    check(valid); 
    valid.add(10);
    check(valid);
    valid.add(11);
    check(valid);
    valid.add(12);
    check(valid);
    valid.add(13);
    check(valid);
    valid.add(14);
    check(valid);
    valid.add(15);
    check(valid);
    cout << "\nHere is the BCTreeSet:\n\n";
    vector<vector<SetNode<int>*>> levels = valid.levelOrder();
    display(levels);
    cout << "\nPerforming deletions...\n";
    valid.remove(5);
    check(valid);
    valid.remove(11);
    check(valid);
    valid.remove(8);
    check(valid);
    valid.remove(10);
    check(valid);
    valid.remove(15);
    check(valid);
    valid.remove(6);
    check(valid);
    valid.remove(9);
    check(valid);
    valid.remove(12);
    check(valid);
    valid.remove(7);
    check(valid);
    valid.remove(13);
    check(valid);
    valid.remove(14);
    check(valid);
    cout << "\nThe BCTreeSet is now empty.\n\n";
}

int main() {
    performInvalidTreeTests();
    performInsertionTests();
    performDeletionTests();
    performValidTreeTest();
    return 0;
}
