#pragma once
#include "domain.h"

template <typename T>
class DynamicArray {
private:
    int size;
    int capacity;
    T* data;

public:
    explicit DynamicArray(int capacity = 10);
    ~DynamicArray();

    int getSize()const;

    T getItem(int index)const;
    T* getItemPtr(int index);

    void addItem(const T& e);
    void removeItem(int index);
    int findItem(T item);
    void resize();


private:
};

template <typename T>
DynamicArray<T>::DynamicArray(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->data = new T[capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->data;
}

template <typename T>
int DynamicArray<T>::getSize() const {
    return this->size;
}

template <typename T>
int DynamicArray<T>::findItem(T item) {
    for (int i = 0; i < this->getSize(); i++)
        if (this->data[i] == item)
            return i;
    return -1;
}

template <typename T>
T DynamicArray<T>::getItem(int index) const {
    return this->data[index];
}

template <typename T>
T* DynamicArray<T>::getItemPtr(int index) {
	return &this->data[index];
}

template <typename T>
void DynamicArray<T>::addItem(const T& e) {
    if (this->size >= capacity) {
        resize();
    }
    this->data[size] = e;
    size++;
}

template <typename T>
void DynamicArray<T>::removeItem(int index) {
    // removes the element found at given `index`
    for (int i = index; i < size - 1; i++)
        this->data[i] = this->data[i + 1];
    size--;
}

template <typename T>
void DynamicArray<T>::resize() {
    // doubles the capacity, and "reallocates" memory for a new Dynamic Array of the now doubled capacity.
    // makes use of an auxiliary Dynamic Array.
    // all of the elements are copied into this new Dynamic Array, and the old Array gets swapped with this one.
    // the old Array is deleted.
    this->capacity *= 2;
    auto* newData = new T[capacity];
    for (int i = 0; i < size; i++)
        newData[i] = this->data[i];

    delete[] this->data;
    this->data = newData;
}











