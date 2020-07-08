#include "../headers/BCTreeMap.h"
#include "../headers/MapNode.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

int main() {
    // create the test tree
    BCTreeMap<int, string> map;
    map.put(5, "this");
    map.put(6, "is");
    map.put(7, "a");
    map.put(8, "red");
    map.put(9, "black");
    map.put(10, "tree");
    map.put(11, "map");
    map.put(6, "fuck");
    map.put(12, "asdf");

    cout << "\n";

    // make sure the tree is self balancing
    vector<vector<MapNode<int, string>*>> levels = map.levelOrder();
    display(levels);

    // make sure the methods work
    cout << map.isEmpty() << "\n";
    cout << map.size() << "\n";
    cout << map.containsKey(10) << "\n";
    cout << map.containsKey(14) << "\n";

    return 0;
}
