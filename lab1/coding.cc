#include "coding.h"

unsigned char Coding::encode(unsigned char c) {
    return ~c;
}

unsigned char Coding::decode(unsigned char c) {
    return ~c;
}