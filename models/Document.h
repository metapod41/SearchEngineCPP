#pragma once

#include <bits/stdc++.h>
using namespace std;

class Document
{
private:
    int id;
    string filename;
    string content;

public:
    Document(int id, const string &filename, const string &content);

    int getId() const;

    const string &getFilename() const;

    const string &getContent() const;
};