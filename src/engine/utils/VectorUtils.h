#pragma once

#include <vector>

namespace Vector
{

template<typename T>
inline void removeElement(std::vector<T>& v, const T& item)
{
    v.erase(std::remove(v.begin(), v.end(), item), v.end());
}

template<typename T>
inline bool hasElement(std::vector<T>& v, const T& item)
{
    return std::find(v.begin(), v.end(), item) != v.end();
}

template<typename T>
inline void removeElementByIndex(std::vector<T>& v, int index)
{
    v.erase(v.begin() + index);
}

} // namespace Vector
