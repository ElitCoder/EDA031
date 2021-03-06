#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>

class Word {
public:
	/* Creates a word w with the sorted trigrams t */
	Word(const std::string& w, const std::vector<std::string>& t);

	Word(const std::string &w);

	/* Returns the word */
	std::string get_word() const;

	/* Returns how many of the trigrams in t that are present
	 in this word's trigram vector */
	unsigned int get_matches(const std::vector<std::string>& t) const;
	bool qualify_trigrams(const Word &word) const;
private:
	std::string m_word;
	std::vector<std::string> m_trigrams;
};

#endif
