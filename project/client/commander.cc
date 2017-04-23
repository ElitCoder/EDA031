#include "commander.h"
#include "protocol.h"
#include "input.h"

#include <iostream>

using namespace std;

Commander::Commander(shared_ptr<Connection> &conn) {
    m_stream.setConnection(conn);
}

void Commander::listNewsgroups() {
    m_stream.addByte(Protocol::COM_LIST_NG);
    m_stream.addByte(Protocol::COM_END);
}

void Commander::createNewsgroup() {
    cout << "Title: ";
    string title = Input::getString();
    
    m_stream.addByte(Protocol::COM_CREATE_NG);
    m_stream.addString(title);
    m_stream.addByte(Protocol::COM_END);
}

void Commander::deleteNewsgroup() {
    cout << "Newsgroup ID: ";
    int id = Input::getInt();
    
    m_stream.addByte(Protocol::COM_DELETE_NG);
    m_stream.addInt(id);
    m_stream.addByte(Protocol::COM_END);
}

void Commander::listArticles() {
    cout << "Newsgroup ID: ";
    int id = Input::getInt();
    
    m_stream.addByte(Protocol::COM_LIST_ART);
    m_stream.addInt(id);
    m_stream.addByte(Protocol::COM_END);
}

void Commander::createArticle() {
    cout << "Newsgroup ID: ";
    int id = Input::getInt();
    
    cout << "Article title: ";
    string title = Input::getString();
    
    cout << "Article author: ";
    string author = Input::getString();
    
    cout << "Article text: ";
    string text = Input::getString();
    
    m_stream.addByte(Protocol::COM_CREATE_ART);
    m_stream.addInt(id);
    m_stream.addString(title);
    m_stream.addString(author);
    m_stream.addString(text);
    m_stream.addByte(Protocol::COM_END);
}

void Commander::deleteArticle() {
    cout << "Newsgroup ID: ";
    int groupId = Input::getInt();
    
    cout << "Article ID: ";
    int articleId = Input::getInt();
    
    m_stream.addByte(Protocol::COM_DELETE_ART);
    m_stream.addInt(groupId);
    m_stream.addInt(articleId);
    m_stream.addByte(Protocol::COM_END);
}

void Commander::getArticle() {
    cout << "Newsgroup ID: ";
    int groupId = Input::getInt();
    
    cout << "Article ID: ";
    int articleId = Input::getInt();
    
    m_stream.addByte(Protocol::COM_GET_ART);
    m_stream.addInt(groupId);
    m_stream.addInt(articleId);
    m_stream.addByte(Protocol::COM_END);
}