#include "process.h"
#include "protocol.h"

#include <iostream>

using namespace std;

Process::Process(shared_ptr<Connection> &conn) {
    m_stream.setConnection(conn);
}

void Process::process() {    
    switch(m_stream.getByte()) {
        case Protocol::ANS_LIST_NG: listNewsgroups();
            break;
            
        case Protocol::ANS_CREATE_NG: createNewsgroup();
            break;
            
        case Protocol::ANS_DELETE_NG: deleteNewsgroup();
            break;
            
        case Protocol::ANS_LIST_ART: listArticles();
            break;
            
        case Protocol::ANS_CREATE_ART: createArticle();
            break;
            
        case Protocol::ANS_DELETE_ART: deleteArticle();
            break;
            
        case Protocol::ANS_GET_ART: getArticle();
            break;
            
        default: cerr << "\n\n ** NOT IMPLEMENTED **\n\n";
    }
    
    m_stream.getByte();
}

void Process::listNewsgroups() {
    cout << "Newsgroups:\n";
    
    int nbrGroups = m_stream.getInt();
    
    for(int i = 0; i != nbrGroups; ++i) {
        int id = m_stream.getInt();
        string title = m_stream.getString();
        
        cout << id << ". " << title << endl;
    }
}

void Process::createNewsgroup() {
    unsigned char answer = m_stream.getByte();
    
    if(answer == Protocol::ANS_ACK) {
        cout << "Newsgroup was created!";
    }
    
    else {
        answer = m_stream.getByte();
        
        switch(answer) {
            case Protocol::ERR_NG_ALREADY_EXISTS: cout << "Error: newsgroup does already exist.";
                break;
                
            default: cout << "Unknown error code (" << answer << ").";
        }
    }
    
    cout << endl;
}

void Process::deleteNewsgroup() {
    unsigned char answer = m_stream.getByte();
    
    if(answer == Protocol::ANS_ACK) {
        cout << "Newsgroup deleted!";
    }
    
    else {
        answer = m_stream.getByte();
        
        switch(answer) {
            case Protocol::ERR_NG_DOES_NOT_EXIST: cout << "Error: newsgroup does not exist.";
                break;
                
            default: cout << "Unknown error code (" << answer << ").";
        }
    }
    
    cout << endl;
}

void Process::listArticles() {
    unsigned char answer = m_stream.getByte();
    
    if(answer == Protocol::ANS_NAK) {
        answer = m_stream.getByte();
        
        switch(answer) {
            case Protocol::ERR_NG_DOES_NOT_EXIST: cout << "Error: newsgroup does not exist.";
                break;
                
            default: cout << "Unknown error code (" << answer << ").";
        }
        
        cout << endl;
        return;
    }
    
    cout << "Articles:\n";
    
    int nbrArticles = m_stream.getInt();
    
    for(int i = 0; i != nbrArticles; ++i) {
        int id = m_stream.getInt();
        string title = m_stream.getString();
        
        cout << id << ". " << title << endl;
    }
    
    cout << endl;
}

void Process::createArticle() {
    unsigned char answer = m_stream.getByte();
    
    if(answer == Protocol::ANS_ACK) {
        cout << "Article was created!\n";
    }
    
    else {
        answer = m_stream.getByte();
        
        switch(answer) {
            case Protocol::ERR_NG_DOES_NOT_EXIST: cout << "Error: newsgroup does not exist.";
                break;
                
            default: cout << "Unknown error code (" << answer << ").";
        }
        
        cout << endl;
    }
}

void Process::deleteArticle() {
    unsigned char answer = m_stream.getByte();
    
    if(answer == Protocol::ANS_ACK) {
        cout << "Article was deleted!\n";
    }
    
    else {
        answer = m_stream.getByte();
        
        switch(answer) {
            case Protocol::ERR_NG_DOES_NOT_EXIST: cout << "Error: newsgroup does not exist.";
                break;
                
            case Protocol::ERR_ART_DOES_NOT_EXIST: cout << "Error: article does not exist.";
                break;
                
            default: cout << "Unknown error code (" << answer << ").";
        }
        
        cout << endl;
    }
}

void Process::getArticle() {
    unsigned char answer = m_stream.getByte();
    
    if(answer == Protocol::ANS_NAK) {
        answer = m_stream.getByte();
        
        switch(answer) {
            case Protocol::ERR_NG_DOES_NOT_EXIST: cout << "Error: newsgroup does not exist.";
                break;
                
            case Protocol::ERR_ART_DOES_NOT_EXIST: cout << "Error: article does not exist.";
                break;
                
            default: cout << "Unknown error code (" << answer << ").";
        }
        
        cout << endl;
        return;
    }
    
    cout << endl;
    
    string title = m_stream.getString();
    string author = m_stream.getString();
    string text = m_stream.getString();
    
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << endl << text << endl;
}