#include "../headers/Trie.h"
#include <iostream>


// constructor
Trie::Trie() {
    head = new TrieNode(' ', 1);
}

// insert
// O(n) time where n is the length of the word
// O(1) space
void Trie::insert(std::string word) {
    TrieNode* curr = head;
    for (int i = 0; i < word.length(); i++) {
        if (curr->children.find(word[i]) != curr->children.end()) {
            curr = curr->children[word[i]];
        } else {
            curr->isLast = 0;
            if (i == word.length()-1) {
                curr->children.insert(std::make_pair(word[i], new TrieNode(word[i], 1)));
            } else {
                curr->children.insert(std::make_pair(word[i], new TrieNode(word[i], 0)));
                curr = curr->children[word[i]];
            }
        }
    }
}

// searches for a prefix in the trie
// returns every word in the trie that starts with that prefix
std::vector<std::string> Trie::search(std::string prefix) {
    TrieNode* curr = head;
    for (int i = 0; i < prefix.length(); i++) {
        if (curr->children.find(prefix[i]) == curr->children.end()) return {};
        else curr = curr->children[prefix[i]];
    }   
    if (curr->isLast) return {prefix};
    std::vector<std::string> out;
    for (std::unordered_map<char, TrieNode*>::iterator it = curr->children.begin(); it != curr->children.end(); it++) {
        searchHelp(it->second, prefix, out);
    }
    return out;
}

// adds all of the words starting with the specified prefix to the vector of words
void Trie::searchHelp(TrieNode* curr, std::string word, std::vector<std::string>& out) {
    // add this character to the word
    word.push_back(curr->letter);
    // if this is a leaf, add this word to the vector of words
    if (curr->isLast) {
        out.push_back(word);
        return;
    }
    // call this function on all of the children nodes
    for (std::unordered_map<char, TrieNode*>::iterator it = curr->children.begin(); it != curr->children.end(); it++) {
        searchHelp(it->second, word, out);
    }
}

// prints the trie
void Trie::printTrie() {
    if (head->children.size() == 0) return;
    // call this function on all of the children nodes
    for (std::unordered_map<char, TrieNode*>::iterator it = head->children.begin(); it != head->children.end(); it++) {
        printHelp(it->second, "");
    }
}

// print helper
void Trie::printHelp(TrieNode* curr, std::string word) {
    // add this character to the word
    word.push_back(curr->letter);
    // if this is a leaf, print the word
    if (curr->isLast) {
        std::cout << word << "\n";
        return;
    }
    // call this function on all of the children nodes
    for (std::unordered_map<char, TrieNode*>::iterator it = curr->children.begin(); it != curr->children.end(); it++) {
        printHelp(it->second, word);
    }
}
