#include "morsecode.h"

#include <fstream>
#include <sstream>

using namespace std;

MorseCode::MorseCode() {
}

string MorseCode::encode(const string& text) const {
	istringstream iss(text);

	string output;
	unsigned char temp;

	while(iss >> temp) {

	}
}

string getMorse(unsigned char c) {
	switch(c) {
		case 'a': return ".-";
		case 'b': return ".-";
		case 'c': return ".-";
		case 'd': return ".-";
		case 'e': return ".-";
		case 'f': return ".-";
		case 'g': return ".-";
		case 'h': return ".-";
		case 'i': return ".-";
		case 'j': return ".-";
		case 'k': return ".-";
		case 'a': return ".-";
		case 'a': return ".-";
		case 'a': return ".-";
		case 'a': return ".-";
		case 'a': return ".-";
		case 'a': return ".-";
		case 'a': return ".-";
		case 'a': return ".-";

		b	-...
		c	-.-.
		d	-..
		e	.
		f	..-.
		g	--.
		h	....
		i	..
		j	.---
		k	-.-
		l	.-..
		m	--
		n	-.
		o	---
		p	.--.
		q	--.-
		r	.-.
		s	...
		t	-
		u	..-
		v	...-
		w	.--
		x	-..-
		y	-.--
		z	--..

	}
}

string MorseCode::decode(const string& code) const {
	return "";
}
