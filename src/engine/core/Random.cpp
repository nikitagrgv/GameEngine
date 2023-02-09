#include "Random.h"

#include <cassert>
#include <random>

namespace
{
    std::random_device random_device;
    std::mt19937 rng(random_device());
}

int Random::getRandomInt(int start, int end)
{
    assert(end >= start);

    const int range_offset = end - start;
    const int unsigned_number = (int)getRandomUInt(0, range_offset);
    return unsigned_number + start;
}

unsigned int Random::getRandomUInt(unsigned int start, unsigned int end)
{
    assert(end >= start);

    std::uniform_int_distribution<std::mt19937::result_type> distribution(start, end);
    return distribution(rng);
}
