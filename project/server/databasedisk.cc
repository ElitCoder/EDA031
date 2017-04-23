#include "databasedisk.h"

#include <algorithm>
#include <sys/stat.h>
#include <iostream>
#include <fstream>

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
        }
    }
}

void DatabaseDisk::readData() {
    ifstream newsgroupFile("newsgroups.txt");
    int id;
    
    while(newsgroupFile >> id) {
        string name;
        getline(newsgroupFile, name);
        
        m_newsgroups.push_back(Newsgroup(name, id));
        Newsgroup &newsgroup = m_newsgroups.back();

        ifstream articleFile(to_string(id) + "/articles.txt");
        int articleId;
        
        while(articleFile >> articleId) {
            ifstream currentArticle(to_string(id) + "/" + to_string(articleId) + ".txt");
            string title, author, text, fullText;
            
            getline(currentArticle, title);
            getline(currentArticle, author);
            
            while(getline(currentArticle, text)) {
                fullText += text;
                fullText += '\n';
            }           
            
            newsgroup.createArticle(title, author, fullText);
            
            currentArticle.close();
        }
        
        articleFile.close();
    }
    
    newsgroupFile.close();
}

bool DatabaseDisk::createNewsgroup(const string &name) {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&name] (const Newsgroup &newsgroup) { return newsgroup.getName() == name; });
    
    if(iterator != m_newsgroups.end()) {
        return false;
    }
    
    m_newsgroups.push_back(Newsgroup(name, ++m_newsgroupId));
    
    return true;
}

bool DatabaseDisk::deleteNewsgroup(const int id) {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&id] (const Newsgroup &newsgroup) { return newsgroup.getId() == static_cast<unsigned int>(id); });
    
    if(iterator == m_newsgroups.end()) {
        return false;
    }
    
    m_newsgroups.erase(iterator);
    
    return true;
}

void DatabaseDisk::createArticle(Newsgroup *newsgroup, const string &title, const string &author, const string &text) {
    newsgroup->createArticle(title, author, text);
}

bool DatabaseDisk::deleteArticle(Newsgroup *newsgroup, const int id) {
    return newsgroup->deleteArticle(id);
}