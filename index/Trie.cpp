#include "Trie.h"

TrieNode::TrieNode()
{
    isWord = false;
}

Trie::Trie()
{
    root = new TrieNode();
}

void Trie::insert(const string &word)
{
    TrieNode *current = root;

    for (char ch : word)
    {
        if (current->children.find(ch) == current->children.end())
        {
            current->children[ch] = new TrieNode();
        }

        current = current->children[ch];
    }

    current->isWord = true;
}

bool Trie::search(const string &word)
{
    TrieNode *current = root;

    for (auto &ch : word)
    {
        if (current->children.find(ch) == current->children.end())
        {
            return false;
        }

        current = current->children[ch];
    }

    return current->isWord;
}

TrieNode *Trie::findPrefix(const string &prefix)
{
    TrieNode *current = root;

    for (auto &ch : prefix)
    {
        if (current->children.find(ch) == current->children.end())
        {
            return nullptr;
        }

        current = current->children[ch];
    }

    return current;
}

void Trie::dfs(TrieNode *node,string &currentWord,vector<string> &suggestions,int k)
{
    if (suggestions.size() == k)
    {
        return;
    }

    if (node->isWord)
    {
        suggestions.push_back(currentWord);

        if (suggestions.size() == k)
        {
            return;
        }
    }

    for (auto &child : node->children)
    {
        currentWord.push_back(child.first);

        dfs(child.second,currentWord,suggestions,k);

        currentWord.pop_back();

        if (suggestions.size() == k)
        {
            return;
        }
    }
}

void Trie::dfsAll(TrieNode *node,string &currentWord,vector<string> &words)
{
    if (node->isWord)
    {
        words.push_back(currentWord);
    }

    for (auto &child : node->children)
    {
        currentWord.push_back(child.first);

        dfsAll(child.second,currentWord,words);

        currentWord.pop_back();
    }
}

vector<string> Trie::collectAllWords(const string &prefix)
{
    vector<string> words;

    TrieNode *node = findPrefix(prefix);

    if (node == nullptr)
    {
        return words;
    }

    string currentWord = prefix;

    dfsAll(node,currentWord,words);

    return words;
}

vector<string> Trie::autocomplete(const string &prefix,int k)
{
    vector<string> suggestions;

    TrieNode *node = findPrefix(prefix);

    if (node == nullptr)
    {
        return suggestions;
    }

    string currentWord = prefix;

    dfs(node,currentWord,suggestions,k);

    return suggestions;
}