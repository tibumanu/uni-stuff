#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

class MultiMap
{
    friend class MultiMapIterator;

private:
    //TODO - Representation
    struct Node {
        TKey key;
        TValue* elems;
        int* next;
        int head;
        int firstFree;
        int cap;
        int sllaSize;
        int lastUsed;
    };
    //struct Node;
    Node* mapElems;
    int mapSize;
    int mapCap;
    int mapHead;
    int* mapNext;
    int mapFirstFree;
    int mapTotalSize;
    int mapLastUsed;

public:

    //constructor
    MultiMap();

    void freePosition(int position);

    void freeNodePosition(int position, Node& currentNode);

    int allocateSpaceForElement();

    int allocateSpaceForNodeElement(Node& currentNode);

    int getKeyRange() const;

    //adds a key value pair to the multimap
    void add(TKey c, TValue v);

    //removes a key value pair from the multimap
    //returns true if the pair was removed (if it was in the multimap) and false otherwise
    bool remove(TKey c, TValue v);

    //returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
    vector<TValue> search(TKey c) const;

    //returns the number of pairs from the multimap
    int size() const;

    //checks whether the multimap is empty
    bool isEmpty() const;

    //returns an iterator for the multimap
    MultiMapIterator iterator() const;

    void resizeMap();

    void resizeSLLA(Node& resizable);

    int* getNext() { return mapNext; };

    Node* getValues() { return mapElems; };

    //descturctor
    ~MultiMap();


};

