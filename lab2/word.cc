#include "word.h"

#include <string>
#include <vector>

using namespace std;

Word::Word(const std::string& w, const std::vector<std::string>& t) : m_word(w), m_trigrams(t) {
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
