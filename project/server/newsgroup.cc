#include "newsgroup.h"

using namespace std;

Newsgroup::Newsgroup(const string &name, const unsigned int id) : m_name(name), m_id(id) {
}

unsigned int Newsgroup::getId() const {
    return m_id;
}

const string& Newsgroup::getName() const {
    return m_name;
}