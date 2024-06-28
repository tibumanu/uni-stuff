#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

class Queue
{
private:
    TElem* arr; //dynamic array
    int front;  //the position of the element in the front of the queue
    int end; //the position of the element at the end of the queue
    int capacity; //the capacity of the dynamic array
    int size;   //current size/number of elements within the queue

public:
    Queue();

    //pushes an element to the end of the queue
    void push(TElem e);

    //resizes the queue, doubling its capacity
    //note: might change the value of front and end; in case it does, front = 0 and end = size - 1
    void resize();

    //returns the element from the front of the queue
    //throws exception if the queue is empty
    TElem top() const;

    //removes and returns the element from the front of the queue
    //throws exception if the queue is empty
    TElem pop();

    //checks if the queue is empty
    bool isEmpty() const;

    // destructor
    ~Queue();
};
