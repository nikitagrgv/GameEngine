#pragma once

class Object
{
public:
    Object() = default;
    virtual ~Object() = default;

    Object(const Object& other) = delete;
    Object& operator=(const Object& other) = delete;

    void addRef();
    void releaseRef();
    int getRefCount() const { return ref_count_; };

private:
    int ref_count_{0};
};
