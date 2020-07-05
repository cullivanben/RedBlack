#include <iostream>
#include "../BCTreeSet.h"

using namespace std;

int main() {

    BCTreeSet<int> set;

    set.add(5);

    cout << set.size();

    return 0;
}