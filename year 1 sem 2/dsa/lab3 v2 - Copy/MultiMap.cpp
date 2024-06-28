#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;
/*
struct MultiMap::Node {
	TKey key;
	TValue* elems;
	int* next;
	int head;
	int firstFree;
	int cap;
	int sllaSize;
	int lastUsed;
};
*/
MultiMap::MultiMap() {
    //TODO - Implementation
    //best case - T(mapCap + mapCap * cap), worst case - T(mapCap + mapCap * cap), total case - T(mapCap + mapCap * cap)
    mapCap = 5;
    mapSize = 0;
    mapElems = new Node[mapCap];
    mapNext = new int[mapCap];
    for (int i = 0; i < mapCap; i++)
    {
        mapNext[i] = i + 1;
    }
    mapNext[mapCap - 1] = -1;
    mapHead = -1;
    mapFirstFree = 0;
    mapTotalSize = 0;
    for (int i = 0; i < mapCap; i++)
    {
        mapElems[i] = Node();
        mapElems[i].key = -1;
        mapElems[i].firstFree = 0;
        mapElems[i].cap = 5;
        mapElems[i].head = -1;
        mapElems[i].sllaSize = 0;
        mapElems[i].elems = new TValue[mapElems[i].cap];
        mapElems[i].next = new int[mapElems[i].cap];
        for (int j = 0; j < mapElems[i].cap; j++)
        {
            mapElems[i].next[j] = j + 1;
        }
        mapElems[i].next[mapElems[i].cap - 1] = -1;
    }
}

void MultiMap::freePosition(int position)
{
    //best case - T(1), worst case - T(1), total case - T(1)
    mapSize--;
    mapNext[position] = mapFirstFree;
    mapFirstFree = position;
}

void MultiMap::freeNodePosition(int position, Node& currentNode)
{
    //best case - T(1), worst case - T(1), total case - T(1)
    currentNode.sllaSize--;
    mapTotalSize--;
    currentNode.next[position] = currentNode.firstFree;
    currentNode.firstFree = position;
}

int MultiMap::allocateSpaceForElement()
{
    //best case - T(1), worst case - T(1), total case - T(1)
    if (mapFirstFree == -1)
        resizeMap();
    int newFreePos = mapFirstFree;
    mapLastUsed = mapFirstFree;
    mapFirstFree = mapNext[mapFirstFree];
    return newFreePos;
}

int MultiMap::allocateSpaceForNodeElement(Node& currentNode)
{
    //best case - T(1), worst case - T(1), total case - T(1)
    if (currentNode.firstFree == -1)
        resizeSLLA(currentNode);
    int newFreePos = currentNode.firstFree;
    currentNode.lastUsed = currentNode.firstFree;
    currentNode.firstFree = currentNode.next[currentNode.firstFree];
    return newFreePos;
}



void MultiMap::add(TKey c, TValue v) {
    //TODO - Implementation
    //best case - T(1), worst case - T(mapSize), total case - O(mapSize)
    if (mapSize == 0)
    {
        int newPos = allocateSpaceForElement();
        int newNodePos = allocateSpaceForNodeElement(mapElems[newPos]);
        mapElems[newPos].elems[newNodePos] = v;
        mapElems[newPos].head = newNodePos;
        mapElems[newPos].next[newNodePos] = -1;
        mapElems[newPos].key = c;
        mapElems[newPos].sllaSize++;
        mapNext[newPos] = -1;
        mapHead = newPos;
        mapSize++;
        mapTotalSize++;
        return;
    }
    int current = mapHead;
    while (current != -1 && mapElems[current].key != c)
        current = mapNext[current];
    if (current == -1)
    {
        int mapPrevPos = mapLastUsed;
        int newPos = allocateSpaceForElement();
        int newNodePos = allocateSpaceForNodeElement(mapElems[newPos]);
        mapElems[newPos].elems[newNodePos] = v;
        mapElems[newPos].head = newNodePos;
        mapElems[newPos].key = c;
        mapElems[newPos].next[newNodePos] = -1;
        mapElems[newPos].sllaSize++;
        mapNext[mapPrevPos] = newPos;
        mapNext[newPos] = -1;
        mapSize++;
        mapTotalSize++;
        return;
    }
    int prevPos = mapElems[current].lastUsed;
    int newNodePos = allocateSpaceForNodeElement(mapElems[current]);
    mapElems[current].elems[newNodePos] = v;
    mapElems[current].next[prevPos] = newNodePos;
    mapElems[current].next[newNodePos] = -1;
    mapElems[current].sllaSize++;
    mapTotalSize++;
}

int MultiMap::getKeyRange() const
{
    //best case - T(1), worst case T(mapSize), total case O(mapSize)
    if (mapTotalSize == 0)
        return -1;
    int current = mapHead;
    TKey minKey, maxKey;
    minKey = maxKey = mapElems[current].key;
    current = mapNext[current];
    while (current != -1)
    {
        if (minKey > mapElems[current].key)
            minKey = mapElems[current].key;
        if(maxKey < mapElems[current].key)
            maxKey = mapElems[current].key;
        current = mapNext[current];
    }
    return maxKey-minKey;
}


