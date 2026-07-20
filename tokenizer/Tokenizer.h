#pragma once

#include <bits/stdc++.h>
using namespace std;

class Tokenizer
{
public:
    vector<string> tokenize(const string &text);

    string toLowerCase(string word) const;

    string removePunctuation(string word);
};