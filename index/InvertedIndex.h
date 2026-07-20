#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "../models/Document.h"

class InvertedIndex
{
public:
    unordered_map<string, unordered_map<int, vector<int>>> index;
    unordered_map<string, int> docFrequency;

    void addDocument(const Document &doc, const vector<string> &words);

    vector<int> getDoc(const string &word);

    int getFrequency(const string &word, int docId);

    void countFreq(const vector<string> &words);

    vector<int> intersection(vector<int> a, vector<int> b);

    vector<int> doUnion(vector<int> a, vector<int> b);

    vector<int> notFind(const vector<int> &docs, const vector<Document> &documents);
};