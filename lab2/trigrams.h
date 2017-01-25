#ifndef TRIGRAMS_H
#define TRIGRAMS_H

#include <string>
#include <iostream>

class Word {
public:
    Word(const std::string &word) : m_word(word) {
        if(m_word.length() >= 3) {
            std::cout << "Allocing " << m_word.length() - 2 << '\n';

            m_trigrams = new std::string[m_word.length() - 2];

            std::cout << "Finished\n";

            createTrigrams();
        }
    }

    ~Word() {
        if(m_word.length() >= 3) {
            delete[] m_trigrams;
        }
    }

private:
    void createTrigrams() {
        for(unsigned int i = 0; i < m_word.length() - 2; i++) {
            m_trigrams[i] = m_word.substr(i, 3);

            std::cout << "Created trigram: " << m_trigrams[i] << '\n';
        }
    }

    std::string m_word;
    std::string *m_trigrams;
};

#endif
