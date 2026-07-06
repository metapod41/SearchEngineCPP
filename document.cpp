#include<bits/stdc++.h>
using namespace std;

class Document{
    private:
    int id;
    string filename;
    string content;

    public:
    Document(int id , const string&  filename , const string& content) : id(id) , filename(filename) , content(content){}

    int getId() const{
        return id;
    }

    const string& getFilename() const{
        return filename;
    }

    const string& getContent() const{
        return content;
    }
};

int main()
{
    Document doc(1, "notes.txt", "Hello Search Engine");

    cout << doc.getId() << endl;
    cout << doc.getFilename() << endl;
    cout << doc.getContent() << endl;
}