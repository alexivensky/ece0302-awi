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
  return (size == 0);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
void LinkedList<T>::insert(std::size_t position, const T& item)
{
  if (position > size || position < 0) {
    throw std::range_error("bad!");
  }
  
  if (position >= 0 && position <= size) {
	Node<T>* newNode = new Node<T>(item);
	size++;
	if (position == 0) {
		newNode->setNext(head);
		head = newNode;
	} else {
		Node<T>* prev = new Node<T>();
		prev = head;
		for (int i = 0; i < position - 1; i++) {
			prev = prev->getNext();
		}
		newNode->setNext(prev->getNext());
		prev->setNext(newNode);
	}
	
  }
  return;
}

template <typename T>
void LinkedList<T>::remove(std::size_t position)
{
  if (position > size || position < 0 || head == nullptr) {
    throw std::range_error("bad!");
  }
  if (position >= 0 && position < size) {
	Node<T>* cur = nullptr;
	if (position == 0) {
		cur = head;
		head = head->getNext();
	} else {
		Node<T>* prev = head;
		for (int i = 0; i < position -1; i++) {
			prev=prev->getNext();
		}
		cur = prev->getNext();
		prev->setNext(cur->getNext());
	}
	delete cur;
	size--;
  }
 
}

template <typename T>
void LinkedList<T>::clear()
{
  while (!isEmpty()) {
	remove(0);
  }
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  if (position >= 0 && position < size) {
	Node<T>* temp = head;
	for (int i = 0; i < position; i++) {
		temp=temp->getNext();
	}
	return temp->getItem();
  } else {
	throw std::range_error("bad!");
  }
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  if (position < 0 || position > size || size == 0) {
    throw std::range_error("bad!");
  }
  Node<T>* temp = new Node<T>();
  temp = head;
  for (int i = 0; i < position; i++) {
    temp = temp->getNext();
  }
  temp->setItem(newValue);
}
