#include "limited_size_bag.hpp"

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() {
  size = 0;
  bagArray = new T [size];
}
  
template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  if (size <= maxsize) {
    int newSize = size + 1;
    T *newArray = new T[newSize];
    for (int i = 0; i < size; i++)
    {
      *(newArray + i) = *(bagArray + i);
    }
    *(newArray + size) = item;
    bagArray = newArray;
    size = newSize;
  }
  if (*(bagArray + size) == item)
  {
    return true;
  }
  return false;
}

template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  int c = 0; // counting instances of object in old array
  for (int i = 0; i < size; i++)
  {
    if (*(bagArray + i) == item)
    {
      c++; // :)
    }
  }
  size -= c;
  T *newArray = new T[size];
  for (int i = 0; i < size; i++)
  {
    if (*(bagArray + i) != item)
    {
      *(newArray + i - c) = *(bagArray + i);
    }
  }
  bagArray = newArray;
  if (c == 0)
  {
    return false;
  }
  return true;
}

template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  if (size == 0)
  {
    return true;
  }
  return false;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return size;
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  for (int i = 0; i < size; i++)
  {
    if (*(bagArray + i) == item)
    {
      return true;
    }
  }
  return false;
}

template<typename T>
void LimitedSizeBag<T>::clear(){
  T *newArray = new T[0];
  size = 0;
  bagArray = newArray;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t freq = 0;
  for (int i = 0; i < size; i++)
  {
    if (*(bagArray + i) == item)
    {
      freq++;
    }
  }
  return freq;
};
