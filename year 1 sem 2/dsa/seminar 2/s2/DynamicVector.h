#pragma once
#include "Song.h"

typedef Song TElem;

class DynamicVector {
private:
    int capacity;
    int length;
    TElem* data;


public:
     DynamicVector(int capacity = 4);
     DynamicVector(const DynamicVector&);
    ~DynamicVector();

    int getSize() const;
    TElem get(int index) const;
    void add(TElem);
    void remove(int index);

    DynamicVector& operator = (const DynamicVector&);

private:
    void resize();
};


