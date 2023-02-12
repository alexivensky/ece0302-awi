#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList() {
  size = 0;
  arrPtr = new T[size];
}

template <typename T>
ArrayList<T>::~ArrayList() {
  arrPtr = nullptr;
  delete [] arrPtr;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs){
  size = rhs.size;
  arrPtr = rhs.arrPtr;
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList rhs){
  swap(rhs);
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList& rhs) {
  std::swap(arrPtr, rhs.arrPtr);
  std::swap(size, rhs.size);
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept {
  return (size==0?1:0);
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept {
  return size;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){
  if (position > size || position < 0) {
    return false;
  }
  int newSize = size + 1;
  T* newArr = new T [newSize];
  for (int i = 0; i < newSize; i++) {
    if (i < position) {
      *(newArr + i) = *(arrPtr + i);
    } else if (i == position) {
      *(newArr + i) = item;
    } else {
      *(newArr + i) = *(arrPtr + i - 1);
    }
  }
  size = newSize;
  arrPtr = newArr;
  return true;
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position){
  if (position > size || position < 0) {
    return false;
  }
  int newSize = size - 1;
  T* newArr = new T [newSize];
  for (int i = 0; i < newSize; i++) {
    if (i < position) {
      *(newArr + i) = *(arrPtr + i);
    } else {
      *(newArr + i) = *(arrPtr + i + 1);
    }
  }
  size = newSize;
  arrPtr = newArr;
  return true;
}

template <typename T>
void ArrayList<T>::clear() {
  size = 0;
  arrPtr = new T [0];
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {
  if (position > size || position < 0) {
    return T();
  } else {
    return *(arrPtr + position);
  }
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
  if (position <= size && position >= 0) {
    *(arrPtr + position) = newValue;
  }
}
