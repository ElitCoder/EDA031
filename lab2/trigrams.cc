#include "trigrams.h"

#include <vector>
#include <fstream>
#include <iostream>

void readWords(const std::string &filename, std::vector<Word> &words) {
    std::ifstream in(filename);

    if(!in) {
        std::cout << "Could not open file\n";

        return;
    }

    std::string temp;

    while(getline(in, temp)) {
        std::cout << "Reading word: " << temp << '\n';

        Word word(temp);
        words.push_back(temp);
    }

    in.close();
}

int main() {
    const std::string filename = "words";
    std::vector<Word> words;

    readWords(filename, words);

    return 0;
}
