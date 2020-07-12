#include "../headers/Trie.h"
#include <iostream>

using namespace std;


void trieTest() {
    Trie trie;
    trie.insert("this");
    trie.insert("that");
    trie.insert("than");
    trie.insert("is");
    trie.insert("a");
    trie.insert("trie");
    trie.insert("an");
    trie.printTrie();
    cout << "Searching for \'t\'\n";
    vector<string> v = trie.search("t");
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << "\n";
    }
}

int main() {
    trieTest();
    return 0;
}