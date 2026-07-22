#include "FuzzySearch.h"

int FuzzySearch::levenshteinDistance(const string &a,const string &b)
{
    int n = a.size();
    int m = b.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for(int i=0;i<=n;i++)
        dp[i][0]=i;

    for(int j=0;j<=m;j++)
        dp[0][j]=j;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(a[i-1]==b[j-1])
            {
                dp[i][j]=dp[i-1][j-1];
            }
            else
            {
                dp[i][j]=1+min({
                    dp[i-1][j],
                    dp[i][j-1],
                    dp[i-1][j-1]
                });
            }
        }
    }

    return dp[n][m];
}

vector<string> FuzzySearch::generateCandidates(const string &query,Trie &trie,InvertedIndex &index)
{
    vector<string> candidates;

    string prefix=query.substr(0,min(3,(int)query.size()));

    candidates=trie.collectAllWords(prefix);

    if(candidates.empty())
    {
        for(auto &entry:index.index)
        {
            const string &word=entry.first;

            if(abs((int)word.size()-(int)query.size())<=2)
            {
                candidates.push_back(word);
            }
        }
    }

    vector<string> filtered;

    for(auto &word:candidates)
    {
        if(abs((int)word.size()-(int)query.size())<=2)
        {
            filtered.push_back(word);
        }
    }

    return filtered;
}

string FuzzySearch::bestSuggestion(const string &query,const vector<string> &candidates)
{
    int bestDistance=INT_MAX;
    string answer=query;

    for(auto &word:candidates)
    {
        int distance=levenshteinDistance(query,word);

        if(distance<bestDistance)
        {
            bestDistance=distance;
            answer=word;
        }
    }

    
    if(bestDistance>2)
        return query;

    return answer;
}

string FuzzySearch::correctQuery(const string &query,Trie &trie,InvertedIndex &index)
{
    stringstream ss(query);

    string token;

    string result;

    while(ss>>token)
    {
        if(token=="and"||
           token=="or"||
           token=="("||
           token==")")
        {
            if(!result.empty())
                result+=" ";

            result+=token;
            continue;
        }

        vector<string> candidates=
            generateCandidates(token,trie,index);

        string best=
            bestSuggestion(token,candidates);

        if(!result.empty())
            result+=" ";

        result+=best;
    }

    return result;
}