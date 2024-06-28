#pragma once
#include "IteratedList.h"

//DO NOT CHANGE THIS PART
class IteratedList;
typedef int TElem;

class ListIterator{
	friend class IteratedList;
private:
	//TODO - Representation 
    IteratedList::Node* current;
	//DO NOT CHANGE THIS PART
	const IteratedList& list;
	ListIterator(const IteratedList& list);
public:
	void first();
	void next();
    bool nextK(int k);
    void jumpForward(int k);
	bool valid() const;
    TElem getCurrent() const;

};


