#ifndef Random_H
#define Random_H

#include <random>

class Random
{
    private:
        std::mt19937 rng;
        std::uniform_int_distribution<uint32_t> dist;
        
    public:
        Random(int begin, int end);
        ~Random();
        int get();
};

#endif
