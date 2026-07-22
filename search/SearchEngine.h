#pragma once

#include <bits/stdc++.h>
#include <filesystem>
using namespace std;

#include "../models/Document.h"
#include "../tokenizer/Tokenizer.h"
#include "../index/InvertedIndex.h"
#include "../index/Trie.h"
#include "../index/FuzzySearch.h"
#include "QueryParser.h"
#include "SnippetGenerator.h"

class SearchEngine
{
private:
    vector<Document> documents;

    Tokenizer tokenizer;
    InvertedIndex invertedIndex;
    Trie trie;
    FuzzySearch fuzzySearch;
    SnippetGenerator snippet;

    unordered_map<int, int> docSize;
    unordered_map<int, vector<string>> documentWords;

public:
    void clearIndex();
    void loadDocuments(string folder);

    void buildIndex();

    void search(string query);

    vector<Document> &getDocuments();
};