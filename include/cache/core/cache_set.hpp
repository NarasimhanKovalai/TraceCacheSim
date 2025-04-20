#ifndef CACHE_SET_HPP
#define CACHE_SET_HPP

#include "cache_block.hpp"
#include <vector>
#include <cstdint>

namespace cache_simulator {

class CacheSet {
private:
    std::vector<CacheBlock> blocks_;
    size_t associativity_;
    
public:
    explicit CacheSet(size_t associativity); // prevent implicit compiler conversion
    
    int findBlock(uint32_t tag) const;
    int chooseVictim() const;
    CacheBlock& operator[](size_t index);
    const CacheBlock& operator[](size_t index) const;
    
    // Get number of blocks
    size_t size() const { return blocks_.size(); }
};

} // namespace cache_simulator 

#endif // CACHE_SET_HPP 