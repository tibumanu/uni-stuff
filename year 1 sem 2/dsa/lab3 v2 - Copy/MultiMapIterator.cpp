#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    //TODO - Implementation
    currentPos = col.mapHead;
    currentNodePos = col.mapElems[col.mapHead].head;
}

TElem MultiMapIterator::getCurrent() const{
    //TODO - Implementation
    if (valid())
    {
        TElem returnable = make_pair(col.mapElems[currentPos].key, col.mapElems[currentPos].elems[currentNodePos]);
        return returnable;
    }
    throw exception();
}

bool MultiMapIterator::valid() const {
    //TODO - Implementation
    return currentPos != -1;
}

void MultiMapIterator::next() {
    //TODO - Implementation
    if (valid())
    {
        if (col.mapElems[currentPos].next[currentNodePos] != -1)
            currentNodePos = col.mapElems[currentPos].next[currentNodePos];
        else
        {
            currentPos = col.mapNext[currentPos];
            currentNodePos = col.mapElems[currentPos].head;
        }
    }
    else
    {
        throw exception();
    }
}

void MultiMapIterator::first() {
    //TODO - Implementation
    currentPos = col.mapHead;
    currentNodePos = col.mapElems[col.mapHead].head;
}

