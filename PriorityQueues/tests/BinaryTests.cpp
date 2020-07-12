#include "../headers/BinaryPQ.h"
#include <iostream>
#include <vector>

using namespace std;


// prints a vector to the console
void display(vector<int>& arr) {
    cout << '[';
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

// tests heapsort
void testHeapsort() {
    vector<int> arr{1, 44, 39, 685, 4, 234, 3, 3, 234, 532, 77, 567, 
        445, 43, 4, 23, 34, 69, 42069, 4983, 55, 3, 5};
    cout << "\nTesting heapsort...\n\nArray before sorting:\n\n";
    display(arr);
    BinaryHeap<int>::heapsort(arr);
    cout << "\nArray after sorting:\n\n";
    display(arr);
    
}

// tests BinaryPQ
void testBinaryPQ() {
    cout << "\nTesting BinaryPQ...\n";
    cout << "Pushing numbers...\n\nHere is the underlying BinaryHeap:\n";
    BinaryPQ<int> test;
    test.push(5);
    test.push(8);
    test.push(1);
    test.push(90);
    test.push(55);
    test.push(69);
    test.push(18);
    test.push(30);
    test.push(19);
    test.print();
    cout << "\nTesting methods...\n";
    cout << "top();  ->  " << test.top() << "\n";
    cout << "size();  ->  " << test.size() << "\n";
    cout << "isEmpty();  ->  " << (test.isEmpty() ? "true\n" : "false\n");
    cout << "pop();  ->  " << test.pop() << "\n";
    test.clear();
    cout << "clear();\n";
    cout << "isEmpty();  ->  " << (test.isEmpty() ? "true\n" : "false\n");
    cout << "\nHere is the underlying BinaryHeap:\n";
    test.print();
    cout << "\nCreating BinaryPQ from vector...\n\n";
    cout << "Here is the vector:\n";
    vector<int> v{100, 78, 44, 150, 3, 33, 2, 8573, -1, 534345, 8574, 44, 33, 55, 9, 19};
    display(v);
    BinaryPQ<int> second(v);
    cout << "\nHere is the underlying BinaryHeap after constructing the BinaryPQ:\n";
    second.print();
    cout << "\nRemoving minimum...\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
    cout << second.pop() << "\n";
}

int main() {
    testHeapsort();
    testBinaryPQ();
    return 0;
}
