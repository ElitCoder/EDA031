#include "process.h"
#include "protocol.h"
#include "databasememory.h"
#include "databasedisk.h"
#include "invalidprotocolexception.h"

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

bool Process::validCommand(const unsigned char command) const {
    return ((command >= Protocol::COM_LIST_NG && command <= Protocol::COM_GET_ART) || (command >= Protocol::ANS_LIST_NG && command <= Protocol::ANS_GET_ART));
}

void Process::process(shared_ptr<Connection> &conn) {
    m_stream.setConnection(conn);
    
    unsigned char command = m_stream.getByte();
    
    if(!validCommand(command)) {
        throw InvalidProtocolException();
    }
    
    cout << "Received command: ";
    
    switch(command) {
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
    
    command = m_stream.getByte();
    
    if(command != Protocol::COM_END) {
        throw InvalidProtocolException();
    }
}

void Process::commandListNewsgroups() {
    auto &newsgroups = m_database->getNewsgroups();
    
    m_stream.addByte(Protocol::ANS_LIST_NG);
    m_stream.addInt(newsgroups.size());
    
    for(const Newsgroup &newsgroup : newsgroups) {
        m_stream.addInt(newsgroup.getId());
        m_stream.addString(newsgroup.getName());
    }
    
    m_stream.addByte(Protocol::ANS_END);
}

void Process::commandCreateNewsgroup() {
    string name = m_stream.getString();
    bool result = m_database->createNewsgroup(name);
        
    m_stream.addByte(Protocol::ANS_CREATE_NG);
    
    if(result) {
        m_stream.addByte(Protocol::ANS_ACK);
    }
    
    else {
        m_stream.addByte(Protocol::ANS_NAK);
        m_stream.addByte(Protocol::ERR_NG_ALREADY_EXISTS);
    }
    
    m_stream.addByte(Protocol::ANS_END);
}

void Process::commandDeleteNewsgroup() {
    int id = m_stream.getInt();
    bool result = m_database->deleteNewsgroup(id);
    
    m_stream.addByte(Protocol::ANS_DELETE_NG);
    
    if(result) {
        m_stream.addByte(Protocol::ANS_ACK);
    }
    
    else {
        m_stream.addByte(Protocol::ANS_NAK);
        m_stream.addByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    
    m_stream.addByte(Protocol::ANS_END);
}

void Process::commandListArticles() {
    int id = m_stream.getInt();
    const Newsgroup *newsgroup = m_database->getNewsgroup(id);
    
    m_stream.addByte(Protocol::ANS_LIST_ART);
    
    if(newsgroup != nullptr) {
        auto &articles = newsgroup->getArticles();
        
        m_stream.addByte(Protocol::ANS_ACK);
        m_stream.addInt(articles.size());
        
        for(const Article &article : articles) {
            m_stream.addInt(article.getId());
            m_stream.addString(article.getTitle());
        }
    }
    
    else {
        m_stream.addByte(Protocol::ANS_NAK);
        m_stream.addByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    
    m_stream.addByte(Protocol::ANS_END);
}

void Process::commandCreateArticle() {
    int id = m_stream.getInt();
    string title = m_stream.getString();
    string author = m_stream.getString();
    string text = m_stream.getString();
    
    Newsgroup *newsgroup = m_database->getNewsgroup(id);
    
    m_stream.addByte(Protocol::ANS_CREATE_ART);
    
    if(newsgroup != nullptr) {
        m_database->createArticle(newsgroup, title, author, text);
        
        m_stream.addByte(Protocol::ANS_ACK);
    }
    
    else {
        m_stream.addByte(Protocol::ANS_NAK);
        m_stream.addByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    
    m_stream.addByte(Protocol::ANS_END);
}

void Process::commandGetArticle() {
    int groupId = m_stream.getInt();
    int articleId = m_stream.getInt();
    
    const Newsgroup *newsgroup = m_database->getNewsgroup(groupId);
        
    m_stream.addByte(Protocol::ANS_GET_ART);
    
    if(newsgroup != nullptr) {
        const Article *article = newsgroup->getArticle(articleId);
        
        if(article != nullptr) {
            m_stream.addByte(Protocol::ANS_ACK);
            m_stream.addString(article->getTitle());
            m_stream.addString(article->getAuthor());
            m_stream.addString(article->getText());
        }
        
        else {
            m_stream.addByte(Protocol::ANS_NAK);
            m_stream.addByte(Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    }
    
    else {
        m_stream.addByte(Protocol::ANS_NAK);
        m_stream.addByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    
    m_stream.addByte(Protocol::ANS_END);
}

void Process::commandDeleteArticle() {
    int groupId = m_stream.getInt();
    int articleId = m_stream.getInt();
    
    Newsgroup *newsgroup = m_database->getNewsgroup(groupId);
    
    m_stream.addByte(Protocol::ANS_DELETE_ART);
    
    if(newsgroup != nullptr) {
        bool result = m_database->deleteArticle(newsgroup, articleId);
        
        if(result) {
            m_stream.addByte(Protocol::ANS_ACK);
        }
        
        else {
            m_stream.addByte(Protocol::ANS_NAK);
            m_stream.addByte(Protocol::ERR_ART_DOES_NOT_EXIST);
        }
    }
    
    else {
        m_stream.addByte(Protocol::ANS_NAK);
        m_stream.addByte(Protocol::ERR_NG_DOES_NOT_EXIST);
    }
    
    m_stream.addByte(Protocol::ANS_END);
}