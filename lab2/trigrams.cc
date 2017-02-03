#include <fstream>
#include <iostream>
#include <algorithm>

int main() {
    std::ifstream in("words");
    std::ofstream out("words.txt");

    if(!in) {
        std::cout << "Could not open file\n";

        return -1;
    }

    if(!out) {
        std::cout << "Could not open output file\n";

        return -2;
    }

    std::string word;

    while(getline(in, word)) {
        std::cout << "Reading word: " << word << '\n';

        transform(word.begin(), word.end(), word.begin(), ::tolower);

        std::vector<std::string> trigrams;

        short trigramLength = word.length() - 2;

        for(short i = 0; i < trigramLength; i++) {
            std::string trigram = word.substr(i, 3);

            trigrams.push_back(trigram);
        }

        sort(trigrams.begin(), trigrams.end());

        out << word << " " << trigrams.size() << " ";

    	for(const std::string &trigram : trigrams) {
    		out << trigram << " ";
    	}

    	out << '\n';
    }

    out.close();
    in.close();

    return 0;
}
