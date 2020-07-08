#include "../headers/BCTreeMap.h"
#include "../headers/MapNode.h"
#include "MapCreation.cpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


// HELPER FUNCTIONS

// prints the tree to the console level by level
void displayStr(vector<vector<MapNode<string, int>*>>& levels) {
    for (int i = 0; i < levels.size(); i++) {
        for (int j = 0; j < levels[i].size(); j++) {
            MapNode<string, int>* curr = levels[i][j];
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

// checks if the tree is valid in for a map of strings to ints
void checkStr(BCTreeMap<string, int> map) {
    map.isValid() ? cout << "PASS\n" : cout << "FAIL\n";
}

// tests the various methods of the BCTreeMap to make sure they work properly
void testMethods(BCTreeMap<string, int> map) {
    cout << "\nTesting BCTreeMap methods...\n";
    cout << "\nisEmpty();\n" << (map.isEmpty() ? "true\n" : "false\n");
    cout << "size();\n" << map.size() << "\n";
    cout << "containsKey(\"a\");  (this should be true)\n" << (map.containsKey("a") ? "true\n" : "false\n");
    cout << "containsKey(\"x\");  (this should be false)\n" << (map.containsKey("x") ? "true\n" : "false\n");
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
    cout << "\n\nPerforming valid tree tests... (these should all pass)\n";
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
    BCTreeMap<int, string> first = createDeletionTree1();
    first.remove(-5);
    check(first);
    cout << "Case where the child of the node being deleted is red...\n";
    BCTreeMap<int, string> second = createDeletionTree2();
    second.remove(-2);
    check(second);
    cout << "Cases where the sibling is black and has a red child...\n";
    BCTreeMap<int, string> thirdLeft = createDeletionTree3Left();
    thirdLeft.remove(40);
    check(thirdLeft);
    BCTreeMap<int, string> thirdRight = createDeletionTree3Right();
    thirdRight.remove(20);
    check(thirdRight);
    cout << "Cases where the sibling is black and has a red child and a pre rotation must be performed...\n";
    BCTreeMap<int, string> fourthLeft = createDeletionTree4Left();
    fourthLeft.remove(40);
    check(fourthLeft);
    BCTreeMap<int, string> fourthRight = createDeletionTree4Right();
    fourthRight.remove(20);
    check(fourthRight);
    cout << "Cases where the sibling is black and its children are black and the parent is red...\n";
    BCTreeMap<int, string> fifthLeft = createDeletionTree5();
    fifthLeft.remove(20);
    check(fifthLeft);
    BCTreeMap<int, string> fifthRight = createDeletionTree5();
    fifthRight.remove(30);
    check(fifthRight);
    cout << "Cases where the sibling is black and its children are black and the parent is black...\n";
    BCTreeMap<int, string> sixthLeft = createDeletionTree6();
    sixthLeft.remove(74);
    check(sixthLeft);
    BCTreeMap<int, string> sixthRight = createDeletionTree6();
    sixthRight.remove(76);
    check(sixthRight);
    cout << "Cases where the sibling is red...\n";
    BCTreeMap<int, string> seventhLeft = createDeletionTree7Left();
    seventhLeft.remove(30);
    check(seventhLeft);
    BCTreeMap<int, string> seventhRight = createDeletionTree7Right();
    seventhRight.remove(10);
    check(seventhRight);
}

// builds a tree and then deletes every node, checking to make sure the 
// tree is valid after every operation
void performValidTreeTest() {
    cout << "\n\nBuilding and deleting every node of a tree...\n";
    cout << "\nTesting empty tree...\n";
    BCTreeMap<int, string> empty;
    check(empty);
    cout << "\nPerforming insertions...\n";
    BCTreeMap<string, int> valid;
    valid.put("a", 0);
    checkStr(valid);
    valid.put("b", 0);
    checkStr(valid);
    valid.put("c", 0);
    checkStr(valid);
    valid.put("d", 0);
    checkStr(valid);
    valid.put("e", 0);
    checkStr(valid);
    valid.put("f", 0);
    checkStr(valid);
    valid.put("g", 0);
    checkStr(valid);
    valid.put("h", 0);
    checkStr(valid);
    valid.put("i", 0);
    checkStr(valid);
    valid.put("j", 0);
    checkStr(valid);
    valid.put("k", 0);
    checkStr(valid);
    cout << "\nHere is the BCTreeSet:\n\n";
    vector<vector<MapNode<string, int>*>> levels = valid.levelOrder();
    displayStr(levels);
    testMethods(valid);
    cout << "\nPerforming deletions...\n";
    valid.remove("d");
    checkStr(valid);
    valid.remove("j");
    checkStr(valid);
    valid.remove("h");
    checkStr(valid);
    valid.remove("x");
    checkStr(valid);
    valid.remove("i");
    checkStr(valid);
    valid.remove("g");
    checkStr(valid);
    valid.remove("a");
    checkStr(valid);
    valid.remove("b");
    checkStr(valid);
    valid.remove("c");
    checkStr(valid);
    valid.remove("f");
    checkStr(valid);
    valid.remove("e");
    checkStr(valid);
    valid.remove("k");
    checkStr(valid);
    valid.remove("z");
    checkStr(valid);
    cout <<"\nThe BCTreeMap is now empty.\n\n";
}


int main() {
    performInvalidTreeTests();
    performInsertionTests();
    performDeletionTests();
    performValidTreeTest();
    return 0;
}
