#include "databasedisk.h"
#include "servererrorexception.h"

#include <algorithm>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;

DatabaseDisk::DatabaseDisk() {    
    string root = "data/";
    struct stat sb;
    
    if(stat(root.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)) {        
        readData();
    }
    
    else {        
        if(mkdir("data/", ACCESSPERMS) != 0) {
            cout << "ERROR: could not create data/ folder. Server will run in-memory.\n";
            
            throw ServerErrorException();
        }
    }
}

void DatabaseDisk::readData() {
    ifstream newsgroupFile("data/newsgroups.txt");
    string temp;
    
    while(getline(newsgroupFile, temp)) {
        string name;
        getline(newsgroupFile, name);
        
        m_newsgroups.push_back(Newsgroup(name, stoi(temp)));
        Newsgroup &newsgroup = m_newsgroups.back();
                
        ifstream articleFile("data/" + temp + "/articles.txt");
        string articleTemp;
        
        while(getline(articleFile, articleTemp)) {
            ifstream currentArticle("data/" + temp + "/" + articleTemp + ".txt");
            string title, author, text, fullText;
                        
            getline(currentArticle, title);
            getline(currentArticle, author);
                        
            while(getline(currentArticle, text)) {
                fullText += text;
                fullText += '\n';
            }         
            
            newsgroup.createArticle(title, author, fullText, stoi(articleTemp));
            
            currentArticle.close();
        }
        
        articleFile.close();
    }
    
    newsgroupFile.close();
    
    m_newsgroupId = m_newsgroups.back().getId() + 1;
}

bool DatabaseDisk::createNewsgroup(const string &name) {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&name] (const Newsgroup &newsgroup) { return newsgroup.getName() == name; });
    
    if(iterator != m_newsgroups.end()) {
        return false;
    }
    
    unsigned int id = m_newsgroupId++;
    m_newsgroups.push_back(Newsgroup(name, id));
            
    string newsgroupPath = "data/" + to_string(id) + "/";
    
    if(mkdir(newsgroupPath.c_str(), ACCESSPERMS) != 0) {
        cout << "Error: newsgroup directory could not be created.\n";
        
        throw ServerErrorException();
    }
    
    ofstream writeArticles("data/" + to_string(id) + "/articles.txt");
    writeArticles.close();
    
    ofstream file("data/newsgroups.txt", ios::app);
    
    file << id << endl;
    file << name << endl;
    
    file.close();
        
    return true;
}

bool DatabaseDisk::deleteNewsgroup(const int id) {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&id] (const Newsgroup &newsgroup) { return newsgroup.getId() == static_cast<unsigned int>(id); });
    
    if(iterator == m_newsgroups.end()) {
        return false;
    }
        
    m_newsgroups.erase(iterator);
    
    if(system(("rm -r data/" + to_string(id)).c_str()) != 0) {
        cout << "Error: system call to remove directory failed.\n";
        
        throw ServerErrorException();
    }
    
    ofstream file("data/newsgroups.txt");
    
    for(const Newsgroup &newsgroup : m_newsgroups) {
        file << newsgroup.getId() << endl;
        file << newsgroup.getName() << endl;
    }
    
    file.close();
    
    return true;
}

void DatabaseDisk::createArticle(Newsgroup *newsgroup, const string &title, const string &author, const string &text) {
    auto newId = newsgroup->createArticle(title, author, text) - 1;
    
    ofstream file("data/" + to_string(newsgroup->getId()) + "/articles.txt", ios::app);
    file << newId << endl;
    file.close();
    
    ofstream articleFile("data/" + to_string(newsgroup->getId()) + "/" + to_string(newId) + ".txt");
    articleFile << title << endl;
    articleFile << author << endl;
    articleFile << text;
    articleFile.close();
}

bool DatabaseDisk::deleteArticle(Newsgroup *newsgroup, const int id) {
    if(!newsgroup->deleteArticle(id)) {
        return false;
    }
    
    if(system(("rm data/" + to_string(newsgroup->getId()) + "/" + to_string(id) + ".txt").c_str()) != 0) {
        cout << "Error: system call to remove file failed.\n";
        
        throw ServerErrorException();
    }
    
    ofstream file("data/" + to_string(newsgroup->getId()) + "/articles.txt");
    
    for(const Article &article : newsgroup->getArticles()) {
        file << article.getId() << endl;
    }
    
    file.close();
    
    return true;
}