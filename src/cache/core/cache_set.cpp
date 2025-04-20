#include "cache/core/cache_set.hpp"

namespace cache_simulator {

CacheSet::CacheSet(size_t associativity)
    : blocks_(associativity), associativity_(associativity) {}

int CacheSet::findBlock(uint32_t tag) const {
    for (size_t i = 0; i < blocks_.size(); i++) {
        if (blocks_[i].isValid() && blocks_[i].getTag() == tag) {
            return i;
        }
    }
    return -1;
}

int CacheSet::chooseVictim() const {
    // First check for invalid blocks
    for (size_t i = 0; i < blocks_.size(); i++) {
        if (!blocks_[i].isValid()) {
            return i;
        }
    }
    
    // Find the least recently used block
    size_t victim = 0;
    uint64_t oldest = blocks_[0].getTimestamp();
    
    for (size_t i = 1; i < blocks_.size(); i++) {
        if (blocks_[i].getTimestamp() < oldest) {
            oldest = blocks_[i].getTimestamp();
            victim = i;
        }
    }
    
    return victim;
}

CacheBlock& CacheSet::operator[](size_t index) {
    return blocks_[index];
}

const CacheBlock& CacheSet::operator[](size_t index) const {
    return blocks_[index];
}

} // namespace cache_simulator 