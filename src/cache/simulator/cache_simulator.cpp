#include "cache/simulator/cache_simulator.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

namespace cache_simulator {

void CacheSimulator::validateConfig() const {
    if (!MathUtils::isPowerOfTwo(config_.numSets) || 
        !MathUtils::isPowerOfTwo(config_.blocksPerSet) || 
        !MathUtils::isPowerOfTwo(config_.blockSize)) {
        throw std::invalid_argument("Sets, blocks per set, and block size must be powers of 2");
    }
    
    if (config_.blockSize < 4) {
        throw std::invalid_argument("Block size must be at least 4 bytes");
    }
    
    if (writeBack_ == WriteBackPolicy::WRITE_BACK && 
        writeAllocate_ == WriteAllocatePolicy::NO_WRITE_ALLOCATE) {
        throw std::invalid_argument("Write-back requires write-allocate");
    }
}

CacheSimulator::CacheSimulator(
    const CacheConfig& config,
    WriteAllocatePolicy writeAllocate,
    WriteBackPolicy writeBack,
    ReplacementPolicy replacementPolicy
) : config_(config),
    writeAllocate_(writeAllocate),
    writeBack_(writeBack),
    replacementPolicy_(replacementPolicy),
    currentTime_(0) {
    
    validateConfig();
    
    // Initialize cache structure
    cache_.resize(config_.numSets, CacheSet(config_.blocksPerSet));
    offsetBits_ = MathUtils::log2(config_.blockSize);
    indexBits_ = MathUtils::log2(config_.numSets);
    indexMask_ = config_.numSets - 1;
}

void CacheSimulator::loadAddress(uint32_t address) {
    uint32_t setIndex = AddressUtils::getSetIndex(address, offsetBits_, indexMask_);
    uint32_t tag = AddressUtils::getTag(address, offsetBits_, indexBits_);
    
    int blockIndex = cache_[setIndex].findBlock(tag);
    
    if (blockIndex != -1) {
        // Cache hit
        stats_.recordLoadHit();
        stats_.addCycles(1); // Cache access costs 1 cycle
        
        // Update timestamp for LRU
        if (replacementPolicy_ == ReplacementPolicy::LRU) {
            cache_[setIndex][blockIndex].setTimestamp(currentTime_++);
        }
    } else {
        // Cache miss
        stats_.recordLoadMiss();
        
        // Fetch from memory - costs 100 cycles per 4 bytes transferred
        uint32_t bytesTransferred = config_.blockSize;
        stats_.addCycles(100 * static_cast<uint32_t>(std::ceil(bytesTransferred / 4.0)));
        stats_.addCycles(1); // Plus 1 cycle for cache access
        
        // Find a block to replace
        int victim = cache_[setIndex].chooseVictim();
        
        // If we're using write-back and the victim is dirty, we need to write it back
        if (writeBack_ == WriteBackPolicy::WRITE_BACK && 
            cache_[setIndex][victim].isValid() && 
            cache_[setIndex][victim].isDirty()) {
            // Write back to memory - costs 100 cycles per 4 bytes transferred
            stats_.addCycles(100 * static_cast<uint32_t>(std::ceil(config_.blockSize / 4.0)));
        }
        
        // Load the new block
        cache_[setIndex][victim].update(tag, currentTime_);
        cache_[setIndex][victim].setDirty(false);
        
        // Update timestamp
        if (replacementPolicy_ == ReplacementPolicy::FIFO || 
            replacementPolicy_ == ReplacementPolicy::LRU) {
            currentTime_++;
        }
    }
}

void CacheSimulator::storeAddress(uint32_t address) {
    uint32_t setIndex = AddressUtils::getSetIndex(address, offsetBits_, indexMask_);
    uint32_t tag = AddressUtils::getTag(address, offsetBits_, indexBits_);
    
    int blockIndex = cache_[setIndex].findBlock(tag);
    
    if (blockIndex != -1) {
        // Cache hit
        stats_.recordStoreHit();
        stats_.addCycles(1); // Cache access costs 1 cycle
        
        // Update the block
        if (writeBack_ == WriteBackPolicy::WRITE_BACK) {
            cache_[setIndex][blockIndex].setDirty(true);
        } else { // WRITE_THROUGH
            // Write to memory - costs 100 cycles per 4 bytes transferred
            stats_.addCycles(100);
        }
        
        // Update timestamp for LRU
        if (replacementPolicy_ == ReplacementPolicy::LRU) {
            cache_[setIndex][blockIndex].setTimestamp(currentTime_++);
        }
    } else {
        // Cache miss
        stats_.recordStoreMiss();
        
        if (writeAllocate_ == WriteAllocatePolicy::WRITE_ALLOCATE) {
            // Fetch from memory - costs 100 cycles per 4 bytes transferred
            uint32_t bytesTransferred = config_.blockSize;
            stats_.addCycles(100 * static_cast<uint32_t>(std::ceil(bytesTransferred / 4.0)));
            stats_.addCycles(1); // Plus 1 cycle for cache access
            int victim = cache_[setIndex].chooseVictim();
            
            // If we're using write-back and the victim is dirty, we need to write it back
            if (writeBack_ == WriteBackPolicy::WRITE_BACK && 
                cache_[setIndex][victim].isValid() && 
                cache_[setIndex][victim].isDirty()) {
                // Write back to memory - costs 100 cycles per 4 bytes transferred
                stats_.addCycles(100 * static_cast<uint32_t>(std::ceil(config_.blockSize / 4.0)));
            }
            
            // Load the new block
            cache_[setIndex][victim].update(tag, currentTime_);
            
            // Set dirty bit or write through depending on policy
            if (writeBack_ == WriteBackPolicy::WRITE_BACK) {
                cache_[setIndex][victim].setDirty(true);
            } else { // WRITE_THROUGH
                cache_[setIndex][victim].setDirty(false);
                // Write to memory - costs 100 cycles per 4 bytes transferred
                stats_.addCycles(100);
            }
            
            // Update timestamp for both
            if (replacementPolicy_ == ReplacementPolicy::FIFO || 
                replacementPolicy_ == ReplacementPolicy::LRU) {
                currentTime_++;
            }
        } else { // NO_WRITE_ALLOCATE
            // Write directly to memory - costs 100 cycles per 4 bytes transferred
            stats_.addCycles(100);
        }
    }
}

void CacheSimulator::processTrace() {
    std::string line;
    while (std::getline(std::cin, line)) {
        char operation;
        uint32_t address;
        int size;
        
        if (sscanf(line.c_str(), "%c %x %d", &operation, &address, &size) != 3) {
            continue; // Skip malformed lines
        }
        
        if (operation == 'l') {
            loadAddress(address);
        } else if (operation == 's') {
            storeAddress(address);
        }
    }
}

void CacheSimulator::printStatistics() const {
    stats_.print();
}

} // namespace cache_simulator 