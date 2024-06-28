#include "ShortTest.h"
#include "Stack.h"
#include <assert.h>

void testAll() { 
	Stack s;
	assert(s.isEmpty() == true);
	s.push(5);
	s.push(1);
	s.push(10);
	assert(s.isEmpty() == false);
	assert(s.top() == 10);
	assert(s.pop() == 10);
	assert(s.top() == 1);
	assert(s.pop() == 1);
	assert(s.top() == 5);
	assert(s.pop() == 5);
	assert(s.isEmpty() == true);

    //added by student
    s.push(10);
    s.push(100);
    s.push(99);
    s.push(101);
    s.push(50);
    assert(s.getMaximum()[0] == 101);
    s.pop();
    s.pop();
    assert(s.getMaximum()[0] == 100);
    s.pop();
    s.pop();
    s.pop();
    assert(s.isEmpty() == true);

    //testing popMaximum()
    s.push(10);
    s.push(100);
    s.push(99);
    s.push(101);
    s.push(50);
    int* test = s.getMaximum();
    assert(test[0] == 101);
    assert(test[1] == 3);
//    assert(s.getMaximum()[0] == 101);
//    assert(s.getMaximum()[1] == 3);
//    assert((s.popMaximum())[0] == 101);
    assert(s.top() == 50);
    assert(s.popMaximum() == 101);
    s.pop();
    assert(s.top() == 99);
}