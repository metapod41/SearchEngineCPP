#include "SnippetGenerator.h"

int SnippetGenerator::findFirstOccurrence(const vector<string> &tokens,int docId,InvertedIndex &index)
{
    int first = INT_MAX;

    for (const string &token : tokens)
    {
        if (token == "and" ||
            token == "or" ||
            token == "(" ||
            token == ")")
            continue;

        auto wordIt = index.index.find(token);

        if (wordIt == index.index.end())
            continue;

        auto docIt = wordIt->second.find(docId);

        if (docIt == wordIt->second.end())
            continue;

        if (!docIt->second.empty())
            first = min(first, docIt->second[0]);
    }

    return (first == INT_MAX ? -1 : first);
}

vector<string> SnippetGenerator::extractSnippet(int position,const vector<string> &words)
{
    vector<string> res;

    int n = words.size();

    int start = max(0, position - 5);
    int end = min(n - 1, position + 5);

    for (int i = start; i <= end; i++)
    {
        res.push_back(words[i]);
        res.push_back(" ");
    }

    return res;
}

string SnippetGenerator::highlightSnippet(vector<string> &snippet,const vector<string> &queryTokens)
{
    unordered_set<string> st;

    for (auto &word : queryTokens)
    {
        if (word == "and" ||
            word == "or" ||
            word == "(" ||
            word == ")")
        {
            continue;
        }

        st.insert(word);
    }

    for (auto &word : snippet)
    {
        if (st.count(word))
        {
            word = "**" + word + "**";
        }
    }

    string res = "";

    for (auto &word : snippet)
    {
        res += word;
        res += " ";
    }

    return res;
}