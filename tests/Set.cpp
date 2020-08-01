#include "../headers/BCTreeSet.h"
#include "SetCreation.cpp"
#include <iostream>
#include <vector>

using namespace std;


// HELPER FUNCTIONS

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

// tests the various methods of the BCTreeSet to make sure they work properly
void testMethods(BCTreeSet<int> set) {
    cout << "\nTesting BCTreeSet methods...\n";
    cout << "\nisEmpty();\n" << (set.isEmpty() ? "true\n" : "false\n");
    cout << "size();\n" << set.size() << "\n";
    cout << "contains(5);  (this should be true)\n" << (set.contains(5) ? "true\n" : "false\n");
    cout << "contains(1);  (this should be false)\n" << (set.contains(1) ? "true\n" : "false\n");
}


// TESTING FUNCTIONS

// performs the invalid tests which should all fail
void performInvalidTreeTests() {
    cout << "\nPerforming invalid tree tests... (these should all fail)\n";
    cout << "These invalid tree tests are to make sure that the testing methods are able to detect invalid red black trees.\n";
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
    cout << "\n\nPerforming valid tree tests... (these should all pass)\n";
}

// tests each insertion case 
void performInsertionTests() {
    cout << "\n\nPerforming tests for each insertion case...\n";
    cout << "\nCase where the parent is black...\n";
    BCTreeSet<int> first = createInsertionTree1();
    first.add(1);
    check(first);
    cout << "Case where the parent and uncle are both red...\n";
    BCTreeSet<int> second = createInsertionTree2();
    second.add(10);
    check(second);
    cout << "Case where the parent is red and the uncle is black...\n";
    BCTreeSet<int> third = createInsertionTree3();
    third.add(-100);
    check(third);
    cout << "Case where the parent is red and the uncle is black and at least two rotations must be performed...\n";
    BCTreeSet<int> fourth = createInsertionTree3();
    fourth.add(-1);
    check(fourth);
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
    cout << "Cases where the sibling is black and has a red child...\n";
    BCTreeSet<int> thirdLeft = createDeletionTree3Left();
    thirdLeft.remove(40);
    check(thirdLeft);
    BCTreeSet<int> thirdRight = createDeletionTree3Right();
    thirdRight.remove(20);
    check(thirdRight);
    cout << "Cases where the sibling is black and has a red child and a pre rotation must be performed...\n";
    BCTreeSet<int> fourthLeft = createDeletionTree4Left();
    fourthLeft.remove(40);
    check(fourthLeft);
    BCTreeSet<int> fourthRight = createDeletionTree4Right();
    fourthRight.remove(20);
    check(fourthRight);
    cout << "Cases where the sibling is black and its children are black and the parent is red...\n";
    BCTreeSet<int> fifthLeft = createDeletionTree5();
    fifthLeft.remove(20);
    check(fifthLeft);
    BCTreeSet<int> fifthRight = createDeletionTree5();
    fifthRight.remove(30);
    check(fifthRight);
    cout << "Cases where the sibling is black and its children are black and the parent is black...\n";
    BCTreeSet<int> sixthLeft = createDeletionTree6();
    sixthLeft.remove(74);
    check(sixthLeft);
    BCTreeSet<int> sixthRight = createDeletionTree6();
    sixthRight.remove(76);
    check(sixthRight);
    cout << "Cases where the sibling is red...\n";
    BCTreeSet<int> seventhLeft = createDeletionTree7Left();
    seventhLeft.remove(30);
    check(seventhLeft);
    BCTreeSet<int> seventhRight = createDeletionTree7Right();
    seventhRight.remove(10);
    check(seventhRight);
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
    testMethods(valid);
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
