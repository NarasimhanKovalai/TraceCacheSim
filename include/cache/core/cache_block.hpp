#ifndef CACHE_BLOCK_HPP
#define CACHE_BLOCK_HPP

#include <cstdint>

namespace cache_simulator {

class CacheBlock {
private:
    bool valid_;      
    bool dirty_;      
    uint32_t tag_;    
    uint64_t timestamp_; 
    
public:
    CacheBlock();
    
    bool isValid() const { return valid_; }
    bool isDirty() const { return dirty_; }
    uint32_t getTag() const { return tag_; }
    uint64_t getTimestamp() const { return timestamp_; }
    
    void setValid(bool valid) { valid_ = valid; }
    void setDirty(bool dirty) { dirty_ = dirty; }
    void setTag(uint32_t tag) { tag_ = tag; }
    void setTimestamp(uint64_t timestamp) { timestamp_ = timestamp; }
    
    void invalidate();
    void update(uint32_t tag, uint64_t timestamp);
};

} // namespace cache_simulator 

#endif // CACHE_BLOCK_HPP 