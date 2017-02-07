#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "word.h"

#include <string>
#include <vector>
#include <unordered_set>
//#include <utility>

enum WORD_LENGTH_MAX {
	WORD_LENGTH_MAX = 25
};

class Dictionary {
public:
	Dictionary();

	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
private:
	void add_trigram_suggestions(std::vector<std::string> &suggestions, const std::string &word) const;
	std::vector<std::pair<int, std::string>> rank_suggestions(std::vector<std::string> &suggestions, const std::string &word) const;
	std::vector<std::string> trim_suggestions(std::vector<std::pair<int, std::string>> &distances) const;

	std::vector<Word> m_words[WORD_LENGTH_MAX];
};

#endif
