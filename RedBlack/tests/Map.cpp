#include "../headers/BCTreeMap.h"
#include "../headers/MapNode.h"
#include "MapCreation.cpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


// HELPER FUNCTIONS

// prints the tree to the console level by level
void display(vector<vector<MapNode<int, string>*>>& levels) {
    for (int i = 0; i < levels.size(); i++) {
        for (int j = 0; j < levels[i].size(); j++) {
            MapNode<int, string>* curr = levels[i][j];
            cout << "Key:" << curr->key;
            cout << " Value:" << curr->value;
            cout << " Color:" << (curr->black ? 'B' : 'R');
            if (curr->left) cout << " Left:" << curr->left->key;
            else cout << " Left:NULL";
            if (curr->right) cout << " Right:" << curr->right->key;
            else cout << " Right:NULL";
            cout << "   "; 
        }
        cout << "\n";
    }
}

// checks if the tree is valid
void check(BCTreeMap<int, string> map) {
    map.isValid() ? cout << "PASS\n" : cout << "FAIL\n";
}

// tests the various methods of the BCTreeMap to make sure they work properly
void testMethods(BCTreeMap<int, string> map) {

}


// TESTING FUNCTIONS

// perfroms the invalid tree tests which should all fail
void performInvalidTreeTests() {
    cout << "\nPerforming invalid tree tests... (these should all fail)\n";
    cout << "These invalid tree tests are to make sure that the testing methods are able to detect invalid red black trees.\n";
    cout << "\nTesting tree with red root... \n";
    BCTreeMap<int, string> first = createInvalidTree1();
    check(first);
    cout << "Testing tree with consecutive red nodes... \n";
    BCTreeMap<int, string> second = createInvalidTree2();
    check(second);
    cout << "Testing tree with unequal black depth... \n";
    BCTreeMap<int, string> third = createInvalidTree3();
    check(third);
    cout << "Testing tree that is not a valid BST... \n";
    BCTreeMap<int, string> fourth = createInvalidTree4();
    check(fourth);
}

// tests each insertion case
void performInsertionTests() {
    cout << "\n\nPerforming tests for each insertion case...\n";
    cout << "\nCase where the parent is black...\n";
    BCTreeMap<int, string> first = createInsertionTree1();
    first.put(1, "");
    check(first);
    cout << "Case where the parent and uncle are both red...\n";
    BCTreeMap<int, string> second = createInsertionTree2();
    second.put(10, "");
    check(second);
    cout << "Case where the parent is red and the uncle is black...\n";
    BCTreeMap<int, string> third = createInsertionTree3();
    third.put(-100, "");
    check(third);
    cout << "Case where the parent is red and the uncle is black and at least two rotations must be performed...\n";
    BCTreeMap<int, string> fourth = createInsertionTree3();
    fourth.put(-1, "");
    check(fourth);
}

// tests each deletion case
void performDeletionTests() {
    cout << "\n\nPerforming tests for each deletion case...\n";
    cout << "\nCase where the node being deleted is red...\n";
}

// builds a tree and then deletes every node, checking to make sure the 
// tree is valid after every operation
void performValidTreeTest() {

}


int main() {
    performInvalidTreeTests();
    performInsertionTests();
    performDeletionTests();
    performValidTreeTest();
    return 0;
}
