#include "cache/simulator/statistics.hpp"
#include <iostream>
#include <iomanip>

namespace cache_simulator {

CacheStatistics::CacheStatistics()
    : totalLoads_(0), totalStores_(0),
      loadHits_(0), loadMisses_(0),
      storeHits_(0), storeMisses_(0),
      totalCycles_(0) {}

void CacheStatistics::recordLoadHit() {
    totalLoads_++;
    loadHits_++;
}

void CacheStatistics::recordLoadMiss() {
    totalLoads_++;
    loadMisses_++;
}

void CacheStatistics::recordStoreHit() {
    totalStores_++;
    storeHits_++;
}

void CacheStatistics::recordStoreMiss() {
    totalStores_++;
    storeMisses_++;
}

void CacheStatistics::addCycles(uint64_t cycles) {
    totalCycles_ += cycles;
}

void CacheStatistics::print(std::ostream& os) const {
    os << std::fixed << std::setprecision(2);
    os << "Total Loads: " << totalLoads_ << "\n";
    os << "Total Stores: " << totalStores_ << "\n";
    os << "Load Hits: " << loadHits_ << "\n";
    os << "Load Misses: " << loadMisses_ << "\n";
    os << "Store Hits: " << storeHits_ << "\n";
    os << "Store Misses: " << storeMisses_ << "\n";
    os << "Total Cycles: " << totalCycles_ << "\n";
    os << "Hit Rate: " << getHitRate() << "\n";
    os << "Average Memory Access Latency: " << getAverageLatency() << "\n";
}

} // namespace cache_simulator 