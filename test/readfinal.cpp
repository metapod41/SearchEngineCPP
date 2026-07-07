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

class Tokenizer{
    public:

    vector<string> tokenize(const string& text){
        vector<string> words;
        string word;
        stringstream ss(text);
        while(ss>>word){
            string lower = toLowerCase(word);
            string punctuation = removePunctuation(lower);
            if(!punctuation.empty()){
            words.push_back(punctuation);
            }
        }
        return words;
    }

    string toLowerCase(string word) const{
        string res = "";
        for(auto& w:word){
            res+=tolower(w);
        }
        return res;
    }

    string removePunctuation(string word){
        string res = "";
        for(auto& c:word){
            if(isalnum(c)){
                res+=c;
            }
        }
        return res;
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
    Tokenizer tokenizer;
    for(auto &doc:documents){
        vector<string> words = tokenizer.tokenize(doc.getContent());

        for(auto& w:words){
            cout<<w<<"\n";
        }
    }
}


