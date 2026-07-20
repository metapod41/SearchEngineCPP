#include "search/SearchEngine.h"

int main()
{
    SearchEngine engine;

    engine.loadDocuments("../data");

    engine.buildIndex();

    cout << "Enter words to search : ";

    string query;

    getline(cin, query);

    engine.search(query);
}