#include "TrieNode.h"
#include <vector>
#include <string>

#pragma once

class Trie {
    TrieNode* head;
    void printHelp(TrieNode* curr, std::string word);
    void searchHelp(TrieNode* curr, std::string word, std::vector<std::string>& out);
    public:
        Trie();
        void insert(std::string word);
        std::vector<std::string> search(std::string prefix);
        void remove(std::string word);
        void printTrie();
};
// include the source file so that the compiler can access it
#include "../sources/Trie.cpp"
