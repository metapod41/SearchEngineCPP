#include<bits/stdc++.h>
#include<filesystem>
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



int main(){
    vector<Document> documents;
    int id = 0;
    for(auto &entry : filesystem::directory_iterator("data")){
        if(entry.path().extension()==".txt"){
            string filename = entry.path().filename().string();
            ifstream file(entry.path());
            if(file){
                cout<<"opened!!";
                string content;
                string line;

                while(getline(file,line)){
                    content+=line;
                    content+="\n";
                }

                id++;
                Document obj(id , filename , content);
                documents.push_back(obj);
            }
        }
    }
    for (const auto &doc : documents) {
    cout << "ID: " << doc.getId() << '\n';
    cout << "Filename: " << doc.getFilename() << '\n';
    cout << "Content:\n" << doc.getContent() << '\n';
}
}