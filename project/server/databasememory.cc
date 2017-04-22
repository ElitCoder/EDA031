#include "databasememory.h"

#include <algorithm>

using namespace std;

bool DatabaseMemory::createNewsgroup(const string &name) {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&name] (const Newsgroup &newsgroup) { return newsgroup.getName() == name; });
    
    if(iterator != m_newsgroups.end()) {
        return false;
    }
    
    m_newsgroups.push_back(Newsgroup(name, ++m_newsgroupId));
    
    return true;
}

bool DatabaseMemory::deleteNewsgroup(const int id) {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&id] (const Newsgroup &newsgroup) { return newsgroup.getId() == static_cast<unsigned int>(id); });
    
    if(iterator == m_newsgroups.end()) {
        return false;
    }
    
    m_newsgroups.erase(iterator);
    
    return true;
}

void DatabaseMemory::createArticle(Newsgroup *newsgroup, const string &title, const string &author, const string &text) {
    newsgroup->createArticle(title, author, text);
}

bool DatabaseMemory::deleteArticle(Newsgroup *newsgroup, const int id) {
    return newsgroup->deleteArticle(id);
}