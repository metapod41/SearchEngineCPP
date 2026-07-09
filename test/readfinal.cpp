#include <bits/stdc++.h>
#include <filesystem>
using namespace std;

class Document
{
private:
    int id;
    string filename;
    string content;

public:
    Document(int id, const string &filename, const string &content) : id(id), filename(filename), content(content) {}

    int getId() const
    {
        return id;
    }

    const string &getFilename() const
    {
        return filename;
    }

    const string &getContent() const
    {
        return content;
    }
};

class Tokenizer
{
public:
    vector<string> tokenize(const string &text)
    {
        vector<string> words;
        string word;
        stringstream ss(text);
        while (ss >> word)
        {
            string lower = toLowerCase(word);
            string punctuation = removePunctuation(lower);
            if (!punctuation.empty())
            {
                words.push_back(punctuation);
            }
        }
        return words;
    }

    string toLowerCase(string word) const
    {
        string res = "";
        for (auto &w : word)
        {
            res += tolower(w);
        }
        return res;
    }

    string removePunctuation(string word)
    {
        string res = "";
        for (auto &c : word)
        {
            if (isalnum(c))
            {
                res += c;
            }
        }
        return res;
    }
};

class InvertedIndex
{
public:
    unordered_map<string, unordered_map<int, vector<int>>> index;

    void addDocument(const Document &doc, const vector<string> &words)
    {
        for (int i = 0; i < words.size(); i++)
        {
            index[words[i]][doc.getId()].push_back(i);
        }
    }

    vector<int> getDoc(string word)
    {
        vector<int> res;
        for (auto &it : index[word])
        {
            res.push_back(it.first);
        }
        return res;
    }

    vector<int> intersection(vector<int> &doc1, vector<int> &doc2)
    {
        unordered_set<int> st;
        vector<int> res;
        for (auto &d : doc1)
        {
            st.insert(d);
        }
        for (auto &d : doc2)
        {
            if (st.count(d))
            {
                res.push_back(d);
                st.erase(d);
            }
        }
        return res;
    }

    vector<int> doUnion(vector<int> &doc1, vector<int> &doc2)
    {
        unordered_set<int> st;
        vector<int> res;
        for (auto &w : doc1)
        {
            st.insert(w);
        }
        for (auto &w : doc2)
        {
            st.insert(w);
        }
        for (auto &w : st)
        {
            res.push_back(w);
        }
        return res;
    }

    vector<int> notFind(const vector<int> &doc1,const vector<Document> &documents){
    
        unordered_set<int> st(doc1.begin(), doc1.end());

        vector<int> res;

        for (const auto &doc : documents){
        
            if (!st.count(doc.getId()))
                res.push_back(doc.getId());
        }

        return res;
    }
};

void queryFind(string word, InvertedIndex &invertedIndex , const vector<Document>& documents)
{
    Tokenizer tokenizer;
    vector<string> actualWords;
    vector<string> tokenisedString = tokenizer.tokenize(word);
    bool andSearch = true, orSearch = false, notSearch = false;
    for (auto &w : tokenisedString)
    {
        if (w != "and" && w != "or" && w != "not")
        {
            actualWords.push_back(w);
        }
        else if (w == "and")
        {
            andSearch = true;
        }
        else if (w == "or")
        {
            orSearch = true;
            andSearch = false;
        }
        else
        {
            notSearch = true;
            andSearch = false;
        }
    }
    vector<vector<int>> docs;
    if (andSearch)
    {
        for (auto &word : actualWords)
        {
            docs.push_back(invertedIndex.getDoc(word));
        }
        vector<int> intersectionDoc = docs[0];
        for (int i = 1; i < docs.size(); i++)
        {
            intersectionDoc = invertedIndex.intersection(intersectionDoc, docs[i]);
        }
        for (int i = 0; i < intersectionDoc.size(); i++)
        {
            cout << intersectionDoc[i] << " ";
        }
        cout << "\n";
    }
    else if (orSearch)
    {
        for (auto &word : actualWords)
        {
            docs.push_back(invertedIndex.getDoc(word));
        }
        vector<int> orDoc = docs[0];
        for (int i = 1; i < docs.size(); i++)
        {
            orDoc = invertedIndex.doUnion(orDoc, docs[i]);
        }

        for (int i = 0; i < orDoc.size(); i++)
        {
            cout << orDoc[i] << " ";
        }
        cout << "\n";
    }
    else
    {
        vector<int> doc1;
        doc1 = invertedIndex.getDoc(actualWords[0]);

        vector<int> res = invertedIndex.notFind(doc1, documents);
        for (int i = 0; i < res.size(); i++)
        {
            cout << res[i] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    vector<Document> documents;
    int id = 0;
    for (auto &entry : filesystem::directory_iterator("data"))
    {
        if (entry.path().extension() == ".txt")
        {
            string filename = entry.path().filename().string();
            ifstream file(entry.path());
            if (file)
            {
                cout << "opened!!\n";
                string content;
                string line;

                while (getline(file, line))
                {
                    content += line;
                    content += "\n";
                }

                id++;
                Document obj(id, filename, content);
                documents.push_back(obj);
            }
        }
    }
    Tokenizer tokenizer;
    InvertedIndex invertedIndex;
    for (auto &doc : documents)
    {
        vector<string> words = tokenizer.tokenize(doc.getContent());

        invertedIndex.addDocument(doc, words);
    }
    unordered_map<string, unordered_map<int, vector<int>>> index = invertedIndex.index;
    cout << "Enter words to search: ";
    string query;
    getline(cin, query);
    cout << "The words \" " << query << " \"" << " is found in : " << endl;
    queryFind(query, invertedIndex , documents);
}
