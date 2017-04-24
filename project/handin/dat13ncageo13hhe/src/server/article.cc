#include "article.h"

using namespace std;

Article::Article(const string &title, const string &author, const string &text, const unsigned int id) : m_title(title), m_author(author), m_text(text), m_id(id) {
}

const string& Article::getTitle() const {
    return m_title;
}

const string& Article::getAuthor() const {
    return m_author;
}

const string& Article::getText() const {
    return m_text;
}

unsigned int Article::getId() const {
    return m_id;
}