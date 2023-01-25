#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>

class Bitset{
public:

  //default constructor
  Bitset();

  //constructor that takes size as a parameter and sets bitset to array of all zeros with size given
  Bitset(intmax_t size);

  //constructor that sets bitset to string given in parameter if string is valid
  Bitset(const std::string & value);

  //deallocates memory taken by bitset
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  //returns size of bitset
  intmax_t size() const;

  //returns validity of bitset
  bool good() const;

  //sets element at index to 1
  void set(intmax_t index);

  //resets element at index to 0
  void reset(intmax_t index);

  //toggles element at index
  void toggle(intmax_t index);

  //returns true if element at index is 1, otherwise returns 0
  bool test(intmax_t index);

  //returns bitset as std::string
  std::string asString() const;

private:
  intmax_t N; //size of bitset
  int* bitArray; //pointer to start of bitset array
  bool valid = 1; //bool representing validity of the bitset
};

#endif
