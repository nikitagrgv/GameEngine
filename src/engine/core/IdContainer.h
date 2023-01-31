#pragma once

#include <vector>

template <typename T>
class IdContainer final
{
private:
    struct ObjectWithId
    {
        T obj;
        int id;
    };

public:
    void clear() { objects_.clear(); }

    int add(const T obj)
    {
        ObjectWithId object_with_id;
        object_with_id.id = generate_id();
        object_with_id.obj = obj;
        objects_.push_back(object_with_id);
        return object_with_id.id;
    }

    void remove(int id)
    {
        for (int i = 0; i < objects_.size(); i++)
        {
            if (objects_[i].id == id)
            {
                objects_.erase(objects_.begin() + i);
                return;
            }
        }
    }

    const T& get(int index) const
    {
        return objects_[index].obj;
    }

    T& get(int index)
    {
        return objects_[index].obj;
    }

    const T& operator[](int index) const
    {
        return get(index);
    }

    T& operator[](int index)
    {
        return get(index);
    }

    int count() const
    {
        return objects_.size();
    }

private:
    int generate_id() const
    {
        int id = 1;
        while (has_id(id))
            id++;
        return id;
    }

    bool has_id(int id) const
    {
        for (const auto& obj : objects_)
        {
            if (obj.id == id)
                return true;
        }
        return false;
    }

private:
    std::vector<ObjectWithId> objects_;
};
