#pragma once

#include "Object.h"

#include <algorithm>
#include <cassert>

template<class T>
class SharedPtr
{
public:
    struct Hash
    {
        size_t operator()(const SharedPtr& p) const { return std::hash<void*>()(p.object_); }
    };

    explicit SharedPtr() noexcept
        : object_(nullptr)
    {
    }

    explicit SharedPtr(T* ptr) noexcept
        : object_(ptr)
    {
        add_ref();
    }

    ~SharedPtr() noexcept
    {
        release_ref();
    }

    SharedPtr(const SharedPtr<T>& rhs) noexcept
        : SharedPtr(rhs.object_)
    {
    }

    template<class U>
    SharedPtr(const SharedPtr<U>& rhs) noexcept
        : SharedPtr(rhs.object_)
    {
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& rhs)
    {
        if (object_ != rhs.object_)
        {
            SharedPtr<T> copy(rhs);
            swap(copy);
        }
        return *this;
    }

    template<class U>
    SharedPtr<T>& operator=(const SharedPtr<U>& rhs)
    {
        if (object_ != rhs.object_)
        {
            SharedPtr<T> copy(rhs);
            swap(copy);
        }
        return *this;
    }

    SharedPtr(SharedPtr<T>&& rhs) noexcept
        : object_(rhs.object_)
    {
        rhs.object_ = nullptr;
    }

    SharedPtr<T>& operator=(SharedPtr<T>&& rhs)
    {
        SharedPtr<T> copy(std::move(rhs));
        swap(copy);
        return *this;
    }

    SharedPtr<T>& operator=(T* ptr)
    {
        if (object_ != ptr)
        {
            SharedPtr<T> copy(ptr);
            swap(copy);
        }
        return *this;
    }

    T* operator->() const
    {
        assert(object_);
        return object_;
    }

    T& operator*() const
    {
        assert(object_);
        return *object_;
    }

    template<class U>
    bool operator==(const SharedPtr<U>& rhs) const
    {
        return object_ == rhs.object_;
    }

    template<class U>
    bool operator!=(const SharedPtr<U>& rhs) const
    {
        return object_ != rhs.object_;
    }

    operator T*() const { return object_; }

    void swap(SharedPtr<T>& rhs) { std::swap(object_, rhs.object_); }

    void reset(T* ptr = nullptr)
    {
        SharedPtr<T> copy(ptr);
        swap(copy);
    }

    T* get() const { return object_; }

    bool isValid() const { return object_ != nullptr; }

    int getRefCount() const { return object_ ? object_->getRefCount() : 0; }

private:
    template<class U>
    friend class SharedPtr;

    void add_ref()
    {
        if (object_)
            object_->addRef();
    }

    void release_ref()
    {
        if (object_)
        {
            object_->releaseRef();
            object_ = nullptr;
        }
    }

private:
    T* object_{nullptr};
};
