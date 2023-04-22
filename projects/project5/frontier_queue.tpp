#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop() {
  if (empty()) {
    throw std::logic_error("cannot pop from empty queue");
  }
  if (queue.size() == 1) {
    State<T> temp = queue.at(0);
    queue.pop_back();
    return temp;
  }
  int i = 0,
      num = queue.size(),
      parent = 0,
      left = 2*i+1,
      right = left+1;
  
  State<T> rootCopy = queue.front();
  State<T> endCopy = queue.back();

  queue[0] = endCopy;
  queue.pop_back();

  while (left < num && right < num && left > 0) {
    if (queue[left].getFCost() < queue[right].getFCost() && queue[left].getFCost() < queue[parent].getFCost()) {
      swap(left, parent);
      parent = left;
    } else if (queue[right].getFCost() < queue[left].getFCost() && queue[right].getFCost() < queue[parent].getFCost()) {
      swap(right, parent);
      parent = right;
    } else { break; }

    i = parent;
    left = 2*i*1;
    right = left+1;
  }

  return rootCopy;



}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {

  State<T> newState(p, cost, heur);
  queue.push_back(newState);
  if (queue.size() == 1) {
    return;
  }
  int num = queue.size(),
      i = num - 1,
      parent = (i-1) / 2;
  
  while(queue[parent].getFCost() > queue[i].getFCost() && parent > 0) {
    swap(parent, i);
    i = parent;
    parent = (i-1) / 2;
  }

  

}

template <typename T>
bool frontier_queue<T>::empty() {

  return queue.size() == 0;
}

template <typename T> 
bool frontier_queue<T>::contains(const T &p) {

  //TODO

  for (int i = 0; i < queue.size(); i++) {
    if (queue[i].getValue() == p) {
      return true;
    }
  }
  return false;

}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) {

  for (int i = 0; i < queue.size(); i++) {
    if (queue[i].getValue() == p && cost < queue[i].getPathCost()) {
      queue[i].updatePathCost(cost);
    }
  }

}

template <typename T>
void frontier_queue<T>::swap(int idx1, int idx2) {
  State<T> temp = queue.at(idx1);
  queue.at(idx1) = queue.at(idx2);
  queue.at(idx2) = temp;
}

