#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"

using namespace std;

bool compareWord(const Word &word1, const Word &word2) {
	return word1.get_word() < word2.get_word();
}

Dictionary::Dictionary() {
	ifstream in("words.txt");

	if(!in) {
		cout << "words.txt could not be opened\n";

		return;
	}

	std::string word;

	while(in >> word) {
		short nbrTrigrams;
		in >> nbrTrigrams;

		std::vector<std::string> trigrams;

		for(short i = 0; i < nbrTrigrams; i++) {
			std::string trigram;
			in >> trigram;

			trigrams.push_back(trigram);
		}

		Word w(word, trigrams);
		m_words[word.length() - 1].push_back(w);
	}

	for(unsigned short i = 0; i < WORD_LENGTH_MAX; i++) {
		sort(m_words[i].begin(), m_words[i].end(), compareWord);
	}

	in.close();
}

bool Dictionary::contains(const string& word) const {
	for(unsigned short i = 0; i < m_words[word.length() - 1].size(); i++) {
		const std::string &currentString = m_words[word.length() - 1].at(i).get_word();

		if(word < currentString) {
			return false;
		}

		if(word == currentString) {
			return true;
		}
	}

	return false;
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;

	add_trigram_suggestions(suggestions, word);

	return suggestions;
}

void Dictionary::add_trigram_suggestions(vector<string> &suggestions, const string &word) const {
	unsigned short start = word.length() == 1 ? 0 : word.length() - 2;
	unsigned short stop = word.length() == WORD_LENGTH_MAX ? word.length() - 1 : word.length();

	Word misspelled(word);

	for(unsigned short i = start; i < stop; i++) {
		for(unsigned short j = 0; j < m_words[i].size(); j++) {
			const Word &currentWord = m_words[i].at(j);

			if(currentWord.get_word().length() >= word.length() - 1 && currentWord.get_word().length() <= word.length() + 1) {
				if(misspelled.qualify_trigrams(currentWord)) {
					suggestions.push_back(currentWord.get_word());
				}
			}
		}
	}
}

void Dictionary::rank_suggestions(vector<string> &suggestions, string &word) const {
	int i = 1, j = 1;

	int d[26][26];
	d[i][0] = i;
	d[0][j] = j;

	for(; i < 26; i++) {
		for(; j < 26; j++) {
			d[i][j] = min()
		}
	}
}
