#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


struct Node {
    TElem info; // key&pair
    Node* left;
    Node* right;
};

class SortedMultiMap {
    friend class SMMIterator;
private:
    Node* root;
    int length;
    Relation relation;
    int tiniest;
    int tiniest2nd;
    int largest;
    int largest2nd;
    

public:
    int currentMax;
    int currentMin;

    // constructor
    SortedMultiMap(Relation r);

    // adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    // returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    // removes a key value pair from the sorted multimap
    // returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    // returns the number of key-value pairs from the sorted multimap
    int size() const;

    // verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;


    int getValueRange();
    void getValueRangeHelp(Node* curr);

    // destructor
    ~SortedMultiMap();

private:
    // helper function to insert a key-value pair into the BST
    Node* insert(Node* node, TElem e);

    Node* getMinimumKey(Node* current);

    // helper function to recursively remove a key
    bool removeRec(Node* node, TKey c, TValue v);

    void destructor(Node* pNode);
};
