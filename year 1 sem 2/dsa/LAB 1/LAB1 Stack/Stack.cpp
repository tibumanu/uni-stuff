#include "Stack.h"
#include <exception>
#include <stdexcept>
#include <iostream>


using namespace std;


Stack::Stack() {
    capacity = 1;
    arr = new TElem[capacity];
    highest = -1;
}
//  Theta(1)


void Stack::push(TElem e) {
    if(highest == capacity - 1) resize();
    arr[++highest] = e;
}
/*
 * Assuming the resize() function is Theta(1), this function is also Theta(1).
 * In reality, the resize() function is Theta(n), where n is the number of elements on that stack.
 * BC: Theta(1), when the dynamic array does not need resizing.
 * WC: Theta(n), when it does.
 * Overall/total: O(n)
 */

TElem Stack::top() const {
    if(highest == -1)
        throw std::underflow_error("Queue is empty");
    return arr[highest];
}
//  Theta(1)

TElem Stack::pop() {
    if(highest == -1)
        throw std::underflow_error("Queue is empty");
    return arr[highest--];
}
//  Theta(1)


bool Stack::isEmpty() const {
	return highest == -1;
}
//  Theta(1)

Stack::~Stack() {
    delete[] arr;
}
// Theta(1)

void Stack::resize() {
    int oldCapacity = capacity;
    capacity *= 2;
    TElem* newArr = new TElem[capacity];
    for(int i = 0; i < oldCapacity; i++)
        newArr[i] = arr[i];

    delete[] arr;
    arr = newArr;
}
/*
 * Let n be the number of elements within the stack.
 * BC and WC: Theta(n).
 * Overall/total: Theta(n).
 */

//TElem Stack::popMaximumOLD() {
//    if(isEmpty())
//        throw std::underflow_error("Stack is empty.");
//
//    Stack aux;
//    TElem max = getMaximum();
//
//    //below we remove the occurrence
//    while(top() != getMaximum()){
//        aux.push(top()); // what we pop is pushed onto aux
//        pop();
//    }
//    pop();  //first occurrence gone now, time to rebuild original stack
//    while(!aux.isEmpty())
//        push(aux.pop());
//    return max;
//}

TElem Stack::popMaximum() {
    if (isEmpty())
        throw std::underflow_error("Stack is empty.");

    int* pair = getMaximum();
    int max = pair[0];
    int index = pair[1];

    for(int i = index; i < highest - 1; i++){
        arr[i] = arr[i+1];
    }
    highest--;
    return max;
}
/*
 * Let n be the number of elements on the stack.
 * The main bulk of this function is executing the getMaximum() function, which is O(n).
 * The for loop is, at worst, executed n times, depending on the index of the maximum element.
 * BC: Theta(1), when the maximum element is at the top of the stack, or the stack is empty.
 * WC -> T(n) =~ 2n -> Theta(n)
 * Overall/total: O(n)
 */


TElem* Stack::getMaximum() {
    if(isEmpty())
        throw std::underflow_error("Stack is empty.");

    int* pair;
    pair = new int[2];
    int oldHighest = highest;
    int maximum = top();
    int index = -1;

    while(highest != -1){
        if(top() > maximum) {
            maximum = top();
            index = highest;
            }
        highest--;
    }

    highest = oldHighest;
    pair[0] = maximum;
    pair[1] = index;
    return pair;
}
/*
 * Let n be the number of elements on the stack.
 * BC: Theta(1), when the maximum is on top of the stack, or the stack is empty.
 * WC: Theta(n), when the maximum is at the bottom of the stack.
 * Overall/total: O(n)
 */

