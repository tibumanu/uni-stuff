#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue() {
    capacity = 1;
    arr = new TElem[capacity];
    size = 0;
    front = -1;
    end = -1;
}
//Theta(1)


void Queue::push(TElem elem) {
    if(isEmpty()){
        front = 0;
        end = 0;
    }
    if(size == capacity)
        resize();   //changed front to -1 and end to size - 1.
    end = (end + 1)%capacity;

    arr[end] = elem;
    size++;
}
/*
 * Assuming the resize() function is Theta(1), this function's T, the number of steps, = Theta(1).
 * In reality, the resize() function is Theta(n), where n is the number of elements in the queue.
 * BC: Theta(1), when the dynamic array does not need resizing.
 * WC: Theta(n), when the dynamic array needs resizing.
 * Overall/total: O(n)
 */

TElem Queue::top() const {
    if(isEmpty()) {
        throw std::underflow_error("Queue is empty.");
    }else {
        return arr[front];
    }
}
//Theta(1)

TElem Queue::pop() {
    if(front == -1)
        throw std::underflow_error("Queue is empty.");
    TElem item = arr[front];

    if(front == end){
        front = -1;
        end = -1;
    }else
        front = (front + 1)%capacity;
    size--;
    return item;
}
//Theta(1)

void Queue::resize(){
    int oldCapacity = capacity;
    capacity *= 2;
    TElem* newArr = new TElem[capacity];
    int index = 0;

    if(front <= end){
        for(int i = front; i <= end; i++)
            newArr[index++] = arr[i];
    }else{
        for(int i = front; i < oldCapacity; i++)
            newArr[index++] = arr[i];
        for(int i = 0; i <= end; i++)
            newArr[index++] = arr[i];
    }
    front = 0;
    end = index - 1;
    delete[] arr;
    arr = newArr;
}
/*
 * Let n be the number of elements in the queue.
 * BC and WC: Theta(n). Overall/total, O(n)
 */

bool Queue::isEmpty() const {
    return size == 0;
}
// Theta(1)


Queue::~Queue() {
    delete[] arr;
}
// Theta(1)

