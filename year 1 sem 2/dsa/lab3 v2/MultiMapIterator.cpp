#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    currentPos = col.headMap;
    currentNodePos = col.elements[col.headMap].head;
}

TElem MultiMapIterator::getCurrent() const{
	if(valid()){
        TElem ret = make_pair(col.elements[currentPos].key, col.elements[currentPos].elements[currentNodePos]);
        return ret;
    }
    throw exception();
}

bool MultiMapIterator::valid() const {
	return currentPos != -1;
}

void MultiMapIterator::next() {
    if(valid()){
        if(col.elements[currentPos].next[currentNodePos] != -1)
            currentNodePos = col.elements[currentPos].next[currentNodePos];
        else{
            currentPos = col.mapNext[currentPos];
            currentNodePos = col.elements[currentPos].head;
        }
    }
    else    throw exception();
}

void MultiMapIterator::first() {
    currentPos = col.headMap;
    currentNodePos = col.elements[col.headMap].head;
}

