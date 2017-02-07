#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <utility>
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
	auto distances = rank_suggestions(suggestions, word);
	suggestions = trim_suggestions(distances);

	return suggestions;
}

void Dictionary::add_trigram_suggestions(vector<string> &suggestions, const string &word) const {
	unsigned short start = word.length() == 1 ? 0 : word.length() - 2;
	unsigned short stop = word.length() == WORD_LENGTH_MAX ? word.length() - 1 : word.length();

	Word misspelled(word);

	for(unsigned short i = start; i < stop; i++) {
		for(unsigned short j = 0; j < m_words[i].size(); j++) {
			const Word &currentWord = m_words[i].at(j);

			if(misspelled.qualify_trigrams(currentWord)) {
				suggestions.push_back(currentWord.get_word());
			}
		}
	}
}

vector<pair<int, string>> Dictionary::rank_suggestions(vector<string> &suggestions, const string &word) const {
	vector<pair<int, string>> distances;

	for(unsigned short x = 0; x < suggestions.size(); x++) {
		const string &suggestion = suggestions.at(x);

		int d[26][26];
		d[0][0] = 0;

		for(unsigned short i = 1; i <= word.length(); i++) {
			d[i][0] = i;
		}

		for(unsigned short i = 1; i <= suggestion.length(); i++) {
			d[0][i] = i;
		}

		for(unsigned short i = 1; i <= word.length(); i++) {
			for(unsigned short j = 1; j <= suggestion.length(); j++) {
				short add(word[i] == suggestion[j] ? 0 : 1);

				d[i][j] = min(d[i - 1][j - 1] + add, min(d[i - 1][j] + 1, d[i][j - 1] + 1));
			}
		}

		distances.push_back(make_pair(d[word.length()][suggestion.length()], suggestion));
	}

	sort(distances.begin(), distances.end());

	return distances;
}

vector<string> Dictionary::trim_suggestions(vector<pair<int, string>> &distances) const {
	vector<string> newSuggestions;
	for(unsigned short i = 0; i < (distances.size() < 5 ? distances.size() : 5); i++){
		cout << "Suggestion: " << distances.at(i).second << " with edit distance " << distances.at(i).first << '\n';

		newSuggestions.push_back(distances.at(i).second);

	}
	return newSuggestions;
}
