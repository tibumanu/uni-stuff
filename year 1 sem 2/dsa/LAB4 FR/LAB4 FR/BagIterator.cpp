#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c) : bag(c)
{
	if (c.sizeNow == 0) {
		currentFrequency = -1;
		currentPosition = -1;
	}
	else {
		currentFrequency = 0;
		currentPosition = 0;
		first();
	}
}

void BagIterator::first() {
	currentFrequency = 0;
	currentPosition = 0;

	while (currentPosition < bag.capacity && bag.hashTable[currentPosition].key == NULL_TELEM) {
		currentPosition++;
	}
}


void BagIterator::next() {
	if(!valid())	throw std::exception("bad");

	currentFrequency++;
	if (currentFrequency == bag.hashTable[currentPosition].frequency) {
		// If the frequency is equal to the current element's frequency,
		// move to the next position in the hash table
		currentPosition++;

		// Find the next non-empty slot in the hash table
		while (currentPosition < bag.capacity && bag.hashTable[currentPosition].key == NULL_TELEM) {
			currentPosition++;
		}

		// Reset the frequency to 0 for the new element at the next position
		currentFrequency = 0;
	}
}


bool BagIterator::valid() const {
	if (currentPosition == -1 || currentFrequency == -1)	return false;
	return (currentPosition < bag.capacity && currentFrequency <= bag.hashTable[currentPosition].frequency);
}



TElem BagIterator::getCurrent() const
{
	if (valid())	return bag.hashTable[currentPosition].key;
	throw std::exception("bad");
}
