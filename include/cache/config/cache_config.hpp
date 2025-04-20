#ifndef CACHE_CONFIG_HPP
#define CACHE_CONFIG_HPP

#include <cstdint>

namespace cache_simulator {

struct CacheConfig {
    uint32_t numSets;
    uint32_t blocksPerSet;
    uint32_t blockSize;
    
    CacheConfig(uint32_t sets, uint32_t blocks, uint32_t size)
        : numSets(sets), blocksPerSet(blocks), blockSize(size) {}
};

} // namespace cache_simulator 

#endif // CACHE_CONFIG_HPP 