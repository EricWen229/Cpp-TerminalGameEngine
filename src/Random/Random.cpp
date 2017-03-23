#include "Random/Random.h"

Random::Random(int begin, int end)
{
    rng.seed(std::random_device()());
    dist = std::uniform_int_distribution<uint32_t>(begin, end);
}

Random::~Random() {}

int Random::get()
{
    return dist(rng);
}
