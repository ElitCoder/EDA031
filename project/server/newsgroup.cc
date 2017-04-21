#include "newsgroup.h"

#include <algorithm>

using namespace std;

Newsgroup::Newsgroup(const string &name, const unsigned int id) : m_name(name), m_id(id), m_articleId(1) {
}

void Newsgroup::createArticle(const string &title, const string &author, const string &text) {
    m_articles.push_back(Article(title, author, text, m_articleId++));
}

unsigned int Newsgroup::getId() const {
    return m_id;
}

const string& Newsgroup::getName() const {
    return m_name;
}

const vector<Article>& Newsgroup::getArticles() const {
    return m_articles;
}

bool Newsgroup::deleteArticle(const int id) {
    auto iterator = find_if(m_articles.begin(), m_articles.end(), [&id] (const Article &article) { return article.getId() == static_cast<unsigned int>(id); });
    
    if(iterator == m_articles.end()) {
        return false;
    } 
    
    m_articles.erase(iterator);
    
    return true;
}