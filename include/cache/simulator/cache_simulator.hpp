#ifndef CACHE_SIMULATOR_HPP
#define CACHE_SIMULATOR_HPP

#include "cache/config/cache_config.hpp"
#include "cache/config/cache_policies.hpp"
#include "cache/core/cache_set.hpp"
#include "cache/simulator/statistics.hpp"
#include "utils/address_utils.hpp"
#include "utils/math_utils.hpp"
#include <vector>
#include <cstdint>

namespace cache_simulator {

class CacheSimulator {
private:
    CacheConfig config_;
    WriteAllocatePolicy writeAllocate_;
    WriteBackPolicy writeBack_;
    ReplacementPolicy replacementPolicy_;
    
    std::vector<CacheSet> cache_;
    CacheStatistics stats_;
    uint64_t currentTime_;
    
    uint32_t indexBits_;
    uint32_t offsetBits_;
    uint32_t indexMask_;
    
    // Helper methods
    void loadAddress(uint32_t address);
    void storeAddress(uint32_t address);
    void validateConfig() const;

public:
    CacheSimulator(
        const CacheConfig& config,
        WriteAllocatePolicy writeAllocate,
        WriteBackPolicy writeBack,
        ReplacementPolicy replacementPolicy
    );
    
    void processTrace();
    void printStatistics() const;
};

} // namespace cache_simulator 

#endif // CACHE_SIMULATOR_HPP 