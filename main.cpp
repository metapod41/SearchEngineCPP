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

    cout << "Enter words to search : ";

    string query;
    getline(cin, query);


    engine.search(query);
}