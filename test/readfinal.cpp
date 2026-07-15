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

        for (char ch : text)
        {
            unsigned char c = static_cast<unsigned char>(ch);

            if (inQuotes)
            {
                if (c == '"')
                {
                    inQuotes = false;

                    if (!word.empty())
                    {
                        words.push_back(toLowerCase(word));
                        word.clear();
                    }

                    continue;
                }

                word += (char)tolower(c);
                continue;
            }

            if (c == '"')
            {
                if (!word.empty())
                {
                    words.push_back(toLowerCase(word));
                    word.clear();
                }

                inQuotes = true;
                continue;
            }

            if (isalnum(c))
            {
                word += (char)tolower(c);
            }
            else if (isspace(c))
            {
                if (!word.empty())
                {
                    words.push_back(toLowerCase(word));
                    word.clear();
                }
            }
            else if (c == '(' || c == ')')
            {
                if (!word.empty())
                {
                    words.push_back(toLowerCase(word));
                    word.clear();
                }

                words.push_back(string(1, c));
            }
            else
            {
                if (!word.empty())
                {
                    words.push_back(toLowerCase(word));
                    word.clear();
                }
            }
        }

        if (!word.empty())
            words.push_back(toLowerCase(word));

        return words;
    }

    string toLowerCase(string word) const
    {
        for (char &c : word)
            c = (char)tolower((unsigned char)c);

        return word;
    }

    string removePunctuation(string word)
    {
        string res;

        for (char c : word)
        {
            if (isalnum((unsigned char)c))
                res += (char)tolower((unsigned char)c);
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
        for (int i = 0; i < (int)words.size(); i++)
        {
            index[words[i]][doc.getId()].push_back(i);
        }
    }

    vector<int> getDoc(const string &word)
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

    int getFrequency(const string &word, int docId)
    {
        auto it = index.find(word);

        if (it == index.end())
            return 0;

        auto jt = it->second.find(docId);

        if (jt == it->second.end())
            return 0;

        return jt->second.size();
    }

    void countFreq(const vector<string> &words)
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

    vector<int> intersection(vector<int> a, vector<int> b)
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

    vector<int> doUnion(vector<int> a, vector<int> b)
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

    vector<int> notFind(const vector<int> &docs,
                        const vector<Document> &documents)
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

int precedence(string op)
{
    if (op == "or")
        return 1;

    if (op == "and")
        return 2;

    return -1;
}

bool isOperand(string token)
{
    return token != "and" &&
           token != "or" &&
           token != "(" &&
           token != ")";
}

QueryNode *buildTree(vector<string> tokens)
{
    stack<QueryNode *> operandStack;
    stack<string> operatorStack;

    auto makeNode = [&]()
    {
        if (operandStack.size() < 2 || operatorStack.empty())
            return;

        string op = operatorStack.top();
        operatorStack.pop();

        QueryNode *right = operandStack.top();
        operandStack.pop();

        QueryNode *left = operandStack.top();
        operandStack.pop();

        QueryNode *root = new QueryNode(op);
        root->left = left;
        root->right = right;

        operandStack.push(root);
    };

    for (auto &token : tokens)
    {
        if (isOperand(token))
        {
            operandStack.push(new QueryNode(token));
        }
        else if (token == "(")
        {
            operatorStack.push(token);
        }
        else if (token == ")")
        {
            while (!operatorStack.empty() && operatorStack.top() != "(")
            {
                makeNode();
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
                makeNode();
            }

            operatorStack.push(token);
        }
    }

    while (!operatorStack.empty())
    {
        makeNode();
    }

    if (operandStack.empty())
        return nullptr;

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

vector<int> phraseSearch(string query,Tokenizer &tokenizer,InvertedIndex &invertedIndex)
{
    vector<string> tokens = tokenizer.tokenize(query);

    if (tokens.empty())
        return {};

    vector<int> docs = invertedIndex.getDoc(tokens[0]);

    for (int i = 1; i < (int)tokens.size(); i++)
    {
        vector<int> currentDocs = invertedIndex.getDoc(tokens[i]);
        docs = invertedIndex.intersection(docs, currentDocs);

        if (docs.empty())
            return {};
    }

    vector<int> answer;

    for (int doc : docs)
    {
        const vector<int> &firstPos =invertedIndex.index[tokens[0]][doc];

        bool found = false;

        for (int start : firstPos)
        {
            bool ok = true;

            for (int i = 1; i < (int)tokens.size(); i++)
            {
                const vector<int> &positions =
                    invertedIndex.index[tokens[i]][doc];

                if (find(positions.begin(),positions.end(),start + i) == positions.end())
                {
                    ok = false;
                    break;
                }
            }

            if (ok)
            {
                found = true;
                break;
            }
        }

        if (found)
            answer.push_back(doc);
    }

    return answer;
}

vector<int> evaluate(QueryNode *root,InvertedIndex &index,Tokenizer &tokenizer)
{
    if (root == nullptr)
        return {};

    if (isOperand(root->value))
    {
        
        if (root->value.find(' ') != string::npos)
            return phraseSearch(root->value, tokenizer, index);

        
        return index.getDoc(root->value);
    }

    vector<int> left = evaluate(root->left, index, tokenizer);
    vector<int> right = evaluate(root->right, index, tokenizer);

    if (root->value == "and")
        return index.intersection(left, right);

    if (root->value == "or")
        return index.doUnion(left, right);

    return {};
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

    for (auto &doc : documents)
{
    cout << doc.getId() << " -> " << doc.getFilename() << endl;
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
    cout << "Enter words to search: ";
    string query;
    getline(cin, query);
    cout << "The words \" " << query << " \"" << " is found in : " << endl;
    
    vector<string> tokens = tokenizer.tokenize(query);
    // for (auto &t : tokens){
    // cout << "[" << t << "] ";
    //  cout << endl;}

    QueryNode *root = buildTree(tokens);
    vector<int> ans = evaluate(root, invertedIndex, tokenizer);

    vector<pair<double,int>> ranked;

    for(int docId : ans)
    {
        double score = 0;

        for(auto &token : tokens)
        {
            if(token=="and" || token=="or" ||
            token=="(" || token==")")
                continue;

            score += getTF(invertedIndex.getFrequency(token, docId),docSize[docId])*getIDF(invertedIndex.docFrequency[token],documents.size());
        }

        ranked.push_back({score, docId});
    }

    sort(ranked.begin(), ranked.end(),
    [](auto &a, auto &b)
    {
        return a.first > b.first;
    });

    cout << "\nRanked Results\n\n";

    for(auto &x : ranked)
    {
        cout << "Doc "<< x.second<< " Score : "<< x.first<< endl;
    }


    
}
