#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <exception>
#include <stdexcept>

MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    index = 0;
    position = col.elements[index].head+1;
}

TElem MultiMapIterator::getCurrent() const{
    if (!valid()) {
        throw std::runtime_error("Invalid iterator state");
    }
    return col.elements[index][position].inside;
}

bool MultiMapIterator::valid() const {
    return index < col.length && position <= col.elements[index].size;
	return false;
}

void MultiMapIterator::next() {
    if (valid()) {
        position++;
        if (position >= col.elements[index].size) {
            index++;
            position = 0;
        }
    } else {
        throw std::runtime_error("Invalid iterator state");
    }
}

void MultiMapIterator::first() {
    index = 0;
    position = 0;
}

