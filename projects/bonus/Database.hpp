
#ifndef _DATABASE_H_
#define _DATABASE_H_

#include "binary_search_tree.hpp"
#include "list.hpp"
#include <vector>

template <typename T>
class Database
{
public:
  Database();

  // determine if the database is empty
  bool isEmpty();

  // return current number of entries
  std::size_t getNumberOfEntries();

  // insert entry 
  bool add(std::string key1, std::string key2, const T& item);

  // remove entry 
  bool remove(std::string key);

  // remove all entries
  void clear();

  // retrieve the value of the entry associated with the input key
  T getValue(std::string key);

  // return true if an entry exists associated with the input key
  bool contains(std::string key);

private:
  struct data_entry {
    std::string key1, key2;
    T item;
  };
  BinarySearchTree<std::string, int> b1, b2;
  List<data_entry> data;
  int size;

  

};

#include "Database.tpp"
#endif // _DATABASE_H_
