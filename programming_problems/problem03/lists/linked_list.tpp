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
 
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  head = x.head;
  size = x.size;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList& x) 
{
  std::swap(head, x.head);
  std::swap(size, x.size);
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  return size == 0;
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
  
  Node<T>* temp = new Node<T>();

  if (head == nullptr && size == 0) {
    temp->setItem(item);
    head = temp;
  } else {
    temp = head;
    for (int i = 0; i < position - 1; i++) {
      temp = temp->getNext();
    }
    Node<T>* newNode = new Node<T>(item);
    if (position < size) {
      newNode->setNext(temp->getNext());
    }
    temp->setNext(newNode);
  }
  size++;
  return true;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  if (position > size || position < 0) {
    return false;
  }
  Node<T>* temp = head;
  Node<T>* ptrDelete = new Node<T>();
  if (position == 0) {
    ptrDelete = head;
    head = temp->getNext();
    ptrDelete->setNext(nullptr);
    delete ptrDelete;
  } else {
    for (int i = 0; i < position - 1; i++) {
      temp = temp->getNext();
    }
    
    ptrDelete = temp->getNext();
    if (position < size - 1) {
      temp->setNext(temp->getNext()->getNext());
    } else {
      temp->setNext(nullptr);
    }
    ptrDelete->setNext(nullptr);
    delete ptrDelete;
    
  }
  size--;
  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  Node<T>* temp = new Node<T>();
  temp = head;
  for (int i = 0; i < size - 1; i++) {
    Node<T>* deletePtr = new Node<T>;
    deletePtr = temp;
    temp = temp->getNext();
    delete deletePtr;
  }
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  int c = 0;
  Node<T>* curPtr = head;
  while (curPtr != nullptr) {
    if (c == position) {
      return curPtr->getItem();
    } else {
      c++;
      curPtr = curPtr->getNext();
    }
  }
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  if (position < 0 || position > size) {
    return;
  }
  Node<T>* temp = new Node<T>();
  temp = head;
  for (int i = 0; i < position - 1; i++) {
    temp = temp->getNext();
  }
  temp->setItem(newValue);
}
