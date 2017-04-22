#include "commander.h"
#include "protocol.h"
#include "input.h"

#include <iostream>

using namespace std;

void Commander::listNewsgroups() {
    m_packet.addByte(Protocol::COM_LIST_NG);
    m_packet.addByte(Protocol::COM_END);
}

void Commander::createNewsgroup() {
    cout << "Title: ";
    string title = Input::getString();
    
    m_packet.addByte(Protocol::COM_CREATE_NG);
    m_packet.addString(title);
    m_packet.addByte(Protocol::COM_END);
}

void Commander::deleteNewsgroup() {
    cout << "Newsgroup ID: ";
    int id = Input::getInt();
    
    m_packet.addByte(Protocol::COM_DELETE_NG);
    m_packet.addInt(id);
    m_packet.addByte(Protocol::COM_END);
}

void Commander::listArticles() {
    cout << "Newsgroup ID: ";
    int id = Input::getInt();
    
    m_packet.addByte(Protocol::COM_LIST_ART);
    m_packet.addInt(id);
    m_packet.addByte(Protocol::COM_END);
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
    
    m_packet.addByte(Protocol::COM_CREATE_ART);
    m_packet.addInt(id);
    m_packet.addString(title);
    m_packet.addString(author);
    m_packet.addString(text);
    m_packet.addByte(Protocol::COM_END);
}

void Commander::deleteArticle() {
    cout << "Newsgroup ID: ";
    int groupId = Input::getInt();
    
    cout << "Article ID: ";
    int articleId = Input::getInt();
    
    m_packet.addByte(Protocol::COM_DELETE_ART);
    m_packet.addInt(groupId);
    m_packet.addInt(articleId);
    m_packet.addByte(Protocol::COM_END);
}

void Commander::getArticle() {
    cout << "Newsgroup ID: ";
    int groupId = Input::getInt();
    
    cout << "Article ID: ";
    int articleId = Input::getInt();
    
    m_packet.addByte(Protocol::COM_GET_ART);
    m_packet.addInt(groupId);
    m_packet.addInt(articleId);
    m_packet.addByte(Protocol::COM_END);
}

const Packet& Commander::getPacket() const {
    return m_packet;
}

void Commander::clean() {
    m_packet.clean();
}