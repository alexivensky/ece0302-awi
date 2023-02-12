#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  head = nullptr;
  size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  delete head;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  //TODO
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> x)
{
  //TODO
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList& x) 
{
  //TODO
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  return (size == 0 ? 1 : 0);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  if (position > size || position < 0) {
    return false;
  }
  
  
  return true;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  //TODO
  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  //TODO
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  //TODO
  return T();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
}
