#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "Trie.h"
#include "InvertedIndex.h"

class FuzzySearch
{
public:
    int levenshteinDistance(const string &a, const string &b);

    vector<string> generateCandidates(const string &query,Trie &trie,InvertedIndex &index);

    string bestSuggestion(const string &query,onst vector<string> &candidates);

    
    string correctQuery(const string &query,Trie &trie,InvertedIndex &index);
};