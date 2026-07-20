#include "Tokenizer.h"

vector<string> Tokenizer::tokenize(const string &text)
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
    {
        words.push_back(toLowerCase(word));
    }

    return words;
}

string Tokenizer::toLowerCase(string word) const
{
    for (char &c : word)
    {
        c = (char)tolower((unsigned char)c);
    }

    return word;
}

string Tokenizer::removePunctuation(string word)
{
    string res;

    for (char c : word)
    {
        if (isalnum((unsigned char)c))
        {
            res += (char)tolower((unsigned char)c);
        }
    }

    return res;
}