#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {
public:
    Article(const std::string &title, const std::string &author, const std::string &text, const unsigned int id);
    
    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    const std::string& getText() const;
    unsigned int getId() const;
    
private:
    std::string m_title, m_author, m_text;
    unsigned int m_id;
};

#endif