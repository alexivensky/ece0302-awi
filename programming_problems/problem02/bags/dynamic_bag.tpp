#include "dynamic_bag.hpp"

template <typename T>
DynamicBag<T>::DynamicBag()
{
  size = 0;
  bagArray = new T[0];
}

template <typename T>
DynamicBag<T>::DynamicBag(const DynamicBag &x)
{
  size = x.size;
  bagArray = x.bagArray;
}

template <typename T>
DynamicBag<T>::~DynamicBag()
{
  bagArray = nullptr;
  delete bagArray;
}

template <typename T>
DynamicBag<T> &DynamicBag<T>::operator=(DynamicBag<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void DynamicBag<T>::swap(DynamicBag<T> &x)
{
  std::swap(bagArray, x.bagArray);
  std::swap(size, x.size);
}

template <typename T>
bool DynamicBag<T>::add(const T &item)
{
  int newSize = size + 1;
  T *newArray = new T[newSize];
  for (int i = 0; i < size; i++)
  {
    *(newArray + i) = *(bagArray + i);
  }
  *(newArray + size) = item;
  bagArray = newArray;
  size = newSize;
  if (*(bagArray + size) == item)
  {
    return true;
  }
  return false;
}

template <typename T>
bool DynamicBag<T>::remove(const T &item)
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

template <typename T>
bool DynamicBag<T>::isEmpty() const
{
  if (size == 0)
  {
    return true;
  }
  return false;
}

template <typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return size;
}

template <typename T>
bool DynamicBag<T>::contains(const T &item) const
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

template <typename T>
void DynamicBag<T>::clear()
{
  T *newArray = new T[0];
  size = 0;
  bagArray = newArray;
}

template <typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T &item) const
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
