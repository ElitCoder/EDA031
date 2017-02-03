#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"

using namespace std;

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
	}

	in.close();
}

bool Dictionary::contains(const string& word) const {
	return true;
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	vector<string> suggestions;
	return suggestions;
}
