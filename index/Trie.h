#pragma once

#include <bits/stdc++.h>
using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode *> children;
    bool isWord;

    TrieNode();
};

class Trie
{
public:
    TrieNode *root;

    Trie();

    void insert(const string &word);

    bool search(const string &word);

    TrieNode *findPrefix(const string &prefix);

    void dfs(TrieNode *node,string &currentWord,vector<string> &suggestions,int k);

    void dfsAll(TrieNode *node,string &currentWord,vector<string> &words);

    vector<string> collectAllWords(const string &prefix);

    vector<string> autocomplete(const string &prefix,int k = 5);

    
    vector<string> autocompleteQuery(const string &query,int k = 5);
};