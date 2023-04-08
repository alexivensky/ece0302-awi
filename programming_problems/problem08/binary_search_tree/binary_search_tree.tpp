#include "binary_search_tree.hpp"

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs)
{
    root = 0;
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs.root;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}


template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(BinarySearchTree<KeyType, ItemType> rhs)
{
    swap(rhs);
    return *this;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::swap(BinarySearchTree<KeyType, ItemType>& rhs)
{
    std::swap(root, rhs.root);
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}


template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    Node<KeyType, ItemType>* insertNode = new Node<KeyType, ItemType>;
    insertNode->data = item;
    insertNode->key = key;
    insertNode->left = 0;
    insertNode->right = 0;
    if (isEmpty()) { //base case.
        root = insertNode;
        return true;
    }
    KeyType tempKey = key;
    ItemType tempItem = item;
    if (retrieve(tempKey, tempItem)) { //if a node with given key already exists, we cannot proceed.
        return false;
    }
    Node<KeyType, ItemType>* tempCurr = new Node<KeyType, ItemType>;
    Node<KeyType, ItemType>* tempParent = new Node<KeyType, ItemType>;
    search(key, tempCurr, tempParent); //finding location at which to insert.
    if (key < tempCurr->key) {
        tempCurr->left = insertNode;
    } else if (key > tempCurr->key) {
        tempCurr->right = insertNode;
    }

    return true;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return (root == 0);
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    if (curr == 0)
        return false;

    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    if (isEmpty())
        return false; // empty tree

    Node<KeyType, ItemType>* curr = new Node<KeyType, ItemType>;
    Node<KeyType, ItemType>* parent = new Node<KeyType, ItemType>;
    search(key, curr, parent); //finding location at which to remove.

    if (curr == nullptr) {
        return false;
    }

    //case: leaf node
    if (curr->left == nullptr && curr->right == nullptr) {
        if (curr == root) {
            root = nullptr;
        } else {
            if (parent->left == curr) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
        delete curr;
        curr = nullptr;
    }
    //case: node has one child
    else if (curr->left == nullptr) {
        if (curr == root) {
            root = curr->right;
        } else if (curr == parent->left) {
            parent->left = curr->right;
        } else {
            parent->right = curr->right;
        }
        delete curr;
        curr = nullptr;
    } else if (curr->right == nullptr) {
        if (curr == root) {
            root = curr->left;
        } else if (curr == parent->left) {
            parent->left = curr->left;
        } else {
            parent->right = curr->left;
        }
        delete curr;
        curr = nullptr;
    }
    //case: node has two children
    else {
        Node<KeyType, ItemType>* next = curr->right;
        Node<KeyType, ItemType>* nextParent = curr;
        while (next->left != nullptr) {
            nextParent = next;
            next = next->left;
        }
        if (nextParent != curr) {
            nextParent->left = next->right;
        } else {
            curr->right = next->right;
        }
        curr->key = next->key;
        curr->data = next->data;
        delete next;
        next = nullptr;
    }
    

    return true; 
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent)
{
    // TODO: find inorder successor of "curr" and assign to "in"
    while(1) {
        if (curr->left == 0) {
            in = curr;
            break;
        }
        parent = curr;
        curr = curr->left;
    }

}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent)
{
    curr = root;
    parent = 0;

    if (isEmpty())
        return;

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else
                break;
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else
                break;
        }
    }
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(KeyType arr[], int size) {
    // TODO: check for duplicate items in the input array

    // TODO: use the tree to sort the array items

    // TODO: overwrite input array values with sorted values
}
