#include "databasememory.h"

#include <algorithm>

using namespace std;

const vector<Newsgroup>& DatabaseMemory::getNewsgroups() const {
    return m_newsgroups;
} 

const vector<Article>& DatabaseMemory::getArticles(const int id) const {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&id] (const Newsgroup &newsgroup) { return newsgroup.getId() == static_cast<unsigned int>(id); });
    
    if(iterator == m_newsgroups.end()) {
        return {};
    }
    
    return iterator->getArticles();
}

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

bool DatabaseMemory::newsgroupExists(const int id) {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&id] (const Newsgroup &newsgroup) { return newsgroup.getId() == static_cast<unsigned int>(id); });
    
    return iterator != m_newsgroups.end();
}

bool DatabaseMemory::createArticle(const int id, const string &title, const string &author, const string &text) {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&id] (const Newsgroup &newsgroup) { return newsgroup.getId() == static_cast<unsigned int>(id); });
    
    if(iterator == m_newsgroups.end()) {
        return false;
    }
    
    iterator->createArticle(title, author, text);
    
    return true;
}

const Article* DatabaseMemory::getArticle(const int groupId, const int articleId) const {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&groupId] (const Newsgroup &newsgroup) { return newsgroup.getId() == static_cast<unsigned int>(groupId); });
    
    if(iterator == m_newsgroups.end()) {
        return nullptr;
    }
    
    const Newsgroup &newsgroup = *iterator;
    
    auto articleIterator = find_if(newsgroup.getArticles().begin(), newsgroup.getArticles().end(), [&articleId] (const Article &article) { return article.getId() == static_cast<unsigned int>(articleId); });
    
    if(articleIterator == newsgroup.getArticles().end()) {
        return nullptr;
    }
    
    return &(*articleIterator);
}

bool DatabaseMemory::deleteArticle(const int groupId, const int articleId) {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&groupId] (const Newsgroup &newsgroup) { return newsgroup.getId() == static_cast<unsigned int>(groupId); });
    
    if(iterator == m_newsgroups.end()) {
        return false;
    }
        
    return iterator->deleteArticle(articleId);
}
