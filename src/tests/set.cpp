#include <iostream>
#include "../BCTreeSet.h"

using namespace std;

int main() {

    BCTreeSet<int> set;

    set.add(5);
    set.add(6);
    set.add(7);
    set.add(8);
    set.add(9);
    set.add(10);
    set.add(11);

    cout << set.size() << "\n\n";

    vector<vector<int>> levels = set.levelOrder();

    for (int i = 0; i < levels.size(); i++) {
        for (int j = 0; j < levels[i].size(); j++) {
            cout << levels[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}