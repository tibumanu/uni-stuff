#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>
#include <cmath>



using namespace std;


MultiMap::MultiMap() {
    length = 0;
    capacity = 16;
    elements = new DLLA[capacity];
    for (int i = 0; i < capacity; i++) {
        elements[i].list = new DLLAnode[capacity];
        elements[i].head = -1;
        elements[i].tail = -1;
        elements[i].capacity = capacity;
        elements[i].size = 0;
        elements[i].firstEmpty = 0;
        for (int j = 0; j < capacity - 1; j++) {
            elements[i].list[j].next = j + 1;
        }
        elements[i].list[capacity - 1].next = -1;
    }
}


void MultiMap::resize(){
    capacity *= 2;
    DLLA* newElements = new DLLA[capacity];

    // copy the old elements into the new array
    for (int i = 0; i < length; i++) {
        newElements[i] = elements[i];
    }

    // initialize the new elements
    for (int i = length; i < capacity; i++) {
        newElements[i].list = new DLLAnode[capacity];
        newElements[i].head = -1;
        newElements[i].tail = -1;
        newElements[i].capacity = capacity;
        newElements[i].size = 0;
        newElements[i].firstEmpty = 0;
        for (int j = 0; j < capacity - 1; j++) {
            newElements[i].list[j].next = j + 1;
        }
        newElements[i].list[capacity - 1].next = -1;
    }

    // update the pointers to the new array
    DLLA* oldElements = elements;
    elements = newElements;

    // delete the old array
    delete[] oldElements;
}


//void MultiMap::add(TKey c, TValue v) {
//    DLLA &e = this->elements;
//    if(e.size == e.capacity && e.firstEmpty == -1)
//        resize();
//    if(e.firstEmpty == -1){
//        e.firstEmpty == e.size;
//        e[e.firstEmpty] = DLLAnode(NULL_TELEM, -1, -1);
//        e.size++;
//    }
//    if(this->length == 0){
//        int emptyCopy = e.firstEmpty;
//        e.firstEmpty = e[e.firstEmpty].next;
//        e[emptyCopy] = DLLAnode(make_pair(c, v), -1, -1);
//        e.tail = e.head = e.firstEmpty;
//        this->length++;
//        return;
//    }
//    int emptyCopy = e.firstEmpty;
//    e.firstEmpty = e[e.firstEmpty].next;
//    int final = e.head;
//    e[emptyCopy] = DLLAnode(make_pair(c, v), final, e[final].next );
//    e[e[final].next].previous = emptyCopy;
//    this->length++;
//}

void MultiMap::add(TKey c, TValue v)
{
    int index = hash(c, capacity);
    DLLA& dlla = elements[index];

    // Check if key already exists in the DLLA
    for (int i = dlla.head; i != -1; i = dlla.list[i].next) {
        if (dlla.list[i].inside.first == c) {
            // Key already exists, append value to the list
            int newNodeIndex = dlla.firstEmpty;
            dlla.firstEmpty = dlla.list[newNodeIndex].next;
            dlla.list[newNodeIndex] = DLLAnode(TElem(c, v), i, -1);
            dlla.list[i].next = newNodeIndex;
            if (dlla.tail == i) {
                dlla.tail = newNodeIndex;
            }
            dlla.size++;
            this->length++;
            return;
        }
    }

    // Key doesn't exist, create a new node and add it at the head
    int newNodeIndex = dlla.firstEmpty;
    dlla.firstEmpty = dlla.list[newNodeIndex].next;
    dlla.list[newNodeIndex] = DLLAnode(TElem(c, v), -1, dlla.head);
    if (dlla.head != -1) {
        dlla.list[dlla.head].previous = newNodeIndex;
    } else {
        dlla.tail = newNodeIndex;
    }
    dlla.head = newNodeIndex;
    dlla.size++;
    this->length++;
    }


bool MultiMap::remove(TKey c, TValue v) {
    int index = hash(c, capacity);
    DLLA &dlla = elements[index];
    int current = dlla.head;
    while (current != -1 && dlla.list[current].inside != make_pair(c, v)) {
        current = dlla.list[current].next;
    }
    if (current == -1) {
        return false; // value not found
    } else {
        // update pointers to bypass the node
        int prev = dlla.list[current].previous;
        int next = dlla.list[current].next;
        if (prev != -1) {
            dlla.list[prev].next = next;
        } else {
            dlla.head = next;
        }
        if (next != -1) {
            dlla.list[next].previous = prev;
        } else {
            dlla.tail = prev;
        }
        // add current node to the list of free nodes
        dlla.list[current].previous = -1;
        dlla.list[current].next = dlla.firstEmpty;
        dlla.firstEmpty = current;
        // update DLLA size
        dlla.size--;
        if(dlla.size==0)
            this->length--;
        return true;
    }
}

vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> values;
    int index = hash(c, elements->capacity);
    MultiMapIterator it(*this);
    it.position = 0;
    while(it.valid()){
            if(it.getCurrent().first == c)
            values.push_back(it.getCurrent().second);
        it.next();
    }
    return values;
}


int MultiMap::size() const {
    int totalSize = 0;
    for (int i = 0; i < capacity; i++) {
        totalSize += elements[i].size;
    }
    return totalSize;
}


bool MultiMap::isEmpty() const {
	return size() == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
    for (int i = 0; i < capacity; i++) {
        delete[] elements[i].list;
    }
    delete[] elements;
}

template <typename TKey>
int MultiMap::hash(TKey key, int cap) const {
    std::hash<TKey> hasher;  // Create a hasher for the key type
    int hashValue = hasher(key) % cap;  // Compute the hash value

    if (hashValue < 0) {
        hashValue += cap;  // Add capacity to make the value positive
    }

    return hashValue;
}

MultiMap::DLLAnode::DLLAnode(TElem ss, int prev, int next) : inside{std::move(ss)}, previous(prev), next(next){}

MultiMap::DLLAnode::DLLAnode() {
    inside = NULL_TELEM;
    previous = 0;
    next = 0;

}

MultiMap::DLLA::DLLA() {
    this->capacity = 1;
    this->size = 1;
    this->list = new DLLAnode[this->capacity];
    this->list[0] = DLLAnode(NULL_TELEM, -1, -1);
    this->firstEmpty = 0;
    this->head = -1;
    this->tail = -1;

}

MultiMap::DLLAnode &MultiMap::DLLA::operator[](int position) {
    return this->list[position];
}


