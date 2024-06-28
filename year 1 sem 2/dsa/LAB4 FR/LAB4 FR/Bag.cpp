#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
    capacity = 5;
    sizeNow = 0;
    alpha = 0.7;
    
    hashTable = new KeyValuePair[capacity];

    for (int i = 0; i < capacity; i++) {
        hashTable[i].key = NULL_TELEM;
        hashTable[i].frequency = 0;
    }
}

void Bag::resizeAndRehash() {
    int oldCapacity = capacity;
    capacity *= 2;  // Double the capacity

    KeyValuePair* oldHashTable = hashTable;
    hashTable = new KeyValuePair[capacity];  // Create a new hash table with the updated capacity

    for (int i = 0; i < capacity; i++) {
        hashTable[i].key = NULL_TELEM;
        hashTable[i].frequency = 0;
    }

    for (int i = 0; i < oldCapacity; i++) {
        if (oldHashTable[i].key != NULL_TELEM) {
            // Rehash the non-empty slots from the old hash table to the new hash table
            int index = hashFunction(oldHashTable[i].key);
            int offset = 1;
            while (hashTable[index].key != NULL_TELEM) {
                index = (index + (offset * offset)) % capacity;  // Quadratic probing
                offset++;
            }
            // Insert the element into the new hash table
            hashTable[index].key = oldHashTable[i].key;
            hashTable[index].frequency = oldHashTable[i].frequency;
        }
    }

    delete[] oldHashTable;  // Deallocate the memory of the old hash table
}

/*
    Number of steps also depends on load factor and number of collisions.
    BC: Theta(1), when the first hashed index leads us the the actual element.
    WC: Theta(n)
    TOTAL: O(n)
*/
void Bag::add(TElem e) {
    // check if resizing is needed
    if( (double)this->sizeNow / capacity > alpha) {     // where sizeNow/capacity is the current load factor
        resizeAndRehash();
    }

    long index = hashFunction(e);    // !!!long long - who thought of doing ExtendedTest on this ?!

    // handle collisions using quadratic probing
    long offset = 1;
    while(hashTable[index].key != NULL_TELEM) {
        if (hashTable[index].key == e) {
            // If the key already exists, increment the frequency
            hashTable[index].frequency++;
            this->sizeNow++;
            return;
        }
        index = (index + (offset * offset)) % capacity;  // Quadratic probing
        offset++;  // Increment the offset for the next probe
    }

    // If the key does not exist, add a new key-value pair
    hashTable[index].key = e;
    hashTable[index].frequency = 1;
    this->sizeNow++;
}


/*
    Number of steps also depends on load factor and number of collisions.
    BC: Theta(1), when the first hashed index leads us the the actual element.
    WC: Theta(n)
    TOTAL: O(n)
*/
bool Bag::remove(TElem e) {
    if(!search(e))   return false;
    long long index = hashFunction(e); // !!!long long - who thought of doing ExtendedTest on this ?!

    // handle collisions using quadratic probing
    long offset = 1;
    int visitedSlots = 0;

    while (visitedSlots < capacity) {
        if (hashTable[index].key == e) {
            // key found
            hashTable[index].frequency--;
            sizeNow--;

            if (hashTable[index].frequency == 0) {
                // Key no longer has occurrences, remove it from the bag
                hashTable[index].key = NULL_TELEM;
            }

            return true; // successfully removed
        }

        index = (index + (offset * offset)) % capacity; // quadratic probing
        offset++; // increment the offset for the next probe
        visitedSlots++;
    }

    return false; // key not found
}


/*
    Number of steps also depends on load factor and number of collisions.
    BC: Theta(1), when the first hashed index leads us the the actual element.
    WC: Theta(n) 
    TOTAL: O(n)
*/
bool Bag::search(TElem e) const {
    long long index = hashFunction(e); // !!! long long - who thought of doing ExtendedTest on this?!

    // handle collisions using quadratic probing
    long long offset = 1;
    int visitedSlots = 0;

    while (visitedSlots < capacity) {
        if (hashTable[index].key == e) {
            // key found
            return true;
        }
        else if (hashTable[index].key == NULL_TELEM) {
            // reached an empty slot, continue probing
            index = (index + (offset * offset)) % capacity; // quadratic probing
            offset++; // increment the offset for the next probe
            visitedSlots++;
            continue;
        }

        index = (index + (offset * offset)) % capacity; // quadratic probing
        offset++; // increment the offset for the next probe
        visitedSlots++;
    }

    return false; // key not found
}


/*
    Number of steps also depends on number of collisions.
    BC: Theta(1), when the first hashed index leads us the the actual element.
    WC: Theta(n) 
    TOTAL: O(n)
*/
int Bag::nrOccurrences(TElem e) const {
    int index = hashFunction(e);
    int offset = 1;
    while (true) {
        if (hashTable[index].key == e) {
            return hashTable[index].frequency;
        }
        else if (hashTable[index].key == NULL_TELEM) {
            return 0;
        }
        index = (index + (offset * offset)) % capacity;  // quadratic probing
        offset++;
    }
    return -1; // something bad happened if we get to here
}


// Theta(1)
int Bag::size() const {
    return sizeNow;
}


// Theta(1)
bool Bag::isEmpty() const {
    return (sizeNow == 0);
}

int Bag::elementsWithMaximumFrequency() const
{
    int to_return = 0;
    int maxFreq = 0;
    for (int i = 0; i < capacity; i++) {
        if (hashTable[i].frequency > maxFreq)
            maxFreq = hashTable[i].frequency;
    }
    for (int i = 0; i < capacity; i++) {
        if (hashTable[i].frequency == maxFreq)
            to_return++;
    }
    return to_return;
    
}

BagIterator Bag::iterator() const {
    return BagIterator(*this);
}


Bag::~Bag() {
    delete[] hashTable;
}