bool MultiMap::remove(TKey c, TValue v) {
    //TODO - Implementation
    //best case - T(1), worst case T(mapSize + sllaSize), total case - O(mapSize + sllaSize)
    int current = mapHead;
    int prevPos = -1;
    while (current != -1 && mapElems[current].key != c)
    {
        prevPos = current;
        current = mapNext[current];
    }
    if (current != -1)
    {
        int currentValue = mapElems[current].head;
        int prevNodePos = -1;
        while (currentValue != -1 && mapElems[current].elems[currentValue] != v)
        {
            prevNodePos = currentValue;
            currentValue = mapElems[current].next[currentValue];
        }
        if (currentValue != -1)
        {
            if (currentValue == mapElems[current].head && mapElems[current].sllaSize == 1)
            {
                mapElems[current].head = -1;
            }
            else if (currentValue == mapElems[current].head)
            {
                mapElems[current].head = mapElems[current].next[mapElems[current].head];
            }
            else
            {
                mapElems[current].next[prevNodePos] = mapElems[current].next[currentValue];
            }
            freeNodePosition(currentValue, mapElems[current]);
            if (mapElems[current].sllaSize == 0)
            {
                if (current == mapHead && mapSize == 1)
                {
                    mapHead = -1;
                }
                else if (current == mapHead)
                {
                    mapHead = mapNext[mapHead];
                }
                else {
                    mapNext[prevPos] = mapNext[current];
                }
                freePosition(current);
            }
            return true;
        }
        return false;
    }
    return  false;
}


vector<TValue> MultiMap::search(TKey c) const {
    //TODO - Implementation
    //best case - T(sllaSize), worst case - T(mapSize + sllaSize), total case - O(mapSize + sllaSize)
    vector<TValue> values = *(new vector<TValue>());
    int current = mapHead;
    while (current != -1 && mapElems[current].key != c)
        current = mapNext[current];
    if (current != -1)
    {
        int currentNode = mapElems[current].head;
        while (currentNode != -1)
        {
            values.push_back(mapElems[current].elems[currentNode]);
            currentNode = mapElems[current].next[currentNode];
        }
    }
    return values;
}


int MultiMap::size() const {
    //TODO - Implementation
    //best case - T(1), worst case - T(1), total case - T(1)
    return mapTotalSize;
}


bool MultiMap::isEmpty() const {
    //TODO - Implementation
    //best case - T(1), worst case - T(1), total case - T(1)
    if(mapTotalSize)
        return false;
    return true;
}

MultiMapIterator MultiMap::iterator() const {
    //best case - T(1), worst case - T(1), total case - T(1)
    return MultiMapIterator(*this);
}

void MultiMap::resizeMap()
{
    //best case - T(mapCap), worst case - T(mapCap), total case - T(mapCap)
    Node* newElems = new Node[mapCap * 2];
    int* newNext = new int[mapCap * 2];
    for (int i = 0; i < mapCap; i++)
    {
        newElems[i] = mapElems[i];
        newNext[i] = mapNext[i];
    }
    for (int i = mapCap; i < mapCap * 2; i++)
    {
        newNext[i] = i + 1;
        newElems[i] = Node();
        newElems[i].key = -1;
        newElems[i].firstFree = 0;
        newElems[i].cap = 5;
        newElems[i].head = -1;
        newElems[i].sllaSize = 0;
        newElems[i].elems = new TValue[newElems[i].cap];
        newElems[i].next = new int[newElems[i].cap];
        for (int j = 0; j < newElems[i].cap; j++)
        {
            newElems[i].next[j] = j + 1;
        }
        newElems[i].next[newElems[i].cap - 1] = -1;
    }
    newNext[mapCap * 2 - 1] = -1;
    mapFirstFree = mapCap;
    mapCap *= 2;
    delete[] mapElems;
    delete[] mapNext;
    mapElems = newElems;
    mapNext = newNext;
}

void MultiMap::resizeSLLA(Node& resizable)
{
    //best case - T(cap), worst case - T(cap), total case - T(cap)
    TValue* newElems = new TValue[resizable.cap * 2];
    int* newNext = new int[resizable.cap * 2];
    for (int i = 0; i < resizable.cap; i++)
    {
        newElems[i] = resizable.elems[i];
        newNext[i] = resizable.next[i];
    }
    for (int i = resizable.cap; i < resizable.cap * 2; i++)
    {
        newNext[i] = i + 1;
    }
    newNext[resizable.cap * 2 - 1] = -1;
    resizable.firstFree = resizable.cap;
    resizable.cap = resizable.cap * 2;
    delete[] resizable.elems;
    delete[] resizable.next;
    resizable.elems = newElems;
    resizable.next = newNext;
}


MultiMap::~MultiMap() {
    //TODO - Implementation
    //best case - T(mapCap), worst case - T(mapCap), total case - T(mapCap)
    for (int i = 0; i < mapCap; i++)
    {
        delete[] mapElems[i].elems;
        delete[] mapElems[i].next;
    }
    delete[] mapElems;
    delete[] mapNext;
}

