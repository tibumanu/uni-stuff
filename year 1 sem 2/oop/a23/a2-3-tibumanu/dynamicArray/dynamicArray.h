#pragma once
#include "../domain/domain.h"

typedef struct {
    Country * data;
    int capacity;
    int index;  // this is where the next element would be placed; equal to the length of the array
}DynamicArray;

void resizeArray(DynamicArray * array);
DynamicArray createDynamicArray(int capacity);
void destroyDynamicArray(DynamicArray * array);
void addElement(DynamicArray * array, Country element);
void deleteElement(DynamicArray * array, int index);
void updateElement(DynamicArray * array, int index, Country update_element);
Country* getElements(DynamicArray * array);
int getArrayCapacity(DynamicArray * array);
int getArrayLength(DynamicArray * array);
