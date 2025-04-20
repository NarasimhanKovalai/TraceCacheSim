#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <cstdint>
#include <iostream>

namespace cache_simulator {

class CacheStatistics {
private:
    uint64_t totalLoads_;
    uint64_t totalStores_;
    uint64_t loadHits_;
    uint64_t loadMisses_;
    uint64_t storeHits_;
    uint64_t storeMisses_;
    uint64_t totalCycles_;
    
public:
    CacheStatistics();
    
    uint64_t getTotalLoads() const { return totalLoads_; }
    uint64_t getTotalStores() const { return totalStores_; }
    uint64_t getLoadHits() const { return loadHits_; }
    uint64_t getLoadMisses() const { return loadMisses_; }
    uint64_t getStoreHits() const { return storeHits_; }
    uint64_t getStoreMisses() const { return storeMisses_; }
    uint64_t getTotalCycles() const { return totalCycles_; }
    
    // Calculate total hits and misses
    uint64_t getTotalHits() const { return loadHits_ + storeHits_; }
    uint64_t getTotalMisses() const { return loadMisses_ + storeMisses_; }
    
    // Calculate total memory accesses
    uint64_t getTotalAccesses() const { return totalLoads_ + totalStores_; }
    
    // Calculate hit rate as percentage
    double getHitRate() const {
        uint64_t total = getTotalAccesses();
        if (total == 0) return 0.0;
        return (static_cast<double>(getTotalHits()) / total) * 100.0;
    }
    
    // Calculate average memory access latency
    double getAverageLatency() const {
        uint64_t total = getTotalAccesses();
        if (total == 0) return 0.0;
        return static_cast<double>(totalCycles_) / total;
    }
    
    void recordLoadHit();
    void recordLoadMiss();
    void recordStoreHit();
    void recordStoreMiss();
    void addCycles(uint64_t cycles);

    void print(std::ostream& os = std::cout) const;
};

} // namespace cache_simulator 

#endif // STATISTICS_HPP 