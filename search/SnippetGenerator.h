#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "../index/InvertedIndex.h"

class SnippetGenerator
{
public:

    int findFirstOccurrence(const vector<string> &tokens,int docId,InvertedIndex &index);

    vector<string> extractSnippet(int position,const vector<string> &words);

    string highlightSnippet(vector<string> &snippet,const vector<string> &queryTokens);
};