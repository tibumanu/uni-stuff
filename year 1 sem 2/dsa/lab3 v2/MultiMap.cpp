#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
    /*
     * BC, WC, TOTAL: Theta(1)
     */
    capacityMap = 4;
    sizeMap = 0;
    lengthMap = 0;
    elements = new Node[capacityMap];
    mapNext = new int[capacityMap];
    mapPrevious = new int[capacityMap];

    for(int i = 0; i < capacityMap; i++){
        mapNext[i] = i + 1;
        mapPrevious[i] = -1;
        elements[i] = Node();
        elements[i].key = -1;
        elements[i].elements = new TValue[elements->capacity];
        elements[i].previous = new int[capacityMap];
        elements[i].next = new int[capacityMap];
        elements[i].firstFree = 0;
        elements[i].lastUsed = -1;
        elements[i].head = -1;
        elements[i].tail = -1;
        elements[i].capacity = 4;
        elements[i].size = 0;
        for(int j = 0; j < elements[i].capacity; j++){
            elements[i].next[j] = j + 1;
            elements[i].previous[j] = j - 1;
        }
        elements[i].next[elements[i].capacity - 1] = -1;
        elements[i].previous[0] = -1;
    }
    mapNext[capacityMap - 1] = -1;
    headMap = -1;
    firstFreeMap = 0;
    sizeMap = 0;
    lengthMap = 0;
}


void MultiMap::add(TKey c, TValue v) {
    if(sizeMap == 0){
        int newPosition = makeSpaceNewElement();
        int newNodePosition = makeSpaceNodeNewElement(elements[newPosition]);
        elements[newPosition].elements[newNodePosition] = v;
        elements[newPosition].head = newNodePosition;
        elements[newPosition].next[newNodePosition] = -1;
        elements[newPosition].previous[newNodePosition] = -1;
        elements[newPosition].key = c;
        elements[newPosition].size++;
        mapNext[newPosition] = -1;

        headMap = newPosition;
        sizeMap++;
        lengthMap++;
        return;
    }
    int current = headMap;
    while(current != -1 && elements[current].key != c)
        current = mapNext[current];
    if(current == -1){
        int newPreviousPos = lastUsedMap;
        int newPos = makeSpaceNewElement();
        int newNodePos = makeSpaceNodeNewElement(elements[newPos]);
        elements[newPos].elements[newNodePos] = v;
        elements[newPos].head = newNodePos;
        elements[newPos].key = c;
        elements[newPos].next[newNodePos] = -1;
        elements[newPos].size++;

        mapNext[newPreviousPos] = newPos;
        mapNext[newPos] = -1;
        sizeMap++;
        lengthMap++;
        return;
    }
    int previousPos = elements[current].lastUsed;
    int newNodePos = makeSpaceNodeNewElement(elements[current]);
    elements[current].elements[newNodePos] = v;
    elements[current].next[previousPos] = newNodePos;
    elements[current].previous[newNodePos] = previousPos;
    lengthMap++;
}


bool MultiMap::remove(TKey c, TValue v) {
	int current = headMap;
    int previousPosition = -1;
    while(current != -1 && elements[current].key != c){
        previousPosition = current;
        current = mapNext[current];
    }
    if(current != -1){
        int currentValue = elements[current].head;
        int previousNodePosition = -1;
        while(currentValue != -1 && elements[current].elements[currentValue] != v){
            previousNodePosition = currentValue;
            currentValue = elements[current].next[currentValue];
        }
        if(currentValue != -1){
            if(currentValue == elements[current].head && elements[current].size == 1)
                elements[current].head = -1;
            else if(currentValue == elements[current].head)
                elements[current].head = elements[current].next[elements[current].head];
            else {
                elements[current].next[previousNodePosition] = elements[current].next[currentValue];
                elements[current].previous[elements[current].next[currentValue]] = elements[current].previous[currentValue];
            }
            disappearNodePosition(currentValue, elements[current]);
            if(elements[current].size == 0){
                if(current == headMap && sizeMap == 1)
                    headMap = -1;
                else if(current == headMap)
                    headMap = mapNext[headMap];
                else
                    mapNext[previousPosition] = mapNext[current];
                disappearPosition(current);
            }
            return true;
        }
        return false;
    }
    return false;
}


vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> values;
    int current = headMap;
    while(current != -1 and elements[current].key != c)
        current = mapNext[current];
    if(current != -1){
        int currentNode = elements[current].head;
        while(currentNode != -1){
            values.push_back(elements[current].elements[currentNode]);
            currentNode = elements[current].next[currentNode];
        }
    }
    return values;
}


int MultiMap::size() const {
	return lengthMap;
}


bool MultiMap::isEmpty() const {
	return lengthMap == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    /*
     * BC, WC, TOTAL: Theta(capacityMap)
     */
    for(int i = 0; i < capacityMap; i++){
        delete[] elements[i].next;
        delete[] elements[i].previous;
        delete[] elements[i].elements;
        }
    }

int MultiMap::makeSpaceNewElement() {
    /*
     * BC: Theta(1), when not needing to resize;
     * WC: Theta(capacityMap), when needing to resize;
     * TOTAL: O(capacityMap)
     */
    if(firstFreeMap == -1)
        resizeMap();
    int newFree = firstFreeMap;
    lastUsedMap = firstFreeMap;
    firstFreeMap = mapNext[firstFreeMap];
    return newFree;
}

int MultiMap::makeSpaceNodeNewElement(MultiMap::Node &givenNode) {
    /*
     * BC: Theta(1), when not needing to resize;
     * WC: Theta(
     */
    if(givenNode.firstFree == -1)
        resizeDLLA(givenNode);
    int newFree = givenNode.firstFree;
    givenNode.lastUsed = givenNode.firstFree;
    givenNode.firstFree = givenNode.next[givenNode.firstFree];
    return newFree;
}

void MultiMap::disappearPosition(int position) {
    mapNext[position] = firstFreeMap;
    firstFreeMap = position;
    sizeMap--;
}

void MultiMap::disappearNodePosition(int position, MultiMap::Node &givenNode) {
    givenNode.next[position] = givenNode.firstFree;
    givenNode.firstFree--;
    lengthMap--;
    givenNode.size--;
}

void MultiMap::resizeMap() {
    /*
     * BC, WC, TOTAL: Theta(capacityMap*2)
     */
    Node* newElements = new Node[capacityMap];
    int* newMapNext = new int[capacityMap];
    int* newMapPrevious = new int[capacityMap];

    for(int i = 0; i < capacityMap * 2; i++){
        newMapNext[i] = i + 1;
        newMapPrevious[i] = -1;
        newElements[i] = Node();
        newElements[i].key = -1;
        newElements[i].elements = new TValue[elements->capacity];
        newElements[i].previous = new int[capacityMap];
        newElements[i].next = new int[capacityMap];
        newElements[i].firstFree = 0;
        newElements[i].lastUsed = -1;
        newElements[i].head = -1;
        newElements[i].tail = -1;
        newElements[i].capacity = 4;
        newElements[i].size = 0;
        for(int j = 0; j < elements[i].capacity; j++){
            newElements[i].next[j] = j + 1;
            newElements[i].previous[j] = j - 1;
        }
        newElements[i].next[elements[i].capacity - 1] = -1;
        newElements[i].previous[0] = -1;
    }
    newMapNext[capacityMap * 2 - 1] = -1;
    newMapPrevious[0] = -1;
    firstFreeMap = capacityMap;
    capacityMap *= 2;
    delete[] elements;
    delete[] mapNext;
    elements = newElements;
    mapNext = newMapNext;
}

void MultiMap::resizeDLLA(MultiMap::Node &givenNode) {
    TValue* newValues = new TValue[givenNode.capacity*2];
    int* newNext =  new int[givenNode.capacity*2];
    int* newPrevious = new int[givenNode.capacity*2];
    for(int i = 0; i < givenNode.capacity; i++){
        newValues[i] = givenNode.elements[i];
        newNext[i] = givenNode.next[i];
        newPrevious[i] = givenNode.previous[i];
    }
    for(int i = 0; i < givenNode.capacity*2; i++){
        newNext[i] = i + 1;
        newPrevious[i] = i - 1;
    }
    newNext[givenNode.capacity * 2 - 1] = -1;
    newPrevious[0] = -1;
    delete[] givenNode.elements;
    delete[] givenNode.next;
    delete[] givenNode.previous;
    givenNode.elements = newValues;
    givenNode.next = newNext;
    givenNode.previous = newPrevious;
}





