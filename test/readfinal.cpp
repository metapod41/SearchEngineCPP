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
        string word = "";
        bool inQuotes = false;

        for (char c : text)
        {
            
            if (inQuotes)
            {
                if (c == '"')
                {
                    inQuotes = false;

                    if (!word.empty())
                    {
                        words.push_back(toLowerCase(word));
                        word = "";
                    }

                    continue;
                }

                word += tolower(c);
                continue;
            }

            // Opening quote
            if (c == '"')
            {
                if (!word.empty())
                {
                    words.push_back(word);
                    word = "";
                }

                inQuotes = true;
                continue;
            }

            if (c == ' ')
            {
                if (!word.empty())
                {
                    words.push_back(word);
                    word = "";
                }
            }
            else if (isalnum(c))
            {
                word += tolower(c);
            }
            else if (c == '(')
            {
                if (!word.empty())
                {
                    words.push_back(word);
                    word = "";
                }

                words.push_back("(");
            }
            else if (c == ')')
            {
                if (!word.empty())
                {
                    words.push_back(word);
                    word = "";
                }

                words.push_back(")");
            }
            else
            {
                
                continue;
            }
        }

        if (!word.empty())
        {
            words.push_back(word);
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
    unordered_map<string, int> docFrequency;

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

    int getFrequency(string word, int docId)
    {
        if (index.find(word) != index.end())
        {
            if (index[word].find(docId) != index[word].end())
            {
                return index[word][docId].size();
            }
            return 0;
        }
        return 0;
    }

    void countFreq(vector<string> word)
    {
        unordered_set<string> st;
        for (auto &w : word)
        {
            if (!st.count(w))
            {
                docFrequency[w]++;
            }
            st.insert(w);
        }
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

    vector<int> notFind(const vector<int> &doc1, const vector<Document> &documents)
    {

        unordered_set<int> st(doc1.begin(), doc1.end());

        vector<int> res;

        for (const auto &doc : documents)
        {

            if (!st.count(doc.getId()))
                res.push_back(doc.getId());
        }

        return res;
    }
};

double getTF(int Termfrequency, int docSize)
{
    return 1.0 * Termfrequency / docSize;
}

double getIDF(int documentFrequency, int totalDoc)
{
    if (documentFrequency == 0)
    {
        return 0;
    }
    return 1.0 * log(1.0 * totalDoc / documentFrequency);
}

void queryFind(string word, InvertedIndex &invertedIndex, const vector<Document> &documents, unordered_map<int, int> &docSize)
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
        vector<pair<double, int>> rankedDocs;

        for (auto docId : intersectionDoc)
        {
            double score = 0;

            for (auto &w : actualWords)
            {
                double tf = getTF(
                    invertedIndex.getFrequency(w, docId),
                    docSize[docId]);

                double idf = getIDF(
                    invertedIndex.docFrequency[w],
                    documents.size());

                score += tf * idf;
            }

            rankedDocs.push_back({score, docId});
        }

        sort(rankedDocs.begin(), rankedDocs.end(),
             [](auto &a, auto &b)
             {
                 return a.first > b.first;
             });

        cout << "Ranked Results\n";

        for (auto &p : rankedDocs)
        {
            cout << "Doc " << p.second
                 << " Score : "
                 << p.first << "\n";
        }
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

        vector<pair<double, int>> rankedDocs;

        for (auto docId : orDoc)
        {
            double score = 0;

            for (auto &w : actualWords)
            {
                double tf = getTF(
                    invertedIndex.getFrequency(w, docId),
                    docSize[docId]);

                double idf = getIDF(
                    invertedIndex.docFrequency[w],
                    documents.size());

                score += tf * idf;
            }

            rankedDocs.push_back({score, docId});
        }

        sort(rankedDocs.begin(), rankedDocs.end(),
             [](auto &a, auto &b)
             {
                 return a.first > b.first;
             });

        cout << "Ranked Results\n";

        for (auto &p : rankedDocs)
        {
            cout << "Doc " << p.second
                 << " Score : "
                 << p.first << "\n";
        }
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

class QueryNode{
    public:

    string value;
    QueryNode *left;
    QueryNode *right;

    QueryNode(string value){
        this->value = value;
        left = nullptr;
        right = nullptr;
    }

    
};

int precedence(string a)
{
    if (a == "or") return 1;
    if (a == "and") return 2;
    if (a == "not") return 3;
    return -1;
}

bool isOperand(string a)
{
    return !(a == "and" || a == "or" || a == "not" || a == "(" || a == ")");
}

QueryNode* buildTree(vector<string> tokens)
{
    stack<QueryNode*> operandStack;
    stack<string> operatorStack;

    for (auto &token : tokens)
    {
        if (isOperand(token))
        {
            QueryNode *newNode = new QueryNode(token);
            operandStack.push(newNode);
        }

        else if (token == "(")
        {
            operatorStack.push(token);
        }

        else if (token == ")")
        {
            while (!operatorStack.empty() && operatorStack.top() != "(")
            {
                string op = operatorStack.top();
                operatorStack.pop();

                QueryNode *node2 = operandStack.top();
                operandStack.pop();

                QueryNode *node1 = operandStack.top();
                operandStack.pop();

                QueryNode *root = new QueryNode(op);
                root->left = node1;
                root->right = node2;

                operandStack.push(root);
            }

            if (!operatorStack.empty())
                operatorStack.pop();   
        }

        else
        {
            while (!operatorStack.empty() &&
                   operatorStack.top() != "(" &&
                   precedence(operatorStack.top()) >= precedence(token))
            {
                string op = operatorStack.top();
                operatorStack.pop();

                QueryNode *node2 = operandStack.top();
                operandStack.pop();

                QueryNode *node1 = operandStack.top();
                operandStack.pop();

                QueryNode *root = new QueryNode(op);
                root->left = node1;
                root->right = node2;

                operandStack.push(root);
            }

            operatorStack.push(token);
        }
    }

    while (!operatorStack.empty())
    {
        string op = operatorStack.top();
        operatorStack.pop();

        QueryNode *node2 = operandStack.top();
        operandStack.pop();

        QueryNode *node1 = operandStack.top();
        operandStack.pop();

        QueryNode *root = new QueryNode(op);
        root->left = node1;
        root->right = node2;

        operandStack.push(root);
    }

    return operandStack.top();
}

void printTree(QueryNode *root){
    if(root==nullptr){
        return;
    }
    cout<<root->value<<endl;
    printTree(root->left);
    printTree(root->right);
}

vector<int> evaluate(QueryNode *root, InvertedIndex &index)
{
    if (root == nullptr)
        return {};

    if (isOperand(root->value))
        return index.getDoc(root->value);

    vector<int> left = evaluate(root->left, index);
    vector<int> right = evaluate(root->right, index);

    if (root->value == "and")
        return index.intersection(left, right);
    else
        return index.doUnion(left, right);   
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
    unordered_map<int, int> docSize;
    for (auto &doc : documents)
    {
        vector<string> words = tokenizer.tokenize(doc.getContent());

        docSize[doc.getId()] = words.size();

        invertedIndex.addDocument(doc, words);

        invertedIndex.countFreq(words);
    }
    // cout << "Enter words to search: ";
    // string query;
    // getline(cin, query);
    // cout << "The words \" " << query << " \"" << " is found in : " << endl;
    // queryFind(query, invertedIndex, documents, docSize);

    string st = "apple AND banana AND fruit OR honey";

    

    Tokenizer tok;
    vector<string> tokens = tok.tokenize(st);

    QueryNode *root = buildTree(tokens);
    printTree(root);
    
}
