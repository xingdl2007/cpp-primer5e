#include <stdint.h>
#include <iostream>

// from code.google.com/p/smhasher/wiki/MurmurHash3
inline uint32_t avalanche(uint32_t h)
{
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

inline uint32_t deavalanche(uint32_t h)
{
    h ^= h >> 16;
    h *= 0x7ed1b41d;
    h ^= (h ^ (h >> 13)) >> 13;
    h *= 0xa5cb9243;
    h ^= h >> 16;
    return h;
}

// from code.google.com/p/smhasher/wiki/MurmurHash3
inline uint64_t avalanche(uint64_t h)
{
    h ^= h >> 33;
    h *= 0xff51afd7ed558ccd;
    h ^= h >> 33;
    h *= 0xc4ceb9fe1a85ec53;
    h ^= h >> 33;
    return h;
}

inline uint64_t deavalanche(uint64_t h)
{
    h ^= h >> 33;
    h *= 0x9cb4b2f8129337db;
    h ^= h >> 33;
    h *= 0x4f74430c22a54005;
    h ^= h >> 33;
    return h;
}

int main()
{
    {
        // 32bits
        uint32_t key = 123456;
        uint32_t hash = avalanche(key);
        std::cout << key << " " << hash << " " << deavalanche(hash) << std::endl;
    }

    {
        // 64bits
        uint64_t key = 123456789;
        uint64_t hash = avalanche(key);
        std::cout << key << " " << hash << " " << deavalanche(hash) << std::endl;
    }
}