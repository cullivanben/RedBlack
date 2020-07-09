#include "../headers/BinaryHeap.h"
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

int main() {
    testHeapsort();
    return 0;
}
