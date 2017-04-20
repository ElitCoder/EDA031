#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {
public:
    Article(const std::string &title, const std::string &author, const std::string &text);
    
private:
    std::string m_title, m_author, m_text;
    unsigned int m_id;
};

#endif