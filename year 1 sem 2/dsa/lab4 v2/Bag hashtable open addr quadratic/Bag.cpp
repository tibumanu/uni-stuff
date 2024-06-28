#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	//TODO - Implementation
}


void Bag::add(TElem e) {
    // check if resizing is needed
    if(size / capacity > alpha) {
        resizeAndRehash();
    }

    int index = hashFunction(e); // Compute the hash value to determine the index

    // Handle collisions using quadratic probing
    int offset = 1;
    while (hashTable[index].key != NULL_TELEM) {
        if (hashTable[index].key == e) {
            // If the key already exists, increment the frequency
            hashTable[index].frequency++;
            this->size++;
            return;
        }
        index = (index + (offset * offset)) % capacity;  // Quadratic probing
        offset++;  // Increment the offset for the next probe
    }

    // If the key does not exist, add a new key-value pair
    hashTable[index].key = e;
    hashTable[index].frequency = 1;
    this->size++;
}


bool Bag::remove(TElem elem) {
	//TODO - Implementation
	return false; 
}


bool Bag::search(TElem elem) const {
	//TODO - Implementation
	return false; 
}

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	return 0; 
}


int Bag::size() const {
	//TODO - Implementation
	return 0;
}


bool Bag::isEmpty() const {
	//TODO - Implementation
	return 0;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	//TODO - Implementation
}

