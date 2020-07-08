#include <iostream>

using namespace std;

void change(bool* b) {
    *b = !(*b);
}
int main() {
    bool b = 0;
    cout << &b << "\n";
    change(&b);
    cout << b << "\n";
}