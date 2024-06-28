#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>
#include <stdexcept>

ListIterator::ListIterator(const IteratedList& list) : current(list.head), list(list){}

//Theta(1)
void ListIterator::first() {
    current = list.head;
}

//Theta(1)
void ListIterator::next() {
    if(current == nullptr)
        throw std::invalid_argument("yikes");
    else
        current = current->next;
}

//Theta(1)
bool ListIterator::valid() const {
	return (current != nullptr);
}

//Theta(1)
TElem ListIterator::getCurrent() const {
    if(current == nullptr)
        throw std::underflow_error("no current to get");
	return current->data;
}

/*
 * BC: Theta(1), when iterator is invalid
 * WC: Theta(k), when we are able to go `k` steps forward
 * Overall/total: O(k)
 */
bool ListIterator::nextK(int k) {
    if(current == nullptr)
        return false;
    else
        for(int i = 0; i < k; i++) {
            current = current->next;
            if(current == nullptr)
                return false;
            }
    return true;
}


/*
 * same as above
 */
void ListIterator::jumpForward(int k) {
    if(k <= 0)
        throw std::invalid_argument("bad k");
    if(!valid())
        throw std::invalid_argument("invalid iterator");
    if(!nextK(k))
        throw std::overflow_error("k too big");
}



