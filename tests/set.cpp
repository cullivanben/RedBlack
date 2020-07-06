#include "../headers/BCTreeSet.h"
#include "../headers/SetNode.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// prints the tree to the console level by level
void display(vector<vector<SetNode<int>*>>& levels) {
    for (int i = 0; i < levels.size(); i++) {
        for (int j = 0; j < levels[i].size(); j++) {
            SetNode<int>* curr = levels[i][j];
            cout << "Value:" << curr->value;
            cout << " Color:" << (curr->black ? 'B':'R');
            if (curr->left) cout << " Left:" << curr->left->value;
            else cout << " Left:NULL";
            if (curr->right) cout << " Right:" << curr->right->value;
            else cout << " Right:NULL";
            cout << "   ";
        }
        cout << "\n";
    }
}

int main() {
    // create the test tree
    BCTreeSet<int> set;
    set.add(5);
    set.add(6);
    set.add(7);
    set.add(8);
    set.add(9);
    set.add(10);
    set.add(11);
    set.add(12);

    cout << "\n";

    // make sure the tree is self balancing
    vector<vector<SetNode<int>*>> levels = set.levelOrder();
    display(levels);

    // make sure the methods work
    cout << set.isEmpty() << "\n";
    cout << set.size() << "\n";
    cout << set.contains(9) << "\n";
    cout << set.contains(-1) << "\n";

    return 0;
}
