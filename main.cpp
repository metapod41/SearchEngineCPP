#include "search/SearchEngine.h"

int main()
{
    SearchEngine engine;

    if (filesystem::exists("backend/uploads") &&
        !filesystem::is_empty("backend/uploads"))
    {
        engine.loadDocuments("backend/uploads");
    }
    else
    {
        engine.loadDocuments("data");
    }

    engine.buildIndex();


    string query;
    getline(cin, query);


    engine.search(query);
}