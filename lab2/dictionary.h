#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "word.h"

#include <string>
#include <vector>
#include <unordered_set>

class Dictionary {
public:
	Dictionary();
	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
private:
	std::vector<Word> m_words[25];
};

#endif
