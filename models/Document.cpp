#include "Document.h"

Document::Document(int id, const string &filename, const string &content)
{
    this->id = id;
    this->filename = filename;
    this->content = content;
}

int Document::getId() const
{
    return id;
}

const string &Document::getFilename() const
{
    return filename;
}

const string &Document::getContent() const
{
    return content;
}