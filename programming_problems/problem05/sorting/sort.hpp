#ifndef _SORT_HPP
#define _SORT_HPP

#include <vector>
#include <algorithm>

#include "linked_list.hpp"

template<typename T> LinkedList<T> sort(LinkedList<T> list)
{
	std::vector<T> vecList;
	for (int i = 0; i < list.getLength(); i++) {
		vecList.push_back(list.getEntry(i));
	}
	std::sort(vecList.begin(), vecList.begin() + vecList.size());
	LinkedList<T> newList;
	for (int i = 0; i < list.getLength(); i++) {
		newList.insert(i, vecList[i]);
	}
	return newList;
}

#endif
