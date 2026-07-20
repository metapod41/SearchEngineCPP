#pragma once

#include <bits/stdc++.h>
using namespace std;

#include "../index/InvertedIndex.h"
#include "../tokenizer/Tokenizer.h"

class QueryNode
{
public:
    string value;
    QueryNode *left;
    QueryNode *right;

    QueryNode(string value);
};

int precedence(string op);

bool isOperand(string token);

QueryNode *buildTree(vector<string> tokens);

void printTree(QueryNode *root);

vector<int> phraseSearch(string query,Tokenizer &tokenizer,InvertedIndex &invertedIndex);

vector<int> evaluate(QueryNode *root,InvertedIndex &index,Tokenizer &tokenizer);