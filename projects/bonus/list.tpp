#include "list.hpp"

template <typename T>
List<T>::List()
{
  head = nullptr;
  size = 0;
}

template <typename T>
List<T>::~List()
{
  //TODO
}

template <typename T>
List<T>::List(const List<T>& x)
{
  head = x.head;
  size = x.size;
}

template <typename T>
List<T>& List<T>::operator=(List<T> x)
{
  swap(x);
  return *this;
}

template <typename T>
void List<T>::swap(List<T>& x) 
{
  std::swap(head, x.head);
  std::swap(size, x.size);
}

template <typename T>
bool List<T>::isEmpty() const noexcept
{
  return (size == 0);
}

template <typename T>
std::size_t List<T>::getLength() const noexcept
{
  return size;
}

template <typename T>
void List<T>::insert(std::size_t position, const T& item)
{
  if (position > size || position < 0) {
    throw std::range_error("List insertion range error!");
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
void List<T>::remove(std::size_t position)
{
  if (position > size || position < 0 || head == nullptr) {
    throw std::range_error("List removal range error!");
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
void List<T>::clear()
{
  while (!isEmpty()) {
	remove(0);
  }
}

template <typename T>
T List<T>::getEntry(std::size_t position) const
{
  if (position >= 0 && position < size) {
	Node<T>* temp = head;
	for (int i = 0; i < position; i++) {
		temp=temp->getNext();
	}
	return temp->getItem();
  } else {
	throw std::range_error("List getEntry range error!");
  }
}

template <typename T>
void List<T>::setEntry(std::size_t position, const T& newValue)
{
  if (position < 0 || position > size || size == 0) {
    throw std::range_error("List setEntry range error!");
  }
  Node<T>* temp = new Node<T>();
  temp = head;
  for (int i = 0; i < position; i++) {
    temp = temp->getNext();
  }
  temp->setItem(newValue);
}
