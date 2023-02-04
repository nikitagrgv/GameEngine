#include "Object.h"

#include <cassert>

void Object::addRef()
{
    assert(ref_count_ >= 0);
    ref_count_++;
}

void Object::releaseRef()
{
    assert(ref_count_ > 0);
    ref_count_--;
    if (!ref_count_)
        delete this;
}
