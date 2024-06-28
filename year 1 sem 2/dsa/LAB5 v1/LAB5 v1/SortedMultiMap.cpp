#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

// BC=WC=TOTAL: O(1)
SortedMultiMap::SortedMultiMap(Relation r) {
    // TODO - Implementation
    this->length = 0;
    this->root = nullptr;
    this->relation = r;
    this->tiniest = NULL_TVALUE;
    this->largest = NULL_TVALUE;
    this->tiniest2nd = NULL_TVALUE;
    this->largest2nd = NULL_TVALUE;
    currentMax = -99999;
    currentMin = 99999;
}

// BC:O(1)
// TOTAL:O(log n), as each insertion divides the search space in half
// WC:O(n) n=number of nodes in the BST
void SortedMultiMap::add(TKey c, TValue v) {
    if (this->isEmpty()) {
        tiniest = v;
        largest = v;
        tiniest2nd = v;
        largest2nd = v;
    }
    else {
        if (v < tiniest) tiniest = v;
        if (v > tiniest && v < tiniest2nd)   tiniest2nd = v;
        if (v > largest) largest = v;
        if (v < largest && v > largest2nd)  largest2nd = v;
    }
    // TODO - Implementation
    // Create a new TElem object el with the specified key c and value v
    TElem el{ c,v };
    // Call the insert helper function to insert the new key-value pair into the BST
    this->root = this->insert(this->root, el);
}

// BC:O(1)
// TOTAL:O(log n)
// WC:O(n)
vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> tmp;
    Node* node = this->root;

    while (node != nullptr) {
        if (c == node->info.first) {
            tmp.push_back(node->info.second);
        }

        if (!relation(node->info.first, c))
        {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return tmp;
}

// BC:O(1)
// TOTAL:O(log n), as each insertion divides the search spTOTALe in half
// WC:O(n)
bool SortedMultiMap::remove(TKey c, TValue v) {
    if (this->removeRec(root, c, v))
    {
        this->length--;
        return true;
    }
    return false;
}

// BC=TOTAL=WC:O(1)
int SortedMultiMap::size() const {
    // TODO - Implementation
    return this->length;
}

// BC=TOTAL=WC:O(1)
bool SortedMultiMap::isEmpty() const {
    // TODO - Implementation
    if (this->length == 0)
        return true;
    return false;
}

// BC=TOTAL=WC:O(1)
SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

int SortedMultiMap::getValueRange()
{
    if (this->isEmpty()) return -1;
    getValueRangeHelp(this->root);
    return currentMax - currentMin;

}

void SortedMultiMap::getValueRangeHelp(Node* curr) {
    if (curr == nullptr) return;
    if ((int)curr->info.second > this->currentMax)   currentMax = curr->info.second;
    if ((int)curr->info.second < this->currentMin)   currentMin = curr->info.second;
    getValueRangeHelp(curr->left);
    getValueRangeHelp(curr->right);

}


//   TOTAL: O(n) n=number of nodes in the BST
SortedMultiMap::~SortedMultiMap() {
    Node* node = this->root;
    this->destructor(node);
}

//   TOTAL: Theta(n)
void SortedMultiMap::destructor(Node* node) {
    if (node != nullptr) {
        this->destructor(node->right);
        this->destructor(node->left);
        delete node;
    }
}

//   TOTAL: O(n)
Node* SortedMultiMap::getMinimumKey(Node* current)
{
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}




/* BC:O(log n)
   WC:O(n)  n = number of nodes in the BST
   TOTAL:O(n)
*/
Node* SortedMultiMap::insert(Node* node, TElem e)
{
    if (node == nullptr)
    {
        node = new Node();
        node->info = e;
        node->left = nullptr;
        node->right = nullptr;
        this->length++;
    }
    else if (!relation(node->info.first, e.first))
        node->left = insert(node->left, e);
    else
        node->right = insert(node->right, e);
    return node;
}

/*
// WC: O(n)
// BC: O(1)
// TOTAL: O(log n)
*/
bool SortedMultiMap::removeRec(Node* node, TKey c, TValue v)
{
    Node* lastNode = nullptr;

    while (node != nullptr)
    {
        if (c == node->info.first && v == node->info.second)
        {
            //  no children
            if (node->left == nullptr && node->right == nullptr)
            {
                //  leaf, not root
                if (node != this->root)
                {
                    if (lastNode->left == node)
                    {
                        lastNode->left = nullptr;
                    }
                    //  if it's the root, we set the tree as empty
                    else
                    {
                        lastNode->right = nullptr;
                    }
                }
                else
                {
                    this->root = nullptr;
                }
            }
            //  two children
            else if (node->left && node->right)
            {
                Node* successor = getMinimumKey(node->right);
                TElem val = successor->info;
                this->removeRec(node, successor->info.first, successor->info.second);
                node->info = val;
            }
            //  1 child
            else
            {
                Node* child = (node->left) ? node->left : node->right;
                //  not the root
                if (node != root)
                {
                    if (node == lastNode->left)
                    {
                        lastNode->left = child;
                    }
                    else
                    {
                        lastNode->right = child;
                    }
                }
                else
                {
                    root = child;
                }
            }
            return true;
        }
        if (!relation(node->info.first, c))
        {
            lastNode = node;
            node = node->left;
        }
        else
        {
            lastNode = node;
            node = node->right;
        }
    }
    return false;
}

