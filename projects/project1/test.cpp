#include <iostream>
#include "bitset.hpp"
#include "bitset.cpp"

using namespace std;

int main() {
    Bitset b1("010101");
    cout << b1.asString();
}