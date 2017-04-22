#include "process.h"
#include "protocol.h"
#include "databasememory.h"
#include "databasedisk.h"

#include <iostream>

using namespace std;

Process::Process(const bool databaseType) {
    if(databaseType) {
        m_database = new DatabaseMemory();
    }
    
    else {
        m_database = new DatabaseDisk();
    }
}

Process::~Process() {
    delete m_database;
}

Packet& Process::process(Packet &packet) {
    m_currentPacket = &packet;
    m_response.clean();
    
    cout << "Received command: ";
    
    switch(packet.getHeader()) {
        case Protocol::COM_LIST_NG: 
                cout << "COM_LIST_NG.\n";
                commandListNewsgroups();
            break;
            
        case Protocol::COM_CREATE_NG:
                cout << "COM_CREATE_NG.\n";
                commandCreateNewsgroup();
            break;
                
        case Protocol::COM_DELETE_NG:
                cout << "COM_DELETE_NG.\n";
                commandDeleteNewsgroup();
            break;
            
        case Protocol::COM_LIST_ART: 
                cout << "COM_LIST_ART.\n";
                commandListArticles();
            break;    
            
        case Protocol::COM_CREATE_ART:
                cout << "COM_CREATE_ART.\n";
                commandCreateArticle();
            break;
            
        case Protocol::COM_GET_ART:
                cout << "COM_GET_ART.\n";
                commandGetArticle();
            break;
            
        case Protocol::COM_DELETE_ART:
                cout << "COM_DELETE_ART.\n";
                commandDeleteArticle();
            break;
    }
    
    return m_response;
}

void Process::commandListNewsgroups() {
    auto &newsgroups = m_database->getNewsgroups();
    
    m_response.addByte(Protocol::ANS_LIST_NG);
    m_response.addInt(newsgroups.size());
    
    for(const Newsgroup &newsgroup : newsgroups) {
        m_response.addInt(newsgroup.getId());
        m_response.addString(newsgroup.getName());
    }
    
    m_response.addByte(Protocol::ANS_END);
}

void Process::commandCreateNewsgroup() {
    string name = m_currentPacket->getString();
    bool result = m_database->createNewsgroup(name);
        
    m_response.addByte(Protocol::ANS_CREATE_NG);
    
    if(result) {
        m_response.addByte(Protocol::ANS_ACK);
    }
    
    else {
        m_response.addByte(Protocol::ANS_NAK);
        m_response.addByte(Protocol::ERR_NG_ALREADY_EXISTS);
    }
    
    m_response.addByte(Protocol::ANS_END);
}

void Process::commandDeleteNewsgroup() {
    int id = m_currentPacket->getInt();
    bool result = m_database->deleteNewsgroup(id);
    
    m_response.addByte(Protocol::ANS_DELETE_NG);
    
    if(result) {
        m_response.addByte(Protocol::ANS_ACK);
    }
    
    else {
        m_response.addByte(Protocol::ANS_NAK);
        m_response.addByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    
    m_response.addByte(Protocol::ANS_END);
}

void Process::commandListArticles() {
    int id = m_currentPacket->getInt();
    const Newsgroup *newsgroup = m_database->getNewsgroup(id);
    
    m_response.addByte(Protocol::ANS_LIST_ART);
    
    if(newsgroup != nullptr) {
        auto &articles = newsgroup->getArticles();
        
        m_response.addByte(Protocol::ANS_ACK);
        m_response.addInt(articles.size());
        
        for(const Article &article : articles) {
            m_response.addInt(article.getId());
            m_response.addString(article.getTitle());
        }
    }
    
    else {
        m_response.addByte(Protocol::ANS_NAK);
        m_response.addByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    
    m_response.addByte(Protocol::ANS_END);
}

void Process::commandCreateArticle() {
    int id = m_currentPacket->getInt();
    string title = m_currentPacket->getString();
    string author = m_currentPacket->getString();
    string text = m_currentPacket->getString();
    
    Newsgroup *newsgroup = m_database->getNewsgroup(id);
    
    m_response.addByte(Protocol::ANS_CREATE_ART);
    
    if(newsgroup != nullptr) {
        m_database->createArticle(newsgroup, title, author, text);
        
        m_response.addByte(Protocol::ANS_ACK);
    }
    
    else {
        m_response.addByte(Protocol::ANS_NAK);
        m_response.addByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    
    m_response.addByte(Protocol::ANS_END);
}

void Process::commandGetArticle() {
    int groupId = m_currentPacket->getInt();
    int articleId = m_currentPacket->getInt();
    
    const Newsgroup *newsgroup = m_database->getNewsgroup(groupId);
        
    m_response.addByte(Protocol::ANS_GET_ART);
    
    if(newsgroup != nullptr) {
        const Article *article = newsgroup->getArticle(articleId);
        
        if(article != nullptr) {
            m_response.addByte(Protocol::ANS_ACK);
            m_response.addString(article->getTitle());
            m_response.addString(article->getAuthor());
            m_response.addString(article->getText());
        }
        
        else {
            m_response.addByte(Protocol::ANS_NAK);
            m_response.addByte(Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    }
    
    else {
        m_response.addByte(Protocol::ANS_NAK);
        m_response.addByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    
    m_response.addByte(Protocol::ANS_END);
}

void Process::commandDeleteArticle() {
    int groupId = m_currentPacket->getInt();
    int articleId = m_currentPacket->getInt();
    
    Newsgroup *newsgroup = m_database->getNewsgroup(groupId);
    
    m_response.addByte(Protocol::ANS_DELETE_ART);
    
    if(newsgroup != nullptr) {
        bool result = m_database->deleteArticle(newsgroup, articleId);
        
        if(result) {
            m_response.addByte(Protocol::ANS_ACK);
        }
        
        else {
            m_response.addByte(Protocol::ANS_NAK);
            m_response.addByte(Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    }
    
    else {
        m_response.addByte(Protocol::ANS_NAK);
        m_response.addByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    
    m_response.addByte(Protocol::ANS_END);
}