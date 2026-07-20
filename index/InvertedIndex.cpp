#include "InvertedIndex.h"

void InvertedIndex::addDocument(const Document &doc, const vector<string> &words)
{
    for (int i = 0; i < (int)words.size(); i++)
    {
        index[words[i]][doc.getId()].push_back(i);
    }
}

vector<int> InvertedIndex::getDoc(const string &word)
{
    vector<int> docs;

    auto it = index.find(word);

    if (it == index.end())
        return docs;

    for (auto &doc : it->second)
        docs.push_back(doc.first);

    sort(docs.begin(), docs.end());

    return docs;
}

int InvertedIndex::getFrequency(const string &word, int docId)
{
    auto it = index.find(word);

    if (it == index.end())
        return 0;

    auto jt = it->second.find(docId);

    if (jt == it->second.end())
        return 0;

    return jt->second.size();
}

void InvertedIndex::countFreq(const vector<string> &words)
{
    unordered_set<string> visited;

    for (auto &word : words)
    {
        if (!visited.count(word))
        {
            docFrequency[word]++;
            visited.insert(word);
        }
    }
}

vector<int> InvertedIndex::intersection(vector<int> a, vector<int> b)
{
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> ans;

    int i = 0;
    int j = 0;

    while (i < (int)a.size() && j < (int)b.size())
    {
        if (a[i] == b[j])
        {
            ans.push_back(a[i]);
            i++;
            j++;
        }
        else if (a[i] < b[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }

    return ans;
}

vector<int> InvertedIndex::doUnion(vector<int> a, vector<int> b)
{
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> ans;

    int i = 0;
    int j = 0;

    while (i < (int)a.size() && j < (int)b.size())
    {
        if (a[i] == b[j])
        {
            ans.push_back(a[i]);
            i++;
            j++;
        }
        else if (a[i] < b[j])
        {
            ans.push_back(a[i]);
            i++;
        }
        else
        {
            ans.push_back(b[j]);
            j++;
        }
    }

    while (i < (int)a.size())
        ans.push_back(a[i++]);

    while (j < (int)b.size())
        ans.push_back(b[j++]);

    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    return ans;
}

vector<int> InvertedIndex::notFind(const vector<int> &docs,const vector<Document> &documents)
{
    unordered_set<int> present(docs.begin(), docs.end());

    vector<int> ans;

    for (auto &doc : documents)
    {
        if (!present.count(doc.getId()))
            ans.push_back(doc.getId());
    }

    return ans;
}