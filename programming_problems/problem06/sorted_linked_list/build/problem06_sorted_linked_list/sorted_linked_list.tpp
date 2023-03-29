#include "sorted_linked_list.hpp"
#include <stdexcept>
#include <vector>
#include <algorithm>


template <typename T>
SortedLinkedList<T>::SortedLinkedList(): LinkedList<T>()
{
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(LinkedList<T> unsorted_list) 
{
  std::vector<T> vecList;
  for (int i = 0; i < unsorted_list.getLength(); i++) {
    vecList.push_back(unsorted_list.getEntry(i));
  }
  std::sort(vecList.begin(), vecList.begin() + vecList.size());
  for (int i = 0; i < vecList.size(); i++) {
    LinkedList<T>::insert(i, vecList[i]);
  }
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> & x):
  LinkedList<T>(x)
{
}

template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(SortedLinkedList<T> x)
{
  LinkedList<T>::operator=(x);
  return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty() const noexcept
{
  return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength() const noexcept
{
  return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T& item)
{
  if (isEmpty()) {
    LinkedList<T>::insert(0, item);

  } else {
    int idx = 0;
    while (idx < getLength() && item > getEntry(idx)) {
      idx++;
    }
    LinkedList<T>::insert(idx, item);
  }
}

template <typename T>
void SortedLinkedList<T>::remove(const T& item)
{
  if(isEmpty()) throw std::range_error("empty list in remove");
  bool exists = 0;
  int idx = -1;
  for (int i = 0; i < getLength()-1; i++) {
    if (getEntry(i) == item) {
      exists = 1;
      idx = i;
    }
  }
  if (!exists) {
    throw std::range_error("does not exist");
  } else {
    LinkedList<T>::remove(idx);
  }
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
  if(isEmpty() || position < 0 || position >= getLength()) {
    throw std::range_error("bad!");
  }

  LinkedList<T>::remove(position);
  
  // TODO
}

template <typename T>
void SortedLinkedList<T>::clear()
{
  LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position) const
{
  if(isEmpty() || position < 0 || position >= getLength()) {
    throw std::range_error("bad!");
  }
  return LinkedList<T>::getEntry(position);
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T& item)
{
  if (isEmpty()) {
    return -1;
  }
  int idx = -1;
  for (int i = 0; i < getLength(); i++) {
    if (getEntry(i) == item) {
      idx = i;
      return idx;
    }
  }
  return idx;
}