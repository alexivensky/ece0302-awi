#include "Database.hpp"



template <typename T>
Database<T>::Database() {
   size = 0;
}

template <typename T>
bool Database<T>::isEmpty() {
    return (size == 0);
}

template <typename T>
std::size_t Database<T>::getNumberOfEntries() {
    return size;
}

template <typename T>
bool Database<T>::add(std::string key1, std::string key2, const T& item) {
    int dummy;
    if (b1.retrieve(key1, dummy) || b2.retrieve(key2, dummy)) {
        return false;
    }
    data_entry e1;
    e1.key1 = key1;
    e1.key2 = key2;
    e1.item = item;
    b1.insert(key1, data.getLength());
    b2.insert(key2, data.getLength());
    data.insert(data.getLength(), e1);
    size++;
    return true;
}

template <typename T>
bool Database<T>::remove(std::string key) {
    int idx1, idx2;
    bool exists_b1 = b1.retrieve(key, idx1);
    bool exists_b2 = b2.retrieve(key, idx2);
    bool success = 0;
    if (idx1 == idx2) {
        data_entry d1 = data.getEntry(idx1);
        std::string key1 = d1.key1;
        std::string key2 = d1.key2;
        b1.remove(key1);
        b2.remove(key2);
        data.remove(idx1);
        size--;
        return true;
    }
    if (exists_b1) {
        data_entry d1 = data.getEntry(idx1);
        std::string key1 = d1.key1;
        std::string key2 = d1.key2;
        b1.remove(key1);
        b2.remove(key2);
        //data.remove(idx1); //binary tree indices do not change but actual positions do
        success = 1;
        size--;
    } else if (exists_b2) {
        data_entry d1 = data.getEntry(idx2);
        std::string key1 = d1.key1;
        std::string key2 = d1.key2;
        b1.remove(key1);
        b2.remove(key2);
        //data.remove(idx2);
        success = 1;
        size--;
    }
    
    return success;

    
}

template <typename T>
void Database<T>::clear() {
    b1.destroy();
    b2.destroy();
    data.clear();
    size = 0;
}

template <typename T>
T Database<T>::getValue(std::string key) {
    int idx1, idx2;
    data_entry d;
    bool exists_b1 = b1.retrieve(key, idx1);
    bool exists_b2 = b2.retrieve(key, idx2);
    if (exists_b1) {
        d = data.getEntry(idx1);
    } else if (exists_b2) {
        d = data.getEntry(idx2);
    }
    T item = d.item;
    return item;
}

template <typename T>
bool Database<T>::contains(std::string key) {
    int idx1, idx2;
    bool exists_b1 = b1.retrieve(key, idx1);
    bool exists_b2 = b2.retrieve(key, idx2);
    return (exists_b1 || exists_b2);
}
