#include <iostream>
#include <vector>
#include "../BCTreeMap.h"

using namespace std;

int main() {

    BCTreeMap<int, string> map;

    map.put(5, "this");
    map.put(6, "is");
    map.put(7, "a");
    map.put(8, "red");
    map.put(9, "black");
    map.put(10, "tree");
    map.put(11, "map");

    

    return 0;
}