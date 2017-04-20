#include "databasememory.h"

using namespace std;

DatabaseMemory::DatabaseMemory() : m_currentId(0) {
}

void DatabaseMemory::addNewsgroup(const string &name) {
    m_newsgroups.push_back(Newsgroup(name, ++m_currentId));
}

const vector<Newsgroup>& DatabaseMemory::getNewsgroups() const {
    return m_newsgroups;
} 

bool DatabaseMemory::createNewsgroup(const std::string &name) {
    return false;
    
    //TODO
}