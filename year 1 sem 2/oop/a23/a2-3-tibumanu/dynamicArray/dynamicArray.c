#include <stdlib.h>
#include "dynamicArray.h"

void resizeArray(DynamicArray * array);


DynamicArray createDynamicArray(int capacity) {
    // creates dynamic array with given capacity
    // input: capacity - integer
    // output: dynamic array
    DynamicArray array;
    array.data = (Country *)malloc(capacity* sizeof(Country));
    array.index = 0;
    array.capacity = capacity;
    return array;
}

void destroyDynamicArray(DynamicArray *array) {
    // destroys dynamic array
    // input: array - pointer to dynamic array
    // output: none
    free(array->data);
    array->data = NULL;
    array->index = 0;
    array->capacity = 0;
}

void addElement(DynamicArray *array, Country element) {
    // adds element to dynamic array
    // input: array - pointer to dynamic array, element - Country
    // output: none
    if (array->index == array->capacity)
        resizeArray(array);
    array->data[array->index++] = element;
}


void deleteElement(DynamicArray *array, int pos) {
    // deletes element from dynamic array
    // input: array - pointer to dynamic array, index - integer
    // output: none
    for (int i = pos; i < array->index - 1; i++)
        array->data[i] = array->data[i + 1];
    array->index--;
}

void updateElement(DynamicArray *array, int pos, Country element) {
    // updates element from dynamic array
    // input: array - pointer to dynamic array, index - integer, element - Country
    // output: none
    array->data[pos] = element;
}

int getArrayLength(DynamicArray *array) {
    // returns length of dynamic array
    // input: array - pointer to dynamic array
    // output: integer
    return array->index;
}

int getArrayCapacity(DynamicArray *array) {
    // returns capacity of dynamic array
    // input: array - pointer to dynamic array
    // output: integer
    return array->capacity;
}

void resizeArray(DynamicArray* array){
    // resizes dynamic array
    // input: array - pointer to dynamic array
    // output: none
    array->capacity *= 2;
    Country* new_data = (Country*)malloc(array->capacity * sizeof(Country));
    for (int i = 0; i < array->index; i++)
        new_data[i] = array->data[i];
    free(array->data);
    array->data = new_data;
}

Country* getElements(DynamicArray* array) {
    // returns elements of dynamic array
    // input: array - pointer to dynamic array
    // output: pointer to Country
    return array->data;
}