//
// Created by Tibuman on 22.03.2023.
//

#include "DynamicVector.h"


DynamicVector::DynamicVector(int capacity) {
    length = 0;
    this->capacity = capacity;
    data = new TElem[capacity];

}

DynamicVector::~DynamicVector() {
    delete[] data;
}

DynamicVector::DynamicVector(const DynamicVector& dv) {
    length = dv.length;
    capacity = dv.capacity;
    data = new TElem[capacity];
    for(int i = 0; i < length; i++){
        data[i] = dv.data[i];
    }
}

DynamicVector &DynamicVector::operator=(const DynamicVector &dv) {
    if(&dv == this)
        return *this;
    length = dv.length;
    capacity = dv.capacity;
    data = new TElem[capacity];
    for(int i = 0; i < length; i++){
        data[i] = dv.data[i];
    }
    return *this;
}


