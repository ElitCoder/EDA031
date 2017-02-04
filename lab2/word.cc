#include "word.h"

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

Word::Word(const std::string& w, const std::vector<std::string>& t) : m_word(w), m_trigrams(t) {
}

Word::Word(const std::string &w) {
	m_word = w;

	short trigramLength = w.length() - 2;

	for(short i = 0; i < trigramLength; i++) {
		std::string trigram = w.substr(i, 3);

		m_trigrams.push_back(trigram);
	}

	sort(m_trigrams.begin(), m_trigrams.end());
}

string Word::get_word() const {
	return m_word;
}

unsigned int Word::get_matches(const vector<string>& t) const {
	short matches(0);

	for(unsigned short i = 0; i < t.size(); i++) {
		for(unsigned short j = 0; j < m_trigrams.size(); j++) {
			if(m_trigrams.at(j) > t.at(i)) { // Alphabetically sorted, everything after can't match
				break;
			}

			if(m_trigrams.at(j) == t.at(i)) {
				matches++;
			}
		}
	}

	return matches;
}

bool Word::qualify_trigrams(const Word &word) const {
	return get_matches(word.m_trigrams) >= m_trigrams.size() / 2;
}
