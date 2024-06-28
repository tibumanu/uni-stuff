
#include <exception>
#include <stdexcept>
#include "ListIterator.h"
#include "IteratedList.h"

//Theta(1)
IteratedList::IteratedList() {
	head = nullptr;
    LSize = 0;
}

//Theta(1)
int IteratedList::size() const {
	return LSize;
}

//Theta(1)
bool IteratedList::isEmpty() const {
	return (LSize == 0);
}

//Theta(1)
ListIterator IteratedList::first() const {
	ListIterator it(*this);
    it.current = this->head;
    return it;
}

//Theta(1)
TElem IteratedList::getElement(ListIterator pos) const {
	if (!pos.valid())
        throw std::invalid_argument("Invalid position");
    return pos.getCurrent();
}

/*
 * BC: Theta(1), when the given position is invalid, or when the position points to the first node (head) of the SLL
 * WC: Given position points to the last element -> T(n) =~ n -> Theta(n)
 * Overall/total: O(n)
 */
TElem IteratedList::remove(ListIterator& pos) {
    if(!pos.valid())
        throw std::invalid_argument("Invalid position");
    TElem returnee = pos.getCurrent();
    ListIterator it = ListIterator(*this);

    if(head == pos.current){
        head = pos.current->next;
        delete pos.current;
        LSize--;
        return returnee;
    }

    while(it.current->next != pos.current)  it.next();
    it.current->next = pos.current->next;
    delete pos.current;
    LSize--;
    return returnee;
}

/*
 * BC: Theta(1), when we find it on `head`
 * WC: T(n) =~ n -> Theta(n), when it's at the end of the SLL
 * Overall/total: O(n)
 */
ListIterator IteratedList::search(TElem e) const{
    ListIterator it(*this);
    while(it.current != nullptr and it.current->data != e)
        it.next();
    return it;
}

// Theta(1)
TElem IteratedList::setElement(ListIterator pos, TElem e) {
    if(!pos.valid())
        throw std::invalid_argument("Invalid position");
    TElem old = pos.current->data;
    pos.current->data = e;
    return old;
}

// Theta(1)
void IteratedList::addToPosition(ListIterator& pos, TElem e) {
    if(!pos.valid())
        throw std::invalid_argument("Invalid position");
    Node* newNode = new Node(e);
    Node* toRight = pos.current->next;
    pos.current->next = newNode;
    newNode->next = toRight;
    pos.current = newNode;
    if(toRight == nullptr)
        this->tail = newNode;
    LSize++;
}

/*
 * BC: Theta(1), when the list is empty. We don't have to iterate through anything.
 * WC: Theta(n), in all other cases.
 * Overall/total: O(n)
 */
void IteratedList::addToEndWorse(TElem e) {
    if(isEmpty()) {
        this->head = new Node(e);
        this->tail = this->head;
        LSize++;
        return;
    }
    ListIterator it(*this);
    while(it.current->next != nullptr)
        it.next();
    Node* newNode = new Node(e);
    it.current->next = newNode;
    this->tail = newNode;
    LSize++;
}


// Theta(1)
void IteratedList::addToBeginning(TElem e) {
    Node* newNode = new Node(e);
    Node* oldHead = head;
    head = newNode;
    newNode->next = oldHead;
    if(LSize == 0)  this->tail = newNode;
    if(LSize == 1)  this->tail = oldHead;
    LSize++;
}

// Theta(1)
void IteratedList::addToEnd(TElem e) {
    if(isEmpty()) {
        this->head = new Node(e);
        this->tail = this->head;
        LSize++;
        return;
        }
    Node* newNode = new Node(e);
    this->tail->next = newNode;
    this->tail = newNode;
    LSize++;
}


/*
 * BC: Theta(1), when the list is empty.
 * WC: Theta(n), when not.
 * Overall/total: O(n)
 */
IteratedList::~IteratedList() {
    Node* current = head;
    while(current != nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
}
