#include "bitreference.h"
#include "bitset.h"

BitReference& BitReference::operator=(bool b) {
	//
	// *** IMPLEMENT ***
	// This corresponds to the set() function in SimpleBitset.
	//

	if (b) {
		*p_bits |= 1L << pos;
	} else {
		*p_bits &= ~ (1L << pos);
	}

	return *this;
}

BitReference::operator bool() const {
	//
	// *** IMPLEMENT ***
	// This corresponds to the get() function in SimpleBitset.
	//

	return (*p_bits & (1L << pos)) != 0;
}
