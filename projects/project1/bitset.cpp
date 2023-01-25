#include "bitset.hpp"

Bitset::Bitset() {
    bitArray = new int[8];
    N = 8;
    for (int i = 0; i < 8; i++) {
        *(bitArray + i) = 0;
    }
}

Bitset::Bitset(intmax_t size) {
    if (size > 0) { //if size parameter is valid, allocate memory for bitset and set all bits to zero
        bitArray = new int[size];
        N = size;
        for (int i = 0; i < size; i++) {
            *(bitArray + i) = 0;
        }
    } else { valid = 0; } //otherwise, do nothing and make bitset invalid
}

Bitset::Bitset(const std::string & value) {
    int len = value.length(); //sets length to length of string 
    bitArray = new int[len]; //allocates memory for array of correct length
    N = len;
    for (int i = 0; i < len; i++) {
        if (value.at(i) != '0' && value.at(i) != '1') { //if string contains an invalid value, set validity to false
            valid = 0;
            break;
        } else { //if current bit is valid, add it to the Bitset
            *(bitArray + i) = ((value.at(i))-'0');
        }
    }
}

Bitset::~Bitset() {
    delete bitArray;
}

intmax_t Bitset::size() const { return N; }

bool Bitset::good() const { return valid; }

void Bitset::set(intmax_t index) {
    if (index > N-1) {
        valid = 0;
    } else {
        *(bitArray + index) = 1;
    }
}

void Bitset::reset(intmax_t index) {
    if (index > N-1) {
        valid = 0;
    } else {
        *(bitArray + index) = 0;
    }
}

void Bitset::toggle(intmax_t index) {
    if (index > N-1) {
        valid = 0;
    } else {
        *(bitArray + index) = !(*(bitArray + index));
    }
}

bool Bitset::test(intmax_t index) {
    if (index > N-1) {
        valid = 0;
        return 0;
    } else {
        return *(bitArray + index);
    }
}

std::string Bitset::asString() const {
    std::string bitString;
    for (int i = 0; i < N; i++) {
        if (valid) {
            bitString.append(std::to_string(*(bitArray + i)));
        }
    }
    return bitString;
}


