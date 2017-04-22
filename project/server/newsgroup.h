#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include "article.h"

#include <string>
#include <vector>

class Newsgroup {
public:
    Newsgroup(const std::string &name, const unsigned int id);
    
    void createArticle(const std::string &title, const std::string &author, const std::string &text);
    bool deleteArticle(const int id);
    
    unsigned int getId() const;
    const std::string& getName() const;
    const std::vector<Article>& getArticles() const;
    const Article* getArticle(const int id) const;
    
private:
    std::string m_name;
    unsigned int m_id;
    unsigned int m_articleId;
    
    std::vector<Article> m_articles;
};

#endif