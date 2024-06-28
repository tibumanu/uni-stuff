#pragma once
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -111111

class Stack
{
private:
    TElem* arr;
    int highest;
    int capacity;

public:

	//constructor
	Stack();
	
	//pushes an element to the top of the Stack
	void push(TElem e);
	
	//returns the element from the top of the Stack
	//throws exception if the stack is empty
	TElem top() const;
	   
	//removes and returns the element from the top of the Stack
	//throws exception if the stack is empty
	TElem pop();
	   
	//checks if the stack is empty
	bool isEmpty() const;

    //resizes the dynamic array, doubling its capacity
    void resize();

    //returns and removes one occurrence of the maximum element from the stack (assume that the elements are integer numbers
    //throws an exception if the stack is empty
    TElem popMaximum();


    //TElem popMaximumOLD();

    //returns the maximum element from the stack and the index on where its found within the dynamic array
    TElem* getMaximum();

	//destructor
	~Stack();
};

