#include "database.h"

#include <algorithm>

using namespace std;

unsigned int Database::m_newsgroupId = 1;

const vector<Newsgroup>& Database::getNewsgroups() const {
    return m_newsgroups;
}

const Newsgroup* Database::getNewsgroup(const int id) const {
    auto iterator = find_if(m_newsgroups.begin(), m_newsgroups.end(), [&id] (const Newsgroup &newsgroup) { return newsgroup.getId() == static_cast<unsigned int>(id); });
    
    return (iterator == m_newsgroups.end() ? nullptr : iterator);
}