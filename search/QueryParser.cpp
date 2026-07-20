#include "QueryParser.h"

QueryNode::QueryNode(string value)
{
    this->value = value;
    left = nullptr;
    right = nullptr;
}

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

void printTree(QueryNode *root)
{
    if (root == nullptr)
    {
        return;
    }

    cout << root->value << endl;

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
        const vector<int> &firstPos =
            invertedIndex.index[tokens[0]][doc];

        bool found = false;

        for (int start : firstPos)
        {
            bool ok = true;

            for (int i = 1; i < (int)tokens.size(); i++)
            {
                const vector<int> &positions =
                    invertedIndex.index[tokens[i]][doc];

                if (find(positions.begin(),
                         positions.end(),
                         start + i) == positions.end())
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
            return phraseSearch(root->value,tokenizer,index);

        return index.getDoc(root->value);
    }

    vector<int> left =
        evaluate(root->left,index,tokenizer);

    vector<int> right =
        evaluate(root->right,index,tokenizer);

    if (root->value == "and")
        return index.intersection(left, right);

    if (root->value == "or")
        return index.doUnion(left, right);

    return {};
}