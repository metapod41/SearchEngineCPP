#include "SearchEngine.h"

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

void SearchEngine::loadDocuments(string folder)
{
    documents.clear();

    int id = 0;

    for (auto &entry : filesystem::directory_iterator(folder))
    {
        if (entry.path().extension() == ".txt")
        {
            string filename = entry.path().filename().string();

            ifstream file(entry.path());

            if (file)
            {
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
}

void SearchEngine::buildIndex()
{
    clearIndex();
    for (auto &doc : documents)
    {
        vector<string> words = tokenizer.tokenize(doc.getContent());

        documentWords[doc.getId()] = words;

        docSize[doc.getId()] = words.size();

        invertedIndex.addDocument(doc, words);

        invertedIndex.countFreq(words);

        unordered_set<string> uniqueWords(words.begin(), words.end());

        for (auto &word : uniqueWords)
        {
            trie.insert(word);
        }
    }
}

void SearchEngine::search(string query)
{
    query = fuzzySearch.correctQuery(query,
                                 trie,
                                 invertedIndex);
    auto suggestions = trie.autocompleteQuery(query);

    if (!suggestions.empty())
    {
        cout << "Did you mean:\n";

        for (auto &word : suggestions)
        {
            cout << word << endl;
        }
    }

    cout << endl;

    vector<string> tokens = tokenizer.tokenize(query);

    QueryNode *root = buildTree(tokens);

    vector<int> ans = evaluate(root,invertedIndex,tokenizer);

    vector<pair<double, int>> ranked;

    for (int docId : ans)
    {
        double score = 0;

        unordered_set<string> uniqueTerms;

        for (auto &token : tokens)
        {
            if (token == "and" ||
                token == "or" ||
                token == "(" ||
                token == ")")
            {
                continue;
            }

            uniqueTerms.insert(token);
        }

        for (auto &term : uniqueTerms)
        {
            score += getTF(invertedIndex.getFrequency(term, docId),docSize[docId]) *getIDF(invertedIndex.docFrequency[term],documents.size());
        }

        ranked.push_back({score, docId});
    }

    sort(ranked.begin(),
         ranked.end(),
         [](auto &a, auto &b)
         {
            return a.first > b.first;
         });

    cout << "\nRanked Results\n\n";

    for (auto &x : ranked)
    {
        cout << documents[x.second - 1].getFilename()
     << " | Score : "
     << fixed << setprecision(3)
     << x.first
     << endl;
    }

    cout << endl;

    for (auto &doc : ranked)
    {
        int first = snippet.findFirstOccurrence(tokens,doc.second,invertedIndex);

        vector<string> res = snippet.extractSnippet(first,documentWords[doc.second]);

        string output = snippet.highlightSnippet(res,tokens);

        cout << documents[doc.second - 1].getFilename()<< " -> "<< output<< endl;
    }
}

vector<Document> &SearchEngine::getDocuments()
{
    return documents;
}

void SearchEngine::clearIndex()
{
    docSize.clear();
    documentWords.clear();

    invertedIndex.index.clear();
    invertedIndex.docFrequency.clear();

    trie = Trie();
}