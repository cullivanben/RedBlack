#include <unordered_map>

#pragma once

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    char letter;
    bool isLast;
    TrieNode(char letter, bool isLast) 
        : letter(letter), isLast(isLast) 
        {}
};