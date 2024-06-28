#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
    friend class MultiMap;

private:
    const MultiMap& col;
    int index;  // current index in DLLA array
    int position;  // current position within DLLA[index].list

    // constructor can only be called by MultiMap
    MultiMapIterator(const MultiMap& c);

public:
    TElem getCurrent() const;
    bool valid() const;
    void next();
    void first();
};
