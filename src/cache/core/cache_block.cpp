#include "cache/core/cache_block.hpp"

namespace cache_simulator {

CacheBlock::CacheBlock()
    : valid_(false), dirty_(false), tag_(0), timestamp_(0) {}

void CacheBlock::invalidate() {
    valid_ = false;
    dirty_ = false;
    tag_ = 0;
    timestamp_ = 0;
}

void CacheBlock::update(uint32_t tag, uint64_t timestamp) {
    valid_ = true;
    tag_ = tag;
    timestamp_ = timestamp;
}

} // namespace cache_simulator 